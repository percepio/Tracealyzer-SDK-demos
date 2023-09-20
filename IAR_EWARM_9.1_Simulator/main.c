#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trcRecorder.h"
#include "util.h"

// RTOS trace hooks, defining the instrumentation 

// Trace hook on task creation
#define tpTASK_CREATE(task) xTraceObjectRegisterWithoutHandle(PSF_EVENT_TASK_CREATE, (task), (task)->name, (task)->priority)

// Trace hook on task switch event
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
	
	for (int i=0; i < 50; i++)
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
	
	// Calls xTraceStreamPortOnTraceEnd to save the trace data to file.
	xTraceDisable();
	return 0;
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
