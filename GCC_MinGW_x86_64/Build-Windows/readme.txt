This makefile is intended for Windows hosts.

Instructions:
- Run "make"
- Run tz-sdk-demo.exe (created in parent folder)
- Open trace.psf in Tracealyzer.

Note that when Tracealyzer opens the trace file, it will also need to find EXAMPLE-v1.0.1.xml. 
It will search the directory of the trace file by default, so it is easiest to run the executable in the same file as the xml file.
You may however add additional directories to search in the Tracealyzer settings (File -> Settings -> Project Settings -> Definition File Paths).

Tested with MinGW_64-13.1.0 in 64-bit mode on Windows 10.
