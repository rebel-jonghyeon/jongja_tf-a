/*
 * Copyright (c) 2021-2023 Cryptography Research, Inc. (CRI).
 * A license or authorization from CRI is needed to use this file.
 */

#include <cri/cmrt/ecies.h>
#include <cmrt/ucu/ecies.h>

cri_ecies_t cri_ecies_open(uint32_t flags)
{
	return (cri_ecies_t)cmrt_ecies_open(flags);
}

int cri_ecies_init(cri_ecies_t ecies, cri_ecies_mode_t mode,
		   cri_ecies_operation_t operation, const void *priv,
		   size_t privlen, const void *peerx, size_t peerxlen,
		   void *pubxout, size_t pubxoutlen)
{
	return cmrt_ecies_init((cmrt_ecies_t)ecies, (cmrt_ecies_mode_t)mode,
	       (cmrt_ecies_operation_t)operation, priv, privlen, peerx,
	       peerxlen, pubxout, pubxoutlen);
}

int cri_ecies_update(cri_ecies_t ecies, const void *input, size_t inputlen,
		     void *output)
{
	return cmrt_ecies_update((cmrt_ecies_t)ecies, input, inputlen, output);
}

int cri_ecies_final(cri_ecies_t ecies, const void *input, size_t inputlen,
		    const void *sharedinfo, size_t sharedinfolen, void *output,
		    void *tag, size_t taglen)
{
	return cmrt_ecies_final((cmrt_ecies_t)ecies,input, inputlen, sharedinfo,
				sharedinfolen, output, tag, taglen);
}

void cri_ecies_close(cri_ecies_t ecies)
{
	cmrt_ecies_close((cmrt_ecies_t)ecies);
}
