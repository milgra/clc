//
//  AppDelegate.h
//  DynamicsOSX
//
//  Created by Milan Toth on 7/2/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#import <Cocoa/Cocoa.h>
	#import "GLView.h"
	#import "clcsrc.h"


	@interface AppDelegate : NSObject < NSApplicationDelegate , NSWindowDelegate >
	{

		NSWindow*					window;
		NSView*						glView;
		BOOL						glInited;
		BOOL						fullScreen;
		double						upStamp;
		int							timeLeft;
		struct Controller*			controller;

	}
	
	+ ( AppDelegate* ) sharedDelegate;
	- ( void ) mouseUp : ( NSPoint ) theLocation;
	- ( void ) mouseDown : ( NSPoint ) theLocation;
	- ( void ) mouseMoved : ( NSPoint ) theLocation;


	@end