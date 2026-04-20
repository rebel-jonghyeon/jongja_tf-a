/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

#include <cmrt/ucu/asn1.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


/* Identifier, class (7..6), constructed/primitive (5), 4..0 is tag,
 * high form is 11111b., with a Base128 encoding (high bit set for the
 * rest).
 * @return 0 for invalid tag (or will not fit into \a in), 1..n bytes
 * @note one extra byte is required in \a in to accommodate length
 */
static unsigned taglen(span in)
{
	unsigned i = 0;
	if (span_valid(in)) {
		i = 1;		/* default low tag is included */
		if ((in.p[0] & 0x1fu) == 0x1fu) {
			/* high tag, Base128 follows */
			for (i = 1; (i < in.n) && (in.p[i] & 0x80u); ++i)
				;
			/* The tag, or the following length won't fit */
			if (++i >= in.n) {
				i = 0;
			}
		}
	}
	return i;
}


/*!
 * Return length encoded at start beginning of span.  Length is
 * encoded in two formats:
 * - short form (0..127 initial)
 * - long form: bit 7 set, next byte is the count of bytes used
 * @param in input to look for length in (not a tag at all)
 * @return length of the encoded length in bytes
 * @retval length of length as specified by #in, or 0 for invalid encoding
 * @pre in.n >= 1 && in.p readable
 */
static uint8_t lenlen(span in)
{
	unsigned n = 1u;
	unsigned x = in.p[0];
	if ((x & 0x80u) != 0u) {	/* long format */
		n += x & 0x7fu;
	}
	if (n > in.n) {
		n = 0;
	}
	return n;
}


/*!
 * Read the length from #in.  No provision is made to limit the
 * length, or, to detect overflow of the bytes in a malformed by
 * stream.
 * @param in length bytes, must not exceed 5 bytes or the value will
 * be wrong, must be correctly formatted to match length
 * @return length in bytes
 */
static unsigned parselen(span in)
{
	unsigned len = 0;
	if (in.n == 1u) {
		len = in.p[0];
	} else {
		for (unsigned i = 1u; i < in.n; ++i) {
			len = (len << 8) | in.p[i];
		}
	}
	return len;
}


asn1e asn1_span2e(span in)
{
	asn1e result = { 0 };
	uint8_t tlen = taglen(in);

	if ((tlen > 0u) && (tlen < in.n)) {
		uint8_t llen = lenlen((span){in.p + tlen, in.n - tlen});
		if (llen > 0 && llen < 4) { /* limit buffer length */
			unsigned dlen  = parselen((span){in.p + tlen, llen});
			uint8_t hlen = tlen + llen;
			unsigned total = hlen + dlen;
			if (total <= in.n) {
				result = (asn1e){in.p, tlen, hlen, total};
			}
		}
	}
	return result;
}


span asn1_e2span(asn1e in)
{
    return (span){ in.p, in.n };
}


/*!
 * return the data-  if it is not in \a in, return an empty span
 */
span asn1_data(asn1e in)
{
	return (span){ in.p + in.idata,
		(uint32_t)in.n - (uint32_t)in.idata };
}


/*!
 * Calculate length required for encoding length.
 * @param length length in bytes
 * @return number of bytes required to encode #length as DER
 */
static uint8_t lenbytes(size_t length)
{
	uint8_t lenlen = 1;
	if (length >= 128) {
		for (unsigned i = length; i != 0u; i >>= 8) {
			++lenlen;
		}
	}
	return lenlen;
}


/* This should also tell if it is ok, and not malformed at the end! */
bool asn1_next(asn1_iter *iter)
{
	if ((iter != NULL) && (iter->current.n > 0u)) {
		uint8_t const *p = iter->current.p + iter->current.n;
		size_t n = (size_t)(iter->range.p + iter->range.n - p);
		iter->current = asn1_span2e((span){ p, n });
	}
	return iter && (iter->current.n > 0u);
}


asn1_iter asn1_start(span range)
{
    return (asn1_iter){range, asn1_span2e(range) };
}


static bool tagmatch(span a, span b)
{
	return (a.n == b.n) && (memcmp(a.p, b.p, a.n) == 0);
}


/* Find first occurrence of oid on top level.  There should be a way
 * to actually match any tag (does that belong here?)
 */
static asn1_iter asn1_find_first(asn1_iter it, span tag)
{
	while ((it.current.n > 0) &&
	       !tagmatch((span){it.current.p, it.current.ilen}, tag)) {
		(void)asn1_next(&it); /* test at top of loop */
	}
	return it;		/* might be zero */
}


asn1_iter asn1_find_nth(span data, span tag, unsigned n)
{
	asn1_iter it = asn1_start(data);
	while ((it.current.n > 0) && (n + 1) > 0) {
		it = asn1_find_first(it, tag);
		if (n > 0) {
			asn1_next(&it);
		}
		--n;
	}
	return it;
}


