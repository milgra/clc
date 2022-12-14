//
//  AppDelegate.m
//  DynamicsOSX
//
//  Created by Milan Toth on 7/2/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#import "AppDelegate.h"


	@implementation AppDelegate


	// entering point

	- ( void ) applicationDidFinishLaunching : ( NSNotification* ) theNotification
	{
	
		// create view and window
		
		NSRect windowRect = NSMakeRect( 0 ,
										0 ,
										900 ,
										600 );
										
		NSOpenGLPixelFormatAttribute attributes[ ] = { NSOpenGLPFADoubleBuffer , 0 };
		NSOpenGLPixelFormat* 		 pixelFormat   = [ [ NSOpenGLPixelFormat alloc ] initWithAttributes : attributes ];
										   
		glView  = [ [ GLView   alloc ]	initWithFrame		: windowRect 
										pixelFormat			: pixelFormat ];
										
		window	= [ [ NSWindow alloc ] 	initWithContentRect : windowRect
										styleMask			: NSTitledWindowMask
										backing				: NSBackingStoreBuffered
										defer				: YES ];
										
		[ window setHasShadow                   : YES ];
		[ window setDelegate                    : self ];
		[ window setContentView                 : glView ];
		[ window setHidesOnDeactivate			: YES ];
		[ window setLevel						: NSMainMenuWindowLevel + 1 ];
		[ window setAcceptsMouseMovedEvents 	: YES ];
		[ window makeKeyAndOrderFront           : self ];
		[ window makeFirstResponder             : glView ];
		[ window makeMainWindow ];
		
		fullScreen 		= NO;
		staticDelegate 	= self;
	
		// create controller
	
		controller = Controller_alloc( );
		
		Controller_init( controller , 
						 glView.frame.size.width ,
						 glView.frame.size.height );
										
		// start timer
		
		[ NSTimer 	scheduledTimerWithTimeInterval 	: 1.0 / 60.0 
					target							: self 
					selector						: @selector(render) 
					userInfo						: nil 
					repeats							: YES ];
	
	}


	// destructor

	- ( void ) dealloc
	{
	
		// cleanup

		// Controller_destruct( controller );	
		
		[ glView release ];
		[ window release ];
	
		[ super dealloc ];
		
	}
	
	
	- ( void ) mouseUp : ( NSPoint ) theLocation
	{
	
		upStamp = [ [ NSDate date ] timeIntervalSince1970 ];
		
		Controller_buttonPressed( 	controller , 
									theLocation.x * ( 900 / glView.frame.size.width ) ,
									theLocation.y * ( 600 / glView.frame.size.height ) );
									
	}


	- ( void ) mouseDown : ( NSPoint ) theLocation
	{
	
		double delay = [ [ NSDate date ] timeIntervalSince1970 ] - upStamp;
		if ( delay < .1 ) [ self changeScreenSize ];
		
	}


	- ( void ) mouseMoved : ( NSPoint ) theLocation
	{
	
		if ( timeLeft == 0 )
		{
			timeLeft = 2;
			controller->showButtons = 1;
		}
		
	}
	
	
	- ( void ) changeScreenSize 
	{
	
		fullScreen = !fullScreen;
		
		if ( fullScreen )
		{

			[ glView enterFullScreenMode	: [ NSScreen mainScreen ]
					 withOptions			: nil ];
				  
		}
		else
		{

			[ glView exitFullScreenModeWithOptions : nil ];
			[ window makeFirstResponder : glView ];
		
		}
	
	}


	static double 	stamp = 0;
	static long 	frames = 0;
	
	- ( void ) render
	{
	
		// update simualtion and renderer

		Controller_updateScene( controller );
		Controller_render( controller );

        // show render buffer

		glSwapAPPLE( );
		
		// frame count
		
		++frames;
		
		double timeStamp = [ [ NSDate date ] timeIntervalSince1970 ];
		if ( timeStamp - stamp > 1.0 )
		{

			NSLog( @"frames %li" , frames );

			stamp = timeStamp;
			frames = 0;
			
			if ( timeLeft > 0 )
			{
				timeLeft -= 1;
				if ( timeLeft == 0 ) controller->showButtons = 0;
			}
			
		}
		
	}


	static AppDelegate* staticDelegate;

	+ ( AppDelegate* ) sharedDelegate
	{
		return staticDelegate;
	}


	@end
