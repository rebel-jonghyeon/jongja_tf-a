/*
 * Copyright (c) 2023-2024 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file
 */

/*!
 * @file asn1.h
 *
 * ASN.1 [1] DER (distinguished encoding rules) [2] functions.  The
 * functions allow iterating through DER elements, descending into
 * constructs, and locating arbitrary sub-elements including
 * constructs (aggregates) with simple queries.
 *
 * Writing DER is possible with a set of append-only writer function.
 * Random insertion, or in-place edit, within the DER is not directly
 * facilitated.
 *
 * All functions work without dynamic memory allocations.  Specified
 * data sections are always copied (`memmove()`) into the location
 * before the header for finished elements is written to allow inplace
 * construction within the same memory region as the header data.
 *
 * The writer has a constant maximum depth of 8.  Exceeding this
 * nesting depth will require a separate #asn1_writer to be used, or
 * the order of construction to be changed to create the contained
 * child elements first.  Generally, any remaining buffer can be used
 * as a scratch space as long as the insertion point will not overflow
 * into the elements.  This condition will be detected and the writer
 * will be marked with an error bit (future functions may succeed, but
 * this bit will remain set until manually cleared.)
 *
 * The functions will read and write correctly formatted DER with
 * identifiers and content lengths of up to 24 bits and are intended
 * for the parsing and creation of structures used in cryptographic
 * operations, and especially certificates, electronic signatures, and
 * signature requests.  For a subset of the expected objects to handle
 * see [3,4,5,6].  There are no functions for handling semantics
 * required by those elements in this header: this is purely about the
 * DER data construction.
 *
 * [1] ISO/IEC 8824-1:2021, Rec. ITU-T X.680 (02/2021) Information
 * technology -- Abstract Syntax Notation One (ASN.1): Specification
 * of basic notation
 *
 * [2] ISO/IEC 8825-1:2021, Rec. ITU-T X.690 (02/2021) Information
 * technology -- ASN.1 encoding rules: Specification of Basic Encoding
 * Rules (BER), Canonical Encoding Rules (CER) and Distinguished
 * Encoding Rules (DER)
 *
 * [3] ISO/IEC 9594-8:2020, Rec. ITU-T X.509 (10/2019) Information
 * technology -- Open System Interconnetion -- The Directory:
 * Public-key and attribute certificate frameworks.
 *
 * [4] PKCS #10: Certification Request Syntax Specification, Version
 * 1.7, RFC 2986
 *
 * [5] PKIX Certificate and CRL Profile, RFC 5280
 *
 * [6] Elliptic Curve Cryptography Subject Public Key Information, RFC
 * 5480
 */

#ifndef CMRT_UCU_ASN1_H
#define CMRT_UCU_ASN1_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <cmrt/ucu/span.h>

