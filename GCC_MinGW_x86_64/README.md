# Tracealyzer SDK demo for desktop testing with GNU tools
 
 This project demonstrates the Tracalyzer SDK using a BareMetal platform with
 simulated RTOS events. This is intended as a starting point for creating your
 own Tracealyzer integration for RTOS kernels, middleware or in-house APIs.
 
 This demo project is for GNU tools (gcc, make). Makefiles are provided for
 Linux and Windows hosts in the sudfolders Build-Windows and Build-Linux.
  
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
 
 ## Building and Running the Demo
 1. Open a terminal window and enter the Build-Linux or Build-Windows directory.
 2. Type "gcc -v" to check that your gcc is for 64-bit x86_64 builds.
 3. Type "make -j8" to build (-j8 is not needed but makes it build a bit faster).
 4. Move to the parent folder ("cd ..") where the executable has been created.
 5. Run the executable (tz-sdk-demo or tz-sdk-demo.exe).
 
 ## Viewing the traces in Tracealyzer
 Once the demo application has completed, you should see "trace.psf" in the top
 folder, i.e. next to this README.md.
 Now start Tracealyzer and open this file (File -> Open -> Open File).
 You may also open the file by dragging it to the Tracealyzer window or by 
 double-clicking the .psf file (if using Windows).
 
 ## Notes
 In this demo, the trace streaming is done using the FILE stream port, that
 uses fwrite to write the data to a host file. This is not representative
 for using Tracealyzer on real hardware.
 
 If you change the Event Definition file name, update TRC_PLATFORM_CFG in
 trcKernelPort.h (now "EXAMPLE"). If you create new versions of your XML
 file, you may keep the old version so older traces still can be opened.
 Create a copy with updated version number (e.g. EXAMPLE-v1.0.2.xml) and
 then update the the TRC_PLATFORM_CFG_MAJOR/MINOR/PATCH definitions.
 
 The function delay_ms() has been added to spread out the events over the
 timeline. This is only for demo purposes and should not be used in real
 integrations.