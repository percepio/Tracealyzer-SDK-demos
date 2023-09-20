This makefile is intended for Linux/Unix hosts.

Instructions:
- Run "make"
- Run tz-sdk-demo (created in parent folder)
- Open trace.psf in Tracealyzer.

Note that when Tracealyzer opens the trace file, it will also need to find EXAMPLE-v1.0.1.xml. 
It will search the directory of the trace file by default, so it is easiest to run the executable in the same file as the xml file.
You may however add additional directories to search in the Tracealyzer settings (File -> Settings -> Project Settings -> Definition File Paths).

Tested on Ubunto 20 with gcc version 9.4.0, Target: x86_64-linux-gnu

