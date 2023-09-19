#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "trcRecorder.h"


// Supporting functions for the demo
static void sleep_ms(unsigned long ms);
static void sleep_tv(const struct timespec *rqtp);

// OS-dependent "Hardware Port" functions for timestamping. Referenced in trcHardwarePort.h (WIN32 port, also used for Linux builds).
uint32_t uiTraceTimerGetValue(void);
void vTraceTimerReset(void);

static uint32_t traceTimerOffset;


// RTOS trace hooks, defining the instrumentation 

#define tpTASK_CREATE(task) xTraceObjectRegisterWithoutHandle(PSF_EVENT_TASK_CREATE, (task), (task)->name, (task)->priority)

#define tpTASK_SWITCH(task) xTraceTaskSwitch((task), (task)->priority)

// RTOS task struct

typedef struct {
	char *name;
	int priority;
} task_t;


// User events provide general logging. Needs a "channel".
TraceStringHandle_t xUserEventChannel;

// Demo application, generating a short trace file for Tracealyzer (trace.psf)

int main(void) {
	
	printf("Tracealyzer SDK demo running...\n");

	// Starts tracing and also registers a "main" task for the current execution context (the main function).
	// Note that the main task is specific for the "bare metal" kernel port. See xTraceKernelPortEnable() in trcKernelPort.c.
	// This is probably not suitable for RTOS integrations, since xTraceEnable might then be called from another task.
	xTraceEnable(TRC_START);

	// Register a channel for "user events"
	xTraceStringRegister("Logging", &xUserEventChannel);

    // Sleep calls are used to spread out the events over the timeline, so the trace becomes more realistic and easier to read.
	sleep_ms(1); 
	
	// Initialize the IDLE task
	task_t idle = {"IDLE",  31};
	task_t *IDLE = &idle;

	// Trace hook for registering a new task.
	tpTASK_CREATE(IDLE);

	sleep_ms(1); 
	
	// Adds a "Ready" event for IDLE, meaning it is ready to execute at this point.
	xTraceTaskReady(IDLE);
	
	// Initialize and register another task.
	task_t mytask = {"MyTask", 5};
	task_t *MyTask = &mytask;
	tpTASK_CREATE(MyTask);
	
	sleep_ms(1);

	for (int i=0; i < 10; i++)
	{	
		// MyTask is ready to execute...
		xTraceTaskReady(MyTask);
		
		// Store a task-switch event when MyTask begins executing.
		tpTASK_SWITCH(MyTask);
		
		// Simulating execution of MyTask
		sleep_ms(10);
		
		// Logging a user event...
		xTracePrintF(xUserEventChannel, "Counter: %d", i);
		
		// Simulating execution of MyTask
		sleep_ms(10);
	
		// Switch back to IDLE
		tpTASK_SWITCH(IDLE);
		
		// Simulating execution of IDLE
		sleep_ms(90);
	}
	
	// Calla xTraceStreamPortOnTraceEnd to save the trace data to file.
	xTraceDisable();
	return 0;
}

// Supporting functions

static void sleep_tv(const struct timespec *rqtp) {
	if (nanosleep(rqtp, NULL) != 0) {
		fprintf(stderr, "%s: %s\n", "nanosleep", strerror(errno));
		exit(1);
	}
}

static void sleep_ms(unsigned long ms) {
	struct timespec rqt;

	rqt.tv_sec  = ms / 1000ul;
	rqt.tv_nsec = ms % 1000ul * 1000000ul;
	sleep_tv(&rqt);
}

// Mock function for returning the interrupt mask, see critical section definitions in trcConfig.h 
int placeholder_get_ISR_mask(void)
{
	return 0;
}

// Mock function for setting the interrupt mask, see critical section definitions in trcConfig.h 
void placeholder_set_ISR_mask(int mask)
{
	(void)mask;
}

#ifdef BUILD_WINDOWS
	
// OS-dependent "Hardware Port" functions for timestamping.

uint32_t uiTraceTimerGetValue(void) {

	FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    unsigned long long tt = ft.dwHighDateTime;
    tt <<=32;
    tt |= ft.dwLowDateTime;
    tt /=10;
    tt -= 11644473600000000ULL;

	return tt + traceTimerOffset;
}

void vTraceTimerReset(void)
{
	traceTimerOffset = -uiTraceTimerGetValue();
}

#endif


#ifdef BUILD_LINUX

// OS-dependent "Hardware Port" functions for timestamping.

void vTraceTimerReset(void) {
	struct timespec res;

	memset(&res, 0, sizeof(struct timespec));
	if (clock_getres(CLOCK_MONOTONIC, &res) != 0) {
		fprintf(stderr, "%s: %s\n", "clock_getres", strerror(errno));
		exit(1);
	}
	traceTimerFreq = 1000000000ul / res.tv_nsec;
	traceTimerOffset = -uiTraceTimerGetValue();
}

uint32_t uiTraceTimerGetValue(void) {
	struct timespec tp;
	uint32_t r;

	memset(&tp, 0, sizeof(struct timespec));
	if (clock_gettime(CLOCK_MONOTONIC, &tp) != 0) {
		fprintf(stderr, "%s: %s\n", "clock_gettime", strerror(errno));
		exit(1);
	}
	r = ((uint64_t)tp.tv_sec * 1000000000ull + 
			(uint32_t)tp.tv_nsec) / (1000000000ul / traceTimerFreq);
	r += traceTimerOffset;
	return r;
}

#endif
