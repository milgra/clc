clcc
====

Class-C source-to-source compiler by Milan Toth

The Projects folder contains the project files for various platforms and IDE's, it only contains the OSX/xCode 5.0 project at the moment, feel free to push me more projects!

The Related folder contains the related files, which is the Class-C compiler source at the moment, in case of emergency you can compile a compiler for the project.

The Sources folder usually contains all platform-independent sources, in this case all source files are platform-independent, C89 compatible.

main.c is the entering point, it instantiates the Main class in Main.clc. 
To create a compiler project for your platform/IDE, just include all the files in this folder, set main.c as the main file, and precompile all *.clc files to clcsrc.h and clcsrc.c, that are located in the Sources folder also.

If you are using xCode, set the proper paths in the run script section of the build phases before building.