//
//  MLVector4.h
//  Cortex
//
//  Created by Milan Toth on 9/27/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#ifndef Cortex_MLVector4_h
#define Cortex_MLVector4_h

	union _MLVector4
	{
		struct { float x, y, z, w; };
		float v[4];
	};
	typedef union _MLVector4 MLVector4;
	
	
	MLVector4 MLVector4Make( float theX , 
							 float theY , 
							 float theZ ,
							 float theW );

#endif
