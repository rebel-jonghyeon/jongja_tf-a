#include <string.h>
#include <cri/cmrt.h>
#include <cri/cmrt/aes.h>
#include <cri/cmrt/hc.h>
#include <cri/cmrt/pke.h>
#include <cri/cmrt/tmc.h>
#include <cri/cmrt/kdc.h>
#include <cri/cmrt/ccp.h>


struct devinfo {
	cri_dev_e id;
	cri_handle_t (*openf)(unsigned);
	void (*closef)(cri_handle_t h);
};


struct handleinfo {
	cri_handle_t h; /* the handle (address shelved out) */
	struct devinfo const *dev; /* the open/close/id */
};


/* Table of allocated handles, not protected. */
enum { NUM_HANDLES = 8 };
static struct handleinfo s_handles[NUM_HANDLES];


static void cri_cshc_close(cri_handle_t h) { cri_hc_close(h); }
static void cri_whc_close(cri_handle_t h) { cri_hc_close(h); }

/* The open/close functions slightly overspecify the function by
 * returning the actual concrete subtype.
 */
#define DEVINFO(N, F) { CRI_DEV_##N, (cri_handle_t (*)(unsigned))cri_##F##_open, (void (*)(cri_handle_t))cri_##F##_close }
static const struct devinfo s_devs[] = {
	DEVINFO(HC, hc),
	DEVINFO(PKE, pke),
	DEVINFO(AES, aes),
	DEVINFO(TMC, tmc),
	DEVINFO(KDC, kdc),
	DEVINFO(CSHC, cshc),
	DEVINFO(WHC, whc),
	// DEVINFO(CCP, ccp),
	{ 0 }
};


static const struct devinfo *findinfo(cri_dev_e id)
{
	for (const struct devinfo *p = s_devs; p->id; ++p) {
		if (p->id == id)
			return p;
	}
	return NULL;
}


static struct handleinfo *findhandle(cri_handle_t h)
{
	for (unsigned i = 0; i < NUM_HANDLES; ++i) {
		if (s_handles[i].h == h) {
			return &s_handles[i];
		}
	}
	return NULL;
}


cri_handle_t cri_open(cri_dev_e id, unsigned flags, ...)
{
	cri_handle_t h = CRI_INVALID_HANDLE;
	struct devinfo const *dev = findinfo(id);
	if (dev != NULL) {
		struct handleinfo *const info = findhandle(NULL);
		if (info != NULL) {
			h = dev->openf(flags);
			if (cri_is_valid(h)) {
				info->dev = dev;
				info->h = h;
			}
		}
	}
	return h;
}


int cri_close(cri_handle_t h)
{
	int res = -1;
	if (cri_is_valid(h)) {
		struct handleinfo *const info = findhandle(h);
		if (info) {
			info->dev->closef(h);
			memset(info, 0, sizeof(struct handleinfo));
			res = 0;
		}
	}
	return res;
}
