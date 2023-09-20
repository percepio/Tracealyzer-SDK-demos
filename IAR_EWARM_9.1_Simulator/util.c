#include "trcRecorder.h"

// Supporting functions for the demo
void sleep_ms(unsigned long ms);


// For this demo only - simulates execution to make the trace more realistic.
void sleep_ms(unsigned long ms) 
{
  /* Valid for the Arm simulator with compiler optimization settings = Low */  
  int32_t cycles_per_ms = TRC_CFG_CPU_CLOCK_HZ/1000;
  int32_t loops = ((cycles_per_ms/11) * ms) - 2; 
  
  for (volatile int i=0; i<loops; i++);
}
