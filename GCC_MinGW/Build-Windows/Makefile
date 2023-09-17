OBJS	= ./obj/main.o ./obj/trcAssert.o ./obj/trcCounter.o ./obj/trcDependency.o ./obj/trcDiagnostics.o ./obj/trcEntryTable.o ./obj/trcError.o ./obj/trcEvent.o ./obj/trcEventBuffer.o ./obj/trcExtension.o ./obj/trcHardwarePort.o ./obj/trcHeap.o ./obj/trcInternalEventBuffer.o ./obj/trcInterval.o ./obj/trcISR.o ./obj/trcKernelPort.o ./obj/trcMultiCoreEventBuffer.o ./obj/trcObject.o ./obj/trcPrint.o ./obj/trcRunnable.o ./obj/trcSnapshotRecorder.o ./obj/trcStackMonitor.o ./obj/trcStateMachine.o ./obj/trcStaticBuffer.o ./obj/trcStreamingRecorder.o ./obj/trcString.o ./obj/trcTask.o ./obj/trcTimestamp.o ./obj/trcStreamPort.o
SOURCE	= ../main.c ../TraceRecorder/trcAssert.c ../TraceRecorder/trcCounter.c ../TraceRecorder/trcDependency.c ../TraceRecorder/trcDiagnostics.c ../TraceRecorder/trcEntryTable.c ../TraceRecorder/trcError.c ../TraceRecorder/trcEvent.c ../TraceRecorder/trcEventBuffer.c ../TraceRecorder/trcExtension.c ../TraceRecorder/trcHardwarePort.c ../TraceRecorder/trcHeap.c ../TraceRecorder/trcInternalEventBuffer.c ../TraceRecorder/trcInterval.c ../TraceRecorder/trcISR.c ../TraceRecorder/trcKernelPort.c ../TraceRecorder/trcMultiCoreEventBuffer.c ../TraceRecorder/trcObject.c ../TraceRecorder/trcPrint.c ../TraceRecorder/trcRunnable.c ../TraceRecorder/trcSnapshotRecorder.c ../TraceRecorder/trcStackMonitor.c ../TraceRecorder/trcStateMachine.c ../TraceRecorder/trcStaticBuffer.c ../TraceRecorder/trcStreamingRecorder.c ../TraceRecorder/trcString.c ../TraceRecorder/trcTask.c ../TraceRecorder/trcTimestamp.c ../TraceRecorder/trcStreamPort.c
HEADER	= -I../TraceRecorder/include -I../TraceRecorder/config
OUT	= ..\tz-sdk-demo.exe
CC	 = gcc
FLAGS	 = -g -c $(HEADER) -DBUILD_WINDOWS
#FLAGS	 = -g -c -Wall $(HEADER)
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

./obj/main.o: ../main.c
	$(CC) $(FLAGS) ../main.c -o ./obj/main.o

./obj/trcAssert.o: ../TraceRecorder/trcAssert.c
	$(CC) $(FLAGS) ../TraceRecorder/trcAssert.c -o ./obj/trcAssert.o

./obj/trcCounter.o: ../TraceRecorder/trcCounter.c
	$(CC) $(FLAGS) ../TraceRecorder/trcCounter.c -o ./obj/trcCounter.o

./obj/trcDependency.o: ../TraceRecorder/trcDependency.c
	$(CC) $(FLAGS) ../TraceRecorder/trcDependency.c -o ./obj/trcDependency.o 

./obj/trcDiagnostics.o: ../TraceRecorder/trcDiagnostics.c
	$(CC) $(FLAGS) ../TraceRecorder/trcDiagnostics.c -o ./obj/trcDiagnostics.o 

./obj/trcEntryTable.o: ../TraceRecorder/trcEntryTable.c
	$(CC) $(FLAGS) ../TraceRecorder/trcEntryTable.c -o ./obj/trcEntryTable.o  

./obj/trcError.o: ../TraceRecorder/trcError.c
	$(CC) $(FLAGS) ../TraceRecorder/trcError.c -o ./obj/trcError.o 

./obj/trcEvent.o: ../TraceRecorder/trcEvent.c
	$(CC) $(FLAGS) ../TraceRecorder/trcEvent.c -o ./obj/trcEvent.o 

./obj/trcEventBuffer.o: ../TraceRecorder/trcEventBuffer.c
	$(CC) $(FLAGS) ../TraceRecorder/trcEventBuffer.c -o ./obj/trcEventBuffer.o 

