#include "rbln/spinlock.h"

unsigned long spin_lock_irqsave(spinlock_t *lock)
{
	unsigned long flags;

	// save interrupt enable state
	asm volatile("mrs %0, daif"
			: "=&r" (flags)
			:
			: "memory");

	// disable interrupts
	asm volatile("msr daifset, #2\n\t"
			"dsb sy\n\t"
			"isb sy\n\t"
			:
			:
			: "memory");

	spin_lock(lock);

	return flags;
}

void spin_unlock_irqrestore(spinlock_t *lock, unsigned long flags)
{
	spin_unlock(lock);

	// restore interrupt enable_state
	asm volatile("msr daif, %0"
			:
			: "r" (flags)
			: "memory");
}