/*!
 * Return length required to represent the identifier id in the tag.
 */
static size_t idlen(uint32_t id)
{
	size_t len = 1;
	if (id > 30) {
		/* rest of the tag, 7 bits into each word */
		for (uint32_t n = id; n != 0; n >>= 7) {
			++len;
		}
	}
	return len;
}


/*!
 * Write tag (identifier) part only.  The maximum length for a tag is
 * is 6 bytes, the output buffer must be able to hold this.
 * @param aid identifier to write
 * @param p output buffer
 * @pre p must support the length, use idlen() to calculate
 */
static unsigned write_tag(asn1id aid, uint8_t *p)
{
	unsigned id = aid.id;
	size_t len = idlen(id);	/* pass in? */
	uint8_t group = (aid.group << 6) | (aid.construct << 5);
	if (len > 1) {
		p[0] = group | 0x1fu;
		uint8_t mask = 0;
		for (unsigned i = len; i > 1; --i) {
			p[i-1] = mask | (id & 0x7fu);
			id >>= 7;
			mask = 0x80; /* set for all but last */
		}
	} else {
		p[0] = group | id;
	}
	return len;
}


static void write_derlen(size_t length, size_t lenlen, uint8_t *p)
{
	if (lenlen == 1) {
		p[0] = length;
	} else {
		p[0] = 0x80u | (lenlen - 1);
		for (unsigned i = lenlen - 1; i > 0; --i) {
			p[i] = length & 0xffu;
			length >>= 8;
		}
	}
}


/*!
 * Wrap the element(s) given (from start to end, the elements must be
 * at the same level.  Returns the header required, -- without the
 * data inside.  Options for the value are a SEQUENCE, TAG, or a
 * constructed private type, NONE are t
 * @param tag tag to use, only single values are accepted without the
 * CONSTRUCTED tag set
 * @param data the data to engulf into out
 * @param out output buffer
 * @note the header is written and must fit
 */
asn1e asn1_construct_header(asn1id id, size_t length, span out)
{
	/* We must be able to support the tag identifiers up to the
	 * date times (which will exceed 30, i.e. may require 2 bytes.
	 * The data are constructed into "out", with the extents
	 * returned.  The flags (the high bytes up to CONSTRUCTED) are
	 * given in a separate value.
	 */
	uint8_t taglen = idlen(id.id);
	uint8_t lenlen = lenbytes(length);
	uint8_t hlen = taglen + lenlen;
	uint8_t *p = (uint8_t *)out.p;
	if ((p != NULL) && (hlen <= out.n)) {
		(void)write_tag(id, p);
		write_derlen(length, lenlen, p + taglen);
	} else {
		taglen = hlen = 0;
		p = NULL;
	}
	return (asn1e){ p, taglen, hlen, hlen };
}


int asn1_writer_init(asn1_writer *writer, span buffer)
{
	*writer = (asn1_writer){
		.buffer = buffer,
		.last = { .p = buffer.p }
	};
	return 0;
}


/* Open a constructed scope.  The length is a hint -- it will be used
 * to align the resulting lengths in hopes nothing will need to be
 * moved afterwards.  Note that the construct bit is not set, but must
 * be supplied.  The header is directly written into place as there is
 * no data can be supplied.  asn1_construct_header() will not modify
 * the buffer unles the full header fits.
 */
asn1e asn1_writer_open(asn1_writer *writer, asn1id id, size_t length_hint)
{
	if (writer->level < ASN1_WRITER_NUM_SCOPES) {
		/* insertion point follows the last entry */
		uint8_t *p = (uint8_t *)writer->last.p + writer->last.n;
		size_t offset = p - writer->buffer.p;
		asn1e head =
			asn1_construct_header(id, length_hint,
					      (span){ p, writer->buffer.n - offset });
		/* The data did fit, and last value is updated. */
		if (head.n > 0u) {
			writer->parents[writer->level++] = head;
			writer->last = head;
			return head;
		} else {
			writer->error |= ASN1_WRITER_OVERFLOW;
		}
	} else {
		writer->error |= ASN1_WRITER_DEPTH;
	}
	return (asn1e){0};
}


