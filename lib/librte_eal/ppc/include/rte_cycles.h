/*
 * SPDX-License-Identifier: BSD-3-Clause
 * Copyright (C) IBM Corporation 2014.
 */

#ifndef _RTE_CYCLES_PPC_64_H_
#define _RTE_CYCLES_PPC_64_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef linux
#include <features.h>
#endif

#ifdef __GLIBC__
#include <sys/platform/ppc.h>
#endif

#include "generic/rte_cycles.h"

#include <rte_byteorder.h>
#include <rte_common.h>

/**
 * Read the time base register.
 *
 * @return
 *   The time base for this lcore.
 */
static inline uint64_t
rte_rdtsc(void)
{
#ifdef __GLIBC__
	return __ppc_get_timebase();
#else
	uint64_t __tb;
	__asm__ volatile ("mfspr %0, 268" : "=r" (__tb));
	return __tb;
#endif
}

static inline uint64_t
rte_rdtsc_precise(void)
{
	rte_mb();
	return rte_rdtsc();
}

static inline uint64_t
rte_get_tsc_cycles(void) { return rte_rdtsc(); }

#ifdef __cplusplus
}
#endif

#endif /* _RTE_CYCLES_PPC_64_H_ */