#ifdef __cplusplus
extern "C" {
#endif


/*!
 * Single ASN.1 DER element.
 */
typedef struct asn1e {
	uint8_t const *p;    /**< start of data */
	uint8_t ilen : 4;    /**< length offset index (length of tag) */
	uint8_t idata : 4;   /**< data offset (length of tag + length) */
	uint32_t n : 24;     /**< size in bytes */
} asn1e;


/*!
 * Transform an element to a span.  Clears all extra fields otherwise
 * present within an asn1e.
 *
 * @param in asn1e element identifier
 * @return data span of the element
 */
span asn1_e2span(asn1e in);


/*!
 * Extract contents (type identifier and length are removed, and only
 * the data part is returned.)
 *
 * @param in input arena to test
 * @return extents of the data contents (subset of \a in)
 */
span asn1_data(asn1e in);


/*!
 * Universal class tag assignments, ISO/IEC 8824-1-2021, Rec ITU-T
 * X.680, p.14.
 *
 * Standard type identifier numbers.  The actual identifier will have
 * the construct bit (bit 5, 0x20) set for SEQUENCE and SET, the use
 * is not enforced by the library.  The encoding of the tag within DER
 * will depend on the actual value.  See [1] for a description of the
 * universal character classes.
 *
 * The same identifier numbers may be present in other classes
 * (groups) within the same structure.
 */
enum Asn1UniversalType {
	/* 0 is reserved for use by encoding rules */
	asn1_boolean = 1,
	asn1_integer = 2,
	asn1_bitstring = 3,
	asn1_octetstring = 4,
	asn1_null = 5,
	asn1_object_identifier = 6,
	asn1_object_descriptor = 7,
	asn1_external_type = 8,
	asn1_instance_of = 8,
	asn1_real = 9,
	asn1_enumerated = 10,
	asn1_embedded_pdv = 11,
	asn1_utf8string = 12,
	asn1_relative_object_identifier = 13,
	asn1_time = 14,
	/* 15 is reserved for future editions of standard */
	asn1_sequence = 16,
	asn1_set = 17,
	asn1_numeric_string = 18,
	asn1_printable_string = 19,
	asn1_t61string = 20,
	asn1_videotex_string = 21,
	asn1_ia5string = 22,
	asn1_utctime = 23,
	asn1_generalized_time = 24,
	asn1_graphic_string = 25,
	asn1_visible_string = 26,
	asn1_general_string = 27,
	asn1_universal_string = 28,
	asn1_character_string = 29,
	asn1_bmpstring = 30,
	asn1_date = 31,
	asn1_time_of_day = 32,
	asn1_date_time = 33,
	asn1_duration = 34,
	asn1_oid_internationalized_resource = 35,
	asn1_relative_oid_internationalized_resource = 36
};


/*!
 * ASN.1 construct values.  Elements may be either constructed
 * (consist of multiple sub-elements) or primitives (not further
 * divisible).  This is bit 6 of the initial tag encoding.
 */
enum Asn1ConstructType {
	asn1_primitive = 0,
	asn1_construct = 1
};


/*!
 * ASN.1 identifier class.  The class is encoded in the 2 highest bits
 * of the first byte of the encded tag.  The classes define distinct
 * name spaces for the identifiers, with universal referring to
 * standardized types.
 */
enum Asn1Class {
	asn1_universal = 0,
	asn1_application = 1,
	asn1_context_specific = 2,
	asn1_private = 3
};


/*!
 * ASN.1 identifier.  The member-wise access is to
 * - id (the actual identifier which can end up in multiple bytes)
 * - construct (flag for constructed, cleared for primitives)
 * - group (the class of the tag)
 * This is a library structure used for describing and returning ids.
 */
typedef struct asn1id {
	uint32_t id : 29;	/**< identifier */
	uint32_t construct : 1; /**< #Asn1ConstructType */
	uint32_t group : 2;	/**< #Asn1Class */
} asn1id;


/*!
 * \defgroup asn1id_macros ASN.1 type macros
 * Named constants for universal asn1id values.  These macros are
 * provided to allow for clearer notation when creating elements and
 * refer to the values of #Asn1UniversalType and to [1].
 * @{
 */

#define ASN1_BOOLEAN ((asn1id){ asn1_boolean, asn1_primitive, asn1_universal })
#define ASN1_INTEGER ((asn1id){ asn1_integer, asn1_primitive, asn1_universal })
#define ASN1_BIT_STRING ((asn1id){ asn1_bitstring, 0, asn1_universal})
#define ASN1_OCTET_STRING ((asn1id){ asn1_octetstring, 0, asn1_universal })
#define ASN1_NULL ((asn1id){ asn1_null, asn1_primitive, asn1_universal })
#define ASN1_OBJECT_IDENTIFIER \
	((asn1id){ asn1_object_identifier, asn1_primitive, asn1_universal })
#define ASN1_ENUMERATED \
	((asn1id){ asn1_enumerated, asn1_primitive, asn1_universal })
#define ASN1_SEQUENCE \
	((asn1id){ asn1_sequence, asn1_construct, asn1_universal })
#define ASN1_SET ((asn1id){ asn1_set, asn1_construct, asn1_universal })
#define ASN1_PrintableString \
	((asn1id){ asn1_printable_string, asn1_primitive, asn1_universal })
#define ASN1_IA5STRING \
	((asn1id){ asn1_ia5string, asn1_primitive, asn1_universal })
#define ASN1_UTF8String \
	((asn1id){ asn1_utf8string, asn1_primitive, asn1_universal })
#define ASN1_DATE ((asn1id){ asn1_date, asn1_primitive, asn1_universal })
#define ASN1_GENERALIZED_TIME \
	((asn1id){ asn1_generalized_time, asn1_primitive, asn1_universal })

/*!
 * Re-tag \a id as implicit, context-specific identifier with \a tag
 * keeping the primitive/construct bit.
 */
#define ASN1_IMPLICIT(tag, id) \
	((asn1id){ (tag), (id).construct, asn1_context_specific })

/*!
 * An explicit, constructed, context-specific identifier.
 */
#define ASN1_EXPLICIT(tag) \
	((asn1id){(tag), asn1_construct, asn1_context_specific})


/*! @} */


/*!
 * Read iterator.  The iterator packs the buffer range iterated over,
 * and the current element into a structure.  Use asn1_start() and
 * asn1_next() to iterate over the elements, or asn1_find() to return
 * the iterator set to an arbitratry element within \a range.
 */
typedef struct asn1_iter {
	span range;		/**< full range (parent) */
	asn1e current;		/**< current (last read) element */
} asn1_iter;


/*!
 * Read next element.  Advance the iterator to the next element.
 *
 * @param[in,out] iter iterator to adjust
 * @return if there is a valid element here and the range is not exhausted
 */
bool asn1_next(asn1_iter *iter);


/*!
 * Start iterating over a range.  The initial element will be set into
 * the returned value.
 *
 * @param range the area to work on
 * @return iterator pointing to first element
 */
asn1_iter asn1_start(span range);


/*!
 * Find matching tag.  This function is very low level, and
 * asn1_find() should be generally preferred.
 *
 * @param data haystack to find in
 * @param tag the tag to look for with exact length
 * @param n 0 for first
 * @return iterator to n+1 match on this level
 */
asn1_iter asn1_find_nth(span data, span tag, unsigned n);


/*!
 * Element in query path.  The query path consists of tag ids and
 * index of match.
 */
typedef struct asn1_query_elem {
	asn1id tagid;		/**< tag to look for */
	uint16_t nth;		/**< match to find (0 for first) */
	uint16_t reserved;	/**< reserved, must be 0 */
} asn1_query_el;


/*!
 * Find an element in the tree.  The query is given as a path of
 * \a npath elements.  The function works at a higher level than
 * asn1_find_nth() and is generally preferred.
 *
 * asn1_find() will descend into elements if more elements are in the
 * path regardless of if the element is constructed or not.
 * Similarily, the #asn1_construct bit must match the elements
 * searched for.
 *
 * The returned iterator will be referring to the next parent scope as
 * the last asn1_find_nth() operation done.  The returned iterator
 * will have the length (n) set to 0 if the element cannot be
 * found in \a where.
 *
 * @param where buffer to look inside
 * @param path query elements to look inside
 * @param npath number of elements in query
 * @return iterator to the element
 */
asn1_iter asn1_find(span where, const asn1_query_el *path, size_t npath);


/*!
 * Nested scopes supported by the writer.  More scopes will result in
 * more memory required for the writer (this will in general be a
 * single allocation for any DER written.)  Each scope will currently
 * increase the size of an as1_writer by 16 bytes.
 */
#define ASN1_WRITER_NUM_SCOPES 12


/*!
 * Writer error flags.  These flags are set and will not be
 * automatically cleared except by asn1_writer_init().
 * @{
 */

#define ASN1_WRITER_OVERFLOW (1U << 1) /**< data overflow */
#define ASN1_WRITER_OVERLAP (1U << 2)  /**< input data badly overlapping */
#define ASN1_WRITER_DEPTH (1U << 3)    /**< open depth exceeded */
#define ASN1_WRITER_CLOSED (1u << 4)   /**< tried to close too much */

/*! @} */

/*!
 * ASN.1 DER writer.  The writer can insert elements as either groups
 * (open scope), raw data, or, elements with data.
 */
typedef struct asn1_writer {
	span buffer;	    /**< total output buffer */
	asn1e last;	    /**< last written element on this level */
	uint8_t level;	    /**< level within structure */
	uint8_t error;	    /**< error flags */
	asn1e parents[ASN1_WRITER_NUM_SCOPES]; /**< parent scopes */
} asn1_writer;


/*!
 * Initialize a writer.  The writer will be initialized to work on \a
 * buffer, errors and open scopes are cleared.
 *
 * @param writer writer structure to initialize
 * @param buffer the data arena to use for writes
 * @return 0
 */
int asn1_writer_init(asn1_writer *writer, span buffer);


/*!
 * Open construct.  The construct will be opened with a length hint,
 * which should be close to the expected total size of the contents.
 * This number is used to reserve space within the DER to prevent
 * later readjustments when the scope is closed.
 *
 * @param writer writer
 * @param id construct to open
 * @param length_hint expected size within the DER
 * @return element opened
 *
 * @note id should have the construct value set, no action is made by
 * the library to verify or change it.  This may be useful for writing
 * key data directly into a BIT STRING for example.
 */
asn1e asn1_writer_open(asn1_writer *writer, asn1id id, size_t length_hint);


/*!
 * Close one group previously opened.  The length of the group will be
 * updated to match the actual length used, which maybe be shorter or
 * longer than originally expected.
 *
 * Closing multiple scopes may result in adjustment of all lengths
 * from the original which may result in pathological cases of moving
 * the child elements back and forth even for elements originally in
 * place.  This can currently only be prevented by having the size
 * hints correct when opening the scopes.
 *
 * @param writer writer
 * @return the adjusted parent scope
 * @see asn1_writer_open()
 */
asn1e asn1_writer_close(asn1_writer *writer);


/*!
 * Construct a new element.  The element will be placed into the
 * current scope with the id in \a data and contents of \a data.
 *
 * @param writer writer
 * @param id identifier
 * @param data data to package into new element.  The data pointer can
 * be NULL to reserve space (not cleared)
 * @param prefix optional data to put into first data: non-zero to
 * use, only lowest byte is used.  Use 0x100 to prefix \a data
 * with a zero byte
 * @return new element descriptor, if zeroed, operation failed
 */
asn1e asn1_write(asn1_writer *writer, asn1id id, span data, uint32_t prefix);


/*!
 * Append raw data at insertion point.  Input data is allowed to
 * overlap final insertion point, no tests are done to detect or
 * prevent pathological movement from across the current insertion
 * point unlike in asn1_write().
 *
 * The data are copied as is with memmove(), and writer->last will be
 * updated to \a data with no parsed length.  If \a data actually
 * consists of DER data, or, is a construct, this may result in
 * different element sequence being read on read.
 *
 * @param writer the writer to append to
 * @param data the data element to add (raw bytes not interpreted)
 * @return reference to data in moved to section or one with 0 length
 */
asn1e asn1_write_raw(asn1_writer *writer, span data);


/*!
 * Low-level header construction.  Encodes the tag and length into the
 * buffer specified by \a out, and return that information.
 *
 * @param id identifier to encode
 * @param length length to encode into buffer
 * @param out output buffer
 * @return descriptor of the tag, pointing to out
 */
asn1e asn1_construct_header(asn1id id, size_t length, span out);


/*!
 * Return the ASN.1 data.  The extracted data will be the next from \a
 * in, and will have zero total length if parsing failed (encoding
 * error in either tag or length, or, the length will not fit into \a
 * in)
 *
 * @param in input data buffer
 * @return element starting at the started, extracted
 */
asn1e asn1_span2e(span in);


/*!
 * ASN.1 DER writer operations.  These denote operations available
 * with asn1_write().
 */
typedef enum asn1_writer_opid {
	asn1_opid_init = 1,
	asn1_opid_open = 2,
	asn1_opid_close = 3,
	asn1_opid_add = 4,
	asn1_opid_raw = 5
} asn1_writer_opid;


/*!
 * A writer operation.  The construct allows the definition of multiple
 * operations and a more readable notation.  The writer will remain
 * the same through all operations.
 * Operations can be:
 * - opening of a construct
 * - closing a construct(s)
 * - writing an element
 * - writing raw data (pre-formatted elements in general)
 * Total size is 16 bytes (type taking up a lot)
 */
struct asn1_write_op {
	enum asn1_writer_opid type;
	asn1id id;		/* tag id for open, add */
	span data;		/* data add, raw. only length used
				 * for open (size_hint) and close */
};


/*!
 * Build ASN.1 DER data.  The function wraps multiple calls to various
 * writer functions into an array.
 *
 * @param writer writer to utilize
 * @param ops array of operations to perform
 * @param nops number of operations in \a ops
 */
asn1e asn1_build(asn1_writer *writer,
		 const struct asn1_write_op *ops,
		 size_t nops);

/*!
 * Helper macros for use with asn1_build().
 * @{
 */

/*!
 * Initialize the builder.  The function will generally be the first
 * call, but could be used to repurpose the same builder within a
 * longer sequence to create multiple DER constructs.
 * @param B buffer (span) to use
 * @see asn1_writer_init()
 */
#define ASN1_INIT(B) { asn1_opid_init, (asn1id){0}, (B) }

/*!
 * Open writer scope.  Generally this is used to open a CONSTRUCT (the
 * bit must be set in the identifier).  The length hint is passed to
 * asn1_open().
 * @param I asn1id id of the construct
 * @param N length hint for the scope
 * @see asn1_writer_open()
 */
#define ASN1_OPEN(I, N) { asn1_opid_open, (I), (span){ NULL, (N) } }

/*!
 * Open a SEQUENCE.
 * @param N length hint (bytes)
 */
#define ASN1_OPEN_SEQUENCE(N) ASN1_OPEN(ASN1_SEQUENCE, (N))

/*!
 * Open a SET.  A set is an list of elements.  The writer must write the
 * members in the correct order as required by DER.
 * @param N length hint (bytes)
 */
#define ASN1_OPEN_SET(N) ASN1_OPEN(ASN1_SET, (N))

/*!
 * Close scopes.  Close \a N scopes, the scopes must have been opened by
 * the writer.
 * @param N number of scopes to close
 */
#define ASN1_CLOSE(N) { asn1_opid_close, (asn1id){0}, (span){ NULL, (N) } }

/*!
 * Add an element.
 * @param ID asn1id of the element
 * @param SPAN data to add into element as contents
 */
#define ASN1_ADD(ID, SPAN) { asn1_opid_add, (ID), (SPAN) }

/*!
 * Add raw data.  Calls asn1_write_raw() to append data directly.
 */
#define ASN1_RAW(SPAN) { asn1_opid_raw, (asn1id){ 0 }, (SPAN) }

/*! @} */

#ifdef __cplusplus
}
#endif

#endif
