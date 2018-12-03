#include "clcsrc.h"
void* cast_object( void* theId , void* theObject )
{
	void**components;
	components=(((struct Instance*)theObject)->_components);
	while(*components!=NULL)
	{
		if (((struct Instance*)*components)->_class->classId==theId) return((void*)*components);
		components += 1;
	}
	#ifdef DEBUG
	components=(((struct Instance*)theObject)->_components);
	printf("\nClassId : %lx Not Found in ClassInstance : %s" , (long) theObject , ((struct Instance*)*components)->_class->className );

	#endif
	return NULL;
}
void free_object( void* theObject )
{
	struct Instance* instance;
	void*  original;
	void** pointer;
	void** components;
	instance   = theObject;
	original   = instance->_components[ 0 ];
	pointer    = &original;
	components = instance->_components;
	free( original );
	free( components );
	*pointer = NULL;
}
static struct Controller_Class* Controller_ClassInstance = NULL;
static struct PLMass_Class* PLMass_ClassInstance = NULL;
static struct PLSpacer_Class* PLSpacer_ClassInstance = NULL;
static struct PLSegment_Class* PLSegment_ClassInstance = NULL;
static struct Scene_Class* Scene_ClassInstance = NULL;
static struct ScenePit_Class* ScenePit_ClassInstance = NULL;
static struct SceneBox_Class* SceneBox_ClassInstance = NULL;
static struct SceneSlope_Class* SceneSlope_ClassInstance = NULL;
static struct SceneParticle_Class* SceneParticle_ClassInstance = NULL;
static struct GLPointP2_Class* GLPointP2_ClassInstance = NULL;
static struct GLRectPT22_Class* GLRectPT22_ClassInstance = NULL;
static struct ShaderP2_Class* ShaderP2_ClassInstance = NULL;
static struct GLSegment_Class* GLSegment_ClassInstance = NULL;
static struct ShaderPT22_Class* ShaderPT22_ClassInstance = NULL;
static struct PLUniverse_Class* PLUniverse_ClassInstance = NULL;
static struct CLDataList_Class* CLDataList_ClassInstance = NULL;
static struct GLTexturePixelText_Class* GLTexturePixelText_ClassInstance = NULL;
static struct GLDrawable_Class* GLDrawable_ClassInstance = NULL;
static struct GLVertexBuffer_Class* GLVertexBuffer_ClassInstance = NULL;
static struct PLVector_Class* PLVector_ClassInstance = NULL;
static struct CLObject_Class* CLObject_ClassInstance = NULL;
static struct GLDrawablePT22_Class* GLDrawablePT22_ClassInstance = NULL;
static struct GLShader_Class* GLShader_ClassInstance = NULL;
static struct TLPixelText_Class* TLPixelText_ClassInstance = NULL;
static struct GLBitmap_Class* GLBitmap_ClassInstance = NULL;
static struct GLBitmapPixelText_Class* GLBitmapPixelText_ClassInstance = NULL;
static struct GLTexture_Class* GLTexture_ClassInstance = NULL;
static struct GLVertexBlock_Class* GLVertexBlock_ClassInstance = NULL;
static struct TLPixelFont_Class* TLPixelFont_ClassInstance = NULL;
static struct CLString_Class* CLString_ClassInstance = NULL;
void Controller_CreateClass( )
{
	Controller_ClassInstance=malloc(sizeof(struct Controller_Class));
	Controller_ClassInstance->className="Controller";
	Controller_ClassInstance->classId=&Controller_ClassInstance;
	Controller_ClassInstance->init=Controller_init;
	Controller_ClassInstance->destruct=Controller_destruct;
	Controller_ClassInstance->render=Controller_render;
	Controller_ClassInstance->updateScene=Controller_updateScene;
	Controller_ClassInstance->setupScene=Controller_setupScene;
	Controller_ClassInstance->openSceneWithId=Controller_openSceneWithId;
	Controller_ClassInstance->addScene=Controller_addScene;
	Controller_ClassInstance->removeScene=Controller_removeScene;
	Controller_ClassInstance->buttonPressed=Controller_buttonPressed;
	
}
struct Controller* Controller_alloc( )
{
	struct Controller* result;
	if(Controller_ClassInstance==NULL)Controller_CreateClass( );
	result=malloc(sizeof(struct Controller));
	result->_components=malloc(sizeof(void*)*2);
	result->_class=(void*)&(Controller_ClassInstance->className);
	result->_components[0]=&(result->_class);
	result->_components[1]=NULL;
	return result;
}
void Controller_init (struct Controller* self, float theContextWidth , float theContextHeight ) 
{
	self->showButtons=0;
	self->contextWidth=theContextWidth;
	self->contextHeight=theContextHeight;
	self->simpleShader=ShaderP2_alloc( );
	ShaderP2_init(self->simpleShader );
	self->textureShader=ShaderPT22_alloc( );
	ShaderPT22_init(self->textureShader );
	self->simpleVertexBuffer=GLVertexBuffer_alloc( );
	GLVertexBuffer_init(self->simpleVertexBuffer );
	self->textureVertexBuffer=GLVertexBuffer_alloc( );
	GLVertexBuffer_init(self->textureVertexBuffer );
	self->simplePMLocation=self->simpleShader->shader->_class->getUniformLocation( (void*) self->simpleShader->shader->_components[0], "projectionMatrix");
	self->texturePMLocation=self->textureShader->shader->_class->getUniformLocation( (void*) self->textureShader->shader->_components[0], "projectionMatrix");
	glEnable(GL_POINTS);
	glPointSize(6);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glClearColor(.65,.65,.65,1.0);
	self->projectionMatrix=GLKMatrix4MakeOrtho(0.0,900.0,0.0,600.0,-1.0,1.0);
	Controller_setupScene( self );
}
void Controller_destruct (struct Controller* self ) 
{
	struct CLLink*link1;
	struct CLLink*link0;
	void* data;
	if(self->scene!=NULL)
	{
		Controller_removeScene( self );
		self->scene->_class->release( (void*) self->scene->_components[0] );
		self->scene=NULL;
	}
	self->universe->_class->release( (void*) self->universe->_components[0] );
	link0=self->buttons->head;while( link0!=NULL){data=link0->data; 
	
		struct GLRectPT22*buttonRect=data;
		GLVertexBuffer_removeDrawable(self->textureVertexBuffer, (cast_object( &GLDrawable_ClassInstance , buttonRect)));
		buttonRect->_class->release( (void*) buttonRect->_components[0] );
	link0=link0->next;}
	self->buttons->_class->release( (void*) self->buttons->_components[0] );
	link1=self->textures->head;while( link1!=NULL){data=link1->data; 
	
		struct GLTexturePixelText*texture=data;
		texture->_class->release( (void*) texture->_components[0] );
	link1=link1->next;}
	self->textures->_class->release( (void*) self->textures->_components[0] );
	self->simpleVertexBuffer->_class->release( (void*) self->simpleVertexBuffer->_components[0] );
	self->textureVertexBuffer->_class->release( (void*) self->textureVertexBuffer->_components[0] );
	self->simpleShader->_class->release( (void*) self->simpleShader->_components[0] );
	self->textureShader->_class->release( (void*) self->textureShader->_components[0] );
}
void Controller_render (struct Controller* self ) 
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	GLVertexBuffer_bindBuffer(self->simpleVertexBuffer );
	self->simpleShader->shader->_class->activate( (void*) self->simpleShader->shader->_components[0] );
	glUniformMatrix4fv(self->simplePMLocation,1,0,self->projectionMatrix.m);
	GLVertexBuffer_drawBuffer(self->simpleVertexBuffer );
	if(self->showButtons==1)
	{
		GLVertexBuffer_bindBuffer(self->textureVertexBuffer );
		self->textureShader->shader->_class->activate( (void*) self->textureShader->shader->_components[0] );
		glUniformMatrix4fv(self->texturePMLocation,1,0,self->projectionMatrix.m);
		GLVertexBuffer_drawBuffer(self->textureVertexBuffer );
	}
}
void Controller_updateScene (struct Controller* self ) 
{
	PLUniverse_update(self->universe );
	GLVertexBuffer_updateBuffers(self->simpleVertexBuffer );
}
void Controller_setupScene (struct Controller* self ) 
{
	self->scene=NULL;
	self->showButtons=1;
	self->buttons=CLDataList_alloc( );
	CLDataList_init(self->buttons );
	self->textures=CLDataList_alloc( );
	CLDataList_init(self->textures );
	self->universe=PLUniverse_alloc( );
	PLUniverse_init(self->universe );
	float freeX=(self->contextWidth-2*256-50)/2;
	float freeY=(self->contextHeight-2*256-50)/2;
	struct GLTexturePixelText*buttonATexture=GLTexturePixelText_alloc();
	struct GLTexturePixelText*buttonBTexture=GLTexturePixelText_alloc();
	struct GLTexturePixelText*buttonCTexture=GLTexturePixelText_alloc();
	struct GLTexturePixelText*buttonDTexture=GLTexturePixelText_alloc();
	GLTexturePixelText_init(buttonATexture, "PIT",256,256,3);
	GLTexturePixelText_init(buttonBTexture, "PARTICLE",256,256,3);
	GLTexturePixelText_init(buttonCTexture, "BOX",256,256,3);
	GLTexturePixelText_init(buttonDTexture, "SLOPE",256,256,3);
	struct GLRectPT22*buttonARect=GLRectPT22_alloc();
	struct GLRectPT22*buttonBRect=GLRectPT22_alloc();
	struct GLRectPT22*buttonCRect=GLRectPT22_alloc();
	struct GLRectPT22*buttonDRect=GLRectPT22_alloc();
	buttonARect->_class->init( (void*) buttonARect->_components[0], buttonATexture->glid);
	buttonBRect->_class->init( (void*) buttonBRect->_components[0], buttonBTexture->glid);
	buttonCRect->_class->init( (void*) buttonCRect->_components[0], buttonCTexture->glid);
	buttonDRect->_class->init( (void*) buttonDRect->_components[0], buttonDTexture->glid);
	buttonARect->_class->flipTexture( (void*) buttonARect->_components[0] );
	buttonBRect->_class->flipTexture( (void*) buttonBRect->_components[0] );
	buttonCRect->_class->flipTexture( (void*) buttonCRect->_components[0] );
	buttonDRect->_class->flipTexture( (void*) buttonDRect->_components[0] );
	buttonARect->_class->scale( (void*) buttonARect->_components[0], 256.0,256.0);
	buttonBRect->_class->scale( (void*) buttonBRect->_components[0], 256.0,256.0);
	buttonCRect->_class->scale( (void*) buttonCRect->_components[0], 256.0,256.0);
	buttonDRect->_class->scale( (void*) buttonDRect->_components[0], 256.0,256.0);
	buttonARect->_class->move( (void*) buttonARect->_components[0], freeX,freeY);
	buttonBRect->_class->move( (void*) buttonBRect->_components[0], freeX,freeY+256+50);
	buttonCRect->_class->move( (void*) buttonCRect->_components[0], freeX+256+50,freeY);
	buttonDRect->_class->move( (void*) buttonDRect->_components[0], freeX+256+50,freeY+256+50);
	CLDataList_addData(self->buttons, buttonARect);
	CLDataList_addData(self->buttons, buttonBRect);
	CLDataList_addData(self->buttons, buttonCRect);
	CLDataList_addData(self->buttons, buttonDRect);
	CLDataList_addData(self->textures, buttonATexture);
	CLDataList_addData(self->textures, buttonBTexture);
	CLDataList_addData(self->textures, buttonCTexture);
	CLDataList_addData(self->textures, buttonDTexture);
	GLVertexBuffer_addDrawable(self->textureVertexBuffer, (cast_object( &GLDrawable_ClassInstance , buttonARect)));
	GLVertexBuffer_addDrawable(self->textureVertexBuffer, (cast_object( &GLDrawable_ClassInstance , buttonBRect)));
	GLVertexBuffer_addDrawable(self->textureVertexBuffer, (cast_object( &GLDrawable_ClassInstance , buttonCRect)));
	GLVertexBuffer_addDrawable(self->textureVertexBuffer, (cast_object( &GLDrawable_ClassInstance , buttonDRect)));
	GLVertexBuffer_updateBuffers(self->textureVertexBuffer );
	Controller_openSceneWithId( self, 1);
}
void Controller_openSceneWithId (struct Controller* self, unsigned char theId ) 
{
	if(self->scene!=NULL)
	{
		Controller_removeScene( self );
		self->scene->_class->release( (void*) self->scene->_components[0] );
		self->scene=NULL;
	}
	void*sceneObj=NULL;
	if(theId==0)sceneObj=ScenePit_alloc();
	else if(theId==1)sceneObj=SceneParticle_alloc();
	else if(theId==2)sceneObj=SceneBox_alloc();
	else if(theId==3)sceneObj=SceneSlope_alloc();
	self->scene=(cast_object( &Scene_ClassInstance , sceneObj));
	self->scene->_class->initWithDimensions( (void*) self->scene->_components[0], self->contextWidth,self->contextHeight);
	Controller_addScene( self );
}
void Controller_addScene (struct Controller* self ) 
{
	struct CLLink*link6;
	struct CLLink*link5;
	struct CLLink*link4;
	struct CLLink*link3;
	struct CLLink*link2;
	void* data;
	link2=self->scene->glPoints->head;while( link2!=NULL){data=link2->data; 
	
		struct GLPointP2*glPoint=data;
		GLVertexBuffer_addDrawable(self->simpleVertexBuffer, (cast_object( &GLDrawable_ClassInstance , glPoint)));
	link2=link2->next;}
	link3=self->scene->glSegments->head;while( link3!=NULL){data=link3->data; 
	
		struct GLSegment*glSegment=data;
		GLVertexBuffer_addDrawable(self->simpleVertexBuffer, (cast_object( &GLDrawable_ClassInstance , glSegment)));
	link3=link3->next;}
	link4=self->scene->masses->head;while( link4!=NULL){data=link4->data; 
	
		struct PLMass*mass=data;
		PLUniverse_addMass(self->universe, mass);
	link4=link4->next;}
	link5=self->scene->segments->head;while( link5!=NULL){data=link5->data; 
	
		struct PLSegment*wall=data;
		PLUniverse_addWall(self->universe, wall);
	link5=link5->next;}
	link6=self->scene->spacers->head;while( link6!=NULL){data=link6->data; 
	
		struct PLSpacer*spacer=data;
		PLUniverse_addSpacer(self->universe, spacer);
	link6=link6->next;}
}
void Controller_removeScene (struct Controller* self ) 
{
	struct CLLink*link11;
	struct CLLink*link10;
	struct CLLink*link9;
	struct CLLink*link8;
	struct CLLink*link7;
	void* data;
	link7=self->scene->glPoints->head;while( link7!=NULL){data=link7->data; 
	
		struct GLPointP2*glPoint=data;
		GLVertexBuffer_removeDrawable(self->simpleVertexBuffer, (cast_object( &GLDrawable_ClassInstance , glPoint)));
	link7=link7->next;}
	link8=self->scene->glSegments->head;while( link8!=NULL){data=link8->data; 
	
		struct GLSegment*glSegment=data;
		GLVertexBuffer_removeDrawable(self->simpleVertexBuffer, (cast_object( &GLDrawable_ClassInstance , glSegment)));
	link8=link8->next;}
	link9=self->scene->masses->head;while( link9!=NULL){data=link9->data; 
	
		struct PLMass*mass=data;
		PLUniverse_removeMass(self->universe, mass);
	link9=link9->next;}
	link10=self->scene->segments->head;while( link10!=NULL){data=link10->data; 
	
		struct PLSegment*wall=data;
		PLUniverse_removeWall(self->universe, wall);
	link10=link10->next;}
	link11=self->scene->spacers->head;while( link11!=NULL){data=link11->data; 
	
		struct PLSpacer*spacer=data;
		PLUniverse_removeSpacer(self->universe, spacer);
	link11=link11->next;}
}
void Controller_buttonPressed (struct Controller* self, float theX , float theY ) 
{
	struct CLLink*link=self->buttons->head;
	unsigned char index=0;
	while(link!=NULL)
	{
		struct GLRectPT22*buttonRect=link->data;
		if(buttonRect->_class->contains( (void*) buttonRect->_components[0], theX,theY))Controller_openSceneWithId( self, index);
		index++;
		link=link->next;
	}
}
void PLMass_CreateClass( )
{
	PLMass_ClassInstance=malloc(sizeof(struct PLMass_Class));
	PLMass_ClassInstance->className="PLMass";
	PLMass_ClassInstance->classId=&PLMass_ClassInstance;
	PLMass_ClassInstance->init=PLMass_init;
	PLMass_ClassInstance->destruct=PLMass_destruct;
	PLMass_ClassInstance->describe=PLMass_describe;
	PLMass_ClassInstance->className_CLObject="CLObject";
	PLMass_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PLMass_ClassInstance->init_CLObject=PLMass_init;
	PLMass_ClassInstance->destruct_CLObject=PLMass_destruct;
	PLMass_ClassInstance->retain=PLMass_retain;
	PLMass_ClassInstance->release=PLMass_release;
	PLMass_ClassInstance->describe_CLObject=PLMass_describe;
	
}
struct PLMass* PLMass_alloc( )
{
	struct PLMass* result;
	if(PLMass_ClassInstance==NULL)PLMass_CreateClass( );
	result=malloc(sizeof(struct PLMass));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PLMass_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PLMass_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PLMass_init (struct PLMass* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->force=PLVector_alloc();
	self->position=PLVector_alloc();
	self->collision=PLVector_alloc();
	self->baseWalls=CLDataList_alloc();
	self->touchedWalls=CLDataList_alloc();
	self->lastTouchedWalls=CLDataList_alloc();
	self->hadCollision=0;
	self->friction=.9;
	self->buoyancy=.9;
	self->force->_class->initWithPoints( (void*) self->force->_components[0], 0,0);
	self->position->_class->initWithPoints( (void*) self->position->_components[0], 0,0);
	self->collision->_class->initWithPoints( (void*) self->collision->_components[0], 0,0);
	self->baseWalls->_class->init( (void*) self->baseWalls->_components[0] );
	self->touchedWalls->_class->init( (void*) self->touchedWalls->_components[0] );
	self->lastTouchedWalls->_class->init( (void*) self->lastTouchedWalls->_components[0] );
}
void PLMass_destruct (struct PLMass* self ) 
{
	self->force->_class->release( (void*) self->force->_components[0] );
	self->position->_class->release( (void*) self->position->_components[0] );
	self->collision->_class->release( (void*) self->collision->_components[0] );
	self->baseWalls->_class->release( (void*) self->baseWalls->_components[0] );
	self->touchedWalls->_class->release( (void*) self->touchedWalls->_components[0] );
	self->lastTouchedWalls->_class->release( (void*) self->lastTouchedWalls->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void PLMass_describe (struct PLMass* self ) 
{
	printf("\nposition ");
	self->position->_class->describe( (void*) self->position->_components[0] );
	printf(" force");
	self->force->_class->describe( (void*) self->force->_components[0] );
}
void PLMass_retain (struct PLMass* self ) 
{
	self->retainCount=self->retainCount+1;
}
void PLMass_release (struct PLMass* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PLSpacer_CreateClass( )
{
	PLSpacer_ClassInstance=malloc(sizeof(struct PLSpacer_Class));
	PLSpacer_ClassInstance->className="PLSpacer";
	PLSpacer_ClassInstance->classId=&PLSpacer_ClassInstance;
	PLSpacer_ClassInstance->initWithMasses=PLSpacer_initWithMasses;
	PLSpacer_ClassInstance->destruct=PLSpacer_destruct;
	PLSpacer_ClassInstance->respace=PLSpacer_respace;
	PLSpacer_ClassInstance->className_CLObject="CLObject";
	PLSpacer_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PLSpacer_ClassInstance->init=PLSpacer_init;
	PLSpacer_ClassInstance->destruct_CLObject=PLSpacer_destruct;
	PLSpacer_ClassInstance->retain=PLSpacer_retain;
	PLSpacer_ClassInstance->release=PLSpacer_release;
	PLSpacer_ClassInstance->describe=PLSpacer_describe;
	
}
struct PLSpacer* PLSpacer_alloc( )
{
	struct PLSpacer* result;
	if(PLSpacer_ClassInstance==NULL)PLSpacer_CreateClass( );
	result=malloc(sizeof(struct PLSpacer));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PLSpacer_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PLSpacer_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PLSpacer_initWithMasses (struct PLSpacer* self, struct PLMass * theMassA , struct PLMass * theMassB ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->massA=theMassA;
	self->massB=theMassB;
	self->massA->_class->retain( (void*) self->massA->_components[0] );
	self->massB->_class->retain( (void*) self->massB->_components[0] );
	self->respaceVectorA=PLVector_alloc();
	self->respaceVectorB=PLVector_alloc();
	PLVector_initWithPoints(self->respaceVectorA, 0,0);
	PLVector_initWithPoints(self->respaceVectorB, 0,0);
	float dx=self->massA->position->x-self->massB->position->x;
	float dy=self->massA->position->y-self->massB->position->y;
	self->space=sqrt(dx*dx+dy*dy);
}
void PLSpacer_destruct (struct PLSpacer* self ) 
{
	self->massA->_class->release( (void*) self->massA->_components[0] );
	self->massB->_class->release( (void*) self->massB->_components[0] );
	self->respaceVectorA->_class->release( (void*) self->respaceVectorA->_components[0] );
	self->respaceVectorB->_class->release( (void*) self->respaceVectorB->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void PLSpacer_respace (struct PLSpacer* self ) 
{
	float dx=self->massB->position->x+self->massB->force->x-(self->massA->position->x+self->massA->force->x);
	float dy=self->massB->position->y+self->massB->force->y-(self->massA->position->y+self->massA->force->y);
	PLVector_setXY(self->respaceVectorA, dx,dy);
	PLVector_setXY(self->respaceVectorB, dx,dy);
	float delta=(self->respaceVectorA->length-self->space)/3;
	PLVector_multiply(self->respaceVectorA, delta/self->respaceVectorA->length);
	PLVector_multiply(self->respaceVectorB, -delta/self->respaceVectorB->length);
	PLVector_addVector(( cast_object( &PLVector_ClassInstance , self->massA->force)),self->respaceVectorA);
	PLVector_addVector(( cast_object( &PLVector_ClassInstance , self->massB->force)),self->respaceVectorB);
}
void PLSpacer_init (struct PLSpacer* self ) 
{
	self->retainCount=1;
}
void PLSpacer_retain (struct PLSpacer* self ) 
{
	self->retainCount=self->retainCount+1;
}
void PLSpacer_release (struct PLSpacer* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PLSpacer_describe (struct PLSpacer* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void PLSegment_CreateClass( )
{
	PLSegment_ClassInstance=malloc(sizeof(struct PLSegment_Class));
	PLSegment_ClassInstance->className="PLSegment";
	PLSegment_ClassInstance->classId=&PLSegment_ClassInstance;
	PLSegment_ClassInstance->initWithVectors=PLSegment_initWithVectors;
	PLSegment_ClassInstance->destruct=PLSegment_destruct;
	PLSegment_ClassInstance->collideMass=PLSegment_collideMass;
	PLSegment_ClassInstance->slideMass=PLSegment_slideMass;
	PLSegment_ClassInstance->className_CLObject="CLObject";
	PLSegment_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PLSegment_ClassInstance->init=PLSegment_init;
	PLSegment_ClassInstance->destruct_CLObject=PLSegment_destruct;
	PLSegment_ClassInstance->retain=PLSegment_retain;
	PLSegment_ClassInstance->release=PLSegment_release;
	PLSegment_ClassInstance->describe=PLSegment_describe;
	
}
struct PLSegment* PLSegment_alloc( )
{
	struct PLSegment* result;
	if(PLSegment_ClassInstance==NULL)PLSegment_CreateClass( );
	result=malloc(sizeof(struct PLSegment));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PLSegment_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PLSegment_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PLSegment_initWithVectors (struct PLSegment* self, struct PLVector * thePointA , struct PLVector * thePointB ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	thePointA->_class->retain( (void*) thePointA->_components[0] );
	thePointB->_class->retain( (void*) thePointB->_components[0] );
	self->normForce=PLVector_alloc();
	self->paraForce=PLVector_alloc();
	self->wallVector=PLVector_alloc();
	self->forceEnding=PLVector_alloc();
	PLVector_init(self->normForce );
	PLVector_init(self->paraForce );
	PLVector_init(self->wallVector );
	PLVector_init(self->forceEnding );
	self->pointA=thePointA;
	self->pointB=thePointB;
	self->A=self->pointB->y-self->pointA->y;
	self->B=self->pointA->x-self->pointB->x;
	self->C=self->A*self->pointA->x+self->B*self->pointA->y;
	self->r=sqrtf(self->A*self->A+self->B*self->B);
	self->a=atan2f(self->pointB->y-self->pointA->y,self->pointB->x-self->pointA->x);
	self->centerX=self->pointA->x+(self->pointB->x-self->pointA->x)/2;
	self->centerY=self->pointA->y+(self->pointB->y-self->pointA->y)/2;
	self->friction=1;
}
void PLSegment_destruct (struct PLSegment* self ) 
{
	self->pointA->_class->release( (void*) self->pointA->_components[0] );
	self->pointB->_class->release( (void*) self->pointB->_components[0] );
	self->normForce->_class->release( (void*) self->normForce->_components[0] );
	self->paraForce->_class->release( (void*) self->paraForce->_components[0] );
	self->wallVector->_class->release( (void*) self->wallVector->_components[0] );
	self->forceEnding->_class->release( (void*) self->forceEnding->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void PLSegment_collideMass (struct PLSegment* self, struct PLMass * theMass , struct CLDataList * theCollidingWallsPerStep , struct CLDataList * theCollidingNormalsPerStep , struct CLDataList * theCollidingParallelsPerStep ) 
{
	float rx=fabsf((theMass->position->x+theMass->force->x)-self->centerX);
	float ry=fabsf((theMass->position->y+theMass->force->y)-self->centerY);
	if(rx<(self->r/2+20)&&ry<(self->r/2+20))
	{
		float dx=(theMass->position->x+theMass->force->x)-self->pointA->x;
		float dy=(theMass->position->y+theMass->force->y)-self->pointA->y;
		float angle=atan2f(dy,dx);
		if(angle<self->a)
		{
			float massA=theMass->force->y;
			float massB=-theMass->force->x;
			float massC=massA*theMass->position->x+massB*theMass->position->y;
			float determinant=massA*self->B-massB*self->A;
			if(determinant!=0)
			{
				float hitX=(self->B*massC-massB*self->C)/determinant;
				float hitY=(massA*self->C-self->A*massC)/determinant;
				PLVector_setXY(self->wallVector, self->pointB->x-self->pointA->x,self->pointB->y-self->pointA->y);
				PLVector_setXY(self->forceEnding, theMass->position->x+theMass->force->x-hitX,theMass->position->y+theMass->force->y-hitY);
				if(self->forceEnding->length<DEPSILON)
				{
					self->forceEnding->_class->set( (void*) self->forceEnding->_components[0], theMass->force);
				}
				float normLength=sinf(theMass->force->angle-self->wallVector->angle)*theMass->force->length;
				float paraLength=cosf(theMass->force->angle-self->wallVector->angle)*theMass->force->length;
				PLVector_setXY(self->normForce, sinf(self->wallVector->angle)*normLength,cosf(self->wallVector->angle)*normLength*-1);
				PLVector_setXY(self->paraForce, cosf(self->wallVector->angle)*paraLength,sinf(self->wallVector->angle)*paraLength);
				PLVector_multiply(self->normForce, self->forceEnding->length/theMass->force->length);
				PLVector_multiply(self->paraForce, self->forceEnding->length/theMass->force->length);
				CLDataList_addData(theCollidingWallsPerStep, self);
				CLDataList_addData(theCollidingNormalsPerStep, self->normForce);
				CLDataList_addData(theCollidingParallelsPerStep, self->paraForce);
				PLVector_setXY(( cast_object( &PLVector_ClassInstance , theMass->collision)),hitX,hitY);
				theMass->hadCollision=1;
			}
		}
	}
}
void PLSegment_slideMass (struct PLSegment* self, struct PLMass * theMass ) 
{
	PLVector_setXY(self->wallVector, self->pointB->x-self->pointA->x,self->pointB->y-self->pointA->y);
	float paraLength=cos(theMass->force->angle-self->wallVector->angle)*theMass->force->length;
	PLVector_setXY(self->paraForce, cosf(self->wallVector->angle)*paraLength,sinf(self->wallVector->angle)*paraLength);
	PLVector_set(( cast_object( &PLVector_ClassInstance , theMass->force)),self->paraForce);
}
void PLSegment_init (struct PLSegment* self ) 
{
	self->retainCount=1;
}
void PLSegment_retain (struct PLSegment* self ) 
{
	self->retainCount=self->retainCount+1;
}
void PLSegment_release (struct PLSegment* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PLSegment_describe (struct PLSegment* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void Scene_CreateClass( )
{
	Scene_ClassInstance=malloc(sizeof(struct Scene_Class));
	Scene_ClassInstance->className="Scene";
	Scene_ClassInstance->classId=&Scene_ClassInstance;
	Scene_ClassInstance->initWithDimensions=Scene_initWithDimensions;
	Scene_ClassInstance->destruct=Scene_destruct;
	Scene_ClassInstance->className_CLObject="CLObject";
	Scene_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Scene_ClassInstance->init=Scene_init;
	Scene_ClassInstance->destruct_CLObject=Scene_destruct;
	Scene_ClassInstance->retain=Scene_retain;
	Scene_ClassInstance->release=Scene_release;
	Scene_ClassInstance->describe=Scene_describe;
	
}
struct Scene* Scene_alloc( )
{
	struct Scene* result;
	if(Scene_ClassInstance==NULL)Scene_CreateClass( );
	result=malloc(sizeof(struct Scene));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Scene_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Scene_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Scene_initWithDimensions (struct Scene* self, float theWidth , float theHeight ) 
{
	printf("\nScene initWithDimensions %f %f",theWidth,theHeight);
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=theWidth;
	self->height=theHeight;
	self->masses=CLDataList_alloc( );
	CLDataList_init(self->masses );
	self->spacers=CLDataList_alloc( );
	CLDataList_init(self->spacers );
	self->segments=CLDataList_alloc( );
	CLDataList_init(self->segments );
	self->glPoints=CLDataList_alloc( );
	CLDataList_init(self->glPoints );
	self->glSegments=CLDataList_alloc( );
	CLDataList_init(self->glSegments );
}
void Scene_destruct (struct Scene* self ) 
{
	printf("\nScene destruct");
	struct CLLink*pointLink=self->glPoints->head;
	while(pointLink!=NULL)
	{
		struct GLPointP2*glPoint=pointLink->data;
		glPoint->vertexes=NULL;
		glPoint->_class->release( (void*) glPoint->_components[0] );
		pointLink=pointLink->next;
	}
	self->glPoints->_class->release( (void*) self->glPoints->_components[0] );
	struct CLLink*segmentLink=self->glSegments->head;
	while(segmentLink!=NULL)
	{
		struct GLSegment*glSegment=segmentLink->data;
		glSegment->_class->release( (void*) glSegment->_components[0] );
		segmentLink=segmentLink->next;
	}
	self->glSegments->_class->release( (void*) self->glSegments->_components[0] );
	struct CLLink*massLink=self->masses->head;
	while(massLink!=NULL)
	{
		struct PLMass*mass=massLink->data;
		mass->_class->release( (void*) mass->_components[0] );
		massLink=massLink->next;
	}
	self->masses->_class->release( (void*) self->masses->_components[0] );
	struct CLLink*spacerLink=self->spacers->head;
	while(spacerLink!=NULL)
	{
		struct PLSpacer*spacer=spacerLink->data;
		spacer->_class->release( (void*) spacer->_components[0] );
		spacerLink=spacerLink->next;
	}
	self->spacers->_class->release( (void*) self->spacers->_components[0] );
	struct CLLink*wallLink=self->segments->head;
	while(wallLink!=NULL)
	{
		struct PLSegment*wall=wallLink->data;
		wall->_class->release( (void*) wall->_components[0] );
		wallLink=wallLink->next;
	}
	self->segments->_class->release( (void*) self->segments->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void Scene_init (struct Scene* self ) 
{
	self->retainCount=1;
}
void Scene_retain (struct Scene* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Scene_release (struct Scene* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Scene_describe (struct Scene* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void ScenePit_CreateClass( )
{
	ScenePit_ClassInstance=malloc(sizeof(struct ScenePit_Class));
	ScenePit_ClassInstance->className="ScenePit";
	ScenePit_ClassInstance->classId=&ScenePit_ClassInstance;
	ScenePit_ClassInstance->initWithDimensions=ScenePit_initWithDimensions;
	ScenePit_ClassInstance->className_Scene="Scene";
	ScenePit_ClassInstance->classId_Scene=&Scene_ClassInstance;
	ScenePit_ClassInstance->initWithDimensions_Scene=ScenePit_initWithDimensions;
	ScenePit_ClassInstance->destruct=ScenePit_destruct;
	ScenePit_ClassInstance->className_CLObject="CLObject";
	ScenePit_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	ScenePit_ClassInstance->init=ScenePit_init;
	ScenePit_ClassInstance->destruct_CLObject=ScenePit_destruct;
	ScenePit_ClassInstance->retain=ScenePit_retain;
	ScenePit_ClassInstance->release=ScenePit_release;
	ScenePit_ClassInstance->describe=ScenePit_describe;
	
}
struct ScenePit* ScenePit_alloc( )
{
	struct ScenePit* result;
	if(ScenePit_ClassInstance==NULL)ScenePit_CreateClass( );
	result=malloc(sizeof(struct ScenePit));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(ScenePit_ClassInstance->className);
	result->_components_Scene=result->_components;
	result->_class_Scene=(void*)&(ScenePit_ClassInstance->className_Scene);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(ScenePit_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_Scene);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void ScenePit_initWithDimensions (struct ScenePit* self, float theWidth , float theHeight ) 
{
	Scene_initWithDimensions(( cast_object( &Scene_ClassInstance , self)),theWidth,theHeight);
	struct PLVector*vectorA=PLVector_alloc();
	struct PLVector*vectorB=PLVector_alloc();
	struct PLVector*vectorC=PLVector_alloc();
	struct PLVector*vectorD=PLVector_alloc();
	PLVector_initWithPoints(vectorA, 250,500);
	PLVector_initWithPoints(vectorB, 270,180);
	PLVector_initWithPoints(vectorC, 730,50);
	PLVector_initWithPoints(vectorD, 870,550);
	struct PLSegment*segmentA=PLSegment_alloc();
	struct PLSegment*segmentB=PLSegment_alloc();
	struct PLSegment*segmentC=PLSegment_alloc();
	PLSegment_initWithVectors(segmentA, vectorA,vectorB);
	PLSegment_initWithVectors(segmentB, vectorB,vectorC);
	PLSegment_initWithVectors(segmentC, vectorC,vectorD);
	vectorA->_class->release( (void*) vectorA->_components[0] );
	vectorB->_class->release( (void*) vectorB->_components[0] );
	vectorC->_class->release( (void*) vectorC->_components[0] );
	vectorD->_class->release( (void*) vectorD->_components[0] );
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentA);
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentB);
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentC);
	struct GLSegment*glSegmentA=GLSegment_alloc();
	struct GLSegment*glSegmentB=GLSegment_alloc();
	struct GLSegment*glSegmentC=GLSegment_alloc();
	GLSegment_initWithPoints(glSegmentA, segmentA->pointA->x,segmentA->pointA->y,segmentA->pointB->x,segmentA->pointB->y);
	GLSegment_initWithPoints(glSegmentB, segmentB->pointA->x,segmentB->pointA->y,segmentB->pointB->x,segmentB->pointB->y);
	GLSegment_initWithPoints(glSegmentC, segmentC->pointA->x,segmentC->pointA->y,segmentC->pointB->x,segmentC->pointB->y);
	CLDataList_addData(self->glSegments, glSegmentA);
	CLDataList_addData(self->glSegments, glSegmentB);
	CLDataList_addData(self->glSegments, glSegmentC);
	for(int index=0;
	index<40000;
	index++)
	{
		struct PLMass*mass=PLMass_alloc();
		PLMass_init(mass );
		mass->position->x=(float)270+(float)(rand()%45000)/100;
		mass->position->y=(float)200+(float)(rand()%40000)/100;
		CLDataList_addData(self->masses, mass);
		struct GLPointP2*point=GLPointP2_alloc();
		point->_class->initWithPoints( (void*) point->_components[0], mass->position->x,mass->position->y);
		free(point->vertexes);
		point->vertexes=(void*)&(mass->position->x);
		CLDataList_addData(self->glPoints, point);
	}
}
void ScenePit_destruct (struct ScenePit* self ) 
{
	printf("\nScene destruct");
	struct CLLink*pointLink=self->glPoints->head;
	while(pointLink!=NULL)
	{
		struct GLPointP2*glPoint=pointLink->data;
		glPoint->vertexes=NULL;
		glPoint->_class->release( (void*) glPoint->_components[0] );
		pointLink=pointLink->next;
	}
	self->glPoints->_class->release( (void*) self->glPoints->_components[0] );
	struct CLLink*segmentLink=self->glSegments->head;
	while(segmentLink!=NULL)
	{
		struct GLSegment*glSegment=segmentLink->data;
		glSegment->_class->release( (void*) glSegment->_components[0] );
		segmentLink=segmentLink->next;
	}
	self->glSegments->_class->release( (void*) self->glSegments->_components[0] );
	struct CLLink*massLink=self->masses->head;
	while(massLink!=NULL)
	{
		struct PLMass*mass=massLink->data;
		mass->_class->release( (void*) mass->_components[0] );
		massLink=massLink->next;
	}
	self->masses->_class->release( (void*) self->masses->_components[0] );
	struct CLLink*spacerLink=self->spacers->head;
	while(spacerLink!=NULL)
	{
		struct PLSpacer*spacer=spacerLink->data;
		spacer->_class->release( (void*) spacer->_components[0] );
		spacerLink=spacerLink->next;
	}
	self->spacers->_class->release( (void*) self->spacers->_components[0] );
	struct CLLink*wallLink=self->segments->head;
	while(wallLink!=NULL)
	{
		struct PLSegment*wall=wallLink->data;
		wall->_class->release( (void*) wall->_components[0] );
		wallLink=wallLink->next;
	}
	self->segments->_class->release( (void*) self->segments->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void ScenePit_init (struct ScenePit* self ) 
{
	self->retainCount=1;
}
void ScenePit_retain (struct ScenePit* self ) 
{
	self->retainCount=self->retainCount+1;
}
void ScenePit_release (struct ScenePit* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void ScenePit_describe (struct ScenePit* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void SceneBox_CreateClass( )
{
	SceneBox_ClassInstance=malloc(sizeof(struct SceneBox_Class));
	SceneBox_ClassInstance->className="SceneBox";
	SceneBox_ClassInstance->classId=&SceneBox_ClassInstance;
	SceneBox_ClassInstance->initWithDimensions=SceneBox_initWithDimensions;
	SceneBox_ClassInstance->className_Scene="Scene";
	SceneBox_ClassInstance->classId_Scene=&Scene_ClassInstance;
	SceneBox_ClassInstance->initWithDimensions_Scene=SceneBox_initWithDimensions;
	SceneBox_ClassInstance->destruct=SceneBox_destruct;
	SceneBox_ClassInstance->className_CLObject="CLObject";
	SceneBox_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	SceneBox_ClassInstance->init=SceneBox_init;
	SceneBox_ClassInstance->destruct_CLObject=SceneBox_destruct;
	SceneBox_ClassInstance->retain=SceneBox_retain;
	SceneBox_ClassInstance->release=SceneBox_release;
	SceneBox_ClassInstance->describe=SceneBox_describe;
	
}
struct SceneBox* SceneBox_alloc( )
{
	struct SceneBox* result;
	if(SceneBox_ClassInstance==NULL)SceneBox_CreateClass( );
	result=malloc(sizeof(struct SceneBox));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(SceneBox_ClassInstance->className);
	result->_components_Scene=result->_components;
	result->_class_Scene=(void*)&(SceneBox_ClassInstance->className_Scene);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(SceneBox_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_Scene);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void SceneBox_initWithDimensions (struct SceneBox* self, float theWidth , float theHeight ) 
{
	Scene_initWithDimensions(( cast_object( &Scene_ClassInstance , self)),theWidth,theHeight);
	struct PLVector*vectorA=PLVector_alloc();
	struct PLVector*vectorB=PLVector_alloc();
	struct PLVector*vectorC=PLVector_alloc();
	struct PLVector*vectorD=PLVector_alloc();
	PLVector_initWithPoints(vectorA, 250,500);
	PLVector_initWithPoints(vectorB, 270,180);
	PLVector_initWithPoints(vectorC, 730,50);
	PLVector_initWithPoints(vectorD, 870,550);
	struct PLSegment*segmentA=PLSegment_alloc();
	struct PLSegment*segmentB=PLSegment_alloc();
	struct PLSegment*segmentC=PLSegment_alloc();
	PLSegment_initWithVectors(segmentA, vectorA,vectorB);
	PLSegment_initWithVectors(segmentB, vectorB,vectorC);
	PLSegment_initWithVectors(segmentC, vectorC,vectorD);
	vectorA->_class->release( (void*) vectorA->_components[0] );
	vectorB->_class->release( (void*) vectorB->_components[0] );
	vectorC->_class->release( (void*) vectorC->_components[0] );
	vectorD->_class->release( (void*) vectorD->_components[0] );
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentA);
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentB);
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentC);
	struct GLSegment*glSegmentA=GLSegment_alloc();
	struct GLSegment*glSegmentB=GLSegment_alloc();
	struct GLSegment*glSegmentC=GLSegment_alloc();
	GLSegment_initWithPoints(glSegmentA, segmentA->pointA->x,segmentA->pointA->y,segmentA->pointB->x,segmentA->pointB->y);
	GLSegment_initWithPoints(glSegmentB, segmentB->pointA->x,segmentB->pointA->y,segmentB->pointB->x,segmentB->pointB->y);
	GLSegment_initWithPoints(glSegmentC, segmentC->pointA->x,segmentC->pointA->y,segmentC->pointB->x,segmentC->pointB->y);
	CLDataList_addData(self->glSegments, glSegmentA);
	CLDataList_addData(self->glSegments, glSegmentB);
	CLDataList_addData(self->glSegments, glSegmentC);
	struct PLMass*massPointA=PLMass_alloc();
	struct PLMass*massPointB=PLMass_alloc();
	struct PLMass*massPointC=PLMass_alloc();
	struct PLMass*massPointD=PLMass_alloc();
	PLMass_init(massPointA );
	PLMass_init(massPointB );
	PLMass_init(massPointC );
	PLMass_init(massPointD );
	float x=300.0+rand()%100;
	float y=400.0+rand()%100;
	massPointA->position->x=x;
	massPointA->position->y=y-10.0;
	massPointB->position->x=x+100.0;
	massPointB->position->y=y;
	massPointC->position->x=x+100.0;
	massPointC->position->y=y+100.0;
	massPointD->position->x=x;
	massPointD->position->y=y+100.0;
	self->masses->_class->addData( (void*) self->masses->_components[0], massPointA);
	self->masses->_class->addData( (void*) self->masses->_components[0], massPointB);
	self->masses->_class->addData( (void*) self->masses->_components[0], massPointC);
	self->masses->_class->addData( (void*) self->masses->_components[0], massPointD);
	struct GLPointP2*pointA=GLPointP2_alloc();
	struct GLPointP2*pointB=GLPointP2_alloc();
	struct GLPointP2*pointC=GLPointP2_alloc();
	struct GLPointP2*pointD=GLPointP2_alloc();
	pointA->_class->initWithPoints( (void*) pointA->_components[0], massPointA->position->x,massPointA->position->y);
	pointB->_class->initWithPoints( (void*) pointB->_components[0], massPointB->position->x,massPointB->position->y);
	pointC->_class->initWithPoints( (void*) pointC->_components[0], massPointC->position->x,massPointC->position->y);
	pointD->_class->initWithPoints( (void*) pointD->_components[0], massPointD->position->x,massPointD->position->y);
	free(pointA->vertexes);
	free(pointB->vertexes);
	free(pointC->vertexes);
	free(pointD->vertexes);
	pointA->vertexes=(void*)&(massPointA->position->x);
	pointB->vertexes=(void*)&(massPointB->position->x);
	pointC->vertexes=(void*)&(massPointC->position->x);
	pointD->vertexes=(void*)&(massPointD->position->x);
	CLDataList_addData(self->glPoints, pointA);
	CLDataList_addData(self->glPoints, pointB);
	CLDataList_addData(self->glPoints, pointC);
	CLDataList_addData(self->glPoints, pointD);
	struct PLSpacer*spacerA=PLSpacer_alloc();
	struct PLSpacer*spacerB=PLSpacer_alloc();
	struct PLSpacer*spacerC=PLSpacer_alloc();
	struct PLSpacer*spacerD=PLSpacer_alloc();
	struct PLSpacer*spacerE=PLSpacer_alloc();
	struct PLSpacer*spacerF=PLSpacer_alloc();
	spacerA->_class->initWithMasses( (void*) spacerA->_components[0], massPointA,massPointB);
	spacerB->_class->initWithMasses( (void*) spacerB->_components[0], massPointB,massPointC);
	spacerC->_class->initWithMasses( (void*) spacerC->_components[0], massPointC,massPointD);
	spacerD->_class->initWithMasses( (void*) spacerD->_components[0], massPointD,massPointA);
	spacerE->_class->initWithMasses( (void*) spacerE->_components[0], massPointA,massPointC);
	spacerF->_class->initWithMasses( (void*) spacerF->_components[0], massPointD,massPointB);
	self->spacers->_class->addData( (void*) self->spacers->_components[0], spacerC);
	self->spacers->_class->addData( (void*) self->spacers->_components[0], spacerD);
	self->spacers->_class->addData( (void*) self->spacers->_components[0], spacerE);
	self->spacers->_class->addData( (void*) self->spacers->_components[0], spacerF);
	self->spacers->_class->addData( (void*) self->spacers->_components[0], spacerA);
	self->spacers->_class->addData( (void*) self->spacers->_components[0], spacerB);
}
void SceneBox_destruct (struct SceneBox* self ) 
{
	printf("\nScene destruct");
	struct CLLink*pointLink=self->glPoints->head;
	while(pointLink!=NULL)
	{
		struct GLPointP2*glPoint=pointLink->data;
		glPoint->vertexes=NULL;
		glPoint->_class->release( (void*) glPoint->_components[0] );
		pointLink=pointLink->next;
	}
	self->glPoints->_class->release( (void*) self->glPoints->_components[0] );
	struct CLLink*segmentLink=self->glSegments->head;
	while(segmentLink!=NULL)
	{
		struct GLSegment*glSegment=segmentLink->data;
		glSegment->_class->release( (void*) glSegment->_components[0] );
		segmentLink=segmentLink->next;
	}
	self->glSegments->_class->release( (void*) self->glSegments->_components[0] );
	struct CLLink*massLink=self->masses->head;
	while(massLink!=NULL)
	{
		struct PLMass*mass=massLink->data;
		mass->_class->release( (void*) mass->_components[0] );
		massLink=massLink->next;
	}
	self->masses->_class->release( (void*) self->masses->_components[0] );
	struct CLLink*spacerLink=self->spacers->head;
	while(spacerLink!=NULL)
	{
		struct PLSpacer*spacer=spacerLink->data;
		spacer->_class->release( (void*) spacer->_components[0] );
		spacerLink=spacerLink->next;
	}
	self->spacers->_class->release( (void*) self->spacers->_components[0] );
	struct CLLink*wallLink=self->segments->head;
	while(wallLink!=NULL)
	{
		struct PLSegment*wall=wallLink->data;
		wall->_class->release( (void*) wall->_components[0] );
		wallLink=wallLink->next;
	}
	self->segments->_class->release( (void*) self->segments->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void SceneBox_init (struct SceneBox* self ) 
{
	self->retainCount=1;
}
void SceneBox_retain (struct SceneBox* self ) 
{
	self->retainCount=self->retainCount+1;
}
void SceneBox_release (struct SceneBox* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void SceneBox_describe (struct SceneBox* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void SceneSlope_CreateClass( )
{
	SceneSlope_ClassInstance=malloc(sizeof(struct SceneSlope_Class));
	SceneSlope_ClassInstance->className="SceneSlope";
	SceneSlope_ClassInstance->classId=&SceneSlope_ClassInstance;
	SceneSlope_ClassInstance->initWithDimensions=SceneSlope_initWithDimensions;
	SceneSlope_ClassInstance->className_Scene="Scene";
	SceneSlope_ClassInstance->classId_Scene=&Scene_ClassInstance;
	SceneSlope_ClassInstance->initWithDimensions_Scene=SceneSlope_initWithDimensions;
	SceneSlope_ClassInstance->destruct=SceneSlope_destruct;
	SceneSlope_ClassInstance->className_CLObject="CLObject";
	SceneSlope_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	SceneSlope_ClassInstance->init=SceneSlope_init;
	SceneSlope_ClassInstance->destruct_CLObject=SceneSlope_destruct;
	SceneSlope_ClassInstance->retain=SceneSlope_retain;
	SceneSlope_ClassInstance->release=SceneSlope_release;
	SceneSlope_ClassInstance->describe=SceneSlope_describe;
	
}
struct SceneSlope* SceneSlope_alloc( )
{
	struct SceneSlope* result;
	if(SceneSlope_ClassInstance==NULL)SceneSlope_CreateClass( );
	result=malloc(sizeof(struct SceneSlope));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(SceneSlope_ClassInstance->className);
	result->_components_Scene=result->_components;
	result->_class_Scene=(void*)&(SceneSlope_ClassInstance->className_Scene);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(SceneSlope_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_Scene);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void SceneSlope_initWithDimensions (struct SceneSlope* self, float theWidth , float theHeight ) 
{
	Scene_initWithDimensions(( cast_object( &Scene_ClassInstance , self)),theWidth,theHeight);
	struct PLMass*massA=PLMass_alloc();
	PLMass_init(massA );
	massA->position->x=350;
	massA->position->y=self->height-400;
	CLDataList_addData(self->masses, massA);
	struct GLPointP2*glPoint=GLPointP2_alloc();
	glPoint->_class->initWithPoints( (void*) glPoint->_components[0], massA->position->x,massA->position->y);
	free(glPoint->vertexes);
	glPoint->vertexes=(void*)&(massA->position->x);
	CLDataList_addData(self->glPoints, glPoint);
	struct PLVector*vectorA=PLVector_alloc();
	struct PLVector*vectorB=PLVector_alloc();
	struct PLVector*vectorC=PLVector_alloc();
	struct PLVector*vectorD=PLVector_alloc();
	PLVector_initWithPoints(vectorA, 250,500);
	PLVector_initWithPoints(vectorB, 270,180);
	PLVector_initWithPoints(vectorC, 730,50);
	PLVector_initWithPoints(vectorD, 870,550);
	struct PLSegment*segmentA=PLSegment_alloc();
	struct PLSegment*segmentB=PLSegment_alloc();
	struct PLSegment*segmentC=PLSegment_alloc();
	PLSegment_initWithVectors(segmentA, vectorA,vectorB);
	PLSegment_initWithVectors(segmentB, vectorB,vectorC);
	PLSegment_initWithVectors(segmentC, vectorC,vectorD);
	vectorA->_class->release( (void*) vectorA->_components[0] );
	vectorB->_class->release( (void*) vectorB->_components[0] );
	vectorC->_class->release( (void*) vectorC->_components[0] );
	vectorD->_class->release( (void*) vectorD->_components[0] );
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentA);
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentB);
	self->segments->_class->addData( (void*) self->segments->_components[0], segmentC);
	struct GLSegment*glSegmentA=GLSegment_alloc();
	struct GLSegment*glSegmentB=GLSegment_alloc();
	struct GLSegment*glSegmentC=GLSegment_alloc();
	GLSegment_initWithPoints(glSegmentA, segmentA->pointA->x,segmentA->pointA->y,segmentA->pointB->x,segmentA->pointB->y);
	GLSegment_initWithPoints(glSegmentB, segmentB->pointA->x,segmentB->pointA->y,segmentB->pointB->x,segmentB->pointB->y);
	GLSegment_initWithPoints(glSegmentC, segmentC->pointA->x,segmentC->pointA->y,segmentC->pointB->x,segmentC->pointB->y);
	CLDataList_addData(self->glSegments, glSegmentA);
	CLDataList_addData(self->glSegments, glSegmentB);
	CLDataList_addData(self->glSegments, glSegmentC);
}
void SceneSlope_destruct (struct SceneSlope* self ) 
{
	printf("\nScene destruct");
	struct CLLink*pointLink=self->glPoints->head;
	while(pointLink!=NULL)
	{
		struct GLPointP2*glPoint=pointLink->data;
		glPoint->vertexes=NULL;
		glPoint->_class->release( (void*) glPoint->_components[0] );
		pointLink=pointLink->next;
	}
	self->glPoints->_class->release( (void*) self->glPoints->_components[0] );
	struct CLLink*segmentLink=self->glSegments->head;
	while(segmentLink!=NULL)
	{
		struct GLSegment*glSegment=segmentLink->data;
		glSegment->_class->release( (void*) glSegment->_components[0] );
		segmentLink=segmentLink->next;
	}
	self->glSegments->_class->release( (void*) self->glSegments->_components[0] );
	struct CLLink*massLink=self->masses->head;
	while(massLink!=NULL)
	{
		struct PLMass*mass=massLink->data;
		mass->_class->release( (void*) mass->_components[0] );
		massLink=massLink->next;
	}
	self->masses->_class->release( (void*) self->masses->_components[0] );
	struct CLLink*spacerLink=self->spacers->head;
	while(spacerLink!=NULL)
	{
		struct PLSpacer*spacer=spacerLink->data;
		spacer->_class->release( (void*) spacer->_components[0] );
		spacerLink=spacerLink->next;
	}
	self->spacers->_class->release( (void*) self->spacers->_components[0] );
	struct CLLink*wallLink=self->segments->head;
	while(wallLink!=NULL)
	{
		struct PLSegment*wall=wallLink->data;
		wall->_class->release( (void*) wall->_components[0] );
		wallLink=wallLink->next;
	}
	self->segments->_class->release( (void*) self->segments->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void SceneSlope_init (struct SceneSlope* self ) 
{
	self->retainCount=1;
}
void SceneSlope_retain (struct SceneSlope* self ) 
{
	self->retainCount=self->retainCount+1;
}
void SceneSlope_release (struct SceneSlope* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void SceneSlope_describe (struct SceneSlope* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void SceneParticle_CreateClass( )
{
	SceneParticle_ClassInstance=malloc(sizeof(struct SceneParticle_Class));
	SceneParticle_ClassInstance->className="SceneParticle";
	SceneParticle_ClassInstance->classId=&SceneParticle_ClassInstance;
	SceneParticle_ClassInstance->initWithDimensions=SceneParticle_initWithDimensions;
	SceneParticle_ClassInstance->className_Scene="Scene";
	SceneParticle_ClassInstance->classId_Scene=&Scene_ClassInstance;
	SceneParticle_ClassInstance->initWithDimensions_Scene=SceneParticle_initWithDimensions;
	SceneParticle_ClassInstance->destruct=SceneParticle_destruct;
	SceneParticle_ClassInstance->className_CLObject="CLObject";
	SceneParticle_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	SceneParticle_ClassInstance->init=SceneParticle_init;
	SceneParticle_ClassInstance->destruct_CLObject=SceneParticle_destruct;
	SceneParticle_ClassInstance->retain=SceneParticle_retain;
	SceneParticle_ClassInstance->release=SceneParticle_release;
	SceneParticle_ClassInstance->describe=SceneParticle_describe;
	
}
struct SceneParticle* SceneParticle_alloc( )
{
	struct SceneParticle* result;
	if(SceneParticle_ClassInstance==NULL)SceneParticle_CreateClass( );
	result=malloc(sizeof(struct SceneParticle));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(SceneParticle_ClassInstance->className);
	result->_components_Scene=result->_components;
	result->_class_Scene=(void*)&(SceneParticle_ClassInstance->className_Scene);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(SceneParticle_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_Scene);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void SceneParticle_initWithDimensions (struct SceneParticle* self, float theWidth , float theHeight ) 
{
	Scene_initWithDimensions(( cast_object( &Scene_ClassInstance , self)),theWidth,theHeight);
	struct PLMass*massA=PLMass_alloc();
	struct PLVector*vectorA=PLVector_alloc();
	struct PLVector*vectorB=PLVector_alloc();
	struct PLSegment*segmentA=PLSegment_alloc();
	PLMass_init(massA );
	massA->position->x=self->width/2;
	massA->position->y=self->height-200;
	PLVector_initWithPoints(vectorA, 0,10);
	PLVector_initWithPoints(vectorB, self->width,10);
	PLSegment_initWithVectors(segmentA, vectorA,vectorB);
	vectorA->_class->release( (void*) vectorA->_components[0] );
	vectorB->_class->release( (void*) vectorB->_components[0] );
	CLDataList_addData(self->masses, massA);
	CLDataList_addData(self->segments, segmentA);
	struct GLPointP2*glPoint=GLPointP2_alloc();
	glPoint->_class->initWithPoints( (void*) glPoint->_components[0], massA->position->x,massA->position->y);
	free(glPoint->vertexes);
	printf("\nmass ");
	massA->_class->describe( (void*) massA->_components[0] );
	glPoint->vertexes=(void*)&(massA->position->x);
	struct GLSegment*glSegmentA=GLSegment_alloc();
	GLSegment_initWithPoints(glSegmentA, segmentA->pointA->x,segmentA->pointA->y,segmentA->pointB->x,segmentA->pointB->y);
	CLDataList_addData(self->glPoints, glPoint);
	CLDataList_addData(self->glSegments, glSegmentA);
}
void SceneParticle_destruct (struct SceneParticle* self ) 
{
	printf("\nScene destruct");
	struct CLLink*pointLink=self->glPoints->head;
	while(pointLink!=NULL)
	{
		struct GLPointP2*glPoint=pointLink->data;
		glPoint->vertexes=NULL;
		glPoint->_class->release( (void*) glPoint->_components[0] );
		pointLink=pointLink->next;
	}
	self->glPoints->_class->release( (void*) self->glPoints->_components[0] );
	struct CLLink*segmentLink=self->glSegments->head;
	while(segmentLink!=NULL)
	{
		struct GLSegment*glSegment=segmentLink->data;
		glSegment->_class->release( (void*) glSegment->_components[0] );
		segmentLink=segmentLink->next;
	}
	self->glSegments->_class->release( (void*) self->glSegments->_components[0] );
	struct CLLink*massLink=self->masses->head;
	while(massLink!=NULL)
	{
		struct PLMass*mass=massLink->data;
		mass->_class->release( (void*) mass->_components[0] );
		massLink=massLink->next;
	}
	self->masses->_class->release( (void*) self->masses->_components[0] );
	struct CLLink*spacerLink=self->spacers->head;
	while(spacerLink!=NULL)
	{
		struct PLSpacer*spacer=spacerLink->data;
		spacer->_class->release( (void*) spacer->_components[0] );
		spacerLink=spacerLink->next;
	}
	self->spacers->_class->release( (void*) self->spacers->_components[0] );
	struct CLLink*wallLink=self->segments->head;
	while(wallLink!=NULL)
	{
		struct PLSegment*wall=wallLink->data;
		wall->_class->release( (void*) wall->_components[0] );
		wallLink=wallLink->next;
	}
	self->segments->_class->release( (void*) self->segments->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void SceneParticle_init (struct SceneParticle* self ) 
{
	self->retainCount=1;
}
void SceneParticle_retain (struct SceneParticle* self ) 
{
	self->retainCount=self->retainCount+1;
}
void SceneParticle_release (struct SceneParticle* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void SceneParticle_describe (struct SceneParticle* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLPointP2_CreateClass( )
{
	GLPointP2_ClassInstance=malloc(sizeof(struct GLPointP2_Class));
	GLPointP2_ClassInstance->className="GLPointP2";
	GLPointP2_ClassInstance->classId=&GLPointP2_ClassInstance;
	GLPointP2_ClassInstance->initWithPoints=GLPointP2_initWithPoints;
	GLPointP2_ClassInstance->className_GLDrawable="GLDrawable";
	GLPointP2_ClassInstance->classId_GLDrawable=&GLDrawable_ClassInstance;
	GLPointP2_ClassInstance->init=GLPointP2_init;
	GLPointP2_ClassInstance->destruct=GLPointP2_destruct;
	GLPointP2_ClassInstance->className_CLObject="CLObject";
	GLPointP2_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLPointP2_ClassInstance->init_CLObject=GLPointP2_init;
	GLPointP2_ClassInstance->destruct_CLObject=GLPointP2_destruct;
	GLPointP2_ClassInstance->retain=GLPointP2_retain;
	GLPointP2_ClassInstance->release=GLPointP2_release;
	GLPointP2_ClassInstance->describe=GLPointP2_describe;
	
}
struct GLPointP2* GLPointP2_alloc( )
{
	struct GLPointP2* result;
	if(GLPointP2_ClassInstance==NULL)GLPointP2_CreateClass( );
	result=malloc(sizeof(struct GLPointP2));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLPointP2_ClassInstance->className);
	result->_components_GLDrawable=result->_components;
	result->_class_GLDrawable=(void*)&(GLPointP2_ClassInstance->className_GLDrawable);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLPointP2_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLDrawable);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLPointP2_initWithPoints (struct GLPointP2* self, GLfloat theX , GLfloat theY ) 
{
	GLDrawable_init(( cast_object( &GLDrawable_ClassInstance , self)));
	self->mode=GL_POINTS;
	self->texture=0;
	self->indexCount=1;
	self->vertexCount=1;
	self->vertexesSize=sizeof(GLfloat)*2*self->vertexCount;
	self->indexesSize=sizeof(GLushort)*self->indexCount;
	self->vertexes=malloc(self->vertexesSize);
	self->indexes=malloc(self->indexesSize);
	self->vertexes[0]=theX;
	self->vertexes[1]=theY;
	self->indexes[0]=0;
}
void GLPointP2_init (struct GLPointP2* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
}
void GLPointP2_destruct (struct GLPointP2* self ) 
{
	free(self->vertexes);
	free(self->indexes);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLPointP2_retain (struct GLPointP2* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLPointP2_release (struct GLPointP2* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLPointP2_describe (struct GLPointP2* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLRectPT22_CreateClass( )
{
	GLRectPT22_ClassInstance=malloc(sizeof(struct GLRectPT22_Class));
	GLRectPT22_ClassInstance->className="GLRectPT22";
	GLRectPT22_ClassInstance->classId=&GLRectPT22_ClassInstance;
	GLRectPT22_ClassInstance->init=GLRectPT22_init;
	GLRectPT22_ClassInstance->flipTexture=GLRectPT22_flipTexture;
	GLRectPT22_ClassInstance->destruct=GLRectPT22_destruct;
	GLRectPT22_ClassInstance->contains=GLRectPT22_contains;
	GLRectPT22_ClassInstance->className_GLDrawablePT22="GLDrawablePT22";
	GLRectPT22_ClassInstance->classId_GLDrawablePT22=&GLDrawablePT22_ClassInstance;
	GLRectPT22_ClassInstance->init_GLDrawablePT22=GLRectPT22_init;
	GLRectPT22_ClassInstance->destruct_GLDrawablePT22=GLRectPT22_destruct;
	GLRectPT22_ClassInstance->origo=GLRectPT22_origo;
	GLRectPT22_ClassInstance->move=GLRectPT22_move;
	GLRectPT22_ClassInstance->scale=GLRectPT22_scale;
	GLRectPT22_ClassInstance->className_GLDrawable="GLDrawable";
	GLRectPT22_ClassInstance->classId_GLDrawable=&GLDrawable_ClassInstance;
	GLRectPT22_ClassInstance->init_GLDrawable=GLRectPT22_init;
	GLRectPT22_ClassInstance->destruct_GLDrawable=GLRectPT22_destruct;
	GLRectPT22_ClassInstance->className_CLObject="CLObject";
	GLRectPT22_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLRectPT22_ClassInstance->init_CLObject=GLRectPT22_init;
	GLRectPT22_ClassInstance->destruct_CLObject=GLRectPT22_destruct;
	GLRectPT22_ClassInstance->retain=GLRectPT22_retain;
	GLRectPT22_ClassInstance->release=GLRectPT22_release;
	GLRectPT22_ClassInstance->describe=GLRectPT22_describe;
	
}
struct GLRectPT22* GLRectPT22_alloc( )
{
	struct GLRectPT22* result;
	if(GLRectPT22_ClassInstance==NULL)GLRectPT22_CreateClass( );
	result=malloc(sizeof(struct GLRectPT22));
	result->_components=malloc(sizeof(void*)*5);
	result->_class=(void*)&(GLRectPT22_ClassInstance->className);
	result->_components_GLDrawablePT22=result->_components;
	result->_class_GLDrawablePT22=(void*)&(GLRectPT22_ClassInstance->className_GLDrawablePT22);
	result->_components_GLDrawable=result->_components;
	result->_class_GLDrawable=(void*)&(GLRectPT22_ClassInstance->className_GLDrawable);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLRectPT22_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLDrawablePT22);
	result->_components[2]=&(result->_class_GLDrawable);
	result->_components[3]=&(result->_class_CLObject);
	result->_components[4]=NULL;
	return result;
}
void GLRectPT22_init (struct GLRectPT22* self, GLuint theTexture ) 
{
	GLDrawablePT22_init(( cast_object( &GLDrawablePT22_ClassInstance , self)));
	self->mode=GL_TRIANGLE_STRIP;
	self->texture=theTexture;
	self->indexCount=4;
	self->vertexCount=4;
	self->indexesSize=sizeof(GLushort)*self->indexCount;
	self->vertexesSize=sizeof(GLfloat)*4*self->vertexCount;
	self->indexes=malloc(self->indexesSize);
	self->vertexes=malloc(self->vertexesSize);
	const GLfloat constva[]=
	{
		0.0,0.0,0.0,0.0,0.0,1.0,0.0,1.0,1.0,0.0,1.0,0.0,1.0,1.0,1.0,1.0
	}
	;
	const GLushort constia[]=
	{
		0,2,1,3
	}
	;
	memcpy(self->vertexes,constva,self->vertexesSize);
	memcpy(self->indexes,constia,self->indexesSize);
}
void GLRectPT22_flipTexture (struct GLRectPT22* self ) 
{
	float temp=self->vertexes[3];
	self->vertexes[3]=self->vertexes[7];
	self->vertexes[7]=temp;
	temp=self->vertexes[11];
	self->vertexes[11]=self->vertexes[15];
	self->vertexes[15]=temp;
}
void GLRectPT22_destruct (struct GLRectPT22* self ) 
{
	GLDrawablePT22_destruct(( cast_object( &GLDrawablePT22_ClassInstance , self)));
}
char GLRectPT22_contains (struct GLRectPT22* self, float theX , float theY ) 
{
	return(theX>=self->dx&&theX<=self->dx+self->sx&&theY>=self->dy&&theY<=self->dy+self->sy);
}
void GLRectPT22_origo (struct GLRectPT22* self, float theX , float theY ) 
{
	for(int index=0;
	index<self->vertexCount*4;
	index+=4)
	{
		self->vertexes[index]+=-self->dx+theX;
		self->vertexes[index+1]+=-self->dy+theY;
	}
	self->dx=theX;
	self->dy=theY;
}
void GLRectPT22_move (struct GLRectPT22* self, float theX , float theY ) 
{
	self->dx+=theX;
	self->dy+=theY;
	for(int index=0;
	index<self->vertexCount*4;
	index+=4)
	{
		self->vertexes[index]+=theX;
		self->vertexes[index+1]+=theY;
	}
}
void GLRectPT22_scale (struct GLRectPT22* self, float theX , float theY ) 
{
	self->sx*=theX;
	self->sy*=theY;
	for(int index=0;
	index<self->vertexCount*4;
	index+=4)
	{
		self->vertexes[index]*=theX;
		self->vertexes[index+1]*=theY;
	}
}
void GLRectPT22_retain (struct GLRectPT22* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLRectPT22_release (struct GLRectPT22* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLRectPT22_describe (struct GLRectPT22* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void ShaderP2_CreateClass( )
{
	ShaderP2_ClassInstance=malloc(sizeof(struct ShaderP2_Class));
	ShaderP2_ClassInstance->className="ShaderP2";
	ShaderP2_ClassInstance->classId=&ShaderP2_ClassInstance;
	ShaderP2_ClassInstance->init=ShaderP2_init;
	ShaderP2_ClassInstance->destruct=ShaderP2_destruct;
	ShaderP2_ClassInstance->className_CLObject="CLObject";
	ShaderP2_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	ShaderP2_ClassInstance->init_CLObject=ShaderP2_init;
	ShaderP2_ClassInstance->destruct_CLObject=ShaderP2_destruct;
	ShaderP2_ClassInstance->retain=ShaderP2_retain;
	ShaderP2_ClassInstance->release=ShaderP2_release;
	ShaderP2_ClassInstance->describe=ShaderP2_describe;
	
}
struct ShaderP2* ShaderP2_alloc( )
{
	struct ShaderP2* result;
	if(ShaderP2_ClassInstance==NULL)ShaderP2_CreateClass( );
	result=malloc(sizeof(struct ShaderP2));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(ShaderP2_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(ShaderP2_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void ShaderP2_init (struct ShaderP2* self ) 
{
	printf("\nShaderP2 init");
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	const char*SIMPLE_VERTEX="attribute   vec4 positionVector;\n""uniform     mat4 projectionMatrix;\n""void main ( )\n""{\n""gl_Position     = projectionMatrix * positionVector;\n""}\n";
	const char*SIMPLE_FRAGMENT="void main( )\n""{\n""gl_FragColor = vec4( 0.0 , 0.0 , 0.0 , 1.0 );\n""}\n";
	self->shader=GLShader_alloc( );
	GLShader_init(self->shader, "SimpleShader");
	GLShader_addVertexShader(self->shader, SIMPLE_VERTEX);
	GLShader_addFragmentShader(self->shader, SIMPLE_FRAGMENT);
	GLShader_addAttributeLocation(self->shader, 0,2,"positionVector");
	GLShader_addUniformIdentifier(self->shader, "projectionMatrix");
	GLShader_link(self->shader );
}
void ShaderP2_destruct (struct ShaderP2* self ) 
{
	printf("\nShaderP2 destruct");
	self->shader->_class->release( (void*) self->shader->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void ShaderP2_retain (struct ShaderP2* self ) 
{
	self->retainCount=self->retainCount+1;
}
void ShaderP2_release (struct ShaderP2* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void ShaderP2_describe (struct ShaderP2* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLSegment_CreateClass( )
{
	GLSegment_ClassInstance=malloc(sizeof(struct GLSegment_Class));
	GLSegment_ClassInstance->className="GLSegment";
	GLSegment_ClassInstance->classId=&GLSegment_ClassInstance;
	GLSegment_ClassInstance->initWithPoints=GLSegment_initWithPoints;
	GLSegment_ClassInstance->className_GLDrawable="GLDrawable";
	GLSegment_ClassInstance->classId_GLDrawable=&GLDrawable_ClassInstance;
	GLSegment_ClassInstance->init=GLSegment_init;
	GLSegment_ClassInstance->destruct=GLSegment_destruct;
	GLSegment_ClassInstance->className_CLObject="CLObject";
	GLSegment_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLSegment_ClassInstance->init_CLObject=GLSegment_init;
	GLSegment_ClassInstance->destruct_CLObject=GLSegment_destruct;
	GLSegment_ClassInstance->retain=GLSegment_retain;
	GLSegment_ClassInstance->release=GLSegment_release;
	GLSegment_ClassInstance->describe=GLSegment_describe;
	
}
struct GLSegment* GLSegment_alloc( )
{
	struct GLSegment* result;
	if(GLSegment_ClassInstance==NULL)GLSegment_CreateClass( );
	result=malloc(sizeof(struct GLSegment));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLSegment_ClassInstance->className);
	result->_components_GLDrawable=result->_components;
	result->_class_GLDrawable=(void*)&(GLSegment_ClassInstance->className_GLDrawable);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLSegment_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLDrawable);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLSegment_initWithPoints (struct GLSegment* self, GLfloat theAx , GLfloat theAy , GLfloat theBx , GLfloat theBy ) 
{
	GLDrawable_init(( cast_object( &GLDrawable_ClassInstance , self)));
	self->texture=0;
	self->mode=GL_LINE_STRIP;
	self->indexCount=2;
	self->vertexCount=2;
	self->vertexesSize=sizeof(GLfloat)*2*self->vertexCount;
	self->indexesSize=sizeof(GLushort)*self->indexCount;
	self->vertexes=malloc(self->vertexesSize);
	self->indexes=malloc(self->indexesSize);
	self->vertexes[0]=theAx;
	self->vertexes[1]=theAy;
	self->vertexes[2]=theBx;
	self->vertexes[3]=theBy;
	self->indexes[0]=0;
	self->indexes[1]=1;
}
void GLSegment_init (struct GLSegment* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
}
void GLSegment_destruct (struct GLSegment* self ) 
{
	free(self->vertexes);
	free(self->indexes);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLSegment_retain (struct GLSegment* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLSegment_release (struct GLSegment* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLSegment_describe (struct GLSegment* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void ShaderPT22_CreateClass( )
{
	ShaderPT22_ClassInstance=malloc(sizeof(struct ShaderPT22_Class));
	ShaderPT22_ClassInstance->className="ShaderPT22";
	ShaderPT22_ClassInstance->classId=&ShaderPT22_ClassInstance;
	ShaderPT22_ClassInstance->init=ShaderPT22_init;
	ShaderPT22_ClassInstance->destruct=ShaderPT22_destruct;
	ShaderPT22_ClassInstance->className_CLObject="CLObject";
	ShaderPT22_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	ShaderPT22_ClassInstance->init_CLObject=ShaderPT22_init;
	ShaderPT22_ClassInstance->destruct_CLObject=ShaderPT22_destruct;
	ShaderPT22_ClassInstance->retain=ShaderPT22_retain;
	ShaderPT22_ClassInstance->release=ShaderPT22_release;
	ShaderPT22_ClassInstance->describe=ShaderPT22_describe;
	
}
struct ShaderPT22* ShaderPT22_alloc( )
{
	struct ShaderPT22* result;
	if(ShaderPT22_ClassInstance==NULL)ShaderPT22_CreateClass( );
	result=malloc(sizeof(struct ShaderPT22));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(ShaderPT22_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(ShaderPT22_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void ShaderPT22_init (struct ShaderPT22* self ) 
{
	printf("\nShaderPT22 init");
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	#ifdef OSX				
	const char*TEXTURE_VERTEX="attribute   vec4 positionVector;\n""attribute   vec2 textureVector;\n""varying 	 vec2 textureVectorOut;\n""uniform     mat4 projectionMatrix;\n""void main ( )\n""{\n""gl_Position     = projectionMatrix * positionVector;\n""textureVectorOut = textureVector;\n""}\n";
	const char*TEXTURE_FRAGMENT="varying vec2 textureVectorOut;\n""uniform sampler2D texture;\n""void main ( )\n""{\n""gl_FragColor = texture2D( texture , textureVectorOut);\n""}\n";
	#endif
	#if defined(IOS)
	const char*TEXTURE_VERTEX_ES="attribute   vec4 positionVector;\n""attribute   vec2 textureVector;\n""varying 	 lowp vec2 textureVectorOut;\n""uniform     mat4 projectionMatrix;\n""void main ( )\n""{\n""gl_Position     = projectionMatrix * positionVector;\n""textureVectorOut = textureVector;\n""}\n";
	const char*TEXTURE_FRAGMENT_ES="varying lowp vec4 varyingColor;\n""void main( )\n""{\n""gl_FragColor = vec4( 0.0 , 0.0 , 0.0 , 1.0 );\n""}\n";
	#endif
	self->shader=GLShader_alloc( );
	GLShader_init(self->shader, "TextureShader");
	#ifdef OSX
	GLShader_addVertexShader(self->shader, TEXTURE_VERTEX);
	GLShader_addFragmentShader(self->shader, TEXTURE_FRAGMENT);
	#endif
	#if defined(IOS) || defined(TIZ)
	GLShader_addVertexShader(self->shader, TEXTURE_VERTEX_ES);
	GLShader_addFragmentShader(self->shader, TEXTURE_FRAGMENT_ES);
	#endif
	GLShader_addAttributeLocation(self->shader, 0,2,"positionVector");
	GLShader_addAttributeLocation(self->shader, 1,2,"textureVector");
	GLShader_addUniformIdentifier(self->shader, "projectionMatrix");
	GLShader_addUniformIdentifier(self->shader, "texture");
	GLShader_link(self->shader );
}
void ShaderPT22_destruct (struct ShaderPT22* self ) 
{
	printf("\nShaderPT22 destruct");
	self->shader->_class->release( (void*) self->shader->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void ShaderPT22_retain (struct ShaderPT22* self ) 
{
	self->retainCount=self->retainCount+1;
}
void ShaderPT22_release (struct ShaderPT22* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void ShaderPT22_describe (struct ShaderPT22* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void PLUniverse_CreateClass( )
{
	PLUniverse_ClassInstance=malloc(sizeof(struct PLUniverse_Class));
	PLUniverse_ClassInstance->className="PLUniverse";
	PLUniverse_ClassInstance->classId=&PLUniverse_ClassInstance;
	PLUniverse_ClassInstance->init=PLUniverse_init;
	PLUniverse_ClassInstance->destruct=PLUniverse_destruct;
	PLUniverse_ClassInstance->reset=PLUniverse_reset;
	PLUniverse_ClassInstance->addMass=PLUniverse_addMass;
	PLUniverse_ClassInstance->removeMass=PLUniverse_removeMass;
	PLUniverse_ClassInstance->addWall=PLUniverse_addWall;
	PLUniverse_ClassInstance->removeWall=PLUniverse_removeWall;
	PLUniverse_ClassInstance->addSpacer=PLUniverse_addSpacer;
	PLUniverse_ClassInstance->removeSpacer=PLUniverse_removeSpacer;
	PLUniverse_ClassInstance->update=PLUniverse_update;
	PLUniverse_ClassInstance->bounceMass=PLUniverse_bounceMass;
	PLUniverse_ClassInstance->className_CLObject="CLObject";
	PLUniverse_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PLUniverse_ClassInstance->init_CLObject=PLUniverse_init;
	PLUniverse_ClassInstance->destruct_CLObject=PLUniverse_destruct;
	PLUniverse_ClassInstance->retain=PLUniverse_retain;
	PLUniverse_ClassInstance->release=PLUniverse_release;
	PLUniverse_ClassInstance->describe=PLUniverse_describe;
	
}
struct PLUniverse* PLUniverse_alloc( )
{
	struct PLUniverse* result;
	if(PLUniverse_ClassInstance==NULL)PLUniverse_CreateClass( );
	result=malloc(sizeof(struct PLUniverse));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PLUniverse_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PLUniverse_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PLUniverse_init (struct PLUniverse* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->walls=CLDataList_alloc();
	self->masses=CLDataList_alloc();
	self->spacers=CLDataList_alloc();
	self->gravity=PLVector_alloc();
	self->bounceMassNormal=PLVector_alloc();
	self->bounceMassParallel=PLVector_alloc();
	self->collidingWallsPerStep=CLDataList_alloc();
	self->collidingNormalsPerStep=CLDataList_alloc();
	self->collidingParallelsPerStep=CLDataList_alloc();
	CLDataList_init(self->walls );
	CLDataList_init(self->masses );
	CLDataList_init(self->spacers );
	self->collidingWallsPerStep->_class->init( (void*) self->collidingWallsPerStep->_components[0] );
	self->collidingNormalsPerStep->_class->init( (void*) self->collidingNormalsPerStep->_components[0] );
	self->collidingParallelsPerStep->_class->init( (void*) self->collidingParallelsPerStep->_components[0] );
	PLVector_initWithPoints(self->gravity, 0,-.5);
	PLVector_initWithPoints(self->bounceMassNormal, 0,0);
	PLVector_initWithPoints(self->bounceMassParallel, 0,0);
}
void PLUniverse_destruct (struct PLUniverse* self ) 
{
	printf("Universe destruct %i\n",(int)self);
	self->walls->_class->release( (void*) self->walls->_components[0] );
	self->masses->_class->release( (void*) self->masses->_components[0] );
	self->spacers->_class->release( (void*) self->spacers->_components[0] );
	self->gravity->_class->release( (void*) self->gravity->_components[0] );
	self->bounceMassNormal->_class->release( (void*) self->bounceMassNormal->_components[0] );
	self->bounceMassParallel->_class->release( (void*) self->bounceMassParallel->_components[0] );
	self->collidingWallsPerStep->_class->release( (void*) self->collidingWallsPerStep->_components[0] );
	self->collidingNormalsPerStep->_class->release( (void*) self->collidingNormalsPerStep->_components[0] );
	self->collidingParallelsPerStep->_class->release( (void*) self->collidingParallelsPerStep->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void PLUniverse_reset (struct PLUniverse* self ) 
{
	CLDataList_removeAllDatas(self->walls );
	CLDataList_removeAllDatas(self->masses );
	CLDataList_removeAllDatas(self->spacers );
	PLVector_setXY(self->bounceMassNormal, 0,0);
	PLVector_setXY(self->bounceMassParallel, 0,0);
}
void PLUniverse_addMass (struct PLUniverse* self, struct PLMass * theMass ) 
{
	theMass->_class->retain( (void*) theMass->_components[0] );
	CLDataList_addData(self->masses, theMass);
}
void PLUniverse_removeMass (struct PLUniverse* self, struct PLMass * theMass ) 
{
	CLDataList_removeData(self->masses, theMass);
	theMass->_class->release( (void*) theMass->_components[0] );
}
void PLUniverse_addWall (struct PLUniverse* self, struct PLSegment * theWall ) 
{
	theWall->_class->retain( (void*) theWall->_components[0] );
	CLDataList_addData(self->walls, theWall);
}
void PLUniverse_removeWall (struct PLUniverse* self, struct PLSegment * theWall ) 
{
	CLDataList_removeData(self->walls, theWall);
	theWall->_class->release( (void*) theWall->_components[0] );
}
void PLUniverse_addSpacer (struct PLUniverse* self, struct PLSpacer * theSpacer ) 
{
	theSpacer->_class->retain( (void*) theSpacer->_components[0] );
	CLDataList_addData(self->spacers, theSpacer);
}
void PLUniverse_removeSpacer (struct PLUniverse* self, struct PLSpacer * theSpacer ) 
{
	CLDataList_removeData(self->spacers, theSpacer);
	theSpacer->_class->release( (void*) theSpacer->_components[0] );
}
void PLUniverse_update (struct PLUniverse* self ) 
{
	struct CLLink*link;
	link=self->masses->head;
	while(link!=NULL)
	{
		struct PLMass*mass=link->data;
		PLVector_addVector(( cast_object( &PLVector_ClassInstance , mass->force)),self->gravity);
		link=link->next;
	}
	link=self->spacers->head;
	while(link!=NULL)
	{
		struct PLSpacer*spacer=link->data;
		PLSpacer_respace(spacer );
		link=link->next;
	}
	link=self->masses->head;
	while(link!=NULL)
	{
		struct PLMass*linkMass=link->data;
		struct CLDataList*baseWalls=linkMass->baseWalls;
		if(baseWalls->length>0)
		{
			if(baseWalls->length==1)
			{
				struct PLSegment*baseWallSegment=CLDataList_dataAtIndex(( cast_object( &CLDataList_ClassInstance , baseWalls)),0);
				PLSegment_slideMass(baseWallSegment, linkMass);
				PLVector_multiply(( cast_object( &PLVector_ClassInstance , linkMass->force)),linkMass->friction);
				CLDataList_addData(( cast_object( &CLDataList_ClassInstance , linkMass->lastTouchedWalls)),baseWallSegment);
			}
			else
			{
				PLVector_reset(( cast_object( &PLVector_ClassInstance , linkMass->force)));
			}
		}
		link=link->next;
	}
	link=self->masses->head;
	while(link!=NULL)
	{
		struct PLMass*linkMass=link->data;
		float originalLength=linkMass->force->length;
		while( PLUniverse_bounceMass(self, linkMass)>0)
		{
		}
		if(linkMass->hadCollision==1)
		{
			struct CLDataList*baseWalls=linkMass->baseWalls;
			if(baseWalls->length==0)
			{
				PLVector_addVector(( cast_object( &PLVector_ClassInstance , linkMass->position)),linkMass->force);
				if(linkMass->force->length!=0)PLVector_multiply(( cast_object( &PLVector_ClassInstance , linkMass->force)),originalLength/linkMass->force->length);
				PLVector_multiply(( cast_object( &PLVector_ClassInstance , linkMass->force)),linkMass->buoyancy);
				if(linkMass->force->length<1)
				{
					CLDataList_addDatasInDataList(baseWalls, linkMass->touchedWalls);
				}
			}
			else
			{
				if(linkMass->force->length<1)
				{
					CLDataList_addDatasInDataList(baseWalls, linkMass->touchedWalls);
				}
				else
				{
					CLDataList_removeAllDatas(( cast_object( &CLDataList_ClassInstance , baseWalls)));
				}
			}
		}
		link=link->next;
	}
	link=self->masses->head;
	while(link!=NULL)
	{
		struct PLMass*linkMass=link->data;
		if(linkMass->hadCollision==0)
		{
			PLVector_addVector(( cast_object( &PLVector_ClassInstance , linkMass->position)),linkMass->force);
		}
		linkMass->hadCollision=0;
		link=link->next;
	}
}
char PLUniverse_bounceMass (struct PLUniverse* self, struct PLMass * theMass ) 
{
	CLDataList_removeAllDatas(self->collidingWallsPerStep );
	CLDataList_removeAllDatas(self->collidingNormalsPerStep );
	CLDataList_removeAllDatas(self->collidingParallelsPerStep );
	struct CLLink*link=self->walls->head;
	while(link!=NULL)
	{
		struct PLSegment*linkWall=link->data;
		char contains=CLDataList_containsData(( cast_object( &CLDataList_ClassInstance , theMass->lastTouchedWalls)),linkWall);
		if(contains==0)PLSegment_collideMass(( cast_object( &PLSegment_ClassInstance , linkWall)),theMass,self->collidingWallsPerStep,self->collidingNormalsPerStep,self->collidingParallelsPerStep);
		link=link->next;
	}
	if(self->collidingWallsPerStep->length>0)
	{
		PLVector_setXY(self->bounceMassNormal, 0,0);
		PLVector_setXY(self->bounceMassParallel, 0,0);
		struct CLLink*normalsLink=self->collidingNormalsPerStep->head;
		while(normalsLink!=NULL)
		{
			struct PLVector*normalsVector=normalsLink->data;
			PLVector_addVector(( cast_object( &PLVector_ClassInstance , self->bounceMassNormal)),normalsVector);
			normalsLink=normalsLink->next;
		}
		struct CLLink*parallelsLink=self->collidingParallelsPerStep->head;
		while(parallelsLink!=NULL)
		{
			struct PLVector*parallelsVector=parallelsLink->data;
			PLVector_addVector(( cast_object( &PLVector_ClassInstance , self->bounceMassParallel)),parallelsVector);
			parallelsLink=parallelsLink->next;
		}
		if(self->collidingWallsPerStep->length==1)
		{
			PLVector_addVector(( cast_object( &PLVector_ClassInstance , self->bounceMassParallel)),self->bounceMassNormal);
			PLVector_set(( cast_object( &PLVector_ClassInstance , theMass->force)),self->bounceMassParallel);
		}
		else
		{
			PLVector_set(( cast_object( &PLVector_ClassInstance , theMass->force)),self->bounceMassNormal);
		}
		CLDataList_removeAllDatas(( cast_object( &CLDataList_ClassInstance , theMass->touchedWalls)));
		CLDataList_addDatasInDataList(( cast_object( &CLDataList_ClassInstance , theMass->touchedWalls)),self->collidingWallsPerStep);
	}
	CLDataList_removeAllDatas(( cast_object( &CLDataList_ClassInstance , theMass->lastTouchedWalls)));
	CLDataList_addDatasInDataList(( cast_object( &CLDataList_ClassInstance , theMass->lastTouchedWalls)),self->collidingWallsPerStep);
	return self->collidingWallsPerStep->length>0;
}
void PLUniverse_retain (struct PLUniverse* self ) 
{
	self->retainCount=self->retainCount+1;
}
void PLUniverse_release (struct PLUniverse* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void PLUniverse_describe (struct PLUniverse* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void CLDataList_CreateClass( )
{
	CLDataList_ClassInstance=malloc(sizeof(struct CLDataList_Class));
	CLDataList_ClassInstance->className="CLDataList";
	CLDataList_ClassInstance->classId=&CLDataList_ClassInstance;
	CLDataList_ClassInstance->init=CLDataList_init;
	CLDataList_ClassInstance->destruct=CLDataList_destruct;
	CLDataList_ClassInstance->addData=CLDataList_addData;
	CLDataList_ClassInstance->addDataAtIndex=CLDataList_addDataAtIndex;
	CLDataList_ClassInstance->addDatasInDataList=CLDataList_addDatasInDataList;
	CLDataList_ClassInstance->removeData=CLDataList_removeData;
	CLDataList_ClassInstance->removeDataAtIndex=CLDataList_removeDataAtIndex;
	CLDataList_ClassInstance->removeAllDatas=CLDataList_removeAllDatas;
	CLDataList_ClassInstance->dataAtIndex=CLDataList_dataAtIndex;
	CLDataList_ClassInstance->containsData=CLDataList_containsData;
	CLDataList_ClassInstance->indexOfData=CLDataList_indexOfData;
	CLDataList_ClassInstance->firstData=CLDataList_firstData;
	CLDataList_ClassInstance->lastData=CLDataList_lastData;
	CLDataList_ClassInstance->describe=CLDataList_describe;
	CLDataList_ClassInstance->className_CLObject="CLObject";
	CLDataList_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	CLDataList_ClassInstance->init_CLObject=CLDataList_init;
	CLDataList_ClassInstance->destruct_CLObject=CLDataList_destruct;
	CLDataList_ClassInstance->retain=CLDataList_retain;
	CLDataList_ClassInstance->release=CLDataList_release;
	CLDataList_ClassInstance->describe_CLObject=CLDataList_describe;
	
}
struct CLDataList* CLDataList_alloc( )
{
	struct CLDataList* result;
	if(CLDataList_ClassInstance==NULL)CLDataList_CreateClass( );
	result=malloc(sizeof(struct CLDataList));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(CLDataList_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(CLDataList_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void CLDataList_init (struct CLDataList* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLDataList_destruct (struct CLDataList* self ) 
{
	CLDataList_removeAllDatas( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void CLDataList_addData (struct CLDataList* self, void * theData ) 
{
	struct CLLink*newLink;
	newLink=malloc(sizeof(struct CLLink));
	newLink->data=theData;
	newLink->next=NULL;
	if(self->head==NULL)self->head=newLink;
	else self->last->next=newLink;
	self->last=newLink;
	self->length=self->length+1;
}
void CLDataList_addDataAtIndex (struct CLDataList* self, void * theData , unsigned long theIndex ) 
{
	struct CLLink*link;
	struct CLLink*lastLink;
	struct CLLink*newLink;
	unsigned long position;
	lastLink=NULL;
	link=self->head;
	position=0;
	while(link!=NULL)
	{
		if(position==theIndex)
		{
			newLink=malloc(sizeof(struct CLLink));
			newLink->data=theData;
			newLink->next=link;
			if(lastLink!=NULL)lastLink->next=newLink;
			else self->head=newLink;
			self->length=self->length+1;
			return;
		}
		position+=1;
		lastLink=link;
		link=link->next;
	}
}
void CLDataList_addDatasInDataList (struct CLDataList* self, struct CLDataList * theDataList ) 
{
	struct CLLink*link;
	if(theDataList->length>0)
	{
		link=theDataList->head;
		while(link!=NULL)
		{
			CLDataList_addData( self, link->data);
			link=link->next;
		}
	}
}
void CLDataList_removeData (struct CLDataList* self, void * theData ) 
{
	struct CLLink*link;
	struct CLLink*prev;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		if(link->data==theData)
		{
			if(link->next==NULL&&prev!=NULL)
			{
				prev->next=NULL;
				self->last=prev;
			}
			else if(link->next!=NULL&&prev==NULL)
			{
				self->head=link->next;
			}
			else if(link->next!=NULL&&prev!=NULL)
			{
				prev->next=link->next;
			}
			else
			{
				self->head=NULL;
				self->last=NULL;
			}
			free(link);
			self->length-=1;
			return;
		}
		prev=link;
		link=link->next;
	}
}
void * CLDataList_removeDataAtIndex (struct CLDataList* self, unsigned long theIndex ) 
{
	void*data;
	data=CLDataList_dataAtIndex( self, theIndex);
	if(data!=NULL)CLDataList_removeData( self, data);
	return data;
}
void CLDataList_removeAllDatas (struct CLDataList* self ) 
{
	struct CLLink*link;
	struct CLLink*prev;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		prev=link;
		link=link->next;
		free(prev);
	}
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void * CLDataList_dataAtIndex (struct CLDataList* self, unsigned long theIndex ) 
{
	struct CLLink*link;
	unsigned long position;
	link=self->head;
	position=0;
	while(link!=NULL)
	{
		if(position==theIndex)return link->data;
		link=link->next;
		position+=1;
	}
	return NULL;
}
char CLDataList_containsData (struct CLDataList* self, void * theData ) 
{
	struct CLLink*link;
	link=self->head;
	while(link!=NULL)
	{
		if(link->data==theData)return 1;
		link=link->next;
	}
	return 0;
}
unsigned long CLDataList_indexOfData (struct CLDataList* self, void * theData ) 
{
	unsigned long index;
	struct CLLink*link;
	index=0;
	link=self->head;
	while(link!=NULL)
	{
		if(link->data==theData)return index;
		index+=1;
		link=link->next;
	}
	return 0;
}
void * CLDataList_firstData (struct CLDataList* self ) 
{
	if(self->head!=NULL)return self->head->data;
	return NULL;
}
void * CLDataList_lastData (struct CLDataList* self ) 
{
	if(self->last!=NULL)return self->last->data;
	return NULL;
}
void CLDataList_describe (struct CLDataList* self ) 
{
	printf("\nDataList %i length %lu",(int)self,self->length);
}
void CLDataList_retain (struct CLDataList* self ) 
{
	self->retainCount=self->retainCount+1;
}
void CLDataList_release (struct CLDataList* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLTexturePixelText_CreateClass( )
{
	GLTexturePixelText_ClassInstance=malloc(sizeof(struct GLTexturePixelText_Class));
	GLTexturePixelText_ClassInstance->className="GLTexturePixelText";
	GLTexturePixelText_ClassInstance->classId=&GLTexturePixelText_ClassInstance;
	GLTexturePixelText_ClassInstance->init=GLTexturePixelText_init;
	GLTexturePixelText_ClassInstance->className_GLTexture="GLTexture";
	GLTexturePixelText_ClassInstance->classId_GLTexture=&GLTexture_ClassInstance;
	GLTexturePixelText_ClassInstance->initWithGLBitmap=GLTexturePixelText_initWithGLBitmap;
	GLTexturePixelText_ClassInstance->initWithDimensions=GLTexturePixelText_initWithDimensions;
	GLTexturePixelText_ClassInstance->destruct=GLTexturePixelText_destruct;
	GLTexturePixelText_ClassInstance->className_CLObject="CLObject";
	GLTexturePixelText_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLTexturePixelText_ClassInstance->init_CLObject=GLTexturePixelText_init;
	GLTexturePixelText_ClassInstance->destruct_CLObject=GLTexturePixelText_destruct;
	GLTexturePixelText_ClassInstance->retain=GLTexturePixelText_retain;
	GLTexturePixelText_ClassInstance->release=GLTexturePixelText_release;
	GLTexturePixelText_ClassInstance->describe=GLTexturePixelText_describe;
	
}
struct GLTexturePixelText* GLTexturePixelText_alloc( )
{
	struct GLTexturePixelText* result;
	if(GLTexturePixelText_ClassInstance==NULL)GLTexturePixelText_CreateClass( );
	result=malloc(sizeof(struct GLTexturePixelText));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLTexturePixelText_ClassInstance->className);
	result->_components_GLTexture=result->_components;
	result->_class_GLTexture=(void*)&(GLTexturePixelText_ClassInstance->className_GLTexture);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLTexturePixelText_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLTexture);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLTexturePixelText_init (struct GLTexturePixelText* self, char * theText , int theWidth , int theHeight , int theSize ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	struct TLPixelText*pixelText=TLPixelText_alloc();
	struct GLBitmapPixelText*foreGround=GLBitmapPixelText_alloc();
	struct GLBitmap*backGround=GLBitmap_alloc();
	TLPixelText_initWithCString(pixelText, theText);
	GLBitmapPixelText_initWithDimensions(foreGround, theWidth,theHeight);
	GLBitmapPixelText_drawPixelTextWithSize(foreGround, pixelText,theSize);
	foreGround->_class->addShadow( (void*) foreGround->_components[0] );
	GLBitmap_initWithDimensions(backGround, theWidth,theHeight);
	GLBitmap_fillRectangle(backGround, 0,0,theWidth,theHeight,1.0,1.0,1.0,.5);
	GLBitmap_blendBitmap(backGround, (cast_object( &GLBitmap_ClassInstance , foreGround)),0,0);
	glGenTextures(1,&self->glid);
	glBindTexture(GL_TEXTURE_2D,self->glid);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,backGround->width,backGround->height,0,GL_RGBA,GL_UNSIGNED_BYTE,backGround->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	backGround->_class->release( (void*) backGround->_components[0] );
	foreGround->_class->release( (void*) foreGround->_components[0] );
	pixelText->_class->release( (void*) pixelText->_components[0] );
}
void GLTexturePixelText_initWithGLBitmap (struct GLTexturePixelText* self, struct GLBitmap * theBitmap ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	glGenTextures(1,&self->glid);
	glBindTexture(GL_TEXTURE_2D,self->glid);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,theBitmap->width,theBitmap->height,0,GL_RGBA,GL_UNSIGNED_BYTE,theBitmap->data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void GLTexturePixelText_initWithDimensions (struct GLTexturePixelText* self, int theWidth , int theHeight ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	glGenTextures(1,&self->glid);
	glBindTexture(GL_TEXTURE_2D,self->glid);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,theWidth,theHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void GLTexturePixelText_destruct (struct GLTexturePixelText* self ) 
{
	glDeleteTextures(1,&(self->glid));
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLTexturePixelText_retain (struct GLTexturePixelText* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLTexturePixelText_release (struct GLTexturePixelText* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLTexturePixelText_describe (struct GLTexturePixelText* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLDrawable_CreateClass( )
{
	GLDrawable_ClassInstance=malloc(sizeof(struct GLDrawable_Class));
	GLDrawable_ClassInstance->className="GLDrawable";
	GLDrawable_ClassInstance->classId=&GLDrawable_ClassInstance;
	GLDrawable_ClassInstance->init=GLDrawable_init;
	GLDrawable_ClassInstance->destruct=GLDrawable_destruct;
	GLDrawable_ClassInstance->className_CLObject="CLObject";
	GLDrawable_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLDrawable_ClassInstance->init_CLObject=GLDrawable_init;
	GLDrawable_ClassInstance->destruct_CLObject=GLDrawable_destruct;
	GLDrawable_ClassInstance->retain=GLDrawable_retain;
	GLDrawable_ClassInstance->release=GLDrawable_release;
	GLDrawable_ClassInstance->describe=GLDrawable_describe;
	
}
struct GLDrawable* GLDrawable_alloc( )
{
	struct GLDrawable* result;
	if(GLDrawable_ClassInstance==NULL)GLDrawable_CreateClass( );
	result=malloc(sizeof(struct GLDrawable));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLDrawable_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLDrawable_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLDrawable_init (struct GLDrawable* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
}
void GLDrawable_destruct (struct GLDrawable* self ) 
{
	free(self->vertexes);
	free(self->indexes);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLDrawable_retain (struct GLDrawable* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLDrawable_release (struct GLDrawable* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLDrawable_describe (struct GLDrawable* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLVertexBuffer_CreateClass( )
{
	GLVertexBuffer_ClassInstance=malloc(sizeof(struct GLVertexBuffer_Class));
	GLVertexBuffer_ClassInstance->className="GLVertexBuffer";
	GLVertexBuffer_ClassInstance->classId=&GLVertexBuffer_ClassInstance;
	GLVertexBuffer_ClassInstance->init=GLVertexBuffer_init;
	GLVertexBuffer_ClassInstance->destruct=GLVertexBuffer_destruct;
	GLVertexBuffer_ClassInstance->bindBuffer=GLVertexBuffer_bindBuffer;
	GLVertexBuffer_ClassInstance->drawBuffer=GLVertexBuffer_drawBuffer;
	GLVertexBuffer_ClassInstance->addDrawables=GLVertexBuffer_addDrawables;
	GLVertexBuffer_ClassInstance->addDrawable=GLVertexBuffer_addDrawable;
	GLVertexBuffer_ClassInstance->removeDrawables=GLVertexBuffer_removeDrawables;
	GLVertexBuffer_ClassInstance->removeDrawable=GLVertexBuffer_removeDrawable;
	GLVertexBuffer_ClassInstance->updateBuffers=GLVertexBuffer_updateBuffers;
	GLVertexBuffer_ClassInstance->className_CLObject="CLObject";
	GLVertexBuffer_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLVertexBuffer_ClassInstance->init_CLObject=GLVertexBuffer_init;
	GLVertexBuffer_ClassInstance->destruct_CLObject=GLVertexBuffer_destruct;
	GLVertexBuffer_ClassInstance->retain=GLVertexBuffer_retain;
	GLVertexBuffer_ClassInstance->release=GLVertexBuffer_release;
	GLVertexBuffer_ClassInstance->describe=GLVertexBuffer_describe;
	
}
struct GLVertexBuffer* GLVertexBuffer_alloc( )
{
	struct GLVertexBuffer* result;
	if(GLVertexBuffer_ClassInstance==NULL)GLVertexBuffer_CreateClass( );
	result=malloc(sizeof(struct GLVertexBuffer));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLVertexBuffer_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLVertexBuffer_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLVertexBuffer_init (struct GLVertexBuffer* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->data=NULL;
	self->buffer=0;
	self->blocks=CLDataList_alloc();
	self->oldSize=0;
	self->changed=0;
	CLDataList_init(self->blocks );
	glGenBuffers(1,&(self->buffer));
}
void GLVertexBuffer_destruct (struct GLVertexBuffer* self ) 
{
	if(self->buffer!=0)glDeleteBuffers(1,&(self->buffer));
	if(self->data!=NULL)free(self->data);
	struct CLLink*link=self->blocks->head;
	while(link!=NULL)
	{
		struct GLVertexBlock*oneBlock=link->data;
		oneBlock->_class->release( (void*) oneBlock->_components[0] );
		link=link->next;
	}
	self->blocks->_class->release( (void*) self->blocks->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLVertexBuffer_bindBuffer (struct GLVertexBuffer* self ) 
{
	glBindBuffer(GL_ARRAY_BUFFER,self->buffer);
	if(self->changed==1)GLVertexBuffer_updateBuffers( self );
}
void GLVertexBuffer_drawBuffer (struct GLVertexBuffer* self ) 
{
	struct CLLink*blockLink=self->blocks->head;
	while(blockLink!=NULL)
	{
		struct GLVertexBlock*renderBlock=blockLink->data;
		if(renderBlock->drawables->length>0)
		{
			glBindTexture(GL_TEXTURE_2D,renderBlock->texture);
			glDrawElements(renderBlock->mode,renderBlock->indexCount,GL_UNSIGNED_SHORT,renderBlock->indexes);
		}
		blockLink=blockLink->next;
	}
}
void GLVertexBuffer_addDrawables (struct GLVertexBuffer* self, struct CLDataList * theDrawables ) 
{
	struct CLLink*link=theDrawables->head;
	while(link!=NULL)
	{
		GLVertexBuffer_addDrawable( self, link->data);
		link=link->next;
	}
}
void GLVertexBuffer_addDrawable (struct GLVertexBuffer* self, struct GLDrawable * theDrawable ) 
{
	self->changed=1;
	struct CLLink*link=self->blocks->head;
	struct GLVertexBlock*blockPick=NULL;
	while(link!=NULL)
	{
		struct GLVertexBlock*block=link->data;
		if(theDrawable->texture==block->texture&&theDrawable->mode==block->mode)
		{
			blockPick=block;
			break;
		}
		link=link->next;
	}
	if(blockPick==NULL)
	{
		blockPick=GLVertexBlock_alloc();
		GLVertexBlock_init(blockPick );
		struct CLDataList*drawables=CLDataList_alloc();
		CLDataList_init(drawables );
		blockPick->mode=theDrawable->mode;
		blockPick->texture=theDrawable->texture;
		blockPick->drawables=drawables;
		blockPick->indexCount=0;
		blockPick->indexesSize=0;
		blockPick->oldIndexesSize=0;
		blockPick->vertexCount=0;
		blockPick->vertexesSize=0;
		blockPick->indexes=NULL;
		self->blocks->_class->addData( (void*) self->blocks->_components[0], blockPick);
	}
	blockPick->drawables->_class->addData( (void*) blockPick->drawables->_components[0], theDrawable);
	blockPick->indexCount+=theDrawable->indexCount;
	blockPick->indexesSize+=theDrawable->indexesSize;
	blockPick->vertexCount+=theDrawable->vertexCount;
	blockPick->vertexesSize+=theDrawable->vertexesSize;
	theDrawable->_class->retain( (void*) theDrawable->_components[0] );
}
void GLVertexBuffer_removeDrawables (struct GLVertexBuffer* self, struct CLDataList * theDrawables ) 
{
	struct CLLink*link=theDrawables->head;
	while(link!=NULL)
	{
		GLVertexBuffer_removeDrawable( self, link->data);
		link=link->next;
	}
}
void GLVertexBuffer_removeDrawable (struct GLVertexBuffer* self, struct GLDrawable * theDrawable ) 
{
	self->changed=1;
	struct CLLink*link=self->blocks->head;
	struct GLVertexBlock*blockPick=NULL;
	while(link!=NULL)
	{
		struct GLVertexBlock*block=link->data;
		if(theDrawable->texture==block->texture&&theDrawable->mode==block->mode)
		{
			blockPick=block;
			break;
		}
		link=link->next;
	}
	if(blockPick==NULL)return;
	char contains=blockPick->drawables->_class->containsData( (void*) blockPick->drawables->_components[0], theDrawable);
	if(contains==1)
	{
		blockPick->drawables->_class->removeData( (void*) blockPick->drawables->_components[0], theDrawable);
		blockPick->indexCount-=theDrawable->indexCount;
		blockPick->indexesSize-=theDrawable->indexesSize;
		blockPick->vertexCount-=theDrawable->vertexCount;
		blockPick->vertexesSize-=theDrawable->vertexesSize;
		theDrawable->_class->release( (void*) theDrawable->_components[0] );
	}
}
void GLVertexBuffer_updateBuffers (struct GLVertexBuffer* self ) 
{
	long vertexesSize=0;
	struct CLLink*blockLink=self->blocks->head;
	while(blockLink!=NULL)
	{
		struct GLVertexBlock*renderBlock=blockLink->data;
		vertexesSize+=renderBlock->vertexesSize;
		blockLink=blockLink->next;
	}
	if(vertexesSize>0)
	{
		if(vertexesSize!=self->oldSize)
		{
			if(self->data==NULL)self->data=malloc(vertexesSize);
			else self->data=realloc(self->data,vertexesSize);
			self->oldSize=vertexesSize;
		}
		int indexOffset=0;
		GLfloat*flatData=self->data;
		blockLink=self->blocks->head;
		while(blockLink!=NULL)
		{
			struct GLVertexBlock*renderBlock=blockLink->data;
			if(renderBlock->drawables->length>0)
			{
				int renderBlockIndex=0;
				struct CLLink*drawableLink=renderBlock->drawables->head;
				if(renderBlock->indexesSize!=renderBlock->oldIndexesSize)
				{
					if(renderBlock->indexes==NULL)renderBlock->indexes=malloc(renderBlock->indexesSize);
					else renderBlock->indexes=realloc(renderBlock->indexes,renderBlock->indexesSize);
					renderBlock->oldIndexesSize=renderBlock->indexesSize;
				}
				while(drawableLink!=NULL)
				{
					struct GLDrawable*drawable=drawableLink->data;
					memcpy(flatData,drawable->vertexes,drawable->vertexesSize);
					flatData=(GLfloat*)((char*)flatData+drawable->vertexesSize);
					for(int index=0;
					index<drawable->indexCount;
					index++)
					{
						renderBlock->indexes[renderBlockIndex++]=indexOffset+drawable->indexes[index];
					}
					indexOffset+=drawable->vertexCount;
					drawableLink=drawableLink->next;
				}
			}
			blockLink=blockLink->next;
		}
		glBindBuffer(GL_ARRAY_BUFFER,self->buffer);
		glBufferData(GL_ARRAY_BUFFER,vertexesSize,self->data,GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER,self->buffer);
		glBufferData(GL_ARRAY_BUFFER,0,NULL,GL_DYNAMIC_DRAW);
	}
	self->changed=0;
}
void GLVertexBuffer_retain (struct GLVertexBuffer* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLVertexBuffer_release (struct GLVertexBuffer* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLVertexBuffer_describe (struct GLVertexBuffer* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void PLVector_CreateClass( )
{
	PLVector_ClassInstance=malloc(sizeof(struct PLVector_Class));
	PLVector_ClassInstance->className="PLVector";
	PLVector_ClassInstance->classId=&PLVector_ClassInstance;
	PLVector_ClassInstance->initWithPoints=PLVector_initWithPoints;
	PLVector_ClassInstance->set=PLVector_set;
	PLVector_ClassInstance->setXY=PLVector_setXY;
	PLVector_ClassInstance->reset=PLVector_reset;
	PLVector_ClassInstance->multiply=PLVector_multiply;
	PLVector_ClassInstance->addVector=PLVector_addVector;
	PLVector_ClassInstance->describe=PLVector_describe;
	PLVector_ClassInstance->className_CLObject="CLObject";
	PLVector_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	PLVector_ClassInstance->init=PLVector_init;
	PLVector_ClassInstance->destruct=PLVector_destruct;
	PLVector_ClassInstance->retain=PLVector_retain;
	PLVector_ClassInstance->release=PLVector_release;
	PLVector_ClassInstance->describe_CLObject=PLVector_describe;
	
}
struct PLVector* PLVector_alloc( )
{
	struct PLVector* result;
	if(PLVector_ClassInstance==NULL)PLVector_CreateClass( );
	result=malloc(sizeof(struct PLVector));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(PLVector_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(PLVector_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void PLVector_initWithPoints (struct PLVector* self, float theX , float theY ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->x=theX;
	self->y=theY;
	self->angle=atan2(self->y,self->x);
	self->length=sqrt(self->x*self->x+self->y*self->y);
}
void PLVector_set (struct PLVector* self, struct PLVector * theVector ) 
{
	self->x=theVector->x;
	self->y=theVector->y;
	self->angle=theVector->angle;
	self->length=theVector->length;
}
void PLVector_setXY (struct PLVector* self, float theX , float theY ) 
{
	self->x=theX;
	self->y=theY;
	self->angle=atan2(self->y,self->x);
	self->length=sqrt(self->x*self->x+self->y*self->y);
}
void PLVector_reset (struct PLVector* self ) 
{
	self->x=0;
	self->y=0;
	self->angle=0;
	self->length=0;
}
void PLVector_multiply (struct PLVector* self, float theValue ) 
{
	self->x*=theValue;
	self->y*=theValue;
	self->length*=theValue;
}
void PLVector_addVector (struct PLVector* self, struct PLVector * theVector ) 
{
	self->x+=theVector->x;
	self->y+=theVector->y;
	self->angle=atan2(self->y,self->x);
	self->length=sqrt(self->x*self->x+self->y*self->y);
}
void PLVector_describe (struct PLVector* self ) 
{
	printf("\nPLVector %f %f",self->x,self->y);
}
void PLVector_init (struct PLVector* self ) 
{
	self->retainCount=1;
}
void PLVector_destruct (struct PLVector* self ) 
{

}
void PLVector_retain (struct PLVector* self ) 
{
	self->retainCount=self->retainCount+1;
}
void PLVector_release (struct PLVector* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLObject_CreateClass( )
{
	CLObject_ClassInstance=malloc(sizeof(struct CLObject_Class));
	CLObject_ClassInstance->className="CLObject";
	CLObject_ClassInstance->classId=&CLObject_ClassInstance;
	CLObject_ClassInstance->init=CLObject_init;
	CLObject_ClassInstance->destruct=CLObject_destruct;
	CLObject_ClassInstance->retain=CLObject_retain;
	CLObject_ClassInstance->release=CLObject_release;
	CLObject_ClassInstance->describe=CLObject_describe;
	
}
struct CLObject* CLObject_alloc( )
{
	struct CLObject* result;
	if(CLObject_ClassInstance==NULL)CLObject_CreateClass( );
	result=malloc(sizeof(struct CLObject));
	result->_components=malloc(sizeof(void*)*2);
	result->_class=(void*)&(CLObject_ClassInstance->className);
	result->_components[0]=&(result->_class);
	result->_components[1]=NULL;
	return result;
}
void CLObject_init (struct CLObject* self ) 
{
	self->retainCount=1;
}
void CLObject_destruct (struct CLObject* self ) 
{

}
void CLObject_retain (struct CLObject* self ) 
{
	self->retainCount=self->retainCount+1;
}
void CLObject_release (struct CLObject* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLObject_describe (struct CLObject* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLDrawablePT22_CreateClass( )
{
	GLDrawablePT22_ClassInstance=malloc(sizeof(struct GLDrawablePT22_Class));
	GLDrawablePT22_ClassInstance->className="GLDrawablePT22";
	GLDrawablePT22_ClassInstance->classId=&GLDrawablePT22_ClassInstance;
	GLDrawablePT22_ClassInstance->init=GLDrawablePT22_init;
	GLDrawablePT22_ClassInstance->destruct=GLDrawablePT22_destruct;
	GLDrawablePT22_ClassInstance->origo=GLDrawablePT22_origo;
	GLDrawablePT22_ClassInstance->move=GLDrawablePT22_move;
	GLDrawablePT22_ClassInstance->scale=GLDrawablePT22_scale;
	GLDrawablePT22_ClassInstance->className_GLDrawable="GLDrawable";
	GLDrawablePT22_ClassInstance->classId_GLDrawable=&GLDrawable_ClassInstance;
	GLDrawablePT22_ClassInstance->init_GLDrawable=GLDrawablePT22_init;
	GLDrawablePT22_ClassInstance->destruct_GLDrawable=GLDrawablePT22_destruct;
	GLDrawablePT22_ClassInstance->className_CLObject="CLObject";
	GLDrawablePT22_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLDrawablePT22_ClassInstance->init_CLObject=GLDrawablePT22_init;
	GLDrawablePT22_ClassInstance->destruct_CLObject=GLDrawablePT22_destruct;
	GLDrawablePT22_ClassInstance->retain=GLDrawablePT22_retain;
	GLDrawablePT22_ClassInstance->release=GLDrawablePT22_release;
	GLDrawablePT22_ClassInstance->describe=GLDrawablePT22_describe;
	
}
struct GLDrawablePT22* GLDrawablePT22_alloc( )
{
	struct GLDrawablePT22* result;
	if(GLDrawablePT22_ClassInstance==NULL)GLDrawablePT22_CreateClass( );
	result=malloc(sizeof(struct GLDrawablePT22));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLDrawablePT22_ClassInstance->className);
	result->_components_GLDrawable=result->_components;
	result->_class_GLDrawable=(void*)&(GLDrawablePT22_ClassInstance->className_GLDrawable);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLDrawablePT22_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLDrawable);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLDrawablePT22_init (struct GLDrawablePT22* self ) 
{
	GLDrawable_init(( cast_object( &GLDrawable_ClassInstance , self)));
	self->dx=0;
	self->dy=0;
	self->sx=1;
	self->sy=1;
}
void GLDrawablePT22_destruct (struct GLDrawablePT22* self ) 
{
	GLDrawable_destruct(( cast_object( &GLDrawable_ClassInstance , self)));
}
void GLDrawablePT22_origo (struct GLDrawablePT22* self, float theX , float theY ) 
{
	for(int index=0;
	index<self->vertexCount*4;
	index+=4)
	{
		self->vertexes[index]+=-self->dx+theX;
		self->vertexes[index+1]+=-self->dy+theY;
	}
	self->dx=theX;
	self->dy=theY;
}
void GLDrawablePT22_move (struct GLDrawablePT22* self, float theX , float theY ) 
{
	self->dx+=theX;
	self->dy+=theY;
	for(int index=0;
	index<self->vertexCount*4;
	index+=4)
	{
		self->vertexes[index]+=theX;
		self->vertexes[index+1]+=theY;
	}
}
void GLDrawablePT22_scale (struct GLDrawablePT22* self, float theX , float theY ) 
{
	self->sx*=theX;
	self->sy*=theY;
	for(int index=0;
	index<self->vertexCount*4;
	index+=4)
	{
		self->vertexes[index]*=theX;
		self->vertexes[index+1]*=theY;
	}
}
void GLDrawablePT22_retain (struct GLDrawablePT22* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLDrawablePT22_release (struct GLDrawablePT22* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLDrawablePT22_describe (struct GLDrawablePT22* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLShader_CreateClass( )
{
	GLShader_ClassInstance=malloc(sizeof(struct GLShader_Class));
	GLShader_ClassInstance->className="GLShader";
	GLShader_ClassInstance->classId=&GLShader_ClassInstance;
	GLShader_ClassInstance->init=GLShader_init;
	GLShader_ClassInstance->destruct=GLShader_destruct;
	GLShader_ClassInstance->addVertexShader=GLShader_addVertexShader;
	GLShader_ClassInstance->addFragmentShader=GLShader_addFragmentShader;
	GLShader_ClassInstance->addAttributeLocation=GLShader_addAttributeLocation;
	GLShader_ClassInstance->addUniformIdentifier=GLShader_addUniformIdentifier;
	GLShader_ClassInstance->getUniformLocation=GLShader_getUniformLocation;
	GLShader_ClassInstance->link=GLShader_link;
	GLShader_ClassInstance->compileShader=GLShader_compileShader;
	GLShader_ClassInstance->linkProgram=GLShader_linkProgram;
	GLShader_ClassInstance->activate=GLShader_activate;
	GLShader_ClassInstance->className_CLObject="CLObject";
	GLShader_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLShader_ClassInstance->init_CLObject=GLShader_init;
	GLShader_ClassInstance->destruct_CLObject=GLShader_destruct;
	GLShader_ClassInstance->retain=GLShader_retain;
	GLShader_ClassInstance->release=GLShader_release;
	GLShader_ClassInstance->describe=GLShader_describe;
	
}
struct GLShader* GLShader_alloc( )
{
	struct GLShader* result;
	if(GLShader_ClassInstance==NULL)GLShader_CreateClass( );
	result=malloc(sizeof(struct GLShader));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLShader_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLShader_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLShader_init (struct GLShader* self, char * theName ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->name=theName;
	self->program=glCreateProgram();
	self->uniformCounter=0;
	self->uniformLocations=malloc(sizeof(GLint));
	self->uniformIdentifiers=malloc(sizeof(const char*));
	self->attributeStride=0;
	self->attributeCounter=0;
	self->attributeLocations=malloc(sizeof(GLuint));
	self->attributeComponents=malloc(sizeof(int));
	self->attributeIdentifiers=malloc(sizeof(const char*));
	self->attributeOffsetSizes=malloc(sizeof(long));
}
void GLShader_destruct (struct GLShader* self ) 
{
	if(self->program!=0)glDeleteProgram(self->program);
	free(self->uniformLocations);
	free(self->uniformIdentifiers);
	free(self->attributeLocations);
	free(self->attributeIdentifiers);
	free(self->attributeComponents);
	free(self->attributeOffsetSizes);
	self->program=0;
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLShader_addVertexShader (struct GLShader* self, const GLchar * theSource ) 
{
	char success= GLShader_compileShader(self, &(self->vertexShader),GL_VERTEX_SHADER,theSource);
	if(success!=1)printf("\nShader %s : Failed to compile vertex shader",self->name);
	else
	{
		printf("\nShader %s : Vertex shader compiled",self->name);
		glAttachShader(self->program,self->vertexShader);
	}
}
void GLShader_addFragmentShader (struct GLShader* self, const GLchar * theSource ) 
{
	char success= GLShader_compileShader(self, &(self->fragmentShader),GL_FRAGMENT_SHADER,theSource);
	if(success!=1)printf("\nShader %s : Failed to compile fragment shader",self->name);
	else
	{
		printf("\nShader %s : Fragment shader compiled",self->name);
		glAttachShader(self->program,self->fragmentShader);
	}
}
void GLShader_addAttributeLocation (struct GLShader* self, GLuint theLocation , int theComponentCount , const char * theIdentifier ) 
{
	self->attributeCounter+=1;
	self->attributeLocations=realloc(self->attributeLocations,sizeof(GLuint)*self->attributeCounter);
	self->attributeComponents=realloc(self->attributeComponents,sizeof(int)*self->attributeCounter);
	self->attributeIdentifiers=realloc(self->attributeIdentifiers,sizeof(const char*)*self->attributeCounter);
	self->attributeOffsetSizes=realloc(self->attributeOffsetSizes,sizeof(long)*self->attributeCounter);
	self->attributeLocations[self->attributeCounter-1]=theLocation;
	self->attributeComponents[self->attributeCounter-1]=theComponentCount;
	self->attributeIdentifiers[self->attributeCounter-1]=theIdentifier;
	self->attributeOffsetSizes[self->attributeCounter-1]=self->attributeStride*sizeof(GLfloat);
	self->attributeStride+=theComponentCount;
}
void GLShader_addUniformIdentifier (struct GLShader* self, const char * theIdentifier ) 
{
	self->uniformCounter+=1;
	self->uniformLocations=realloc(self->uniformLocations,sizeof(GLint)*self->uniformCounter);
	self->uniformIdentifiers=realloc(self->uniformIdentifiers,sizeof(const char*)*self->uniformCounter);
	self->uniformIdentifiers[self->uniformCounter-1]=theIdentifier;
}
GLint GLShader_getUniformLocation (struct GLShader* self, const char * theIdentifier ) 
{
	for(int index=0;
	index<self->uniformCounter;
	index++)
	{
		if(strcmp(self->uniformIdentifiers[index],theIdentifier)==0)return self->uniformLocations[index];
	}
	return 0;
}
void GLShader_link (struct GLShader* self ) 
{
	for(int index=0;
	index<self->attributeCounter;
	index++)
	{
		glBindAttribLocation(self->program,self->attributeLocations[index],self->attributeIdentifiers[index]);
	}
	char success= GLShader_linkProgram(self );
	if(success!=1)
	{
		printf("\nShader %s : Failed to link self->program: %d",self->name,self->program);
		if(self->program>0)glDeleteProgram(self->program);
		self->program=0;
	}
	else
	{
		printf("\nShader %s : Program linked",self->name);
		for(int index=0;
		index<self->uniformCounter;
		index++)
		{
			self->uniformLocations[index]=glGetUniformLocation(self->program,self->uniformIdentifiers[index]);
		}
	}
	if(self->vertexShader>0)
	{
		glDetachShader(self->program,self->vertexShader);
		glDeleteShader(self->vertexShader);
	}
	if(self->fragmentShader>0)
	{
		glDetachShader(self->program,self->fragmentShader);
		glDeleteShader(self->fragmentShader);
	}
	self->vertexShader=0;
	self->fragmentShader=0;
	self->attributeStride=self->attributeStride*sizeof(GLfloat);
}
char GLShader_compileShader (struct GLShader* self, GLuint * theShader , GLenum theType , const GLchar * theSource ) 
{
	GLint status;
	GLint logLength;
	*theShader=glCreateShader(theType);
	glShaderSource(*theShader,1,&theSource,NULL);
	glCompileShader(*theShader);
	glGetShaderiv(*theShader,GL_INFO_LOG_LENGTH,&logLength);
	if(logLength>0)
	{
		GLchar*log=(GLchar*)malloc(logLength);
		glGetShaderInfoLog(*theShader,logLength,&logLength,log);
		printf("\nShader %s : compile log:\n%s",self->name,log);
		free(log);
	}
	glGetShaderiv(*theShader,GL_COMPILE_STATUS,&status);
	if(status==0)
	{
		glDeleteShader(*theShader);
		return 0;
	}
	return 1;
}
char GLShader_linkProgram (struct GLShader* self ) 
{
	GLint status;
	GLint logLength;
	glLinkProgram(self->program);
	glGetProgramiv(self->program,GL_INFO_LOG_LENGTH,&logLength);
	if(logLength>0)
	{
		GLchar*log=(GLchar*)malloc(logLength);
		glGetProgramInfoLog(self->program,logLength,&logLength,log);
		printf("\nShader %s : Program link log:\n%s",self->name,log);
		free(log);
	}
	glGetProgramiv(self->program,GL_LINK_STATUS,&status);
	if(status==0)return 0;
	return 1;
}
void GLShader_activate (struct GLShader* self ) 
{
	glUseProgram(self->program);
	for(int index=0;
	index<self->attributeCounter;
	index++)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,self->attributeComponents[index],GL_FLOAT,GL_FALSE,self->attributeStride,(const GLvoid*)(self->attributeOffsetSizes[index]));
	}
}
void GLShader_retain (struct GLShader* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLShader_release (struct GLShader* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLShader_describe (struct GLShader* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void TLPixelText_CreateClass( )
{
	TLPixelText_ClassInstance=malloc(sizeof(struct TLPixelText_Class));
	TLPixelText_ClassInstance->className="TLPixelText";
	TLPixelText_ClassInstance->classId=&TLPixelText_ClassInstance;
	TLPixelText_ClassInstance->initWithString=TLPixelText_initWithString;
	TLPixelText_ClassInstance->initWithCString=TLPixelText_initWithCString;
	TLPixelText_ClassInstance->destruct=TLPixelText_destruct;
	TLPixelText_ClassInstance->className_CLObject="CLObject";
	TLPixelText_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	TLPixelText_ClassInstance->init=TLPixelText_init;
	TLPixelText_ClassInstance->destruct_CLObject=TLPixelText_destruct;
	TLPixelText_ClassInstance->retain=TLPixelText_retain;
	TLPixelText_ClassInstance->release=TLPixelText_release;
	TLPixelText_ClassInstance->describe=TLPixelText_describe;
	
}
struct TLPixelText* TLPixelText_alloc( )
{
	struct TLPixelText* result;
	if(TLPixelText_ClassInstance==NULL)TLPixelText_CreateClass( );
	result=malloc(sizeof(struct TLPixelText));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(TLPixelText_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(TLPixelText_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void TLPixelText_initWithString (struct TLPixelText* self, struct CLString * theString ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=0;
	self->height=0;
	self->letters=CLDataList_alloc( );
	self->letters->_class->init( (void*) self->letters->_components[0] );
	struct CLChar*link=theString->head;
	while(link!=NULL)
	{
		struct TLPixelFont*font=TLPixelFont_alloc();
		TLPixelFont_initWithCharacter(font, link->character);
		CLDataList_addData(self->letters, font);
		self->width=self->width+font->width;
		if(self->height<font->height)self->height=font->height;
		link=link->next;
	}
}
void TLPixelText_initWithCString (struct TLPixelText* self, char * theString ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=0;
	self->height=0;
	self->letters=CLDataList_alloc( );
	self->letters->_class->init( (void*) self->letters->_components[0] );
	while(*theString!='\0')
	{
		struct TLPixelFont*font=TLPixelFont_alloc();
		TLPixelFont_initWithCharacter(font, *theString);
		CLDataList_addData(self->letters, font);
		self->width=self->width+font->width;
		if(self->height<font->height)self->height=font->height;
		theString+=1;
	}
}
void TLPixelText_destruct (struct TLPixelText* self ) 
{
	struct CLLink*link=self->letters->head;
	while(link!=NULL)
	{
		struct TLPixelFont*font=link->data;
		font->_class->release( (void*) font->_components[0] );
		link=link->next;
	}
	self->letters->_class->release( (void*) self->letters->_components[0] );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void TLPixelText_init (struct TLPixelText* self ) 
{
	self->retainCount=1;
}
void TLPixelText_retain (struct TLPixelText* self ) 
{
	self->retainCount=self->retainCount+1;
}
void TLPixelText_release (struct TLPixelText* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLPixelText_describe (struct TLPixelText* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLBitmap_CreateClass( )
{
	GLBitmap_ClassInstance=malloc(sizeof(struct GLBitmap_Class));
	GLBitmap_ClassInstance->className="GLBitmap";
	GLBitmap_ClassInstance->classId=&GLBitmap_ClassInstance;
	GLBitmap_ClassInstance->initWithDimensions=GLBitmap_initWithDimensions;
	GLBitmap_ClassInstance->destruct=GLBitmap_destruct;
	GLBitmap_ClassInstance->fillRectangle=GLBitmap_fillRectangle;
	GLBitmap_ClassInstance->setPixel=GLBitmap_setPixel;
	GLBitmap_ClassInstance->getPixel=GLBitmap_getPixel;
	GLBitmap_ClassInstance->addShadow=GLBitmap_addShadow;
	GLBitmap_ClassInstance->blendBitmap=GLBitmap_blendBitmap;
	GLBitmap_ClassInstance->className_CLObject="CLObject";
	GLBitmap_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLBitmap_ClassInstance->init=GLBitmap_init;
	GLBitmap_ClassInstance->destruct_CLObject=GLBitmap_destruct;
	GLBitmap_ClassInstance->retain=GLBitmap_retain;
	GLBitmap_ClassInstance->release=GLBitmap_release;
	GLBitmap_ClassInstance->describe=GLBitmap_describe;
	
}
struct GLBitmap* GLBitmap_alloc( )
{
	struct GLBitmap* result;
	if(GLBitmap_ClassInstance==NULL)GLBitmap_CreateClass( );
	result=malloc(sizeof(struct GLBitmap));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLBitmap_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLBitmap_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLBitmap_initWithDimensions (struct GLBitmap* self, int theWidth , int theHeight ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=theWidth;
	self->height=theHeight;
	self->length=4*self->width*self->height;
	self->data=malloc(self->length);
	memset(self->data,0x0,self->length);
}
void GLBitmap_destruct (struct GLBitmap* self ) 
{
	free(self->data);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLBitmap_fillRectangle (struct GLBitmap* self, int theX , int theY , int theWidth , int theHeight , float theR , float theG , float theB , float theA ) 
{
	unsigned int r=(int)(theR*255.0);
	unsigned int g=(int)(theG*255.0);
	unsigned int b=(int)(theB*255.0);
	unsigned int a=(int)(theA*255.0);
	for(int y=theY;
	y<theY+theHeight;
	y++)
	{
		for(int x=theX;
		x<theX+theWidth;
		x++)
		{
			int position=(y*self->width+x)*4;
			self->data[position]=r;
			self->data[position+1]=g;
			self->data[position+2]=b;
			self->data[position+3]=a;
		}
	}
}
void GLBitmap_setPixel (struct GLBitmap* self, int theX , int theY , int theR , int theG , int theB , int theA ) 
{
	printf("");
}
void GLBitmap_getPixel (struct GLBitmap* self, int theX , int theY , int * theR , int * theG , int * theB , int * theA ) 
{
	printf("");
}
void GLBitmap_addShadow (struct GLBitmap* self ) 
{
	unsigned char*clone=malloc(self->length);
	memcpy(clone,self->data,self->length);
	for(int y=0;
	y<self->height;
	y++)
	{
		for(int x=0;
		x<self->width;
		x++)
		{
			int srcIndex=(y*self->width+x)*4;
			unsigned int srcA=clone[srcIndex+3];
			if(srcA>0)
			{
				int NI=((y-1)*self->width+x)*4;
				int SI=((y+1)*self->width+x)*4;
				int EI=(y*self->width+x-1)*4;
				int WI=(y*self->width+x+1)*4;
				if(NI>0&&clone[NI+3]==0)
				{
					self->data[NI+3]=155;
					int NI2=((y-2)*self->width+x)*4;
					if(NI2>0&&clone[NI2+3]==0)self->data[NI2+3]=55;
				}
				if(SI<self->length&&clone[SI+3]==0)
				{
					self->data[SI+3]=155;
					int SI2=((y+2)*self->width+x)*4;
					if(SI2<self->length&&clone[SI2+3]==0)self->data[SI2+3]=55;
				}
				if(x-1>0&&clone[EI+3]==0)
				{
					self->data[EI+3]=155;
					int EI2=(y*self->width+x-2)*4;
					if(EI2>0&&clone[EI2+3]==0)self->data[EI2+3]=55;
				}
				if(x+1<self->width&&clone[WI+3]==0)
				{
					self->data[WI+3]=155;
					int WI2=(y*self->width+x+2)*4;
					if(WI2<self->length&&clone[WI2+3]==0)self->data[WI2+3]=55;
				}
			}
		}
	}
	free(clone);
}
void GLBitmap_blendBitmap (struct GLBitmap* self, struct GLBitmap * theBitmap , int theX , int theY ) 
{
	int bx=theX+theBitmap->width;
	if(bx>self->width)bx=self->width;
	int by=theY+theBitmap->height;
	if(by>self->height)by=self->height;
	unsigned char*srcData=theBitmap->data;
	unsigned char*dstData=self->data;
	for(int y=theY;
	y<by;
	y++)
	{
		for(int x=theX;
		x<bx;
		x++)
		{
			int srcIndex=((y-theY)*theBitmap->width+(x-theX))*4;
			int dstIndex=(y*self->width+x)*4;
			float srcR=(float)srcData[srcIndex]/255.0;
			float srcG=(float)srcData[srcIndex+1]/255.0;
			float srcB=(float)srcData[srcIndex+2]/255.0;
			float srcA=(float)srcData[srcIndex+3]/255.0;
			float dstR=(float)dstData[dstIndex]/255.0;
			float dstG=(float)dstData[dstIndex+1]/255.0;
			float dstB=(float)dstData[dstIndex+2]/255.0;
			float dstA=(float)dstData[dstIndex+3]/255.0;
			float outA=srcA+dstA*(1-srcA);
			float outR=(srcR*srcA+dstR*dstA*(1-srcA))/outA;
			float outG=(srcG*srcA+dstG*dstA*(1-srcA))/outA;
			float outB=(srcB*srcA+dstB*dstA*(1-srcA))/outA;
			dstData[dstIndex]=(int)(outR*255.0);
			dstData[dstIndex+1]=(int)(outG*255.0);
			dstData[dstIndex+2]=(int)(outB*255.0);
			dstData[dstIndex+3]=(int)(outA*255.0);
		}
	}
}
void GLBitmap_init (struct GLBitmap* self ) 
{
	self->retainCount=1;
}
void GLBitmap_retain (struct GLBitmap* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLBitmap_release (struct GLBitmap* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLBitmap_describe (struct GLBitmap* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLBitmapPixelText_CreateClass( )
{
	GLBitmapPixelText_ClassInstance=malloc(sizeof(struct GLBitmapPixelText_Class));
	GLBitmapPixelText_ClassInstance->className="GLBitmapPixelText";
	GLBitmapPixelText_ClassInstance->classId=&GLBitmapPixelText_ClassInstance;
	GLBitmapPixelText_ClassInstance->init=GLBitmapPixelText_init;
	GLBitmapPixelText_ClassInstance->destruct=GLBitmapPixelText_destruct;
	GLBitmapPixelText_ClassInstance->drawPixelTextWithSize=GLBitmapPixelText_drawPixelTextWithSize;
	GLBitmapPixelText_ClassInstance->className_GLBitmap="GLBitmap";
	GLBitmapPixelText_ClassInstance->classId_GLBitmap=&GLBitmap_ClassInstance;
	GLBitmapPixelText_ClassInstance->initWithDimensions=GLBitmapPixelText_initWithDimensions;
	GLBitmapPixelText_ClassInstance->destruct_GLBitmap=GLBitmapPixelText_destruct;
	GLBitmapPixelText_ClassInstance->fillRectangle=GLBitmapPixelText_fillRectangle;
	GLBitmapPixelText_ClassInstance->setPixel=GLBitmapPixelText_setPixel;
	GLBitmapPixelText_ClassInstance->getPixel=GLBitmapPixelText_getPixel;
	GLBitmapPixelText_ClassInstance->addShadow=GLBitmapPixelText_addShadow;
	GLBitmapPixelText_ClassInstance->blendBitmap=GLBitmapPixelText_blendBitmap;
	GLBitmapPixelText_ClassInstance->className_CLObject="CLObject";
	GLBitmapPixelText_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLBitmapPixelText_ClassInstance->init_CLObject=GLBitmapPixelText_init;
	GLBitmapPixelText_ClassInstance->destruct_CLObject=GLBitmapPixelText_destruct;
	GLBitmapPixelText_ClassInstance->retain=GLBitmapPixelText_retain;
	GLBitmapPixelText_ClassInstance->release=GLBitmapPixelText_release;
	GLBitmapPixelText_ClassInstance->describe=GLBitmapPixelText_describe;
	
}
struct GLBitmapPixelText* GLBitmapPixelText_alloc( )
{
	struct GLBitmapPixelText* result;
	if(GLBitmapPixelText_ClassInstance==NULL)GLBitmapPixelText_CreateClass( );
	result=malloc(sizeof(struct GLBitmapPixelText));
	result->_components=malloc(sizeof(void*)*4);
	result->_class=(void*)&(GLBitmapPixelText_ClassInstance->className);
	result->_components_GLBitmap=result->_components;
	result->_class_GLBitmap=(void*)&(GLBitmapPixelText_ClassInstance->className_GLBitmap);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLBitmapPixelText_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_GLBitmap);
	result->_components[2]=&(result->_class_CLObject);
	result->_components[3]=NULL;
	return result;
}
void GLBitmapPixelText_init (struct GLBitmapPixelText* self, char * theLabel , int theWidth , int theHeight ) 
{
	GLBitmap_initWithDimensions(( cast_object( &GLBitmap_ClassInstance , self)),theWidth,theHeight);
}
void GLBitmapPixelText_destruct (struct GLBitmapPixelText* self ) 
{
	GLBitmap_destruct(( cast_object( &GLBitmap_ClassInstance , self)));
}
void GLBitmapPixelText_drawPixelTextWithSize (struct GLBitmapPixelText* self, struct TLPixelText * theText , float theSize ) 
{
	float dx=(float)self->width-theText->width*theSize;
	float dy=(float)self->height-theText->height*theSize;
	dx/=2;
	dy/=2;
	struct CLLink*link=theText->letters->head;
	while(link!=NULL)
	{
		struct TLPixelFont*font=link->data;
		float*cdata=font->data;
		if(font->length>0)
		{
			for(int index=0;
			index<font->length;
			index+=2)
			{
				GLBitmapPixelText_fillRectangle( self, (int)dx+cdata[index]*theSize,(int)dy+cdata[index+1]*theSize,(int)theSize,(int)theSize,1,1,1,1);
			}
		}
		dx+=font->width*theSize;
		link=link->next;
	}
}
void GLBitmapPixelText_initWithDimensions (struct GLBitmapPixelText* self, int theWidth , int theHeight ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->width=theWidth;
	self->height=theHeight;
	self->length=4*self->width*self->height;
	self->data=malloc(self->length);
	memset(self->data,0x0,self->length);
}
void GLBitmapPixelText_fillRectangle (struct GLBitmapPixelText* self, int theX , int theY , int theWidth , int theHeight , float theR , float theG , float theB , float theA ) 
{
	unsigned int r=(int)(theR*255.0);
	unsigned int g=(int)(theG*255.0);
	unsigned int b=(int)(theB*255.0);
	unsigned int a=(int)(theA*255.0);
	for(int y=theY;
	y<theY+theHeight;
	y++)
	{
		for(int x=theX;
		x<theX+theWidth;
		x++)
		{
			int position=(y*self->width+x)*4;
			self->data[position]=r;
			self->data[position+1]=g;
			self->data[position+2]=b;
			self->data[position+3]=a;
		}
	}
}
void GLBitmapPixelText_setPixel (struct GLBitmapPixelText* self, int theX , int theY , int theR , int theG , int theB , int theA ) 
{
	printf("");
}
void GLBitmapPixelText_getPixel (struct GLBitmapPixelText* self, int theX , int theY , int * theR , int * theG , int * theB , int * theA ) 
{
	printf("");
}
void GLBitmapPixelText_addShadow (struct GLBitmapPixelText* self ) 
{
	unsigned char*clone=malloc(self->length);
	memcpy(clone,self->data,self->length);
	for(int y=0;
	y<self->height;
	y++)
	{
		for(int x=0;
		x<self->width;
		x++)
		{
			int srcIndex=(y*self->width+x)*4;
			unsigned int srcA=clone[srcIndex+3];
			if(srcA>0)
			{
				int NI=((y-1)*self->width+x)*4;
				int SI=((y+1)*self->width+x)*4;
				int EI=(y*self->width+x-1)*4;
				int WI=(y*self->width+x+1)*4;
				if(NI>0&&clone[NI+3]==0)
				{
					self->data[NI+3]=155;
					int NI2=((y-2)*self->width+x)*4;
					if(NI2>0&&clone[NI2+3]==0)self->data[NI2+3]=55;
				}
				if(SI<self->length&&clone[SI+3]==0)
				{
					self->data[SI+3]=155;
					int SI2=((y+2)*self->width+x)*4;
					if(SI2<self->length&&clone[SI2+3]==0)self->data[SI2+3]=55;
				}
				if(x-1>0&&clone[EI+3]==0)
				{
					self->data[EI+3]=155;
					int EI2=(y*self->width+x-2)*4;
					if(EI2>0&&clone[EI2+3]==0)self->data[EI2+3]=55;
				}
				if(x+1<self->width&&clone[WI+3]==0)
				{
					self->data[WI+3]=155;
					int WI2=(y*self->width+x+2)*4;
					if(WI2<self->length&&clone[WI2+3]==0)self->data[WI2+3]=55;
				}
			}
		}
	}
	free(clone);
}
void GLBitmapPixelText_blendBitmap (struct GLBitmapPixelText* self, struct GLBitmap * theBitmap , int theX , int theY ) 
{
	int bx=theX+theBitmap->width;
	if(bx>self->width)bx=self->width;
	int by=theY+theBitmap->height;
	if(by>self->height)by=self->height;
	unsigned char*srcData=theBitmap->data;
	unsigned char*dstData=self->data;
	for(int y=theY;
	y<by;
	y++)
	{
		for(int x=theX;
		x<bx;
		x++)
		{
			int srcIndex=((y-theY)*theBitmap->width+(x-theX))*4;
			int dstIndex=(y*self->width+x)*4;
			float srcR=(float)srcData[srcIndex]/255.0;
			float srcG=(float)srcData[srcIndex+1]/255.0;
			float srcB=(float)srcData[srcIndex+2]/255.0;
			float srcA=(float)srcData[srcIndex+3]/255.0;
			float dstR=(float)dstData[dstIndex]/255.0;
			float dstG=(float)dstData[dstIndex+1]/255.0;
			float dstB=(float)dstData[dstIndex+2]/255.0;
			float dstA=(float)dstData[dstIndex+3]/255.0;
			float outA=srcA+dstA*(1-srcA);
			float outR=(srcR*srcA+dstR*dstA*(1-srcA))/outA;
			float outG=(srcG*srcA+dstG*dstA*(1-srcA))/outA;
			float outB=(srcB*srcA+dstB*dstA*(1-srcA))/outA;
			dstData[dstIndex]=(int)(outR*255.0);
			dstData[dstIndex+1]=(int)(outG*255.0);
			dstData[dstIndex+2]=(int)(outB*255.0);
			dstData[dstIndex+3]=(int)(outA*255.0);
		}
	}
}
void GLBitmapPixelText_retain (struct GLBitmapPixelText* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLBitmapPixelText_release (struct GLBitmapPixelText* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLBitmapPixelText_describe (struct GLBitmapPixelText* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLTexture_CreateClass( )
{
	GLTexture_ClassInstance=malloc(sizeof(struct GLTexture_Class));
	GLTexture_ClassInstance->className="GLTexture";
	GLTexture_ClassInstance->classId=&GLTexture_ClassInstance;
	GLTexture_ClassInstance->initWithGLBitmap=GLTexture_initWithGLBitmap;
	GLTexture_ClassInstance->initWithDimensions=GLTexture_initWithDimensions;
	GLTexture_ClassInstance->destruct=GLTexture_destruct;
	GLTexture_ClassInstance->className_CLObject="CLObject";
	GLTexture_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLTexture_ClassInstance->init=GLTexture_init;
	GLTexture_ClassInstance->destruct_CLObject=GLTexture_destruct;
	GLTexture_ClassInstance->retain=GLTexture_retain;
	GLTexture_ClassInstance->release=GLTexture_release;
	GLTexture_ClassInstance->describe=GLTexture_describe;
	
}
struct GLTexture* GLTexture_alloc( )
{
	struct GLTexture* result;
	if(GLTexture_ClassInstance==NULL)GLTexture_CreateClass( );
	result=malloc(sizeof(struct GLTexture));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLTexture_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLTexture_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLTexture_initWithGLBitmap (struct GLTexture* self, struct GLBitmap * theBitmap ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	glGenTextures(1,&self->glid);
	glBindTexture(GL_TEXTURE_2D,self->glid);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,theBitmap->width,theBitmap->height,0,GL_RGBA,GL_UNSIGNED_BYTE,theBitmap->data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void GLTexture_initWithDimensions (struct GLTexture* self, int theWidth , int theHeight ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	glGenTextures(1,&self->glid);
	glBindTexture(GL_TEXTURE_2D,self->glid);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,theWidth,theHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void GLTexture_destruct (struct GLTexture* self ) 
{
	glDeleteTextures(1,&(self->glid));
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void GLTexture_init (struct GLTexture* self ) 
{
	self->retainCount=1;
}
void GLTexture_retain (struct GLTexture* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLTexture_release (struct GLTexture* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void GLTexture_describe (struct GLTexture* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void GLVertexBlock_CreateClass( )
{
	GLVertexBlock_ClassInstance=malloc(sizeof(struct GLVertexBlock_Class));
	GLVertexBlock_ClassInstance->className="GLVertexBlock";
	GLVertexBlock_ClassInstance->classId=&GLVertexBlock_ClassInstance;
	GLVertexBlock_ClassInstance->init=GLVertexBlock_init;
	GLVertexBlock_ClassInstance->destruct=GLVertexBlock_destruct;
	GLVertexBlock_ClassInstance->describe=GLVertexBlock_describe;
	GLVertexBlock_ClassInstance->className_CLObject="CLObject";
	GLVertexBlock_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	GLVertexBlock_ClassInstance->init_CLObject=GLVertexBlock_init;
	GLVertexBlock_ClassInstance->destruct_CLObject=GLVertexBlock_destruct;
	GLVertexBlock_ClassInstance->retain=GLVertexBlock_retain;
	GLVertexBlock_ClassInstance->release=GLVertexBlock_release;
	GLVertexBlock_ClassInstance->describe_CLObject=GLVertexBlock_describe;
	
}
struct GLVertexBlock* GLVertexBlock_alloc( )
{
	struct GLVertexBlock* result;
	if(GLVertexBlock_ClassInstance==NULL)GLVertexBlock_CreateClass( );
	result=malloc(sizeof(struct GLVertexBlock));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(GLVertexBlock_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(GLVertexBlock_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void GLVertexBlock_init (struct GLVertexBlock* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->indexes=NULL;
	self->drawables=NULL;
}
void GLVertexBlock_destruct (struct GLVertexBlock* self ) 
{
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
	if(self->indexes!=NULL)free(self->indexes);
	if(self->drawables!=NULL)self->drawables->_class->release( (void*) self->drawables->_components[0] );
}
void GLVertexBlock_describe (struct GLVertexBlock* self ) 
{
	printf("\nmode: %u texture: %u indexCount %i vertexCount %i",self->mode,self->texture,self->indexCount,self->vertexCount);
}
void GLVertexBlock_retain (struct GLVertexBlock* self ) 
{
	self->retainCount=self->retainCount+1;
}
void GLVertexBlock_release (struct GLVertexBlock* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLPixelFont_CreateClass( )
{
	TLPixelFont_ClassInstance=malloc(sizeof(struct TLPixelFont_Class));
	TLPixelFont_ClassInstance->className="TLPixelFont";
	TLPixelFont_ClassInstance->classId=&TLPixelFont_ClassInstance;
	TLPixelFont_ClassInstance->initWithCharacter=TLPixelFont_initWithCharacter;
	TLPixelFont_ClassInstance->destruct=TLPixelFont_destruct;
	TLPixelFont_ClassInstance->getPattern=TLPixelFont_getPattern;
	TLPixelFont_ClassInstance->className_CLObject="CLObject";
	TLPixelFont_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	TLPixelFont_ClassInstance->init=TLPixelFont_init;
	TLPixelFont_ClassInstance->destruct_CLObject=TLPixelFont_destruct;
	TLPixelFont_ClassInstance->retain=TLPixelFont_retain;
	TLPixelFont_ClassInstance->release=TLPixelFont_release;
	TLPixelFont_ClassInstance->describe=TLPixelFont_describe;
	
}
struct TLPixelFont* TLPixelFont_alloc( )
{
	struct TLPixelFont* result;
	if(TLPixelFont_ClassInstance==NULL)TLPixelFont_CreateClass( );
	result=malloc(sizeof(struct TLPixelFont));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(TLPixelFont_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(TLPixelFont_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void TLPixelFont_initWithCharacter (struct TLPixelFont* self, char theCharacter ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	const char*pattern=TLPixelFont_getPattern( self, theCharacter);
	const char*counter=pattern;
	self->character=theCharacter;
	self->length=0;
	while(*counter!='\0')
	{
		if(*counter=='1')self->length+=2;
		counter+=1;
	}
	self->data=malloc(sizeof(float)*self->length);
	int index=0;
	float x=0.0;
	float y=0.0;
	while(*pattern!='\0')
	{
		switch(*pattern)
		{
			case'1':
			{
				self->data[index++]=x;
				self->data[index++]=y;
				x+=1.0;
				break;
			}
			case'0':
			{
				x+=1.0;
				break;
			}
			case' ':
			{
				self->width=x+1;
				x=0.0;
				y+=1;
				break;
			}
		}
		self->height=y+1;
		pattern+=1;
	}
}
void TLPixelFont_destruct (struct TLPixelFont* self ) 
{
	free(self->data);
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
const char * TLPixelFont_getPattern (struct TLPixelFont* self, char theCharacter ) 
{
	switch(theCharacter)
	{
		case'A':return"000 111 101 111 101 101";
		break;
		case'B':return"000 110 101 110 101 110";
		break;
		case'C':return"000 111 100 100 100 111";
		break;
		case'D':return"000 110 101 101 101 110";
		break;
		case'E':return"000 111 100 111 100 111";
		break;
		case'F':return"000 111 100 111 100 100";
		break;
		case'G':return"000 111 100 101 101 111";
		break;
		case'H':return"000 101 101 111 101 101";
		break;
		case'I':return"0 1 1 1 1 1";
		break;
		case'J':return"000 001 001 001 101 111";
		break;
		case'K':return"000 101 101 110 101 101";
		break;
		case'L':return"000 100 100 100 100 111";
		break;
		case'M':return"00000 11111 10101 10101 10101 10101";
		break;
		case'N':return"000 111 101 101 101 101";
		break;
		case'O':return"000 111 101 101 101 111";
		break;
		case'P':return"000 111 101 111 100 100";
		break;
		case'Q':return"000 111 101 101 101 111 001";
		break;
		case'R':return"000 111 101 110 101 101";
		break;
		case'S':return"000 111 100 111 001 111";
		break;
		case'T':return"000 111 010 010 010 010";
		break;
		case'U':return"000 101 101 101 101 111";
		break;
		case'V':return"000 101 101 101 101 010";
		break;
		case'W':return"00000 10101 10101 10101 10101 11111";
		break;
		case'X':return"000 101 101 010 101 101";
		break;
		case'Y':return"000 101 101 111 010 010";
		break;
		case'Z':return"000 111 001 111 100 111";
		break;
		case'0':return"000 010 101 101 101 010";
		break;
		case'1':return"00 01 11 01 01 01";
		break;
		case'2':return"000 110 001 010 100 111";
		break;
		case'3':return"000 110 001 110 001 110";
		break;
		case'4':return"000 100 101 111 010 010";
		break;
		case'5':return"000 111 100 111 001 110";
		break;
		case'6':return"000 011 100 111 101 111";
		break;
		case'7':return"000 111 001 011 001 001";
		break;
		case'8':return"000 111 101 111 101 111";
		break;
		case'9':return"000 111 101 111 001 111";
		break;
		case'.':return"0 0 0 0 0 1";
		break;
		case'!':return"0 1 1 1 0 1";
		break;
		case'?':return"0000 0110 1001 0010 0000 0010";
		break;
		case':':return"0 0 1 0 1 0";
		break;
		case' ':return"0 0 0 0 0 0";
		break;
		case'/':return"000 001 001 010 100 100";
		break;
		case'-':return"000 000 000 111 000 000";
		break;
		case'+':return"000 000 010 111 010 000";
		break;
		case'l':return"000 001 010 100 010 001";
		break;
		case'r':return"000 100 010 001 010 100";
		break;
		case'u':return"00000 00000 00100 01010 10001 00000";
		break;
		case'd':return"00000 00000 10001 01010 00100 00000";
		break;
		case'<':return"0000 1111 1000 1000 1000 0000";
		break;
		case'>':return"0000 1111 0001 0001 0001 0000";
		break;
	}
	return"\0";
}
void TLPixelFont_init (struct TLPixelFont* self ) 
{
	self->retainCount=1;
}
void TLPixelFont_retain (struct TLPixelFont* self ) 
{
	self->retainCount=self->retainCount+1;
}
void TLPixelFont_release (struct TLPixelFont* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void TLPixelFont_describe (struct TLPixelFont* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void CLString_CreateClass( )
{
	CLString_ClassInstance=malloc(sizeof(struct CLString_Class));
	CLString_ClassInstance->className="CLString";
	CLString_ClassInstance->classId=&CLString_ClassInstance;
	CLString_ClassInstance->init=CLString_init;
	CLString_ClassInstance->initWithString=CLString_initWithString;
	CLString_ClassInstance->initWithCString=CLString_initWithCString;
	CLString_ClassInstance->destruct=CLString_destruct;
	CLString_ClassInstance->appendCharacter=CLString_appendCharacter;
	CLString_ClassInstance->appendString=CLString_appendString;
	CLString_ClassInstance->appendCString=CLString_appendCString;
	CLString_ClassInstance->removeAllCharacters=CLString_removeAllCharacters;
	CLString_ClassInstance->readFile=CLString_readFile;
	CLString_ClassInstance->readFilePointer=CLString_readFilePointer;
	CLString_ClassInstance->writeToFile=CLString_writeToFile;
	CLString_ClassInstance->writeToFilePointer=CLString_writeToFilePointer;
	CLString_ClassInstance->stringWithLastPathComponent=CLString_stringWithLastPathComponent;
	CLString_ClassInstance->stringByRemovingExtension=CLString_stringByRemovingExtension;
	CLString_ClassInstance->stringByRemovingLastPathComponent=CLString_stringByRemovingLastPathComponent;
	CLString_ClassInstance->containsString=CLString_containsString;
	CLString_ClassInstance->indexOfString=CLString_indexOfString;
	CLString_ClassInstance->equals=CLString_equals;
	CLString_ClassInstance->cString=CLString_cString;
	CLString_ClassInstance->describe=CLString_describe;
	CLString_ClassInstance->className_CLObject="CLObject";
	CLString_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	CLString_ClassInstance->init_CLObject=CLString_init;
	CLString_ClassInstance->destruct_CLObject=CLString_destruct;
	CLString_ClassInstance->retain=CLString_retain;
	CLString_ClassInstance->release=CLString_release;
	CLString_ClassInstance->describe_CLObject=CLString_describe;
	
}
struct CLString* CLString_alloc( )
{
	struct CLString* result;
	if(CLString_ClassInstance==NULL)CLString_CreateClass( );
	result=malloc(sizeof(struct CLString));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(CLString_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(CLString_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void CLString_init (struct CLString* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLString_initWithString (struct CLString* self, struct CLString * theString ) 
{
	CLString_init( self );
	CLString_appendString( self, theString);
}
void CLString_initWithCString (struct CLString* self, char * theString ) 
{
	CLString_init( self );
	CLString_appendCString( self, theString);
}
void CLString_destruct (struct CLString* self ) 
{
	CLString_removeAllCharacters( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void CLString_appendCharacter (struct CLString* self, char theCharacter ) 
{
	struct CLChar*newChar;
	newChar=malloc(sizeof(struct CLChar));
	newChar->next=NULL;
	newChar->character=theCharacter;
	if(self->head==NULL)self->head=newChar;
	else self->last->next=newChar;
	self->last=newChar;
	self->length=self->length+1;
}
void CLString_appendString (struct CLString* self, struct CLString * theString ) 
{
	struct CLChar*link;
	if(theString!=NULL&&theString->length>0)
	{
		link=theString->head;
		while(link!=NULL)
		{
			CLString_appendCharacter( self, link->character);
			link=link->next;
		}
	}
}
void CLString_appendCString (struct CLString* self, char * theString ) 
{
	while(*theString!='\0')
	{
		CLString_appendCharacter( self, *theString);
		theString+=1;
	}
}
void CLString_removeAllCharacters (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLChar*prev;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		prev=link;
		link=link->next;
		free(prev);
	}
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLString_readFile (struct CLString* self, struct CLString * thePath ) 
{
	char*fileName;
	int character;
	FILE*filePointer;
	fileName=thePath->_class->cString( (void*) thePath->_components[0] );
	filePointer=fopen(fileName,"r");
	if(filePointer!=NULL)
	{
		character=getc(filePointer);
		while(character!=EOF)
		{
			CLString_appendCharacter( self, character);
			character=getc(filePointer);
		}
		fclose(filePointer);
	}
	free(fileName);
}
void CLString_readFilePointer (struct CLString* self, FILE * thePointer ) 
{
	int character;
	character=getc(thePointer);
	while(character!=EOF)
	{
		CLString_appendCharacter( self, character);
		character=getc(thePointer);
	}
	fclose(thePointer);
}
void CLString_writeToFile (struct CLString* self, struct CLString * thePath ) 
{
	char*fileName;
	FILE*filePointer;
	struct CLChar*link;
	fileName=thePath->_class->cString( (void*) thePath->_components[0] );
	filePointer=fopen(fileName,"w");
	link=self->head;
	while(link!=NULL)
	{
		putc(link->character,filePointer);
		link=link->next;
	}
	fclose(filePointer);
	free(fileName);
}
void CLString_writeToFilePointer (struct CLString* self, FILE * theFilePointer ) 
{
	struct CLChar*link;
	link=self->head;
	while(link!=NULL)
	{
		putc(link->character,theFilePointer);
		link=link->next;
	}
}
struct CLString * CLString_stringWithLastPathComponent (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLString*result;
	link=self->head;
	result=CLString_alloc( );
	CLString_init(result );
	while(link!=NULL)
	{
		if(link->character=='/'||link->character=='\\')
		{
			result->_class->release( (void*) result->_components[0] );
			result=CLString_alloc();
			result->_class->init( (void*) result->_components[0] );
		}
		else result->_class->appendCharacter( (void*) result->_components[0], link->character);
		link=link->next;
	}
	return result;
}
struct CLString * CLString_stringByRemovingExtension (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLString*part;
	struct CLString*result;
	char inExtension;
	link=self->head;
	inExtension=0;
	part=CLString_alloc( );
	result=CLString_alloc( );
	CLString_init(part );
	CLString_init(result );
	while(link!=NULL)
	{
		if(link->character=='.')
		{
			inExtension=1;
			CLString_appendString(result, part);
			CLString_release(part );
			part=CLString_alloc();
			CLString_init(part );
		}
		else if(inExtension==1)inExtension=0;
		CLString_appendCharacter(part, link->character);
		link=link->next;
	}
	CLString_release(part );
	return result;
}
struct CLString * CLString_stringByRemovingLastPathComponent (struct CLString* self ) 
{
	struct CLChar*link;
	struct CLString*part;
	struct CLString*result;
	link=self->head;
	result=CLString_alloc( );
	part=CLString_alloc( );
	CLString_init(result );
	CLString_init(part );
	while(link!=NULL)
	{
		CLString_appendCharacter(part, link->character);
		if(link->character=='/'||link->character=='\\')
		{
			CLString_appendString(result, part);
			CLString_release(part );
			part=CLString_alloc();
			CLString_init(part );
		}
		link=link->next;
	}
	if(result->length==0) CLString_appendString(result, part);
	CLString_release(part );
	return result;
}
char CLString_containsString (struct CLString* self, struct CLString * theString ) 
{
	struct CLChar*link;
	struct CLChar*search;
	link=self->head;
	search=theString->head;
	while(link!=NULL)
	{
		if(link->character==search->character)
		{
			search=search->next;
			if(search==NULL)return 1;
		}
		else
		{
			search=theString->head;
		}
		link=link->next;
	}
	return 0;
}
unsigned long CLString_indexOfString (struct CLString* self, struct CLString * theSearchString ) 
{
	char found;
	unsigned long result;
	unsigned long index;
	struct CLChar*link;
	struct CLChar*search;
	found=0;
	result=0;
	index=0;
	link=self->head;
	search=theSearchString->head;
	while(link!=NULL)
	{
		if(link->character==search->character)
		{
			if(found==0)
			{
				found=1;
				result=index;
			}
			search=search->next;
			if(search==NULL)return result;
		}
		else
		{
			found=0;
			search=theSearchString->head;
		}
		link=link->next;
		index=index+1;
	}
	return result;
}
char CLString_equals (struct CLString* self, struct CLString * theStringB ) 
{
	struct CLChar*linkA;
	struct CLChar*linkB;
	if(self->length!=theStringB->length)return 0;
	linkA=self->head;
	linkB=theStringB->head;
	while(linkA!=NULL&&linkB!=NULL)
	{
		if(linkA->character!=linkB->character)return 0;
		linkA=linkA->next;
		linkB=linkB->next;
	}
	return 1;
}
char * CLString_cString (struct CLString* self ) 
{
	int index;
	char*result;
	struct CLChar*link;
	if(self->head!=NULL)
	{
		link=self->head;
		result=malloc(sizeof(char)*(self->length+1));
		index=0;
		while(link!=NULL&&link->character!=0)
		{
			result[index++]=link->character;
			link=link->next;
		}
		result[index]=0;
		return result;
	}
	else return NULL;
}
void CLString_describe (struct CLString* self ) 
{
	struct CLChar*link;
	link=self->head;
	while(link!=NULL)
	{
		printf("%c",link->character);
		link=link->next;
	}
}
void CLString_retain (struct CLString* self ) 
{
	self->retainCount=self->retainCount+1;
}
void CLString_release (struct CLString* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
