OBJ_DIR = ./obj
BIN_DIR = $(HOME)/bin

PROJ = tz-sdk-demo

SRC = \
	main.c \
	trcAssert.c \
	trcCounter.c \
	trcDependency.c \
	trcDiagnostics.c \
	trcEntryTable.c \
	trcError.c \
	trcEvent.c \
	trcEventBuffer.c \
	trcExtension.c \
	trcHardwarePort.c \
	trcHeap.c \
	trcInternalEventBuffer.c \
	trcInterval.c \
	trcISR.c \
	trcKernelPort.c \
	trcMultiCoreEventBuffer.c \
	trcObject.c \
	trcPrint.c \
	trcRunnable.c \
	trcSnapshotRecorder.c \
	trcStackMonitor.c \
	trcStateMachine.c \
	trcStaticBuffer.c \
	trcStreamingRecorder.c \
	trcString.c \
	trcTask.c \
	trcTimestamp.c \
	trcStreamPort.c
	
INC_DIR = . \
	include \
	config

COMPILE_FLAGS = -g3

LINK_FLAGS = -g3

COMPILER = gcc
LINKER = gcc

INCLUDES = $(patsubst %,-I%,$(INC_DIR))

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

$(OBJ_DIR)/%.o : %.c
	$(COMPILER) $(COMPILE_FLAGS) $(INCLUDES) -c $< -o $@

build: $(OBJ)
	$(LINKER) $(LINK_FLAGS) $(OBJ) -o $(PROJ).exe

install: $(PROJ).exe
	cp $(OBJ_DIR)/$(PROJ).exe $(BIN_DIR)/

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(OBJ_DIR)/$(PROJ).exe
