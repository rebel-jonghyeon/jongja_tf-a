#ifndef PKE_INTERNAL_H
#define PKE_INTERNAL_H


#include <drivers/cmrt/pke.h>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef CRI_PKE_STANDALONE
/* Max RSA key size in bits */
#define RSA_MAX_KEY_SIZE 8192
#else
#if (CONFIG_CMRT_PKERAM_SIZE >= 0x2000) && !defined(CONFIG_CMRT_FBOOT)
#define RSA_MAX_KEY_SIZE 8192
#else
#define RSA_MAX_KEY_SIZE 4096
#endif
#endif


/*!
 * Complete a request.  This will do the equivalent of trying to
 * automatically synchronize on a result of "0".  If the handle is
 * asynchronous, it is signaled so that a wait() and sync() on the
 * handle will finish.
 * @param pke valid open pke context
 * @return 0 for no errors, or synchronously retrieved result
 */
int cmrt_pke_complete(cmrt_pke_context_t *pke);


/*!
 * Retrieve and clear irqs.  Clear and return all interrupts on the
 * PKE.  This function runs without any locking done on the driver,
 * but will clear and report a snapshot of reported interrupts.  This
 * may result in an unnecessary wakeup, and also, no interrupts may be
 * reported a result.  The signaling semaphore is not affected by the
 * function.  The function can be called both with PKE interrupts
 * disabled, or enabled (which may result in an extra wakeup).
 * @return interrupts reported (and cleared)
 */
uint32_t cmrt_pke_irqs(void);


#ifdef __cplusplus
}
#endif


#endif
