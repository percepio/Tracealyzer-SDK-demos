
/******************************************************************************
 * 
 * Tracealyzer SDK demo for IAR ARM C-Spy Simulator
 * ------------------------------------------------
 * This project demonstrates the Tracalyzer SDK using a BareMetal platform with
 * simulated RTOS events. This is intended as a starting point for creating your
 * own Tracealyzer integration for RTOS kernels, middleware or in-house APIs.
 *
 * --- Getting Tracealyzer ---
 * If you don't have Tracealyzer already, get it from https://percepio.com 
 * If requesting an evaluation license, select the "BareMetal" option.
 * If you already have a Tracealyzer license, make sure you have the BareMetal
 * option included (Help -> About Percepio Tracealyzer -> License information).
 * If you don't see BareMetal in the list, please contact support@percepio.com.
 *
 * --- Setting up Event Definition Path ---
 * This project relies on custom event definitions in EXAMPLE-v1.0.1.xml.
 * You need to tell Tracealyzer in what folder this file is located.
 *  1. Start Tracealyzer
 *  2. Open File -> Settings -> Project Settings -> Definition File Paths
 *  3. Add the project root folder path, where EXAMPLE-v1.0.1.xml is located.
 *
 * --- Viewing traces in Tracealyzer ---
 * 1. Select "Download and Debug" (Ctrl-D).
 * 2. Select Run (F5)
 * 3. Check the Terminal I/O window (View menu).
 * 4. Wait until you see "Trace file closed." 
 * 5. You should now have a trace file called "trace.psf" in the project folder.
 * 6. Start Tracealyzer, select File -> Open -> Open File and select this file.
 * 
 * Notes:
 *
 * - In this demo, the trace streaming is done using semihosting, i.e. fwrite
 *   to host files. The performance of this fairly slow and varies quite a lot
 *   between different computers. This is not representative for using
 *   Tracealyzer on real hardware.
 *
 * - You may want to verify that the macro file "IAR_ARM_DWT_Simulator.mac"
 *   is included under project options -> debugger -> setup and that the path
 *   is correct. Don't use this macro file for real hardware!
 * 
 * - In the Breakpoints view, you may note two special breakpoints. They are
 *   added by the macro file and provide simulation of the DWT cycle counter
 *   register for timestamping in TraceRecorder.
 *
 * - If you change the Event Definition file name, update TRC_PLATFORM_CFG in
 *   trcKernelPort.h (now "EXAMPLE"). If you create new versions of your XML
 *   file, you may keep the old version so older traces still can be opened.
 *   Create a copy with updated version number (e.g. EXAMPLE-v1.0.2.xml) and
 *   then update the the TRC_PLATFORM_CFG_MAJOR/MINOR/PATCH definitions.
 *
 * - The function delay_ms() has been added to spread out the events over the
 *   timeline. This is only for demo purposes and should not be used in real
 *   integrations.
 * 
 * - To use Tracealyzer on real hardware, see https://percepio.com/IAR
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trcRecorder.h"


// Supporting functions for the demo
static void sleep_ms(unsigned long ms);

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

int main(void) {
	
        printf("Tracealyzer SDK demo\n\n");
        
	// Starts tracing
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
		
		// Simulating execution of MyTask, with an occational anomaly
                if (i%10==0) sleep_ms(25); else sleep_ms(10);
		  
		// Logging a user event...
		xTracePrintF(xUserEventChannel, "Counter: %d", i);
		
		// Simulating execution of MyTask
		sleep_ms(10);
	
		// Switch back to IDLE
		tpTASK_SWITCH(IDLE);
		
		// Simulating execution of MyTask, with an occational anomaly
                if (i%10==0) sleep_ms(75); else sleep_ms(90);
        }
	
	xTraceDisable();
	return 0;
}


// For this demo only - simulates execution to make the trace more realistic.
static void sleep_ms(unsigned long ms) 
{
  /* Valid for the Arm simulator with compiler optimization settings = Low */  
  int32_t cycles_per_ms = TRC_CFG_CPU_CLOCK_HZ/1000;
  int32_t loops = ((cycles_per_ms/11) * ms) - 2; 
  
  for (volatile int i=0; i<loops; i++);
}