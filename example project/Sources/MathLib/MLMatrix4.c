	#include "MLMatrix4.h"


	// creates identity matrix

	MLMatrix4 MLMatrix4CreateIdentity( )
	{

		MLMatrix4 result;
		float* 	  matrix = result.m;
		
		matrix[ 0  ] = 1.0f;
		matrix[ 1  ] = 0.0f;
		matrix[ 2  ] = 0.0f;
		matrix[ 3  ] = 0.0f;
		matrix[ 4  ] = 0.0f;
		matrix[ 5  ] = 1.0f;
		matrix[ 6  ] = 0.0f;
		matrix[ 7  ] = 0.0f;
		matrix[ 8  ] = 0.0f;
		matrix[ 9  ] = 0.0f;
		matrix[ 10 ] = 1.0f;
		matrix[ 11 ] = 0.0f;
		matrix[ 12 ] = 0.0f;
		matrix[ 13 ] = 0.0f;
		matrix[ 14 ] = 0.0f;
		matrix[ 15 ] = 1.0f;
		
		return result;
		
	}


	// creates ortographic projection

	MLMatrix4 MLMatrix4CreateOrtho( 	
		float theLeft 	, 
		float theRight 	,
		float theBottom , 
		float theTop 	,
		float theNear	, 
		float theFar 	)
	{

		float rpl = theRight + theLeft;
		float rml = theRight - theLeft;
		float tpb = theTop + theBottom;
		float tmb = theTop - theBottom;
		float fpn = theFar + theNear;
		float fmn = theFar - theNear;

		MLMatrix4 result;
		float* 	  matrix = result.m;
		
		matrix[0]  = 2.0f / rml;
		matrix[1]  = 0.0f;
		matrix[2]  = 0.0f;
		matrix[3]  = 0.0f;
		matrix[4]  = 0.0f;
		matrix[5]  = 2.0f / tmb;
		matrix[6]  = 0.0f;
		matrix[7]  = 0.0f;
		matrix[8]  = 0.0f;
		matrix[9]  = 0.0f;
		matrix[10] = -2.0f / fmn;
		matrix[11] = 0.0f;
		matrix[12] = -rpl / rml;
		matrix[13] = -tpb / tmb;
		matrix[14] = -fpn / fmn;
		matrix[15] = 1.0f;
		
		return result;
				
	}


	// create perspective projection

	MLMatrix4 MLMatrix4CreatePerspective( 	
		float fovyRadians , 
		float aspect , 
		float nearZ , 
		float farZ )
	{
	
		float cotan = 1.0f / tanf(fovyRadians / 2.0f);
		
		MLMatrix4 m = { cotan / aspect, 0.0f, 0.0f, 0.0f,
						 0.0f, cotan, 0.0f, 0.0f,
						 0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
						 0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f };
		
		return m;
		
	}


	// creates lookat

	MLMatrix4 MLMatrix4CreateLookAt( 
		float eyeX		, float eyeY	, float eyeZ	,
		float centerX	, float centerY	, float centerZ	,
		float upX		, float upY		, float upZ		)
	{
	
//		GLKVector3 ev = { eyeX, eyeY, eyeZ };
//		GLKVector3 cv = { centerX, centerY, centerZ };
//		GLKVector3 uv = { upX, upY, upZ };
//		GLKVector3 n = GLKVector3Normalize(GLKVector3Add(ev, GLKVector3Negate(cv)));
//		GLKVector3 u = GLKVector3Normalize(GLKVector3CrossProduct(uv, n));
//		GLKVector3 v = GLKVector3CrossProduct(n, u);
//		
//		GLKMatrix4 m = { u.v[0], v.v[0], n.v[0], 0.0f,
//						 u.v[1], v.v[1], n.v[1], 0.0f,
//						 u.v[2], v.v[2], n.v[2], 0.0f,
//						 GLKVector3DotProduct( GLKVector3Negate(u) , ev ) ,
//						 GLKVector3DotProduct( GLKVector3Negate(v) , ev ) ,
//						 GLKVector3DotProduct( GLKVector3Negate(n) , ev ) ,
//						 1.0f };
//		
		MLMatrix4 m;

		return m;
		
	}


	// creates rotation

	MLMatrix4 MLMatrix4CreateRotation( 	
		float theRadians , 
		float theX , 
		float theY , 
		float theZ )
	{

		// for readability
		
		float x = theX;
		float y = theY;
		float z = theZ;

		// normalize values

		float scale  = 1.0f / sqrtf( x * x + y * y + z * z );

		x *= scale;
		y *= scale;
		z *= scale;
		
		// precalc
		
		float sin = sinf( theRadians );
		float cos = cosf( theRadians );
		float cosp = 1.0f - cos;
		
		// create matrix

		MLMatrix4 result;
		float* 	  matrix = result.m;
		
		matrix[ 0 ]  = cos + cosp * x * x;
		matrix[ 1 ]  = cosp * x * y + z * sin;
		matrix[ 2 ]  = cosp * x * z - y * sin;
		matrix[ 3 ]  = 0.0f;
		matrix[ 4 ]  = cosp * x * y - z * sin;
		matrix[ 5 ]  = cos + cosp * y * y;
		matrix[ 6 ]  = cosp * y * z + x * sin;
		matrix[ 7 ]  = 0.0f;
		matrix[ 8 ]  = cosp * x * z + y * sin;
		matrix[ 9 ]  = cosp * y * z - x * sin;
		matrix[ 10 ] = cos + cosp * z * z;
		matrix[ 11 ] = 0.0f;
		matrix[ 12 ] = 0.0f;
		matrix[ 13 ] = 0.0f;
		matrix[ 14 ] = 0.0f;
		matrix[ 15 ] = 1.0f;
		
		return result;
							
	}


	// multiplies matrices

	MLMatrix4 MLMatrix4Multiply( 	
		MLMatrix4 theLeft , 
		MLMatrix4 theRight )
	{
		
		MLMatrix4 result;

		float* a 	  = theLeft.m;
		float* b 	  = theRight.m;		
		float* matrix = result.m;
		
		matrix[0]  = a[0] * b[0]  + a[4] * b[1]  + a[8] * b[2]   + a[12] * b[3];
		matrix[4]  = a[0] * b[4]  + a[4] * b[5]  + a[8] * b[6]   + a[12] * b[7];
		matrix[8]  = a[0] * b[8]  + a[4] * b[9]  + a[8] * b[10]  + a[12] * b[11];
		matrix[12] = a[0] * b[12] + a[4] * b[13] + a[8] * b[14]  + a[12] * b[15];
		
		matrix[1]  = a[1] * b[0]  + a[5] * b[1]  + a[9] * b[2]   + a[13] * b[3];
		matrix[5]  = a[1] * b[4]  + a[5] * b[5]  + a[9] * b[6]   + a[13] * b[7];
		matrix[9]  = a[1] * b[8]  + a[5] * b[9]  + a[9] * b[10]  + a[13] * b[11];
		matrix[13] = a[1] * b[12] + a[5] * b[13] + a[9] * b[14]  + a[13] * b[15];
		
		matrix[2]  = a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2]  + a[14] * b[3];
		matrix[6]  = a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6]  + a[14] * b[7];
		matrix[10] = a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10] + a[14] * b[11];
		matrix[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15];
		
		matrix[3]  = a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2]  + a[15] * b[3];
		matrix[7]  = a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6]  + a[15] * b[7];
		matrix[11] = a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10] + a[15] * b[11];
		matrix[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15];
		
		return result;
		
	}
	
	
	MLMatrix4 MLMatrix4CreateTranslate( float theX , float theY , float theZ )
	{
	
		MLMatrix4 result = MLMatrix4CreateIdentity( );
		
		result.m[12] = theX;
		result.m[13] = theY;
		result.m[14] = theZ;
		
		return result;
		
	}
		
	
	// translates matrix
	
	MLMatrix4 MLMatrix4Translate( 
		MLMatrix4 	theMatrix,
		float 		theX , 
		float 		theY , 
		float 		theZ )
	{

		MLMatrix4 result;
		float*	  other  = theMatrix.m;
		float* 	  matrix = result.m;

		matrix[0]  = other[0];
		matrix[1]  = other[1];
		matrix[2]  = other[2];
		matrix[3]  = other[3];
		matrix[4]  = other[4];
		matrix[5]  = other[5];
		matrix[6]  = other[6];
		matrix[7]  = other[7];
		matrix[8]  = other[8];
		matrix[9]  = other[9];
		matrix[10] = other[10];
		matrix[11] = other[11];
		matrix[12] = other[0] * theX + other[4] * theY + other[8]  * theZ + other[12];
		matrix[13] = other[1] * theX + other[5] * theY + other[9]  * theZ + other[13];
		matrix[14] = other[2] * theX + other[6] * theY + other[10] * theZ + other[14];
		matrix[15] = other[15];
		
		return result;

	}

	

	// scales matrix
	
	MLMatrix4 MLMatrix4Scale( 	
		MLMatrix4 	theMatrix , 
		float 		theX , 
		float 		theY , 
		float		theZ )
	{

		MLMatrix4 result;
		float*	  other  = theMatrix.m;
		float* 	  matrix = result.m;
	
		matrix[0]  = other[0] * theX;
		matrix[1]  = other[1] * theX;
		matrix[2]  = other[2] * theX;
		matrix[3]  = other[3] * theX;
		matrix[4]  = other[4] * theY;
		matrix[5]  = other[5] * theY;
		matrix[6]  = other[6] * theY;
		matrix[7]  = other[7] * theY;
		matrix[8]  = other[8] * theZ;
		matrix[9]  = other[9] * theZ;
		matrix[10] = other[10] * theZ;
		matrix[11] = other[11] * theZ;
		matrix[12] = other[12];
		matrix[13] = other[13];
		matrix[14] = other[14];
		matrix[15] = other[15];
		
		return result;
	
	}


	// rotates matrix

	MLMatrix4 MLMatrix4Rotate(  	
		MLMatrix4 	theMatrix  ,
		float 		theRadians , 
		float 		theX , 
		float 		theY , 
		float 		theZ )
	{

		MLMatrix4 rotation = MLMatrix4CreateRotation( theRadians , theX , theY , theZ );
		return MLMatrix4Multiply( theMatrix , rotation );
			
	}
	
	
	// multiplies with vector

	MLVector3 MLMatrix4MultiplyVector3( MLMatrix4 theMatrix , 
										MLVector3 theVector )
	{

		MLVector3 result;
		float*	  vector = theVector.v;
		float* 	  matrix = theMatrix.m;

    	result.x = matrix[0]  * vector[0] + matrix[1]  * vector[1] + matrix[2]  * vector[2] + matrix[3];
		result.y = matrix[4]  * vector[0] + matrix[5]  * vector[1] + matrix[6]  * vector[2] + matrix[7];
		result.z = matrix[8]  * vector[0] + matrix[9]  * vector[1] + matrix[10] * vector[2] + matrix[11];

	    return result;
	
	}


	MLVector4 MLMatrix4MultiplyVector4Transposed( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector )
	{
	
		MLVector4 result;
		float*	  vector = theVector.v;
		float* 	  matrix = theMatrix.m;

    	result.x = matrix[0]  * vector[0] + matrix[4]  * vector[1] + matrix[8]  * vector[2] + matrix[12] * vector[3];
		result.y = matrix[1]  * vector[0] + matrix[5]  * vector[1] + matrix[9]  * vector[2] + matrix[13] * vector[3];
		result.z = matrix[2]  * vector[0] + matrix[6]  * vector[1] + matrix[10] * vector[2] + matrix[14] * vector[3];
		result.w = matrix[3]  * vector[0] + matrix[7]  * vector[1] + matrix[11] * vector[2] + matrix[15] * vector[3];

	    return result;
	
	}


	MLVector4 MLMatrix4MultiplyVector4( 
		MLMatrix4 theMatrix , 
		MLVector4 theVector )
	{
	
		MLVector4 result;
		float*	  vector = theVector.v;
		float* 	  matrix = theMatrix.m;

    	result.x = matrix[0]  * vector[0] + matrix[1]  * vector[1] + matrix[2]  * vector[2] + matrix[3] * vector[3];
		result.y = matrix[4]  * vector[0] + matrix[5]  * vector[1] + matrix[6]  * vector[2] + matrix[7] * vector[3];
		result.z = matrix[8]  * vector[0] + matrix[9]  * vector[1] + matrix[10] * vector[2] + matrix[11] * vector[3];
		result.w = matrix[12]  * vector[0] + matrix[13]  * vector[1] + matrix[14] * vector[2] + matrix[15] * vector[3];

	    return result;
	
	}
	
	
	MLMatrix4 MLMatrix4Transpose( MLMatrix4 src )
	{
	
		MLMatrix4 mtx;
		float tmp;
	
		mtx.m[0]  = src.m[0];
		mtx.m[5]  = src.m[5];
		mtx.m[10] = src.m[10];
		mtx.m[15] = src.m[15];
		
		tmp = src.m[4];
		mtx.m[4]  = src.m[1];
		mtx.m[1]  = tmp;
		
		tmp = src.m[8];
		mtx.m[8]  = src.m[2];
		mtx.m[2] = tmp;
		
		tmp = src.m[12];
		mtx.m[12] = src.m[3];
		mtx.m[3]  = tmp;
		
		tmp = src.m[9];
		mtx.m[9]  = src.m[6];
		mtx.m[6]  = tmp;
		
		tmp = src.m[13];
		mtx.m[13] = src.m[7];
		mtx.m[ 7] = tmp;
		
		tmp = src.m[14];
		mtx.m[14] = src.m[11];
		mtx.m[11] = tmp;	
		
		return mtx;
	
	}
	
	
	MLMatrix4 MLMatrix4Invert( MLMatrix4 src , char* success )
	{
	
		MLMatrix4 result;
	
		double inv[16], det;
		float* m = src.m;
		int i;

		inv[0] = m[5]  * m[10] * m[15] - 
				 m[5]  * m[11] * m[14] - 
				 m[9]  * m[6]  * m[15] + 
				 m[9]  * m[7]  * m[14] +
				 m[13] * m[6]  * m[11] - 
				 m[13] * m[7]  * m[10];

		inv[4] = -m[4]  * m[10] * m[15] + 
				  m[4]  * m[11] * m[14] + 
				  m[8]  * m[6]  * m[15] - 
				  m[8]  * m[7]  * m[14] - 
				  m[12] * m[6]  * m[11] + 
				  m[12] * m[7]  * m[10];

		inv[8] = m[4]  * m[9] * m[15] - 
				 m[4]  * m[11] * m[13] - 
				 m[8]  * m[5] * m[15] + 
				 m[8]  * m[7] * m[13] + 
				 m[12] * m[5] * m[11] - 
				 m[12] * m[7] * m[9];

		inv[12] = -m[4]  * m[9] * m[14] + 
				   m[4]  * m[10] * m[13] +
				   m[8]  * m[5] * m[14] - 
				   m[8]  * m[6] * m[13] - 
				   m[12] * m[5] * m[10] + 
				   m[12] * m[6] * m[9];

		inv[1] = -m[1]  * m[10] * m[15] + 
				  m[1]  * m[11] * m[14] + 
				  m[9]  * m[2] * m[15] - 
				  m[9]  * m[3] * m[14] - 
				  m[13] * m[2] * m[11] + 
				  m[13] * m[3] * m[10];

		inv[5] = m[0]  * m[10] * m[15] - 
				 m[0]  * m[11] * m[14] - 
				 m[8]  * m[2] * m[15] + 
				 m[8]  * m[3] * m[14] + 
				 m[12] * m[2] * m[11] - 
				 m[12] * m[3] * m[10];

		inv[9] = -m[0]  * m[9] * m[15] + 
				  m[0]  * m[11] * m[13] + 
				  m[8]  * m[1] * m[15] - 
				  m[8]  * m[3] * m[13] - 
				  m[12] * m[1] * m[11] + 
				  m[12] * m[3] * m[9];

		inv[13] = m[0]  * m[9] * m[14] - 
				  m[0]  * m[10] * m[13] - 
				  m[8]  * m[1] * m[14] + 
				  m[8]  * m[2] * m[13] + 
				  m[12] * m[1] * m[10] - 
				  m[12] * m[2] * m[9];

		inv[2] = m[1]  * m[6] * m[15] - 
				 m[1]  * m[7] * m[14] - 
				 m[5]  * m[2] * m[15] + 
				 m[5]  * m[3] * m[14] + 
				 m[13] * m[2] * m[7] - 
				 m[13] * m[3] * m[6];

		inv[6] = -m[0]  * m[6] * m[15] + 
				  m[0]  * m[7] * m[14] + 
				  m[4]  * m[2] * m[15] - 
				  m[4]  * m[3] * m[14] - 
				  m[12] * m[2] * m[7] + 
				  m[12] * m[3] * m[6];

		inv[10] = m[0]  * m[5] * m[15] - 
				  m[0]  * m[7] * m[13] - 
				  m[4]  * m[1] * m[15] + 
				  m[4]  * m[3] * m[13] + 
				  m[12] * m[1] * m[7] - 
				  m[12] * m[3] * m[5];

		inv[14] = -m[0]  * m[5] * m[14] + 
				   m[0]  * m[6] * m[13] + 
				   m[4]  * m[1] * m[14] - 
				   m[4]  * m[2] * m[13] - 
				   m[12] * m[1] * m[6] + 
				   m[12] * m[2] * m[5];

		inv[3] = -m[1] * m[6] * m[11] + 
				  m[1] * m[7] * m[10] + 
				  m[5] * m[2] * m[11] - 
				  m[5] * m[3] * m[10] - 
				  m[9] * m[2] * m[7] + 
				  m[9] * m[3] * m[6];

		inv[7] = m[0] * m[6] * m[11] - 
				 m[0] * m[7] * m[10] - 
				 m[4] * m[2] * m[11] + 
				 m[4] * m[3] * m[10] + 
				 m[8] * m[2] * m[7] - 
				 m[8] * m[3] * m[6];

		inv[11] = -m[0] * m[5] * m[11] + 
				   m[0] * m[7] * m[9] + 
				   m[4] * m[1] * m[11] - 
				   m[4] * m[3] * m[9] - 
				   m[8] * m[1] * m[7] + 
				   m[8] * m[3] * m[5];

		inv[15] = m[0] * m[5] * m[10] - 
				  m[0] * m[6] * m[9] - 
				  m[4] * m[1] * m[10] + 
				  m[4] * m[2] * m[9] + 
				  m[8] * m[1] * m[6] - 
				  m[8] * m[2] * m[5];

		det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

		if (det == 0) *success = 0; 

		det = 1.0 / det;

		for (i = 0; i < 16; i++)
			result.m[i] = inv[i] * det;
			
		return result;
	
	}	


	MLVector4 MLMatrix4ProjectVector4ToScreen( 
		MLMatrix4 theMVPMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight )
	{

		// printf( "\n\nVECTORTOSCREEN %f %f %f %f" , theVector.x , theVector.y , theVector.z , theVector.w );
	
		theVector.w = 1;
		
		MLVector4 result;
		MLVector4 vector = MLMatrix4MultiplyVector4Transposed( theMVPMatrix , theVector );

		// perspective divide to normalized device coordinates
		
		vector.x /= vector.w;
		vector.y /= vector.w;
		vector.z /= vector.w;
		
		// viewport transformation

		result.x = ( vector.x + 1 ) * theWidth * 0.5;
		result.y = ( vector.y + 1 ) * theHeight * 0.5;
		result.z = vector.z;
		result.w = vector.w;
		
		return result;
	
	}


	MLVector4 MLMatrix4UnProjectVector4FromScreen( 
		MLMatrix4 theMVPMatrix , 
		MLVector4 theVector ,
		float	  theWidth  ,
		float	  theHeight )
	{

		// printf( "\n\nVECTORFROMSCREEN %f %f %f %f" , theVector.x , theVector.y , theVector.z , theVector.w );
	
		char success = 1;
		MLVector4 vector;
		MLVector4 result;
		
		// invert projection matrix
		
		MLMatrix4 invert = MLMatrix4Invert( theMVPMatrix , &success );
		
		// get normalized device coordinates

		vector.x = theVector.x / theWidth * 2.0 - 1.0;
		vector.y = theVector.y / theHeight * 2.0 - 1.0;
		vector.z = theVector.z;
		vector.w = 1.0;
		
		// multiply transposed inverted projection matrix with vector

		result = MLMatrix4MultiplyVector4Transposed( invert , vector );

		if ( result.w == 0 ) return result;
		
		// get world space coordinates

		result.w = 1.0 / result.w;
		
		result.x *= result.w;
		result.y *= result.w;
		result.z *= result.w;

		return result;
	
	}
	

	void MLMatrix4Describe( MLMatrix4 theMatrix )
	{
	
		for ( int index = 0 ; index < 16 ; index++ )
		{
			if ( index % 4 == 0 ) printf( "\n" );
			printf( "%f " , theMatrix.m[ index ] );
		}
	
	}
	