asn1e asn1_write(asn1_writer *writer, asn1id id, span data, uint32_t prefix)
{
	uint8_t *p = (uint8_t *)writer->last.p + writer->last.n;
	size_t offset = p - writer->buffer.p;
	/* Check the input data will not cross the end, that is,
	 * overlap the insertion point.  The header can be consructed
	 * there (it will be written last), but the crossing will make
	 * the input data badly defined and is indicative an invalid
	 * buffer.
	 */
	if ((data.p != NULL) && (data.p < p) && (data.p + data.n > p)) {
		writer->error |= ASN1_WRITER_OVERLAP;
		return (asn1e){0};
	}
	/* Check it will fit.  This should be exact to allow the last
	 * element to fit just in, or not.  The intermediate
	 * construction will allow to transform data which is "just
	 * here".  If it is actually referring to data before this in
	 * the buffer, we might want to abort?
	 */
	bool prefixed = (prefix != 0);
	uint8_t header[16];
	asn1e head =
		asn1_construct_header(id, data.n + prefixed,
				      (span){ header, sizeof(header) });
	if (head.idata + data.n + prefixed <= writer->buffer.n - offset) {
		if (data.p != NULL) {	/* can be NULL to keep uninitialized */
			memmove(p + head.idata + prefixed, data.p, data.n);
		}
		if (prefixed) {
			p[head.idata] = prefix & 0xffu;
		}
		memcpy(p, head.p, head.idata);
		head.p = p;	/* make it point to the write buffer */
		head.n += data.n + prefixed;
		writer->last = head;
	} else {		/* cannot fit into writer buffer */
		writer->error |= ASN1_WRITER_OVERFLOW;
		head = (asn1e){0};
	}
	return head;
}


/* Close a group previously opened.  The length of the group will be
 * updated to match the actual length used, which maybe shorter than
 * expected.
 *
 * Closing multiple scopes may result in adjustment of all lengths
 * from the original and in pathological cases move the child elements
 * back and forth: this case could be handled partially at the cost of
 * extra complexity.  For now it is best to "guess right" on open()
 * (or construct the children first, however, those will then quite
 * certainly end up copied.
 */
asn1e asn1_writer_close(asn1_writer *writer)
{
	asn1e res = (asn1e){ 0 };
	if (writer->level > 0) {
		asn1e parent = writer->parents[--writer->level];
		/* Check where the last element is (should be possible
		   to handle the same element here, so an empty
		   structure/set is allowed
		*/
		const uint8_t *pe = writer->last.p + writer->last.n;
		size_t len = pe - (parent.p + parent.idata);
		/* if the length required for the actual length is
		 * different, we need to readjust and then write the
		 * length.  Verify all fits into buffer still.
		 */
		int lenlen = lenbytes(len);
		int olen = parent.idata - parent.ilen;
		int offset = lenlen - olen;
		uint8_t *p = (uint8_t *)parent.p;
		if (offset != 0) { /* adjust contents to new offset */
			/* if contents are pushed forward, it may
			 * overflow the arena
			 */
			const uint8_t *buffer_end = writer->buffer.p + writer->buffer.n;
			uint8_t *new_end = p + parent.idata + offset + len;
			if ((offset > 0) && (new_end > buffer_end)) {
				writer->error |= ASN1_WRITER_OVERFLOW;
				return res; /* return */
			} else {
				memmove(p + parent.idata + offset,
					p + parent.idata, len);
				parent.idata = parent.ilen + lenlen;
				pe += offset;
			}
		}
		/* rewrite the length into constructed element */
		write_derlen(len, lenlen, p + parent.ilen);
		parent.n = pe - parent.p;
		res = writer->last = parent;
	} else {
		writer->error |= ASN1_WRITER_CLOSED;
	}
	return res;
}


/* Space available in the writer. */
static size_t asn1_writer_available(asn1_writer const *writer)
{
	return writer->buffer.p + writer->buffer.n
		- (writer->last.p + writer->last.n);
}


/* Append at insertion point.  Input data is allowed to overlap final
 * insertion point.  The returned span is set to show this data.
 */
asn1e asn1_write_raw(asn1_writer *writer, span data)
{
	asn1e res = { 0 };
	if (asn1_writer_available(writer) >= data.n) {
		uint8_t *p = (uint8_t *)writer->last.p + writer->last.n;
		memmove(p, data.p, data.n);
		res = writer->last = (asn1e){ p, 0, 0, (uint32_t)data.n };
	} else {
		writer->error |= ASN1_WRITER_OVERFLOW;
	}
	return res;
}


asn1_iter asn1_find(span where, const asn1_query_el *path, size_t npath)
{
	asn1_iter res = { 0 };
	while (npath) {
		uint8_t tagbuf[8];
		unsigned taglen = write_tag(path->tagid, tagbuf);
		asn1_iter it = asn1_find_nth(where, (span){tagbuf, taglen}, path->nth);
		if (it.current.n == 0) { /* not found */
			return res;
		}
		--npath;
		if (npath == 0) { /* last element */
			res = it;
		} else {	/* descend */
			where = asn1_data(it.current);
			++path;
		}
	}
	return res;
}
