//
//  MLVector4.c
//  Cortex
//
//  Created by Milan Toth on 9/27/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#include "MLVector4.h"


	MLVector4 MLVector4Make( float theX , 
							 float theY , 
							 float theZ ,
							 float theW )
	{
	
		MLVector4 result;
		
		result.x = theX;
		result.y = theY;
		result.z = theZ;
		result.w = theW;
		
		return result;
	
	}
