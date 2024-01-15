#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trcRecorder.h"
#include "util.h"

/*** Stuff for simulating a small RTOS ***/ 

// RTOS task struct
typedef struct {
	char *name;
	int priority;
	uint64_t thread_id;
} task_t;

// Mutex struct
typedef struct {
	char *name;
	int owner;
	uint64_t id;
} os_mutex_t;

// Task and Mutex object instances
task_t idle = {"IDLE",  31, 1};
task_t mytask = {"Task2", 10, 2};
os_mutex_t m1 = {"mutex1", 0, 3};

void os_mutex_lock(os_mutex_t mutex);
void os_mutex_unlock(os_mutex_t mutex);

/*** The Demo Application ***/

int main(void)
{
	// This keeps a handle for a user event channel, used for general logging.
	TraceStringHandle_t xUserEventChannel;

	printf("Tracealyzer SDK demo running...\n");

	// Starts tracing
	xTraceEnable(TRC_START);

	// Register a channel for "user events"
	xTraceStringRegister("Logging", &xUserEventChannel);

    // Sleep calls are used to simulate longer execution time.
	sleep_ms(1); 

	// Registers the objects in the trace. Normally hidden in the object initialization calls.
	(void)xTraceObjectRegisterWithoutHandle(PSF_EVENT_TASK_CREATE, (void*)idle.thread_id, idle.name, idle.priority);
	(void)xTraceObjectRegisterWithoutHandle(PSF_EVENT_TASK_CREATE, (void*)mytask.thread_id, mytask.name, mytask.priority);
	(void)xTraceObjectRegisterWithoutHandle(PSF_EVENT_MUTEX_CREATE, (void*)m1.id, m1.name, 0);

	sleep_ms(1); 
	
	// Adds a "Ready" event for IDLE, meaning it is ready to execute at this point. Normally hidden in the kernel.
	xTraceTaskReady((void*)idle.thread_id);
		
	sleep_ms(1);

	// Terminate after 50 cycles
	for (int i=0; i < 50; i++)
	{	
		// Normally in kernel instrumentation
		xTraceTaskReady((void*)mytask.thread_id);

		// Normally in kernel instrumentation
		xTraceTaskSwitch((void*)mytask.thread_id, mytask.priority);
		
		sleep_ms(10);

		os_mutex_lock(m1);
	
		xTracePrintF(xUserEventChannel, "Counter: %d", i);

		os_mutex_unlock(m1);
	
		sleep_ms(10);
		
		// Normally in kernel instrumentation
		xTraceTaskSwitch((void*)idle.thread_id, idle.priority);
		
		sleep_ms(90);
	}
	
	// Calls xTraceStreamPortOnTraceEnd to save the trace data to file.
	xTraceDisable();
	return 0;
}

void os_mutex_lock(os_mutex_t mutex)
{
	(void)xTraceEventCreate1(PSF_EVENT_MUTEX_LOCK, mutex.id);
}

void os_mutex_unlock(os_mutex_t mutex)
{
	(void)xTraceEventCreate1(PSF_EVENT_MUTEX_UNLOCK, mutex.id);
}

/******************************************************************************
 * Mock function for returning the interrupt mask
 * Need to be replaced before using TraceRecorder in a multithreaded system.
 * See critical section definitions in trcConfig.h 
 *****************************************************************************/
int placeholder_get_ISR_mask(void)
{
	return 0;
}

/******************************************************************************
 * Mock function for setting the interrupt mask
 * Need to be replaced before using TraceRecorder in a multithreaded system.
 * See critical section definitions in trcConfig.h 
 *****************************************************************************/
void placeholder_set_ISR_mask(int mask)
{
	(void)mask;
}

