
// Supporting functions for the demo
void sleep_ms(unsigned long ms);

// OS-dependent "Hardware Port" functions for timestamping. Referenced in trcHardwarePort.h (WIN32 port, also used for Linux builds).
uint32_t uiTraceTimerGetValue(void);
uint32_t uiTraceTimerGetFrequency(void);
void vTraceTimerReset(void);