./obj/trcExtension.o: ../TraceRecorder/trcExtension.c
	$(CC) $(FLAGS) ../TraceRecorder/trcExtension.c -o ./obj/trcExtension.o 

./obj/trcHardwarePort.o: ../TraceRecorder/trcHardwarePort.c
	$(CC) $(FLAGS) ../TraceRecorder/trcHardwarePort.c -o ./obj/trcHardwarePort.o

./obj/trcHeap.o: ../TraceRecorder/trcHeap.c
	$(CC) $(FLAGS) ../TraceRecorder/trcHeap.c -o ./obj/trcHeap.o

./obj/trcInternalEventBuffer.o: ../TraceRecorder/trcInternalEventBuffer.c
	$(CC) $(FLAGS) ../TraceRecorder/trcInternalEventBuffer.c -o ./obj/trcInternalEventBuffer.o

./obj/trcInterval.o: ../TraceRecorder/trcInterval.c
	$(CC) $(FLAGS) ../TraceRecorder/trcInterval.c -o ./obj/trcInterval.o

./obj/trcISR.o: ../TraceRecorder/trcISR.c
	$(CC) $(FLAGS) ../TraceRecorder/trcISR.c -o ./obj/trcISR.o

./obj/trcKernelPort.o: ../TraceRecorder/trcKernelPort.c
	$(CC) $(FLAGS) ../TraceRecorder/trcKernelPort.c -o ./obj/trcKernelPort.o

./obj/trcMultiCoreEventBuffer.o: ../TraceRecorder/trcMultiCoreEventBuffer.c
	$(CC) $(FLAGS) ../TraceRecorder/trcMultiCoreEventBuffer.c  -o ./obj/trcMultiCoreEventBuffer.o

./obj/trcObject.o: ../TraceRecorder/trcObject.c
	$(CC) $(FLAGS) ../TraceRecorder/trcObject.c -o ./obj/trcObject.o 

./obj/trcPrint.o: ../TraceRecorder/trcPrint.c
	$(CC) $(FLAGS) ../TraceRecorder/trcPrint.c -o ./obj/trcPrint.o

./obj/trcRunnable.o: ../TraceRecorder/trcRunnable.c
	$(CC) $(FLAGS) ../TraceRecorder/trcRunnable.c -o ./obj/trcRunnable.o

./obj/trcSnapshotRecorder.o: ../TraceRecorder/trcSnapshotRecorder.c
	$(CC) $(FLAGS) ../TraceRecorder/trcSnapshotRecorder.c -o ./obj/trcSnapshotRecorder.o

./obj/trcStackMonitor.o: ../TraceRecorder/trcStackMonitor.c
	$(CC) $(FLAGS) ../TraceRecorder/trcStackMonitor.c -o ./obj/trcStackMonitor.o

./obj/trcStateMachine.o: ../TraceRecorder/trcStateMachine.c
	$(CC) $(FLAGS) ../TraceRecorder/trcStateMachine.c -o ./obj/trcStateMachine.o

./obj/trcStaticBuffer.o: ../TraceRecorder/trcStaticBuffer.c
	$(CC) $(FLAGS) ../TraceRecorder/trcStaticBuffer.c -o ./obj/trcStaticBuffer.o

./obj/trcStreamingRecorder.o: ../TraceRecorder/trcStreamingRecorder.c
	$(CC) $(FLAGS) ../TraceRecorder/trcStreamingRecorder.c -o ./obj/trcStreamingRecorder.o

./obj/trcString.o: ../TraceRecorder/trcString.c
	$(CC) $(FLAGS) ../TraceRecorder/trcString.c -o ./obj/trcString.o

./obj/trcTask.o: ../TraceRecorder/trcTask.c
	$(CC) $(FLAGS) ../TraceRecorder/trcTask.c -o ./obj/trcTask.o

./obj/trcTimestamp.o: ../TraceRecorder/trcTimestamp.c
	$(CC) $(FLAGS) ../TraceRecorder/trcTimestamp.c -o ./obj/trcTimestamp.o

./obj/trcStreamPort.o: ../TraceRecorder/trcStreamPort.c
	$(CC) $(FLAGS) ../TraceRecorder/trcStreamPort.c -o ./obj/trcStreamPort.o


clean:
	del /Q obj
	del $(OUT)