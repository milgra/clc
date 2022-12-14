dynamicsx
=========

Simple Dynamics Engine written in Class-C by Milan Toth

The Projects folder contains the project files for various platforms and IDE's, it only contains the OSX/xCode 5.0 project at the moment, feel free to push me more projects!

The Related folder contains the related files, which is the Class-C compiler source at the moment, in case of emergency you can compile a compiler for the project.

The Sources folder contains all platform-independent sources.

The main class of the indepent source group is Controller in Controller.clc, you should start examining that class, it has to be initialized with the opengl context width and context height. The openGL context have to be initialized platform-dependently before initializing this class!!!

If you are using xCode, set the proper paths in the run script section of the build phases before building.