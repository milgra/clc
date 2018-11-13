# clc

Class-C programming language documentation, compiler source and core library

## What? Another Object-Oriented C language? Why do we need another?

C is a really simple and minimalistic language, that's why we love it. But C++ and Objective-C
became language monsters with over a 100 keywords and confusing features, and more confusing
libraries. Just because you need classes and objects, you don't have to overcomplicate things.

The idea behind Class-C is very simple : take your existing C code, put global variables and
functions in a block and global variables become member variables, functions become methods.
Class is ready.

```
BigPerson:Person
{
  CLString* name;

  void sayHello( )
  {
    printf( "Hello" );
  }
}
```
