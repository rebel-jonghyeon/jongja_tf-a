#include "libZebuZEMI3.hh"
#include <thread>
#include <dlfcn.h>

#include <vector>
#include <iomanip>

#include "svt_zebu_platform.hh"
#include "svt_pthread_threading.hh"
#include "XtorScheduler.hh"
#include "xtor_wrapper_pcie_svs.hh"

#include "monitor_pcie_svs.hh"

using namespace ZEBU;
using namespace ZEBU_IP;
using namespace XTOR_PCIE_SVS;
using namespace MONITOR_PCIE_SVS;

/*****************************************************************************
 *      Random data generator/checker                                        *
 *****************************************************************************/
#define MAXFUNC 1

#define bar0SizeF0  0x000000FF // IO SPACE
#define bar0TypeF0  0x01       // IO SPACE
#define bar0StartF0 0x00000000 // IO SPACE
#define bar1SizeF0  0x0000FFFF // MEM 32
#define bar1TypeF0  0x00       // MEM 32
#define bar1StartF0 0x00000000 // MEM 32
#define bar2SizeF0  0x00FFFFFF // MEM 64(LOW)
#define bar2TypeF0  0x00000004 // MEM 64(LOW)
#define bar2StartF0 0x00000000 // MEM 64(LOW)
#define bar3SizeF0  0x00000000 // MEM 64(HIGH)
#define bar3TypeF0  0x00000000 // MEM 64(HIGH)
#define bar3StartF0 0x00000000 // MEM 64(HIGH)
#define bar4SizeF0  0x00000000
#define bar5SizeF0  0x00000000

// #define BAR1SizeF0_RC  0xFFFFFFFF // BAR1 MEM32
// #define BAR1TypeF0_RC  0x00       // BAR1 MEM32
// #define BAR1StartF0_RC 0x80000000 // BAR1 MEM32

#define BAR0SizeF0_RC  0xFFFFFFFF // BAR0 MEM64
#define BAR0TypeF0_RC  0x4        // BAR0 MEM64
#define BAR1SizeF0_RC  0xFFFFFFFF // BAR1 MEM64
#define BAR1TypeF0_RC  0x0        // BAR1 MEM64

#define DOWNSTREAM_KEY "1013456789abcdefcafebabe000000000123456789abcdefcafebabedeadbeef"
#define UPSTREAM_KEY   "1023456789abcdefcafebabedeadbeef1123456789abcdefcafebabe00000000"

// Random Stream -----------------------------------------------
#define RANDOM_TABLE_SIZE 1024*1024

void zRci_pcie_post_board_init ();
void zRci_pcie_cleanup ();
void Xtor_Pcie_analyzer_stop();
void Xtor_Pcie_analyzer_start();
void zRci_pcie_command (const string key, const string& value);
