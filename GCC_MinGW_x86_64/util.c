#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trcRecorder.h"
#include "util.h"

static uint32_t traceTimerOffset;

// Supporting functions

#ifdef BUILD_WINDOWS
	
// OS-dependent functions

#include "Windows.h"

void sleep_ms(unsigned long ms)
{
	Sleep(ms);
}

uint32_t uiTraceTimerGetValue(void)
{
	FILETIME ft;

    GetSystemTimeAsFileTime(&ft);
    unsigned long long tt = ft.dwHighDateTime;
    tt <<=32;
    tt |= ft.dwLowDateTime;

	// Return timestamp in microseconds.
	return tt + traceTimerOffset;
}

void vTraceTimerReset(void)
{
	traceTimerOffset = -uiTraceTimerGetValue();
}

uint32_t uiTraceTimerGetFrequency(void)
{
	// 100 ns resolution
	return 10000000;
}

#endif


#ifdef BUILD_LINUX

// OS-dependent functions

#include "time.h"

static uint32_t traceTimerFreq = 0;

static void sleep_tv(const struct timespec *rqtp)
{
	if (nanosleep(rqtp, NULL) != 0)
	{
		fprintf(stderr, "%s: %s\n", "nanosleep", strerror(errno));
		exit(1);
	}
}
 
void sleep_ms(unsigned long ms)
{
	struct timespec rqt;
 
	rqt.tv_sec  = ms / 1000ul;
	rqt.tv_nsec = ms % 1000ul * 1000000ul;
	sleep_tv(&rqt);	
}

void vTraceTimerReset(void)
{
	struct timespec res;

	memset(&res, 0, sizeof(struct timespec));
	if (clock_getres(CLOCK_MONOTONIC, &res) != 0) {
		fprintf(stderr, "%s: %s\n", "clock_getres", strerror(errno));
		exit(1);
	}
	traceTimerFreq = 1000000000ul / res.tv_nsec;
	traceTimerOffset = -uiTraceTimerGetValue();
}

uint32_t uiTraceTimerGetValue(void)
{
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

uint32_t uiTraceTimerGetFrequency(void)
{
	return traceTimerFreq;
}

#endif
