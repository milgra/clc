//
//  MLVector3.h
//  Cortex
//
//  Created by Milan Toth on 9/18/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

#ifndef MLVector3_h
#define MLVector3_h


	#include <math.h>
	#include <stdio.h>

	union _MLVector3
	{
		struct { float x, y, z; };
		float v[3];
	};
	typedef union _MLVector3 MLVector3;
	
	
	MLVector3 MLVector3Make( float theX , 
							 float theY , 
							 float theZ );

	MLVector3 MLVector3Add( MLVector3 a , MLVector3 b );
	
	MLVector3 MLVector3Sub( MLVector3 a , MLVector3 b );

	float MLVector3Dot( MLVector3 a , MLVector3 b );

	MLVector3 MLVector3Cross( MLVector3 vectorLeft, MLVector3 vectorRight);

	MLVector3 MLVector3Scale( MLVector3 a , float f );
	
	MLVector3 MLVector3IntersectWithPlane(
		MLVector3 lineV1 ,
		MLVector3 lineV2 ,
		MLVector3 planeV ,
		MLVector3 planeN );

#endif
