	#ifndef MLMatrix4_h
	#define MLMatrix4_h

	
	#include <math.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "MLVector3.h"
	#include "MLVector4.h"
	

	union _MLMatrix4
	{
		struct
		{
			float m00, m01, m02, m03;
			float m10, m11, m12, m13;
			float m20, m21, m22, m23;
			float m30, m31, m32, m33;
		};
		float m[16];
	};
	typedef union _MLMatrix4 MLMatrix4;


	// creates identity matrix

	MLMatrix4 MLMatrix4CreateIdentity( );

	// creates ortographic projection

	MLMatrix4 MLMatrix4CreateOrtho( 	
		float theLeft 	, 
		float theRight 	,
		float theBottom , 
		float theTop 	,
		float theNear	, 
		float theFar 	);
		
	// creates perspective matrix
	
	MLMatrix4 MLMatrix4CreatePerspective( 	
		float fovyRadians , 
		float aspect , 
		float nearZ , 
		float farZ );
		
	// creates look at
		
	MLMatrix4 MLMatrix4CreateLookAt( 
		float eyeX		, float eyeY	, float eyeZ	,
		float centerX	, float centerY	, float centerZ	,
		float upX		, float upY		, float upZ		);

	// creates rotation

	MLMatrix4 MLMatrix4CreateRotation( 	
		float theRadians , 
		float theX , 
		float theY , 
		float theZ );

	// multiplies matrices

	MLMatrix4 MLMatrix4Multiply( 	
		MLMatrix4 theLeft , 
		MLMatrix4 theRight );

	// translates matrix

	MLMatrix4 MLMatrix4CreateTranslate( 
		float theX , 
		float theY , 
		float theZ );
	
	MLMatrix4 MLMatrix4Translate( 
		MLMatrix4 	theMatrix,
		float 		theX , 
		float 		theY , 
		float 		theZ );

	// scales matrix
	
	MLMatrix4 MLMatrix4Scale( 	
		MLMatrix4 	theMatrix , 
		float 		theX , 
		float 		theY , 
		float		theZ );

	// rotates matrix

	MLMatrix4 MLMatrix4Rotate(  	
		MLMatrix4 	theMatrix  ,
		float 		theRadians , 
		float 		theX , 
		float 		theY , 
		float 		theZ );
		
	void MLMatrix4Describe( MLMatrix4 theMatrix );

	// multiplies with vector

	MLVector4 MLMatrix4ProjectVector4ToScreen( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight );

	MLVector4 MLMatrix4UnProjectVector4FromScreen( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight );

	MLVector3 MLMatrix4MultiplyVector3( 
		MLMatrix4 theMatrix , 
		MLVector3 theVector );

	MLVector4 MLMatrix4MultiplyVector4( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector );

	MLVector4 MLMatrix4MultiplyVector4Transposed( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector );

	MLMatrix4 MLMatrix4Invert( MLMatrix4 src , char* success );
	MLMatrix4 MLMatrix4Transpose( MLMatrix4 src );



	#endif
