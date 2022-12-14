//
//  GLView.m
//  DynamicsX
//
//  Created by Milan Toth on 9/4/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#import "GLView.h"
	#import "AppDelegate.h"

	@implementation GLView


	- ( BOOL ) canBecomeFirstResponder
	{
	
		return YES;
		
	}
	
	
	- ( void ) mouseDown : ( NSEvent* ) theEvent 
	{

		NSPoint location = [ theEvent locationInWindow ];
		
		[ [ AppDelegate sharedDelegate ] mouseDown : location ];

	}


	- ( void ) mouseUp : ( NSEvent* ) theEvent 
	{

		NSPoint location = [ theEvent locationInWindow ];
		
		[ [ AppDelegate sharedDelegate ] mouseUp : location ];

	}


	- ( void ) mouseMoved : ( NSEvent* ) theEvent 
	{

		NSPoint location = [ theEvent locationInWindow ];

		[ [ AppDelegate sharedDelegate ] mouseMoved : location ];

	}


	@end
