/*
  main.c
  Compiler

  Created by Milan Toth on 10/17/13.
  Copyright (c) 2013 Milan Toth. All rights reserved.
*/

#include <stdio.h>
#include "clcsrc.h"

int main( 	int			theCount , 
			const char* theTokens[ ] )
{
	struct Main* main;
	int result;

	main	= Main_alloc( );
    result	= Main_init( main , theCount , theTokens );

    Main_release( main );
    return result;
}

