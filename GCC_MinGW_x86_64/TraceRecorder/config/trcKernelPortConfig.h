/*
 * Trace Recorder for Tracealyzer v989.878.767
 * Copyright 2023 Percepio AB
 * www.percepio.com
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Configuration parameters for the kernel port.
 * More settings can be found in trcKernelPortStreamingConfig.h.
 */

#ifndef TRC_KERNEL_PORT_CONFIG_H
#define TRC_KERNEL_PORT_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Setting this to 0 will completely disable the recorder
 */
#define TRC_CFG_USE_TRACEALYZER_RECORDER 1

/**
 * @brief Critical Sections
 * The TraceRecorder has its own macros for local critical sections. Some
 * TraceRecorder functions are called both in kernel/interrupt and thread
 * context, so the critical sections must work in both cases. 
 * This is often implemented by disabling and restoring interrupts, which
 * allows for calling TraceRecorder functions also from interrupt handlers.
 * But other solutions are possible.
 *
 * The Bare Metal kernel port (that this demo is based on) does not define
 * these macros, but placeholders are provided below. Make sure to implement
 * these before using TraceRecorder in a multitasking system. 
 */
#define TRC_KERNEL_PORT_ALLOC_CRITICAL_SECTION() TraceUnsignedBaseType_t TRACE_ALLOC_CRITICAL_SECTION_NAME;
#define TRC_CFG_ENTER_CRITICAL_SECTION() {TRACE_ALLOC_CRITICAL_SECTION_NAME = placeholder_get_ISR_mask(); placeholder_set_ISR_mask(1);}
#define TRC_CFG_EXIT_CRITICAL_SECTION() {placeholder_set_ISR_mask(TRACE_ALLOC_CRITICAL_SECTION_NAME);}

/* Defined in main.c */
extern int placeholder_get_ISR_mask(void);

/* Defined in main.c */
extern void placeholder_set_ISR_mask(int mask);

#ifdef __cplusplus
}
#endif

#endif /* TRC_KERNEL_PORT_CONFIG_H */
