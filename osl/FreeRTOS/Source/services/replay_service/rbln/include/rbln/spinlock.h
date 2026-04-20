/*
 * Copyright (c) 2013-2018, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SPINLOCK_H
#define SPINLOCK_H

#ifndef __ASSEMBLER__

#include <stdint.h>

typedef struct spinlock {
	volatile uint32_t lock;
} spinlock_t;

static inline void spin_lock_init(spinlock_t *lock)
{
	lock->lock = 0;
}

#define metal_lock_take(lock) spin_lock(lock)
#define metal_lock_give(lock) spin_unlock(lock)

void spin_lock(spinlock_t *lock);
void spin_unlock(spinlock_t *lock);
unsigned long spin_lock_irqsave(spinlock_t *lock);
void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags);
#else

/* Spin lock definitions for use in assembly */
#define SPINLOCK_ASM_ALIGN	2
#define SPINLOCK_ASM_SIZE	4

#endif

#endif /* SPINLOCK_H */
