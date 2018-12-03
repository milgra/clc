#ifndef clcsrc_h
#define clcsrc_h
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glext.h>
#include <OpenGL/OpenGL.h>
#include <GLKit/GLKMath.h>
#define kScenePlayXOffset -200.0
#define DEPSILON 0.0001f
#include <stdio.h>
#include <stdlib.h>
#include "CLLink.h"
#include <math.h>
#include <string.h>
#include "CLChar.h"
struct Class
{
	char*	className;
	void*	classId;
};
struct Instance
{
	struct Class*	_class;
	void**	_components;
};
struct Controller;
struct Controller_Class;
struct PLMass;
struct PLMass_Class;
struct PLSpacer;
struct PLSpacer_Class;
struct PLSegment;
struct PLSegment_Class;
struct Scene;
struct Scene_Class;
struct ScenePit;
struct ScenePit_Class;
struct SceneBox;
struct SceneBox_Class;
struct SceneSlope;
struct SceneSlope_Class;
struct SceneParticle;
struct SceneParticle_Class;
struct GLPointP2;
struct GLPointP2_Class;
struct GLRectPT22;
struct GLRectPT22_Class;
struct ShaderP2;
struct ShaderP2_Class;
struct GLSegment;
struct GLSegment_Class;
struct ShaderPT22;
struct ShaderPT22_Class;
struct PLUniverse;
struct PLUniverse_Class;
struct CLDataList;
struct CLDataList_Class;
struct GLTexturePixelText;
struct GLTexturePixelText_Class;
struct GLDrawable;
struct GLDrawable_Class;
struct GLVertexBuffer;
struct GLVertexBuffer_Class;
struct PLVector;
struct PLVector_Class;
struct CLObject;
struct CLObject_Class;
struct GLDrawablePT22;
struct GLDrawablePT22_Class;
struct GLShader;
struct GLShader_Class;
struct TLPixelText;
struct TLPixelText_Class;
struct GLBitmap;
struct GLBitmap_Class;
struct GLBitmapPixelText;
struct GLBitmapPixelText_Class;
struct GLTexture;
struct GLTexture_Class;
struct GLVertexBlock;
struct GLVertexBlock_Class;
struct TLPixelFont;
struct TLPixelFont_Class;
struct CLString;
struct CLString_Class;
struct Controller
{
	struct Controller_Class* _class;
	void** _components;
	float contextWidth ; 
	float contextHeight ; 
	struct ShaderP2 * simpleShader ; 
	struct ShaderPT22 * textureShader ; 
	struct GLVertexBuffer * simpleVertexBuffer ; 
	struct GLVertexBuffer * textureVertexBuffer ; 
	GLint simplePMLocation ; 
	GLint texturePMLocation ; 
	GLKMatrix4 projectionMatrix ; 
	char showButtons ; 
	struct CLDataList * buttons ; 
	struct CLDataList * textures ; 
	struct PLUniverse * universe ; 
	struct Scene * scene ; 
	
};
struct Controller_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct Controller*, float  , float  ) ;
	void 	(*destruct) (struct Controller* ) ;
	void 	(*render) (struct Controller* ) ;
	void 	(*updateScene) (struct Controller* ) ;
	void 	(*setupScene) (struct Controller* ) ;
	void 	(*openSceneWithId) (struct Controller*, unsigned char  ) ;
	void 	(*addScene) (struct Controller* ) ;
	void 	(*removeScene) (struct Controller* ) ;
	void 	(*buttonPressed) (struct Controller*, float  , float  ) ;
	
};
struct PLMass
{
	struct PLMass_Class* _class;
	void** _components;
	char hadCollision ; 
	float friction ; 
	float buoyancy ; 
	struct PLVector * force ; 
	struct PLVector * position ; 
	struct PLVector * collision ; 
	struct CLDataList * baseWalls ; 
	struct CLDataList * touchedWalls ; 
	struct CLDataList * lastTouchedWalls ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct PLMass_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct PLMass* ) ;
	void 	(*destruct) (struct PLMass* ) ;
	void 	(*describe) (struct PLMass* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct PLMass* ) ;
	void 	(*destruct_CLObject) (struct PLMass* ) ;
	void 	(*retain) (struct PLMass* ) ;
	void 	(*release) (struct PLMass* ) ;
	void 	(*describe_CLObject) (struct PLMass* ) ;
	
};
struct PLSpacer
{
	struct PLSpacer_Class* _class;
	void** _components;
	struct PLMass * massA ; 
	struct PLMass * massB ; 
	float space ; 
	struct PLVector * respaceVectorA ; 
	struct PLVector * respaceVectorB ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct PLSpacer_Class
{
	char* className;
	void* classId;
	void 	(*initWithMasses) (struct PLSpacer*, struct PLMass *  , struct PLMass *  ) ;
	void 	(*destruct) (struct PLSpacer* ) ;
	void 	(*respace) (struct PLSpacer* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct PLSpacer* ) ;
	void 	(*destruct_CLObject) (struct PLSpacer* ) ;
	void 	(*retain) (struct PLSpacer* ) ;
	void 	(*release) (struct PLSpacer* ) ;
	void 	(*describe) (struct PLSpacer* ) ;
	
};
struct PLSegment
{
	struct PLSegment_Class* _class;
	void** _components;
	float A ; 
	float B ; 
	float C ; 
	float r ; 
	float a ; 
	float centerX ; 
	float centerY ; 
	float friction ; 
	struct PLVector * pointA ; 
	struct PLVector * pointB ; 
	struct PLVector * normForce ; 
	struct PLVector * paraForce ; 
	struct PLVector * wallVector ; 
	struct PLVector * forceEnding ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct PLSegment_Class
{
	char* className;
	void* classId;
	void 	(*initWithVectors) (struct PLSegment*, struct PLVector *  , struct PLVector *  ) ;
	void 	(*destruct) (struct PLSegment* ) ;
	void 	(*collideMass) (struct PLSegment*, struct PLMass *  , struct CLDataList *  , struct CLDataList *  , struct CLDataList *  ) ;
	void 	(*slideMass) (struct PLSegment*, struct PLMass *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct PLSegment* ) ;
	void 	(*destruct_CLObject) (struct PLSegment* ) ;
	void 	(*retain) (struct PLSegment* ) ;
	void 	(*release) (struct PLSegment* ) ;
	void 	(*describe) (struct PLSegment* ) ;
	
};
struct Scene
{
	struct Scene_Class* _class;
	void** _components;
	struct CLDataList * masses ; 
	struct CLDataList * spacers ; 
	struct CLDataList * segments ; 
	struct CLDataList * glPoints ; 
	struct CLDataList * glSegments ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Scene_Class
{
	char* className;
	void* classId;
	void 	(*initWithDimensions) (struct Scene*, float  , float  ) ;
	void 	(*destruct) (struct Scene* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct Scene* ) ;
	void 	(*destruct_CLObject) (struct Scene* ) ;
	void 	(*retain) (struct Scene* ) ;
	void 	(*release) (struct Scene* ) ;
	void 	(*describe) (struct Scene* ) ;
	
};
struct ScenePit
{
	struct ScenePit_Class* _class;
	void** _components;
	struct Scene_Class* _class_Scene;
	void** _components_Scene;
	struct CLDataList * masses ; 
	struct CLDataList * spacers ; 
	struct CLDataList * segments ; 
	struct CLDataList * glPoints ; 
	struct CLDataList * glSegments ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct ScenePit_Class
{
	char* className;
	void* classId;
	void 	(*initWithDimensions) (struct ScenePit*, float  , float  ) ;
	char* className_Scene;
	void* classId_Scene;
	void 	(*initWithDimensions_Scene) (struct ScenePit*, float  , float  ) ;
	void 	(*destruct) (struct ScenePit* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct ScenePit* ) ;
	void 	(*destruct_CLObject) (struct ScenePit* ) ;
	void 	(*retain) (struct ScenePit* ) ;
	void 	(*release) (struct ScenePit* ) ;
	void 	(*describe) (struct ScenePit* ) ;
	
};
struct SceneBox
{
	struct SceneBox_Class* _class;
	void** _components;
	struct Scene_Class* _class_Scene;
	void** _components_Scene;
	struct CLDataList * masses ; 
	struct CLDataList * spacers ; 
	struct CLDataList * segments ; 
	struct CLDataList * glPoints ; 
	struct CLDataList * glSegments ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct SceneBox_Class
{
	char* className;
	void* classId;
	void 	(*initWithDimensions) (struct SceneBox*, float  , float  ) ;
	char* className_Scene;
	void* classId_Scene;
	void 	(*initWithDimensions_Scene) (struct SceneBox*, float  , float  ) ;
	void 	(*destruct) (struct SceneBox* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct SceneBox* ) ;
	void 	(*destruct_CLObject) (struct SceneBox* ) ;
	void 	(*retain) (struct SceneBox* ) ;
	void 	(*release) (struct SceneBox* ) ;
	void 	(*describe) (struct SceneBox* ) ;
	
};
struct SceneSlope
{
	struct SceneSlope_Class* _class;
	void** _components;
	struct Scene_Class* _class_Scene;
	void** _components_Scene;
	struct CLDataList * masses ; 
	struct CLDataList * spacers ; 
	struct CLDataList * segments ; 
	struct CLDataList * glPoints ; 
	struct CLDataList * glSegments ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct SceneSlope_Class
{
	char* className;
	void* classId;
	void 	(*initWithDimensions) (struct SceneSlope*, float  , float  ) ;
	char* className_Scene;
	void* classId_Scene;
	void 	(*initWithDimensions_Scene) (struct SceneSlope*, float  , float  ) ;
	void 	(*destruct) (struct SceneSlope* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct SceneSlope* ) ;
	void 	(*destruct_CLObject) (struct SceneSlope* ) ;
	void 	(*retain) (struct SceneSlope* ) ;
	void 	(*release) (struct SceneSlope* ) ;
	void 	(*describe) (struct SceneSlope* ) ;
	
};
struct SceneParticle
{
	struct SceneParticle_Class* _class;
	void** _components;
	struct Scene_Class* _class_Scene;
	void** _components_Scene;
	struct CLDataList * masses ; 
	struct CLDataList * spacers ; 
	struct CLDataList * segments ; 
	struct CLDataList * glPoints ; 
	struct CLDataList * glSegments ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct SceneParticle_Class
{
	char* className;
	void* classId;
	void 	(*initWithDimensions) (struct SceneParticle*, float  , float  ) ;
	char* className_Scene;
	void* classId_Scene;
	void 	(*initWithDimensions_Scene) (struct SceneParticle*, float  , float  ) ;
	void 	(*destruct) (struct SceneParticle* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct SceneParticle* ) ;
	void 	(*destruct_CLObject) (struct SceneParticle* ) ;
	void 	(*retain) (struct SceneParticle* ) ;
	void 	(*release) (struct SceneParticle* ) ;
	void 	(*describe) (struct SceneParticle* ) ;
	
};
struct GLPointP2
{
	struct GLPointP2_Class* _class;
	void** _components;
	struct GLDrawable_Class* _class_GLDrawable;
	void** _components_GLDrawable;
	GLuint mode ; 
	GLuint texture ; 
	GLfloat * vertexes ; 
	GLsizei vertexCount ; 
	long vertexesSize ; 
	GLushort * indexes ; 
	GLsizei indexCount ; 
	long indexesSize ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLPointP2_Class
{
	char* className;
	void* classId;
	void 	(*initWithPoints) (struct GLPointP2*, GLfloat  , GLfloat  ) ;
	char* className_GLDrawable;
	void* classId_GLDrawable;
	void 	(*init) (struct GLPointP2* ) ;
	void 	(*destruct) (struct GLPointP2* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLPointP2* ) ;
	void 	(*destruct_CLObject) (struct GLPointP2* ) ;
	void 	(*retain) (struct GLPointP2* ) ;
	void 	(*release) (struct GLPointP2* ) ;
	void 	(*describe) (struct GLPointP2* ) ;
	
};
struct GLRectPT22
{
	struct GLRectPT22_Class* _class;
	void** _components;
	struct GLDrawablePT22_Class* _class_GLDrawablePT22;
	void** _components_GLDrawablePT22;
	float dx ; 
	float dy ; 
	float sx ; 
	float sy ; 
	struct GLDrawable_Class* _class_GLDrawable;
	void** _components_GLDrawable;
	GLuint mode ; 
	GLuint texture ; 
	GLfloat * vertexes ; 
	GLsizei vertexCount ; 
	long vertexesSize ; 
	GLushort * indexes ; 
	GLsizei indexCount ; 
	long indexesSize ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLRectPT22_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLRectPT22*, GLuint  ) ;
	void 	(*flipTexture) (struct GLRectPT22* ) ;
	void 	(*destruct) (struct GLRectPT22* ) ;
	char 	(*contains) (struct GLRectPT22*, float  , float  ) ;
	char* className_GLDrawablePT22;
	void* classId_GLDrawablePT22;
	void 	(*init_GLDrawablePT22) (struct GLRectPT22*, GLuint  ) ;
	void 	(*destruct_GLDrawablePT22) (struct GLRectPT22* ) ;
	void 	(*origo) (struct GLRectPT22*, float  , float  ) ;
	void 	(*move) (struct GLRectPT22*, float  , float  ) ;
	void 	(*scale) (struct GLRectPT22*, float  , float  ) ;
	char* className_GLDrawable;
	void* classId_GLDrawable;
	void 	(*init_GLDrawable) (struct GLRectPT22*, GLuint  ) ;
	void 	(*destruct_GLDrawable) (struct GLRectPT22* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLRectPT22*, GLuint  ) ;
	void 	(*destruct_CLObject) (struct GLRectPT22* ) ;
	void 	(*retain) (struct GLRectPT22* ) ;
	void 	(*release) (struct GLRectPT22* ) ;
	void 	(*describe) (struct GLRectPT22* ) ;
	
};
struct ShaderP2
{
	struct ShaderP2_Class* _class;
	void** _components;
	struct GLShader * shader ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct ShaderP2_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct ShaderP2* ) ;
	void 	(*destruct) (struct ShaderP2* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct ShaderP2* ) ;
	void 	(*destruct_CLObject) (struct ShaderP2* ) ;
	void 	(*retain) (struct ShaderP2* ) ;
	void 	(*release) (struct ShaderP2* ) ;
	void 	(*describe) (struct ShaderP2* ) ;
	
};
struct GLSegment
{
	struct GLSegment_Class* _class;
	void** _components;
	struct GLDrawable_Class* _class_GLDrawable;
	void** _components_GLDrawable;
	GLuint mode ; 
	GLuint texture ; 
	GLfloat * vertexes ; 
	GLsizei vertexCount ; 
	long vertexesSize ; 
	GLushort * indexes ; 
	GLsizei indexCount ; 
	long indexesSize ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLSegment_Class
{
	char* className;
	void* classId;
	void 	(*initWithPoints) (struct GLSegment*, GLfloat  , GLfloat  , GLfloat  , GLfloat  ) ;
	char* className_GLDrawable;
	void* classId_GLDrawable;
	void 	(*init) (struct GLSegment* ) ;
	void 	(*destruct) (struct GLSegment* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLSegment* ) ;
	void 	(*destruct_CLObject) (struct GLSegment* ) ;
	void 	(*retain) (struct GLSegment* ) ;
	void 	(*release) (struct GLSegment* ) ;
	void 	(*describe) (struct GLSegment* ) ;
	
};
struct ShaderPT22
{
	struct ShaderPT22_Class* _class;
	void** _components;
	struct GLShader * shader ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct ShaderPT22_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct ShaderPT22* ) ;
	void 	(*destruct) (struct ShaderPT22* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct ShaderPT22* ) ;
	void 	(*destruct_CLObject) (struct ShaderPT22* ) ;
	void 	(*retain) (struct ShaderPT22* ) ;
	void 	(*release) (struct ShaderPT22* ) ;
	void 	(*describe) (struct ShaderPT22* ) ;
	
};
struct PLUniverse
{
	struct PLUniverse_Class* _class;
	void** _components;
	struct CLDataList * walls ; 
	struct CLDataList * masses ; 
	struct CLDataList * spacers ; 
	struct PLVector * gravity ; 
	struct PLVector * bounceMassNormal ; 
	struct PLVector * bounceMassParallel ; 
	struct CLDataList * collidingWallsPerStep ; 
	struct CLDataList * collidingNormalsPerStep ; 
	struct CLDataList * collidingParallelsPerStep ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct PLUniverse_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct PLUniverse* ) ;
	void 	(*destruct) (struct PLUniverse* ) ;
	void 	(*reset) (struct PLUniverse* ) ;
	void 	(*addMass) (struct PLUniverse*, struct PLMass *  ) ;
	void 	(*removeMass) (struct PLUniverse*, struct PLMass *  ) ;
	void 	(*addWall) (struct PLUniverse*, struct PLSegment *  ) ;
	void 	(*removeWall) (struct PLUniverse*, struct PLSegment *  ) ;
	void 	(*addSpacer) (struct PLUniverse*, struct PLSpacer *  ) ;
	void 	(*removeSpacer) (struct PLUniverse*, struct PLSpacer *  ) ;
	void 	(*update) (struct PLUniverse* ) ;
	char 	(*bounceMass) (struct PLUniverse*, struct PLMass *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct PLUniverse* ) ;
	void 	(*destruct_CLObject) (struct PLUniverse* ) ;
	void 	(*retain) (struct PLUniverse* ) ;
	void 	(*release) (struct PLUniverse* ) ;
	void 	(*describe) (struct PLUniverse* ) ;
	
};
struct CLDataList
{
	struct CLDataList_Class* _class;
	void** _components;
	struct CLLink * head ; 
	struct CLLink * last ; 
	unsigned long length ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct CLDataList_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct CLDataList* ) ;
	void 	(*destruct) (struct CLDataList* ) ;
	void 	(*addData) (struct CLDataList*, void *  ) ;
	void 	(*addDataAtIndex) (struct CLDataList*, void *  , unsigned long  ) ;
	void 	(*addDatasInDataList) (struct CLDataList*, struct CLDataList *  ) ;
	void 	(*removeData) (struct CLDataList*, void *  ) ;
	void * 	(*removeDataAtIndex) (struct CLDataList*, unsigned long  ) ;
	void 	(*removeAllDatas) (struct CLDataList* ) ;
	void * 	(*dataAtIndex) (struct CLDataList*, unsigned long  ) ;
	char 	(*containsData) (struct CLDataList*, void *  ) ;
	unsigned long 	(*indexOfData) (struct CLDataList*, void *  ) ;
	void * 	(*firstData) (struct CLDataList* ) ;
	void * 	(*lastData) (struct CLDataList* ) ;
	void 	(*describe) (struct CLDataList* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct CLDataList* ) ;
	void 	(*destruct_CLObject) (struct CLDataList* ) ;
	void 	(*retain) (struct CLDataList* ) ;
	void 	(*release) (struct CLDataList* ) ;
	void 	(*describe_CLObject) (struct CLDataList* ) ;
	
};
struct GLTexturePixelText
{
	struct GLTexturePixelText_Class* _class;
	void** _components;
	struct GLTexture_Class* _class_GLTexture;
	void** _components_GLTexture;
	GLuint glid ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLTexturePixelText_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLTexturePixelText*, char *  , int  , int  , int  ) ;
	char* className_GLTexture;
	void* classId_GLTexture;
	void 	(*initWithGLBitmap) (struct GLTexturePixelText*, struct GLBitmap *  ) ;
	void 	(*initWithDimensions) (struct GLTexturePixelText*, int  , int  ) ;
	void 	(*destruct) (struct GLTexturePixelText* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLTexturePixelText*, char *  , int  , int  , int  ) ;
	void 	(*destruct_CLObject) (struct GLTexturePixelText* ) ;
	void 	(*retain) (struct GLTexturePixelText* ) ;
	void 	(*release) (struct GLTexturePixelText* ) ;
	void 	(*describe) (struct GLTexturePixelText* ) ;
	
};
struct GLDrawable
{
	struct GLDrawable_Class* _class;
	void** _components;
	GLuint mode ; 
	GLuint texture ; 
	GLfloat * vertexes ; 
	GLsizei vertexCount ; 
	long vertexesSize ; 
	GLushort * indexes ; 
	GLsizei indexCount ; 
	long indexesSize ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLDrawable_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLDrawable* ) ;
	void 	(*destruct) (struct GLDrawable* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLDrawable* ) ;
	void 	(*destruct_CLObject) (struct GLDrawable* ) ;
	void 	(*retain) (struct GLDrawable* ) ;
	void 	(*release) (struct GLDrawable* ) ;
	void 	(*describe) (struct GLDrawable* ) ;
	
};
struct GLVertexBuffer
{
	struct GLVertexBuffer_Class* _class;
	void** _components;
	GLfloat * data ; 
	GLuint buffer ; 
	struct CLDataList * blocks ; 
	long oldSize ; 
	char changed ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLVertexBuffer_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLVertexBuffer* ) ;
	void 	(*destruct) (struct GLVertexBuffer* ) ;
	void 	(*bindBuffer) (struct GLVertexBuffer* ) ;
	void 	(*drawBuffer) (struct GLVertexBuffer* ) ;
	void 	(*addDrawables) (struct GLVertexBuffer*, struct CLDataList *  ) ;
	void 	(*addDrawable) (struct GLVertexBuffer*, struct GLDrawable *  ) ;
	void 	(*removeDrawables) (struct GLVertexBuffer*, struct CLDataList *  ) ;
	void 	(*removeDrawable) (struct GLVertexBuffer*, struct GLDrawable *  ) ;
	void 	(*updateBuffers) (struct GLVertexBuffer* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLVertexBuffer* ) ;
	void 	(*destruct_CLObject) (struct GLVertexBuffer* ) ;
	void 	(*retain) (struct GLVertexBuffer* ) ;
	void 	(*release) (struct GLVertexBuffer* ) ;
	void 	(*describe) (struct GLVertexBuffer* ) ;
	
};
struct PLVector
{
	struct PLVector_Class* _class;
	void** _components;
	float x ; 
	float y ; 
	float angle ; 
	float length ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct PLVector_Class
{
	char* className;
	void* classId;
	void 	(*initWithPoints) (struct PLVector*, float  , float  ) ;
	void 	(*set) (struct PLVector*, struct PLVector *  ) ;
	void 	(*setXY) (struct PLVector*, float  , float  ) ;
	void 	(*reset) (struct PLVector* ) ;
	void 	(*multiply) (struct PLVector*, float  ) ;
	void 	(*addVector) (struct PLVector*, struct PLVector *  ) ;
	void 	(*describe) (struct PLVector* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct PLVector* ) ;
	void 	(*destruct) (struct PLVector* ) ;
	void 	(*retain) (struct PLVector* ) ;
	void 	(*release) (struct PLVector* ) ;
	void 	(*describe_CLObject) (struct PLVector* ) ;
	
};
struct CLObject
{
	struct CLObject_Class* _class;
	void** _components;
	unsigned long retainCount ; 
	
};
struct CLObject_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct CLObject* ) ;
	void 	(*destruct) (struct CLObject* ) ;
	void 	(*retain) (struct CLObject* ) ;
	void 	(*release) (struct CLObject* ) ;
	void 	(*describe) (struct CLObject* ) ;
	
};
struct GLDrawablePT22
{
	struct GLDrawablePT22_Class* _class;
	void** _components;
	float dx ; 
	float dy ; 
	float sx ; 
	float sy ; 
	struct GLDrawable_Class* _class_GLDrawable;
	void** _components_GLDrawable;
	GLuint mode ; 
	GLuint texture ; 
	GLfloat * vertexes ; 
	GLsizei vertexCount ; 
	long vertexesSize ; 
	GLushort * indexes ; 
	GLsizei indexCount ; 
	long indexesSize ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLDrawablePT22_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLDrawablePT22* ) ;
	void 	(*destruct) (struct GLDrawablePT22* ) ;
	void 	(*origo) (struct GLDrawablePT22*, float  , float  ) ;
	void 	(*move) (struct GLDrawablePT22*, float  , float  ) ;
	void 	(*scale) (struct GLDrawablePT22*, float  , float  ) ;
	char* className_GLDrawable;
	void* classId_GLDrawable;
	void 	(*init_GLDrawable) (struct GLDrawablePT22* ) ;
	void 	(*destruct_GLDrawable) (struct GLDrawablePT22* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLDrawablePT22* ) ;
	void 	(*destruct_CLObject) (struct GLDrawablePT22* ) ;
	void 	(*retain) (struct GLDrawablePT22* ) ;
	void 	(*release) (struct GLDrawablePT22* ) ;
	void 	(*describe) (struct GLDrawablePT22* ) ;
	
};
struct GLShader
{
	struct GLShader_Class* _class;
	void** _components;
	char * name ; 
	GLuint program ; 
	GLuint vertexShader ; 
	GLuint fragmentShader ; 
	GLuint uniformCounter ; 
	GLint * uniformLocations ; 
	const char * * uniformIdentifiers ; 
	int attributeStride ; 
	GLuint attributeCounter ; 
	GLuint * attributeLocations ; 
	int * attributeComponents ; 
	const char * * attributeIdentifiers ; 
	long * attributeOffsetSizes ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLShader_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLShader*, char *  ) ;
	void 	(*destruct) (struct GLShader* ) ;
	void 	(*addVertexShader) (struct GLShader*, const GLchar *  ) ;
	void 	(*addFragmentShader) (struct GLShader*, const GLchar *  ) ;
	void 	(*addAttributeLocation) (struct GLShader*, GLuint  , int  , const char *  ) ;
	void 	(*addUniformIdentifier) (struct GLShader*, const char *  ) ;
	GLint 	(*getUniformLocation) (struct GLShader*, const char *  ) ;
	void 	(*link) (struct GLShader* ) ;
	char 	(*compileShader) (struct GLShader*, GLuint *  , GLenum  , const GLchar *  ) ;
	char 	(*linkProgram) (struct GLShader* ) ;
	void 	(*activate) (struct GLShader* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLShader*, char *  ) ;
	void 	(*destruct_CLObject) (struct GLShader* ) ;
	void 	(*retain) (struct GLShader* ) ;
	void 	(*release) (struct GLShader* ) ;
	void 	(*describe) (struct GLShader* ) ;
	
};
struct TLPixelText
{
	struct TLPixelText_Class* _class;
	void** _components;
	struct CLDataList * letters ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct TLPixelText_Class
{
	char* className;
	void* classId;
	void 	(*initWithString) (struct TLPixelText*, struct CLString *  ) ;
	void 	(*initWithCString) (struct TLPixelText*, char *  ) ;
	void 	(*destruct) (struct TLPixelText* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct TLPixelText* ) ;
	void 	(*destruct_CLObject) (struct TLPixelText* ) ;
	void 	(*retain) (struct TLPixelText* ) ;
	void 	(*release) (struct TLPixelText* ) ;
	void 	(*describe) (struct TLPixelText* ) ;
	
};
struct GLBitmap
{
	struct GLBitmap_Class* _class;
	void** _components;
	unsigned char * data ; 
	int length ; 
	int width ; 
	int height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLBitmap_Class
{
	char* className;
	void* classId;
	void 	(*initWithDimensions) (struct GLBitmap*, int  , int  ) ;
	void 	(*destruct) (struct GLBitmap* ) ;
	void 	(*fillRectangle) (struct GLBitmap*, int  , int  , int  , int  , float  , float  , float  , float  ) ;
	void 	(*setPixel) (struct GLBitmap*, int  , int  , int  , int  , int  , int  ) ;
	void 	(*getPixel) (struct GLBitmap*, int  , int  , int *  , int *  , int *  , int *  ) ;
	void 	(*addShadow) (struct GLBitmap* ) ;
	void 	(*blendBitmap) (struct GLBitmap*, struct GLBitmap *  , int  , int  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct GLBitmap* ) ;
	void 	(*destruct_CLObject) (struct GLBitmap* ) ;
	void 	(*retain) (struct GLBitmap* ) ;
	void 	(*release) (struct GLBitmap* ) ;
	void 	(*describe) (struct GLBitmap* ) ;
	
};
struct GLBitmapPixelText
{
	struct GLBitmapPixelText_Class* _class;
	void** _components;
	struct GLBitmap_Class* _class_GLBitmap;
	void** _components_GLBitmap;
	unsigned char * data ; 
	int length ; 
	int width ; 
	int height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLBitmapPixelText_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLBitmapPixelText*, char *  , int  , int  ) ;
	void 	(*destruct) (struct GLBitmapPixelText* ) ;
	void 	(*drawPixelTextWithSize) (struct GLBitmapPixelText*, struct TLPixelText *  , float  ) ;
	char* className_GLBitmap;
	void* classId_GLBitmap;
	void 	(*initWithDimensions) (struct GLBitmapPixelText*, int  , int  ) ;
	void 	(*destruct_GLBitmap) (struct GLBitmapPixelText* ) ;
	void 	(*fillRectangle) (struct GLBitmapPixelText*, int  , int  , int  , int  , float  , float  , float  , float  ) ;
	void 	(*setPixel) (struct GLBitmapPixelText*, int  , int  , int  , int  , int  , int  ) ;
	void 	(*getPixel) (struct GLBitmapPixelText*, int  , int  , int *  , int *  , int *  , int *  ) ;
	void 	(*addShadow) (struct GLBitmapPixelText* ) ;
	void 	(*blendBitmap) (struct GLBitmapPixelText*, struct GLBitmap *  , int  , int  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLBitmapPixelText*, char *  , int  , int  ) ;
	void 	(*destruct_CLObject) (struct GLBitmapPixelText* ) ;
	void 	(*retain) (struct GLBitmapPixelText* ) ;
	void 	(*release) (struct GLBitmapPixelText* ) ;
	void 	(*describe) (struct GLBitmapPixelText* ) ;
	
};
struct GLTexture
{
	struct GLTexture_Class* _class;
	void** _components;
	GLuint glid ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLTexture_Class
{
	char* className;
	void* classId;
	void 	(*initWithGLBitmap) (struct GLTexture*, struct GLBitmap *  ) ;
	void 	(*initWithDimensions) (struct GLTexture*, int  , int  ) ;
	void 	(*destruct) (struct GLTexture* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct GLTexture* ) ;
	void 	(*destruct_CLObject) (struct GLTexture* ) ;
	void 	(*retain) (struct GLTexture* ) ;
	void 	(*release) (struct GLTexture* ) ;
	void 	(*describe) (struct GLTexture* ) ;
	
};
struct GLVertexBlock
{
	struct GLVertexBlock_Class* _class;
	void** _components;
	GLuint mode ; 
	GLuint texture ; 
	GLushort * indexes ; 
	GLsizei indexCount ; 
	long oldIndexesSize ; 
	long indexesSize ; 
	GLsizei vertexCount ; 
	long vertexesSize ; 
	struct CLDataList * drawables ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct GLVertexBlock_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct GLVertexBlock* ) ;
	void 	(*destruct) (struct GLVertexBlock* ) ;
	void 	(*describe) (struct GLVertexBlock* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct GLVertexBlock* ) ;
	void 	(*destruct_CLObject) (struct GLVertexBlock* ) ;
	void 	(*retain) (struct GLVertexBlock* ) ;
	void 	(*release) (struct GLVertexBlock* ) ;
	void 	(*describe_CLObject) (struct GLVertexBlock* ) ;
	
};
struct TLPixelFont
{
	struct TLPixelFont_Class* _class;
	void** _components;
	float * data ; 
	int length ; 
	char character ; 
	float width ; 
	float height ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct TLPixelFont_Class
{
	char* className;
	void* classId;
	void 	(*initWithCharacter) (struct TLPixelFont*, char  ) ;
	void 	(*destruct) (struct TLPixelFont* ) ;
	const char * 	(*getPattern) (struct TLPixelFont*, char  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct TLPixelFont* ) ;
	void 	(*destruct_CLObject) (struct TLPixelFont* ) ;
	void 	(*retain) (struct TLPixelFont* ) ;
	void 	(*release) (struct TLPixelFont* ) ;
	void 	(*describe) (struct TLPixelFont* ) ;
	
};
struct CLString
{
	struct CLString_Class* _class;
	void** _components;
	struct CLChar * head ; 
	struct CLChar * last ; 
	unsigned long length ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct CLString_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct CLString* ) ;
	void 	(*initWithString) (struct CLString*, struct CLString *  ) ;
	void 	(*initWithCString) (struct CLString*, char *  ) ;
	void 	(*destruct) (struct CLString* ) ;
	void 	(*appendCharacter) (struct CLString*, char  ) ;
	void 	(*appendString) (struct CLString*, struct CLString *  ) ;
	void 	(*appendCString) (struct CLString*, char *  ) ;
	void 	(*removeAllCharacters) (struct CLString* ) ;
	void 	(*readFile) (struct CLString*, struct CLString *  ) ;
	void 	(*readFilePointer) (struct CLString*, FILE *  ) ;
	void 	(*writeToFile) (struct CLString*, struct CLString *  ) ;
	void 	(*writeToFilePointer) (struct CLString*, FILE *  ) ;
	struct CLString * 	(*stringWithLastPathComponent) (struct CLString* ) ;
	struct CLString * 	(*stringByRemovingExtension) (struct CLString* ) ;
	struct CLString * 	(*stringByRemovingLastPathComponent) (struct CLString* ) ;
	char 	(*containsString) (struct CLString*, struct CLString *  ) ;
	unsigned long 	(*indexOfString) (struct CLString*, struct CLString *  ) ;
	char 	(*equals) (struct CLString*, struct CLString *  ) ;
	char * 	(*cString) (struct CLString* ) ;
	void 	(*describe) (struct CLString* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct CLString* ) ;
	void 	(*destruct_CLObject) (struct CLString* ) ;
	void 	(*retain) (struct CLString* ) ;
	void 	(*release) (struct CLString* ) ;
	void 	(*describe_CLObject) (struct CLString* ) ;
	
};
void* cast_object( void* theObject , void* theId );
void  free_object( void* theObject );
void Controller_CreateClass( );
struct Controller* Controller_alloc( );
void Controller_init (struct Controller* self, float theContextWidth , float theContextHeight ) ;
void Controller_destruct (struct Controller* self ) ;
void Controller_render (struct Controller* self ) ;
void Controller_updateScene (struct Controller* self ) ;
void Controller_setupScene (struct Controller* self ) ;
void Controller_openSceneWithId (struct Controller* self, unsigned char theId ) ;
void Controller_addScene (struct Controller* self ) ;
void Controller_removeScene (struct Controller* self ) ;
void Controller_buttonPressed (struct Controller* self, float theX , float theY ) ;
void PLMass_CreateClass( );
struct PLMass* PLMass_alloc( );
void PLMass_init (struct PLMass* self ) ;
void PLMass_destruct (struct PLMass* self ) ;
void PLMass_describe (struct PLMass* self ) ;
void PLMass_retain (struct PLMass* self ) ;
void PLMass_release (struct PLMass* self ) ;
void PLSpacer_CreateClass( );
struct PLSpacer* PLSpacer_alloc( );
void PLSpacer_initWithMasses (struct PLSpacer* self, struct PLMass * theMassA , struct PLMass * theMassB ) ;
void PLSpacer_destruct (struct PLSpacer* self ) ;
void PLSpacer_respace (struct PLSpacer* self ) ;
void PLSpacer_init (struct PLSpacer* self ) ;
void PLSpacer_retain (struct PLSpacer* self ) ;
void PLSpacer_release (struct PLSpacer* self ) ;
void PLSpacer_describe (struct PLSpacer* self ) ;
void PLSegment_CreateClass( );
struct PLSegment* PLSegment_alloc( );
void PLSegment_initWithVectors (struct PLSegment* self, struct PLVector * thePointA , struct PLVector * thePointB ) ;
void PLSegment_destruct (struct PLSegment* self ) ;
void PLSegment_collideMass (struct PLSegment* self, struct PLMass * theMass , struct CLDataList * theCollidingWallsPerStep , struct CLDataList * theCollidingNormalsPerStep , struct CLDataList * theCollidingParallelsPerStep ) ;
void PLSegment_slideMass (struct PLSegment* self, struct PLMass * theMass ) ;
void PLSegment_init (struct PLSegment* self ) ;
void PLSegment_retain (struct PLSegment* self ) ;
void PLSegment_release (struct PLSegment* self ) ;
void PLSegment_describe (struct PLSegment* self ) ;
void Scene_CreateClass( );
struct Scene* Scene_alloc( );
void Scene_initWithDimensions (struct Scene* self, float theWidth , float theHeight ) ;
void Scene_destruct (struct Scene* self ) ;
void Scene_init (struct Scene* self ) ;
void Scene_retain (struct Scene* self ) ;
void Scene_release (struct Scene* self ) ;
void Scene_describe (struct Scene* self ) ;
void ScenePit_CreateClass( );
struct ScenePit* ScenePit_alloc( );
void ScenePit_initWithDimensions (struct ScenePit* self, float theWidth , float theHeight ) ;
void ScenePit_destruct (struct ScenePit* self ) ;
void ScenePit_init (struct ScenePit* self ) ;
void ScenePit_retain (struct ScenePit* self ) ;
void ScenePit_release (struct ScenePit* self ) ;
void ScenePit_describe (struct ScenePit* self ) ;
void SceneBox_CreateClass( );
struct SceneBox* SceneBox_alloc( );
void SceneBox_initWithDimensions (struct SceneBox* self, float theWidth , float theHeight ) ;
void SceneBox_destruct (struct SceneBox* self ) ;
void SceneBox_init (struct SceneBox* self ) ;
void SceneBox_retain (struct SceneBox* self ) ;
void SceneBox_release (struct SceneBox* self ) ;
void SceneBox_describe (struct SceneBox* self ) ;
void SceneSlope_CreateClass( );
struct SceneSlope* SceneSlope_alloc( );
void SceneSlope_initWithDimensions (struct SceneSlope* self, float theWidth , float theHeight ) ;
void SceneSlope_destruct (struct SceneSlope* self ) ;
void SceneSlope_init (struct SceneSlope* self ) ;
void SceneSlope_retain (struct SceneSlope* self ) ;
void SceneSlope_release (struct SceneSlope* self ) ;
void SceneSlope_describe (struct SceneSlope* self ) ;
void SceneParticle_CreateClass( );
struct SceneParticle* SceneParticle_alloc( );
void SceneParticle_initWithDimensions (struct SceneParticle* self, float theWidth , float theHeight ) ;
void SceneParticle_destruct (struct SceneParticle* self ) ;
void SceneParticle_init (struct SceneParticle* self ) ;
void SceneParticle_retain (struct SceneParticle* self ) ;
void SceneParticle_release (struct SceneParticle* self ) ;
void SceneParticle_describe (struct SceneParticle* self ) ;
void GLPointP2_CreateClass( );
struct GLPointP2* GLPointP2_alloc( );
void GLPointP2_initWithPoints (struct GLPointP2* self, GLfloat theX , GLfloat theY ) ;
void GLPointP2_init (struct GLPointP2* self ) ;
void GLPointP2_destruct (struct GLPointP2* self ) ;
void GLPointP2_retain (struct GLPointP2* self ) ;
void GLPointP2_release (struct GLPointP2* self ) ;
void GLPointP2_describe (struct GLPointP2* self ) ;
void GLRectPT22_CreateClass( );
struct GLRectPT22* GLRectPT22_alloc( );
void GLRectPT22_init (struct GLRectPT22* self, GLuint theTexture ) ;
void GLRectPT22_flipTexture (struct GLRectPT22* self ) ;
void GLRectPT22_destruct (struct GLRectPT22* self ) ;
char GLRectPT22_contains (struct GLRectPT22* self, float theX , float theY ) ;
void GLRectPT22_origo (struct GLRectPT22* self, float theX , float theY ) ;
void GLRectPT22_move (struct GLRectPT22* self, float theX , float theY ) ;
void GLRectPT22_scale (struct GLRectPT22* self, float theX , float theY ) ;
void GLRectPT22_retain (struct GLRectPT22* self ) ;
void GLRectPT22_release (struct GLRectPT22* self ) ;
void GLRectPT22_describe (struct GLRectPT22* self ) ;
void ShaderP2_CreateClass( );
struct ShaderP2* ShaderP2_alloc( );
void ShaderP2_init (struct ShaderP2* self ) ;
void ShaderP2_destruct (struct ShaderP2* self ) ;
void ShaderP2_retain (struct ShaderP2* self ) ;
void ShaderP2_release (struct ShaderP2* self ) ;
void ShaderP2_describe (struct ShaderP2* self ) ;
void GLSegment_CreateClass( );
struct GLSegment* GLSegment_alloc( );
void GLSegment_initWithPoints (struct GLSegment* self, GLfloat theAx , GLfloat theAy , GLfloat theBx , GLfloat theBy ) ;
void GLSegment_init (struct GLSegment* self ) ;
void GLSegment_destruct (struct GLSegment* self ) ;
void GLSegment_retain (struct GLSegment* self ) ;
void GLSegment_release (struct GLSegment* self ) ;
void GLSegment_describe (struct GLSegment* self ) ;
void ShaderPT22_CreateClass( );
struct ShaderPT22* ShaderPT22_alloc( );
void ShaderPT22_init (struct ShaderPT22* self ) ;
void ShaderPT22_destruct (struct ShaderPT22* self ) ;
void ShaderPT22_retain (struct ShaderPT22* self ) ;
void ShaderPT22_release (struct ShaderPT22* self ) ;
void ShaderPT22_describe (struct ShaderPT22* self ) ;
void PLUniverse_CreateClass( );
struct PLUniverse* PLUniverse_alloc( );
void PLUniverse_init (struct PLUniverse* self ) ;
void PLUniverse_destruct (struct PLUniverse* self ) ;
void PLUniverse_reset (struct PLUniverse* self ) ;
void PLUniverse_addMass (struct PLUniverse* self, struct PLMass * theMass ) ;
void PLUniverse_removeMass (struct PLUniverse* self, struct PLMass * theMass ) ;
void PLUniverse_addWall (struct PLUniverse* self, struct PLSegment * theWall ) ;
void PLUniverse_removeWall (struct PLUniverse* self, struct PLSegment * theWall ) ;
void PLUniverse_addSpacer (struct PLUniverse* self, struct PLSpacer * theSpacer ) ;
void PLUniverse_removeSpacer (struct PLUniverse* self, struct PLSpacer * theSpacer ) ;
void PLUniverse_update (struct PLUniverse* self ) ;
char PLUniverse_bounceMass (struct PLUniverse* self, struct PLMass * theMass ) ;
void PLUniverse_retain (struct PLUniverse* self ) ;
void PLUniverse_release (struct PLUniverse* self ) ;
void PLUniverse_describe (struct PLUniverse* self ) ;
void CLDataList_CreateClass( );
struct CLDataList* CLDataList_alloc( );
void CLDataList_init (struct CLDataList* self ) ;
void CLDataList_destruct (struct CLDataList* self ) ;
void CLDataList_addData (struct CLDataList* self, void * theData ) ;
void CLDataList_addDataAtIndex (struct CLDataList* self, void * theData , unsigned long theIndex ) ;
void CLDataList_addDatasInDataList (struct CLDataList* self, struct CLDataList * theDataList ) ;
void CLDataList_removeData (struct CLDataList* self, void * theData ) ;
void * CLDataList_removeDataAtIndex (struct CLDataList* self, unsigned long theIndex ) ;
void CLDataList_removeAllDatas (struct CLDataList* self ) ;
void * CLDataList_dataAtIndex (struct CLDataList* self, unsigned long theIndex ) ;
char CLDataList_containsData (struct CLDataList* self, void * theData ) ;
unsigned long CLDataList_indexOfData (struct CLDataList* self, void * theData ) ;
void * CLDataList_firstData (struct CLDataList* self ) ;
void * CLDataList_lastData (struct CLDataList* self ) ;
void CLDataList_describe (struct CLDataList* self ) ;
void CLDataList_retain (struct CLDataList* self ) ;
void CLDataList_release (struct CLDataList* self ) ;
void GLTexturePixelText_CreateClass( );
struct GLTexturePixelText* GLTexturePixelText_alloc( );
void GLTexturePixelText_init (struct GLTexturePixelText* self, char * theText , int theWidth , int theHeight , int theSize ) ;
void GLTexturePixelText_initWithGLBitmap (struct GLTexturePixelText* self, struct GLBitmap * theBitmap ) ;
void GLTexturePixelText_initWithDimensions (struct GLTexturePixelText* self, int theWidth , int theHeight ) ;
void GLTexturePixelText_destruct (struct GLTexturePixelText* self ) ;
void GLTexturePixelText_retain (struct GLTexturePixelText* self ) ;
void GLTexturePixelText_release (struct GLTexturePixelText* self ) ;
void GLTexturePixelText_describe (struct GLTexturePixelText* self ) ;
void GLDrawable_CreateClass( );
struct GLDrawable* GLDrawable_alloc( );
void GLDrawable_init (struct GLDrawable* self ) ;
void GLDrawable_destruct (struct GLDrawable* self ) ;
void GLDrawable_retain (struct GLDrawable* self ) ;
void GLDrawable_release (struct GLDrawable* self ) ;
void GLDrawable_describe (struct GLDrawable* self ) ;
void GLVertexBuffer_CreateClass( );
struct GLVertexBuffer* GLVertexBuffer_alloc( );
void GLVertexBuffer_init (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_destruct (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_bindBuffer (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_drawBuffer (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_addDrawables (struct GLVertexBuffer* self, struct CLDataList * theDrawables ) ;
void GLVertexBuffer_addDrawable (struct GLVertexBuffer* self, struct GLDrawable * theDrawable ) ;
void GLVertexBuffer_removeDrawables (struct GLVertexBuffer* self, struct CLDataList * theDrawables ) ;
void GLVertexBuffer_removeDrawable (struct GLVertexBuffer* self, struct GLDrawable * theDrawable ) ;
void GLVertexBuffer_updateBuffers (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_retain (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_release (struct GLVertexBuffer* self ) ;
void GLVertexBuffer_describe (struct GLVertexBuffer* self ) ;
void PLVector_CreateClass( );
struct PLVector* PLVector_alloc( );
void PLVector_initWithPoints (struct PLVector* self, float theX , float theY ) ;
void PLVector_set (struct PLVector* self, struct PLVector * theVector ) ;
void PLVector_setXY (struct PLVector* self, float theX , float theY ) ;
void PLVector_reset (struct PLVector* self ) ;
void PLVector_multiply (struct PLVector* self, float theValue ) ;
void PLVector_addVector (struct PLVector* self, struct PLVector * theVector ) ;
void PLVector_describe (struct PLVector* self ) ;
void PLVector_init (struct PLVector* self ) ;
void PLVector_destruct (struct PLVector* self ) ;
void PLVector_retain (struct PLVector* self ) ;
void PLVector_release (struct PLVector* self ) ;
void CLObject_CreateClass( );
struct CLObject* CLObject_alloc( );
void CLObject_init (struct CLObject* self ) ;
void CLObject_destruct (struct CLObject* self ) ;
void CLObject_retain (struct CLObject* self ) ;
void CLObject_release (struct CLObject* self ) ;
void CLObject_describe (struct CLObject* self ) ;
void GLDrawablePT22_CreateClass( );
struct GLDrawablePT22* GLDrawablePT22_alloc( );
void GLDrawablePT22_init (struct GLDrawablePT22* self ) ;
void GLDrawablePT22_destruct (struct GLDrawablePT22* self ) ;
void GLDrawablePT22_origo (struct GLDrawablePT22* self, float theX , float theY ) ;
void GLDrawablePT22_move (struct GLDrawablePT22* self, float theX , float theY ) ;
void GLDrawablePT22_scale (struct GLDrawablePT22* self, float theX , float theY ) ;
void GLDrawablePT22_retain (struct GLDrawablePT22* self ) ;
void GLDrawablePT22_release (struct GLDrawablePT22* self ) ;
void GLDrawablePT22_describe (struct GLDrawablePT22* self ) ;
void GLShader_CreateClass( );
struct GLShader* GLShader_alloc( );
void GLShader_init (struct GLShader* self, char * theName ) ;
void GLShader_destruct (struct GLShader* self ) ;
void GLShader_addVertexShader (struct GLShader* self, const GLchar * theSource ) ;
void GLShader_addFragmentShader (struct GLShader* self, const GLchar * theSource ) ;
void GLShader_addAttributeLocation (struct GLShader* self, GLuint theLocation , int theComponentCount , const char * theIdentifier ) ;
void GLShader_addUniformIdentifier (struct GLShader* self, const char * theIdentifier ) ;
GLint GLShader_getUniformLocation (struct GLShader* self, const char * theIdentifier ) ;
void GLShader_link (struct GLShader* self ) ;
char GLShader_compileShader (struct GLShader* self, GLuint * theShader , GLenum theType , const GLchar * theSource ) ;
char GLShader_linkProgram (struct GLShader* self ) ;
void GLShader_activate (struct GLShader* self ) ;
void GLShader_retain (struct GLShader* self ) ;
void GLShader_release (struct GLShader* self ) ;
void GLShader_describe (struct GLShader* self ) ;
void TLPixelText_CreateClass( );
struct TLPixelText* TLPixelText_alloc( );
void TLPixelText_initWithString (struct TLPixelText* self, struct CLString * theString ) ;
void TLPixelText_initWithCString (struct TLPixelText* self, char * theString ) ;
void TLPixelText_destruct (struct TLPixelText* self ) ;
void TLPixelText_init (struct TLPixelText* self ) ;
void TLPixelText_retain (struct TLPixelText* self ) ;
void TLPixelText_release (struct TLPixelText* self ) ;
void TLPixelText_describe (struct TLPixelText* self ) ;
void GLBitmap_CreateClass( );
struct GLBitmap* GLBitmap_alloc( );
void GLBitmap_initWithDimensions (struct GLBitmap* self, int theWidth , int theHeight ) ;
void GLBitmap_destruct (struct GLBitmap* self ) ;
void GLBitmap_fillRectangle (struct GLBitmap* self, int theX , int theY , int theWidth , int theHeight , float theR , float theG , float theB , float theA ) ;
void GLBitmap_setPixel (struct GLBitmap* self, int theX , int theY , int theR , int theG , int theB , int theA ) ;
void GLBitmap_getPixel (struct GLBitmap* self, int theX , int theY , int * theR , int * theG , int * theB , int * theA ) ;
void GLBitmap_addShadow (struct GLBitmap* self ) ;
void GLBitmap_blendBitmap (struct GLBitmap* self, struct GLBitmap * theBitmap , int theX , int theY ) ;
void GLBitmap_init (struct GLBitmap* self ) ;
void GLBitmap_retain (struct GLBitmap* self ) ;
void GLBitmap_release (struct GLBitmap* self ) ;
void GLBitmap_describe (struct GLBitmap* self ) ;
void GLBitmapPixelText_CreateClass( );
struct GLBitmapPixelText* GLBitmapPixelText_alloc( );
void GLBitmapPixelText_init (struct GLBitmapPixelText* self, char * theLabel , int theWidth , int theHeight ) ;
void GLBitmapPixelText_destruct (struct GLBitmapPixelText* self ) ;
void GLBitmapPixelText_drawPixelTextWithSize (struct GLBitmapPixelText* self, struct TLPixelText * theText , float theSize ) ;
void GLBitmapPixelText_initWithDimensions (struct GLBitmapPixelText* self, int theWidth , int theHeight ) ;
void GLBitmapPixelText_fillRectangle (struct GLBitmapPixelText* self, int theX , int theY , int theWidth , int theHeight , float theR , float theG , float theB , float theA ) ;
void GLBitmapPixelText_setPixel (struct GLBitmapPixelText* self, int theX , int theY , int theR , int theG , int theB , int theA ) ;
void GLBitmapPixelText_getPixel (struct GLBitmapPixelText* self, int theX , int theY , int * theR , int * theG , int * theB , int * theA ) ;
void GLBitmapPixelText_addShadow (struct GLBitmapPixelText* self ) ;
void GLBitmapPixelText_blendBitmap (struct GLBitmapPixelText* self, struct GLBitmap * theBitmap , int theX , int theY ) ;
void GLBitmapPixelText_retain (struct GLBitmapPixelText* self ) ;
void GLBitmapPixelText_release (struct GLBitmapPixelText* self ) ;
void GLBitmapPixelText_describe (struct GLBitmapPixelText* self ) ;
void GLTexture_CreateClass( );
struct GLTexture* GLTexture_alloc( );
void GLTexture_initWithGLBitmap (struct GLTexture* self, struct GLBitmap * theBitmap ) ;
void GLTexture_initWithDimensions (struct GLTexture* self, int theWidth , int theHeight ) ;
void GLTexture_destruct (struct GLTexture* self ) ;
void GLTexture_init (struct GLTexture* self ) ;
void GLTexture_retain (struct GLTexture* self ) ;
void GLTexture_release (struct GLTexture* self ) ;
void GLTexture_describe (struct GLTexture* self ) ;
void GLVertexBlock_CreateClass( );
struct GLVertexBlock* GLVertexBlock_alloc( );
void GLVertexBlock_init (struct GLVertexBlock* self ) ;
void GLVertexBlock_destruct (struct GLVertexBlock* self ) ;
void GLVertexBlock_describe (struct GLVertexBlock* self ) ;
void GLVertexBlock_retain (struct GLVertexBlock* self ) ;
void GLVertexBlock_release (struct GLVertexBlock* self ) ;
void TLPixelFont_CreateClass( );
struct TLPixelFont* TLPixelFont_alloc( );
void TLPixelFont_initWithCharacter (struct TLPixelFont* self, char theCharacter ) ;
void TLPixelFont_destruct (struct TLPixelFont* self ) ;
const char * TLPixelFont_getPattern (struct TLPixelFont* self, char theCharacter ) ;
void TLPixelFont_init (struct TLPixelFont* self ) ;
void TLPixelFont_retain (struct TLPixelFont* self ) ;
void TLPixelFont_release (struct TLPixelFont* self ) ;
void TLPixelFont_describe (struct TLPixelFont* self ) ;
void CLString_CreateClass( );
struct CLString* CLString_alloc( );
void CLString_init (struct CLString* self ) ;
void CLString_initWithString (struct CLString* self, struct CLString * theString ) ;
void CLString_initWithCString (struct CLString* self, char * theString ) ;
void CLString_destruct (struct CLString* self ) ;
void CLString_appendCharacter (struct CLString* self, char theCharacter ) ;
void CLString_appendString (struct CLString* self, struct CLString * theString ) ;
void CLString_appendCString (struct CLString* self, char * theString ) ;
void CLString_removeAllCharacters (struct CLString* self ) ;
void CLString_readFile (struct CLString* self, struct CLString * thePath ) ;
void CLString_readFilePointer (struct CLString* self, FILE * thePointer ) ;
void CLString_writeToFile (struct CLString* self, struct CLString * thePath ) ;
void CLString_writeToFilePointer (struct CLString* self, FILE * theFilePointer ) ;
struct CLString * CLString_stringWithLastPathComponent (struct CLString* self ) ;
struct CLString * CLString_stringByRemovingExtension (struct CLString* self ) ;
struct CLString * CLString_stringByRemovingLastPathComponent (struct CLString* self ) ;
char CLString_containsString (struct CLString* self, struct CLString * theString ) ;
unsigned long CLString_indexOfString (struct CLString* self, struct CLString * theSearchString ) ;
char CLString_equals (struct CLString* self, struct CLString * theStringB ) ;
char * CLString_cString (struct CLString* self ) ;
void CLString_describe (struct CLString* self ) ;
void CLString_retain (struct CLString* self ) ;
void CLString_release (struct CLString* self ) ;
#endif
