# Tracealyzer SDK demo for IAR ARM C-Spy Simulator
 
 This project demonstrates the Tracalyzer SDK using a BareMetal platform with
 simulated RTOS events. This is intended as a starting point for creating your
 own Tracealyzer integration for RTOS kernels, middleware or in-house APIs.
 
 ## Getting Tracealyzer
 If you don't have Tracealyzer already, get it from https://percepio.com 
 If requesting an evaluation license, select the "BareMetal" option.
 If you already have a Tracealyzer license, make sure you have the BareMetal
 option included (Help -> About Percepio Tracealyzer -> License information).
 If you don't see BareMetal in the list, please contact support@percepio.com.
 
 ## Setting up Event Definition Path
 This project relies on custom event definitions in EXAMPLE-v1.0.1.xml.
 You need to tell Tracealyzer in what folder this file is located.
 1. Start Tracealyzer
 2. Open File -> Settings -> Project Settings -> Definition File Paths
 3. Add the project root folder path, where EXAMPLE-v1.0.1.xml is located.
 
  ## Viewing traces in Tracealyzer
 1. Select "Download and Debug" (Ctrl-D).
 2. Select Run (F5)
 3. Check the Terminal I/O window (View menu).
 4. Wait until you see "Trace file closed." 
 5. You should now have a trace file called "trace.psf" in the project folder.
 6. Start Tracealyzer, select File -> Open -> Open File and select this file.
 
 ## Notes
 In this demo, the trace streaming is done using semihosting, i.e. fwrite
 to host files. The performance of this fairly slow and varies quite a lot
 between different computers. This is not representative for using
 Tracealyzer on real hardware.
 
 You may want to verify that the macro file "IAR_ARM_DWT_Simulator.mac"
 is included under project options -> debugger -> setup and that the path
 is correct. Don't use this macro file for real hardware!
 
 In the Breakpoints view, you may note two special breakpoints. They are
 added by the macro file and provide simulation of the DWT cycle counter
 register for timestamping in TraceRecorder.
 
 If you change the Event Definition file name, update TRC_PLATFORM_CFG in
 trcKernelPort.h (now "EXAMPLE"). If you create new versions of your XML
 file, you may keep the old version so older traces still can be opened.
 Create a copy with updated version number (e.g. EXAMPLE-v1.0.2.xml) and
 then update the the TRC_PLATFORM_CFG_MAJOR/MINOR/PATCH definitions.
 
 The function delay_ms() has been added to spread out the events over the
 timeline. This is only for demo purposes and should not be used in real
 integrations.
 
 To use Tracealyzer on real hardware, see https://percepio.com/IAR.
