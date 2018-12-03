//
//  MLVector43.c
//  Cortex
//
//  Created by Milan Toth on 9/18/13.
//  Copyright (c) 2013 Milan Toth. All rights reserved.
//

	#include "MLVector3.h"


	MLVector3 MLVector3Make( float theX , 
							 float theY , 
							 float theZ )
	{
	
		MLVector3 result;
		
		result.x = theX;
		result.y = theY;
		result.z = theZ;
		
		return result;
	
	}



	MLVector3 MLVector3Add( MLVector3 a , MLVector3 b )
	{
	
		MLVector3 result;
		
		result.x = a.x + b.x;
		result.y = a.y + b.y;
		result.z = a.z + b.z;
		
		return result;
				
	}

	
	MLVector3 MLVector3Sub( MLVector3 a , MLVector3 b )
	{

		MLVector3 result;
		
		result.x = a.x - b.x;
		result.y = a.y - b.y;
		result.z = a.z - b.z;
		
		return result;
				
	}


	float MLVector3Dot( MLVector3 a , MLVector3 b )
	{
		
		return a.x * b.x + a.y * b.y + a.z * b.z;
				
	}


	MLVector3 MLVector3Cross( MLVector3 vectorLeft, MLVector3 vectorRight)
	{
		MLVector3 v = {  vectorLeft.v[1] * vectorRight.v[2] - vectorLeft.v[2] * vectorRight.v[1],
						 vectorLeft.v[2] * vectorRight.v[0] - vectorLeft.v[0] * vectorRight.v[2],
						 vectorLeft.v[0] * vectorRight.v[1] - vectorLeft.v[1] * vectorRight.v[0] };
		return v;
	}


	MLVector3 MLVector3Scale( MLVector3 a , float f )
	{

		MLVector3 result;

		result.x = a.x * f;
		result.y = a.y * f;
		result.z = a.z * f;
		
		return result;
				
	}


	MLVector3 MLVector3IntersectWithPlane(
		MLVector3 lineV1 ,
		MLVector3 lineV2 ,
		MLVector3 planeV ,
		MLVector3 planeN )
	{

		MLVector3 u   = MLVector3Sub( lineV2 , lineV1 );
		MLVector3 w   = MLVector3Sub( planeV , lineV1 );
		float 	  div = MLVector3Dot( planeN , w ) / MLVector3Dot( planeN , u );
		MLVector3 scale  = MLVector3Scale( u , div );
		MLVector3 result   = MLVector3Add( lineV1 , scale );

		return result;
		
	}
