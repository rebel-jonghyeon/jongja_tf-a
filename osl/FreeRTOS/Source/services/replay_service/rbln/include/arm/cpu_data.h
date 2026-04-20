#ifndef _CPU_DATA_H_
#define _CPU_DATA_H_

#include <stdint.h>
#include <sys/types.h>
//#include "rbln/context.h"
#include "context.h"


typedef uint32_t magic_key;


#define REG_SZ               (sizeof(uint32_t))
#define CRASH_BUF_SIZE       (CTX_GPREGS_END)
#define CPU_REG_NUM          (CRASH_BUF_SIZE / REG_SZ)
#define CRASH_MAGIC_KEY_SIZE (sizeof(magic_key) * 2)
#define CPU_DATA_SIZE        (CRASH_BUF_SIZE + CRASH_MAGIC_KEY_SIZE)


struct cpu_data {
	uint32_t regs[CPU_REG_NUM];
	magic_key magic_key[2];
};

struct cpu_data *get_cpu_data(void);

#endif /* _CPU_DATA_H_ */
