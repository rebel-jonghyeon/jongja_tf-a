/*
 * Copyright (c) 2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

/**
 * @file
 *
 * Bit statistics.  Various APIs to allow taking some simple
 * statistics from bits.  Useful to establish basic sanity checks on
 * data expected to have random properties.  The APIs are fast
 * executing.
 */


#ifndef BITSTATS_H
#define BITSTATS_H


#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif


/* A bitstring.  A bitstring denotes a sequence of /bits/, which can
 * be of arbitrary length (in bits).  The data are not part of the
 * sequence but held in other storage.  This data buffer must be
 * word-aligned.
 */
typedef struct bitstring {
	const uint32_t *p;	/**< start of data */
	uint32_t n;		/**< number of bits */
} bitstring;


/*!
 * Calculate the number of bits set.
 * @param p bitstring passed in
 * @param n number of bits in p
 * @return number of bits set
 * @see bitstat_ones32()
 */
uint32_t bitstat_ones(const uint32_t *p, uint32_t n);


/*!
 * Calculate number of bits set in a vector of 32-bit values.  The
 * number of bits must be a multiple of n.
 * @param p vector of values
 * @param n number of bits
 * @return number of bits set
 * @pre n % 32 == 0
 * @see bitstat_ones()
 */
uint32_t bitstat_ones32(const uint32_t *p, uint32_t n);


/*!
 * Return the run count.  A run denotes a consecutive run of bits of
 * the same value, for example 000 will have a single run, 010 will
 * have 3 runs (0, 1, 0), while 000111000 will also have 3 runs.
 * An empty bitstring is the only string with a run count of 0.
 *
 * @param p bits to test
 * @param n count of bits to test
 * @return count of unchanged values (0..x.n)
 */
uint32_t bitstat_runs(const uint32_t *p, uint32_t n);


/*!
 * Correlate two bit strings.  The correlation will be performed with
 * no shifts, only directly at the start, up to the maximum common
 * length.  For example, the correlation value between "1110" and "1010"
 * would be 3 (3 bits match with the same value), while "000" and
 * "111" would have a value of 0.
 * @param x first pointer to use
 * @param y second bit array to use
 * @param n number of bits to test
 * @return number of matching values (0..n)
 */
uint32_t bitstat_matches(const uint32_t *x, const uint32_t *y, uint32_t n);


/*!
 * Correlate two fully aligned bit strings.  This function is
 * marginally faster on long bit sequences than bitstat_matches().
 * @param a first bit array
 * @param b second bit array
 * @param n number of bits to test
 * @return number of matching bits (0..n)
 * @pre n % 32 == 0
 */
uint32_t bitstat_matches32(const uint32_t *a, const uint32_t *b, uint32_t n);


/*!
 * Correlate two sequences, unaligned.  The function will shift \a y
 * by \a shift bits.
 * @param x first bit array
 * @param y second bit array
 * @param n number of bits to test
 * @param shift shift amount of bits in \a y; the values in y will be
 * delayed by this much, discarding lowest bits
 * @return number of matching bits (0..n)
 */
uint32_t bitstat_shifted_matches(const uint32_t *x, const uint32_t *y,
				 uint32_t n, uint32_t shift);


/*!
 * Edge iterator.  The iterator is initialized with bits_edges_init()
 * to traverse a bit string.  The transitions are returned by calls to
 * bits_edges_next().
 */
typedef struct bits_edge_iter {
	const uint32_t *p;      /**< data pointer */
	uint32_t n;             /**< total bit count */
	uint32_t i;             /**< index of start of word */
	uint32_t edges;         /**< edges in this word */
	uint32_t mask;          /**< test mask for edges */
} bits_edge_iter;


/*!
 * Initialize edge iterator.  The iterator start value is at the first
 * word and the edges within \a p can be retrieved with
 * bits_edges_next().
 * @param it iterator to initialize
 * @param p pointer to start of data
 * @param n number of bits in \a p
 * @return 0 for success, -1 for failure to initialize
 * @pre it != NULL
 */
int bits_edges_init(bits_edge_iter *it, const uint32_t *p, uint32_t n);


/*!
 * Find next value transition.  The function can be called repeatedly
 * to return the next edge on the bit string until exhausted.
 * @param it iterator initialized with bits_edge_init()
 * @return bit number of next edge, or 0 if not found
 */
int bits_edges_next(bits_edge_iter *it);


/*!
 * Retrieve run length distribution.  All runs are collected into bins.
 * @param it initialized iterator (updated during traversal)
 * @param bins bins to update with counts
 * @param nbins count of bins
 * @note \a bins is not cleared, but directly added to
 * @return count of edges (transitions)
 */
int bits_runlens(bits_edge_iter *it, uint32_t *bins, size_t nbins);



#ifdef __cplusplus
}
#endif


#endif
