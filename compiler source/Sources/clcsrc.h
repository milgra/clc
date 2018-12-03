#ifndef clcsrc_h
#define clcsrc_h
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "CLChar.h"
#include "CLLink.h"
#define kTokenMainTypeUndefined			0
#define kTokenMainTypeWord				1
#define kTokenMainTypeString			2
#define kTokenMainTypeSymbol			3
#define kTokenMainTypeComment			4
#define kTokenMainTypeSetting			5
#define kTokenSubTypeUndefined			6
#define kTokenSubTypeClass				7
#define kTokenSubTypeCast				8
#define kTokenSubTypeInstance			9
#define kTokenSubTypeVariable			10
#define kTokenSubTypeMethod				11
#define kTokenSubTypeLocalCall			12
#define kTokenSubTypeImplicitCall		13
#define kTokenSubTypeExplicitCall		14
#define kTokenSubTypeExplicitAllocCall	15
#define kTokenSubTypeExplicitClassCall	16
#define kTokenSubTypeExplicitCallClass	17
#define kTokenSubTypeExplicitAccessor	18
#define kTokenSubTypeImplicitAccessor	19
#define kTokenSubTypeForEachCycle		20
#define kTokenSubTypeLocalCallReference 21
#define kTokenSubTypeStructAccessor		22
#define kLineTypeGeneral	0
#define kLineTypeClassDef	1
#define kLineTypeBlockStart	2
#define kLineTypeBlockEnd	3
#define kLineTypeSetting	4
#define kLineTypeComment	5
#define kScopeTypeUndefined 0
#define kScopeTypeNormal    1
#define kScopeTypeForEach   2
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
struct Main;
struct Main_Class;
struct CLObject;
struct CLObject_Class;
struct CLString;
struct CLString_Class;
struct CLObjectList;
struct CLObjectList_Class;
struct CLStringObjectList;
struct CLStringObjectList_Class;
struct Creator;
struct Creator_Class;
struct Analyzer;
struct Analyzer_Class;
struct Tokenizer;
struct Tokenizer_Class;
struct Constants;
struct Constants_Class;
struct FileElements;
struct FileElements_Class;
struct ClassElements;
struct ClassElements_Class;
struct Token;
struct Token_Class;
struct Line;
struct Line_Class;
struct Scope;
struct Scope_Class;
struct Main
{
	struct Main_Class* _class;
	void** _components;
	struct Creator * creator ; 
	struct Analyzer * analyzer ; 
	struct Tokenizer * tokenizer ; 
	struct CLString * targetPath ; 
	struct Constants * constants ; 
	struct FileElements * collector ; 
	struct CLObjectList * pathsList ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Main_Class
{
	char* className;
	void* classId;
	int 	(*init) (struct Main*, int  , const char *  [ ] ) ;
	void 	(*analyzeParameters) (struct Main*, int  , char * *  ) ;
	void 	(*compileClass) (struct Main*, struct CLString *  , struct FileElements *  ) ;
	void 	(*createAndOrganizeLines) (struct Main*, struct CLString *  , struct ClassElements *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*getLinesForClass) (struct Main*, struct CLString *  , struct CLObjectList *  ) ;
	void 	(*filterAndAddSettings) (struct Main*, struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*writeFiles) (struct Main*, struct FileElements *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	int 	(*init_CLObject) (struct Main*, int  , const char *  [ ] ) ;
	void 	(*destruct) (struct Main* ) ;
	void 	(*retain) (struct Main* ) ;
	void 	(*release) (struct Main* ) ;
	void 	(*describe) (struct Main* ) ;
	
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
struct CLObjectList
{
	struct CLObjectList_Class* _class;
	void** _components;
	struct CLLink * head ; 
	struct CLLink * last ; 
	unsigned long length ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct CLObjectList_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct CLObjectList* ) ;
	void 	(*destruct) (struct CLObjectList* ) ;
	void 	(*addObject) (struct CLObjectList*, struct CLObject *  ) ;
	void 	(*addObjectAtIndex) (struct CLObjectList*, struct CLObject *  , unsigned long  ) ;
	void 	(*addObjectsInObjectList) (struct CLObjectList*, struct CLObjectList *  ) ;
	void 	(*removeObject) (struct CLObjectList*, struct CLObject *  ) ;
	struct CLObject * 	(*removeObjectAtIndex) (struct CLObjectList*, unsigned long  ) ;
	void 	(*removeAllObjects) (struct CLObjectList* ) ;
	struct CLObject * 	(*objectAtIndex) (struct CLObjectList*, unsigned long  ) ;
	char 	(*containsObject) (struct CLObjectList*, struct CLObject *  ) ;
	unsigned long 	(*indexOfObject) (struct CLObjectList*, struct CLObject *  ) ;
	struct CLObject * 	(*firstObject) (struct CLObjectList* ) ;
	struct CLObject * 	(*lastObject) (struct CLObjectList* ) ;
	void 	(*describe) (struct CLObjectList* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct CLObjectList* ) ;
	void 	(*destruct_CLObject) (struct CLObjectList* ) ;
	void 	(*retain) (struct CLObjectList* ) ;
	void 	(*release) (struct CLObjectList* ) ;
	void 	(*describe_CLObject) (struct CLObjectList* ) ;
	
};
struct CLStringObjectList
{
	struct CLStringObjectList_Class* _class;
	void** _components;
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct CLStringObjectList_Class
{
	char* className;
	void* classId;
	char 	(*containsString) (struct CLStringObjectList*, struct CLString *  , struct CLObjectList *  ) ;
	unsigned long 	(*indexOfString) (struct CLStringObjectList*, struct CLString *  , struct CLObjectList *  ) ;
	void 	(*removeString) (struct CLStringObjectList*, struct CLString *  , struct CLObjectList *  ) ;
	void 	(*removeStrings) (struct CLStringObjectList*, struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*addStringAsUnique) (struct CLStringObjectList*, struct CLString *  , struct CLObjectList *  ) ;
	void 	(*addStringsAsUnique) (struct CLStringObjectList*, struct CLObjectList *  , struct CLObjectList *  ) ;
	struct CLObjectList * 	(*splitStringByCharacter) (struct CLStringObjectList*, struct CLString *  , char  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct CLStringObjectList* ) ;
	void 	(*destruct) (struct CLStringObjectList* ) ;
	void 	(*retain) (struct CLStringObjectList* ) ;
	void 	(*release) (struct CLStringObjectList* ) ;
	void 	(*describe) (struct CLStringObjectList* ) ;
	
};
struct Creator
{
	struct Creator_Class* _class;
	void** _components;
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Creator_Class
{
	char* className;
	void* classId;
	const char * 	(*createGeneralStructs) (struct Creator* ) ;
	const char * 	(*createCasterMethod) (struct Creator* ) ;
	const char * 	(*createDeallocatorMethod) (struct Creator* ) ;
	void 	(*createStructures) (struct Creator*, struct ClassElements *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createInstanceStruct) (struct Creator*, struct CLString *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createClassStruct) (struct Creator*, struct CLString *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createFunctions) (struct Creator*, struct ClassElements *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createClassInitializer) (struct Creator*, struct CLString *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createInstanceInitializer) (struct Creator*, struct CLString *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createMethodFunction) (struct Creator*, struct CLString *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*createFunctionHeader) (struct Creator*, struct CLString *  , struct CLString *  , struct CLObjectList *  ) ;
	void 	(*createFunctionLine) (struct Creator*, struct CLString *  , struct CLString *  , struct CLObjectList *  ) ;
	char 	(*parameterFollows) (struct Creator*, struct CLLink *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct Creator* ) ;
	void 	(*destruct) (struct Creator* ) ;
	void 	(*retain) (struct Creator* ) ;
	void 	(*release) (struct Creator* ) ;
	void 	(*describe) (struct Creator* ) ;
	
};
struct Analyzer
{
	struct Analyzer_Class* _class;
	void** _components;
	struct Constants * constants ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Analyzer_Class
{
	char* className;
	void* classId;
	void 	(*organizeTokens) (struct Analyzer*, struct CLObjectList *  , struct ClassElements *  , struct CLObjectList *  ) ;
	void 	(*analyzeGeneral) (struct Analyzer*, struct Line *  , long  , struct CLObjectList * *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*analyzeSetting) (struct Analyzer*, struct Line *  , long  , struct CLObjectList * *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*analyzeClassDef) (struct Analyzer*, struct Line *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	struct CLString * 	(*extractClassName) (struct Analyzer*, struct CLObjectList *  ) ;
	struct CLString * 	(*extractMemberName) (struct Analyzer*, struct CLObjectList *  ) ;
	struct CLString * 	(*extractMethodName) (struct Analyzer*, struct CLObjectList *  ) ;
	void 	(*analyzeMembers) (struct Analyzer*, struct ClassElements *  ) ;
	void 	(*analyzeMethods) (struct Analyzer*, struct ClassElements *  ) ;
	void 	(*analyzeMethodDef) (struct Analyzer*, struct CLObjectList *  , struct CLObjectList *  , struct ClassElements *  ) ;
	void 	(*analyzeLine) (struct Analyzer*, struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  , struct ClassElements *  ) ;
	void 	(*analyzeForEachToken) (struct Analyzer*, struct CLLink * *  , struct Scope *  , struct CLObjectList *  , struct CLObjectList *  , struct CLObjectList *  ) ;
	void 	(*addLinkStructAndVariable) (struct Analyzer*, struct CLString *  , struct CLString *  , struct CLString *  , struct Scope *  , struct CLObjectList *  ) ;
	void 	(*analyzeAllocToken) (struct Analyzer*, struct Token *  , struct CLObjectList *  ) ;
	void 	(*analyzeClassToken) (struct Analyzer*, struct CLLink * *  , struct Scope *  , struct ClassElements *  ) ;
	void 	(*analyzeMethodToken) (struct Analyzer*, struct CLLink * *  ) ;
	void 	(*analyzeMemberToken) (struct Analyzer*, struct CLLink * *  , long  , struct CLObjectList *  ) ;
	void 	(*analyzeInstanceToken) (struct Analyzer*, struct CLLink * *  , long  , struct CLObjectList *  ) ;
	void 	(*analyzeInstanceList) (struct Analyzer*, struct CLLink * *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct Analyzer* ) ;
	void 	(*destruct) (struct Analyzer* ) ;
	void 	(*retain) (struct Analyzer* ) ;
	void 	(*release) (struct Analyzer* ) ;
	void 	(*describe) (struct Analyzer* ) ;
	
};
struct Tokenizer
{
	struct Tokenizer_Class* _class;
	void** _components;
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Tokenizer_Class
{
	char* className;
	void* classId;
	void 	(*createLines) (struct Tokenizer*, struct CLString *  , struct CLObjectList *  ) ;
	void 	(*resetActualLine) (struct Tokenizer*, struct Line * *  , struct CLObjectList *  ) ;
	void 	(*createTokens) (struct Tokenizer*, struct CLString *  , struct CLObjectList *  ) ;
	void 	(*resetActualToken) (struct Tokenizer*, struct Token * *  , struct CLObjectList *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init) (struct Tokenizer* ) ;
	void 	(*destruct) (struct Tokenizer* ) ;
	void 	(*retain) (struct Tokenizer* ) ;
	void 	(*release) (struct Tokenizer* ) ;
	void 	(*describe) (struct Tokenizer* ) ;
	
};
struct Constants
{
	struct Constants_Class* _class;
	void** _components;
	long linkId ; 
	struct CLString * clcString ; 
	struct CLString * forString ; 
	struct CLString * selfString ; 
	struct CLString * nullString ; 
	struct CLString * linkString ; 
	struct CLString * ifdefString ; 
	struct CLString * endifString ; 
	struct CLString * classString ; 
	struct CLString * allocString ; 
	struct CLString * settingString ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Constants_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct Constants* ) ;
	void 	(*destruct) (struct Constants* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct Constants* ) ;
	void 	(*destruct_CLObject) (struct Constants* ) ;
	void 	(*retain) (struct Constants* ) ;
	void 	(*release) (struct Constants* ) ;
	void 	(*describe) (struct Constants* ) ;
	
};
struct FileElements
{
	struct FileElements_Class* _class;
	void** _components;
	struct CLObjectList * classesList ; 
	struct CLObjectList * settingsList ; 
	struct CLObjectList * settingNamesList ; 
	struct CLObjectList * functionsList ; 
	struct CLObjectList * functionHeadersList ; 
	struct CLObjectList * structuresList ; 
	struct CLObjectList * structureHeadersList ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct FileElements_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct FileElements* ) ;
	void 	(*destruct) (struct FileElements* ) ;
	void 	(*describe) (struct FileElements* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct FileElements* ) ;
	void 	(*destruct_CLObject) (struct FileElements* ) ;
	void 	(*retain) (struct FileElements* ) ;
	void 	(*release) (struct FileElements* ) ;
	void 	(*describe_CLObject) (struct FileElements* ) ;
	
};
struct ClassElements
{
	struct ClassElements_Class* _class;
	void** _components;
	struct CLString * className ; 
	struct CLObjectList * usedClassNamesList ; 
	struct CLObjectList * unusedClassNamesList ; 
	struct CLObjectList * memberNamesList ; 
	struct CLObjectList * memberTokensList ; 
	struct CLObjectList * methodNamesList ; 
	struct CLObjectList * methodTokensList ; 
	struct CLObjectList * settingNamesList ; 
	struct CLObjectList * settingTokensList ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct ClassElements_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct ClassElements*, struct CLString *  ) ;
	void 	(*destruct) (struct ClassElements* ) ;
	void 	(*describe) (struct ClassElements* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct ClassElements*, struct CLString *  ) ;
	void 	(*destruct_CLObject) (struct ClassElements* ) ;
	void 	(*retain) (struct ClassElements* ) ;
	void 	(*release) (struct ClassElements* ) ;
	void 	(*describe_CLObject) (struct ClassElements* ) ;
	
};
struct Token
{
	struct Token_Class* _class;
	void** _components;
	struct CLString * text ; 
	struct CLString * linkId ; 
	struct CLString * classId ; 
	struct CLString * variableId ; 
	struct CLString * containerId ; 
	struct CLString * instanceList ; 
	char subType ; 
	char mainType ; 
	char isMember ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Token_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct Token* ) ;
	void 	(*destruct) (struct Token* ) ;
	void 	(*setText) (struct Token*, struct CLString *  ) ;
	void 	(*setLinkId) (struct Token*, struct CLString *  ) ;
	void 	(*setClassId) (struct Token*, struct CLString *  ) ;
	void 	(*setVariableId) (struct Token*, struct CLString *  ) ;
	void 	(*setContainerId) (struct Token*, struct CLString *  ) ;
	void 	(*setInstanceList) (struct Token*, struct CLString *  ) ;
	void 	(*describe) (struct Token* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct Token* ) ;
	void 	(*destruct_CLObject) (struct Token* ) ;
	void 	(*retain) (struct Token* ) ;
	void 	(*release) (struct Token* ) ;
	void 	(*describe_CLObject) (struct Token* ) ;
	
};
struct Line
{
	struct Line_Class* _class;
	void** _components;
	char type ; 
	struct CLString * text ; 
	struct CLObjectList * tokens ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Line_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct Line* ) ;
	void 	(*destruct) (struct Line* ) ;
	void 	(*describe) (struct Line* ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct Line* ) ;
	void 	(*destruct_CLObject) (struct Line* ) ;
	void 	(*retain) (struct Line* ) ;
	void 	(*release) (struct Line* ) ;
	void 	(*describe_CLObject) (struct Line* ) ;
	
};
struct Scope
{
	struct Scope_Class* _class;
	void** _components;
	char type ; 
	struct CLString * scopeLink ; 
	struct CLObjectList * forEachList ; 
	struct CLObjectList * instancesList ; 
	struct CLObjectList * instanceNamesList ; 
	char nextScopeType ; 
	struct CLString * nextScopeLink ; 
	struct CLObject_Class* _class_CLObject;
	void** _components_CLObject;
	unsigned long retainCount ; 
	
};
struct Scope_Class
{
	char* className;
	void* classId;
	void 	(*init) (struct Scope* ) ;
	void 	(*destruct) (struct Scope* ) ;
	void 	(*setScopeLink) (struct Scope*, struct CLString *  ) ;
	void 	(*setNextScopeLink) (struct Scope*, struct CLString *  ) ;
	char* className_CLObject;
	void* classId_CLObject;
	void 	(*init_CLObject) (struct Scope* ) ;
	void 	(*destruct_CLObject) (struct Scope* ) ;
	void 	(*retain) (struct Scope* ) ;
	void 	(*release) (struct Scope* ) ;
	void 	(*describe) (struct Scope* ) ;
	
};
void* cast_object( void* theObject , void* theId );
void  free_object( void* theObject );
void Main_CreateClass( );
struct Main* Main_alloc( );
int Main_init (struct Main* self, int theCount , const char * theTokens [ ] ) ;
void Main_analyzeParameters (struct Main* self, int theCount , char * * theTokens ) ;
void Main_compileClass (struct Main* self, struct CLString * theClassName , struct FileElements * theFileElements ) ;
void Main_createAndOrganizeLines (struct Main* self, struct CLString * theClassName , struct ClassElements * theElements , struct CLObjectList * theParentNamesList , struct CLObjectList * theParentElementsList ) ;
void Main_getLinesForClass (struct Main* self, struct CLString * theClassName , struct CLObjectList * theLines ) ;
void Main_filterAndAddSettings (struct Main* self, struct CLObjectList * theCombinedSettingsList , struct CLObjectList * theCombinedSettingNamesList , struct CLObjectList * theSettingsList , struct CLObjectList * theSettingNamesList ) ;
void Main_writeFiles (struct Main* self, struct FileElements * theFileElements ) ;
void Main_destruct (struct Main* self ) ;
void Main_retain (struct Main* self ) ;
void Main_release (struct Main* self ) ;
void Main_describe (struct Main* self ) ;
void CLObject_CreateClass( );
struct CLObject* CLObject_alloc( );
void CLObject_init (struct CLObject* self ) ;
void CLObject_destruct (struct CLObject* self ) ;
void CLObject_retain (struct CLObject* self ) ;
void CLObject_release (struct CLObject* self ) ;
void CLObject_describe (struct CLObject* self ) ;
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
void CLObjectList_CreateClass( );
struct CLObjectList* CLObjectList_alloc( );
void CLObjectList_init (struct CLObjectList* self ) ;
void CLObjectList_destruct (struct CLObjectList* self ) ;
void CLObjectList_addObject (struct CLObjectList* self, struct CLObject * theObject ) ;
void CLObjectList_addObjectAtIndex (struct CLObjectList* self, struct CLObject * theObject , unsigned long theIndex ) ;
void CLObjectList_addObjectsInObjectList (struct CLObjectList* self, struct CLObjectList * theObjectList ) ;
void CLObjectList_removeObject (struct CLObjectList* self, struct CLObject * theObject ) ;
struct CLObject * CLObjectList_removeObjectAtIndex (struct CLObjectList* self, unsigned long theIndex ) ;
void CLObjectList_removeAllObjects (struct CLObjectList* self ) ;
struct CLObject * CLObjectList_objectAtIndex (struct CLObjectList* self, unsigned long theIndex ) ;
char CLObjectList_containsObject (struct CLObjectList* self, struct CLObject * theObject ) ;
unsigned long CLObjectList_indexOfObject (struct CLObjectList* self, struct CLObject * theObject ) ;
struct CLObject * CLObjectList_firstObject (struct CLObjectList* self ) ;
struct CLObject * CLObjectList_lastObject (struct CLObjectList* self ) ;
void CLObjectList_describe (struct CLObjectList* self ) ;
void CLObjectList_retain (struct CLObjectList* self ) ;
void CLObjectList_release (struct CLObjectList* self ) ;
void CLStringObjectList_CreateClass( );
struct CLStringObjectList* CLStringObjectList_alloc( );
char CLStringObjectList_containsString (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) ;
unsigned long CLStringObjectList_indexOfString (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) ;
void CLStringObjectList_removeString (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) ;
void CLStringObjectList_removeStrings (struct CLStringObjectList* self, struct CLObjectList * theStringList , struct CLObjectList * theObjectList ) ;
void CLStringObjectList_addStringAsUnique (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) ;
void CLStringObjectList_addStringsAsUnique (struct CLStringObjectList* self, struct CLObjectList * theStringList , struct CLObjectList * theObjectList ) ;
struct CLObjectList * CLStringObjectList_splitStringByCharacter (struct CLStringObjectList* self, struct CLString * theString , char theCharacter ) ;
void CLStringObjectList_init (struct CLStringObjectList* self ) ;
void CLStringObjectList_destruct (struct CLStringObjectList* self ) ;
void CLStringObjectList_retain (struct CLStringObjectList* self ) ;
void CLStringObjectList_release (struct CLStringObjectList* self ) ;
void CLStringObjectList_describe (struct CLStringObjectList* self ) ;
void Creator_CreateClass( );
struct Creator* Creator_alloc( );
const char * Creator_createGeneralStructs (struct Creator* self ) ;
const char * Creator_createCasterMethod (struct Creator* self ) ;
const char * Creator_createDeallocatorMethod (struct Creator* self ) ;
void Creator_createStructures (struct Creator* self, struct ClassElements * theElements , struct CLObjectList * theParentNamesList , struct CLObjectList * theParentElementsList , struct CLObjectList * theStructuresTargetList , struct CLObjectList * theStructureHeadersTargetList ) ;
void Creator_createInstanceStruct (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theStructuresTargetList , struct CLObjectList * theStructureHeadersTargetList ) ;
void Creator_createClassStruct (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theCombinedMethodsList , struct CLObjectList * theCombinedMethodNamesList , struct CLObjectList * theStructuresTargetList , struct CLObjectList * theStructureHeadersTargetList ) ;
void Creator_createFunctions (struct Creator* self, struct ClassElements * theElements , struct CLObjectList * theParentNamesList , struct CLObjectList * theParentElementsList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) ;
void Creator_createClassInitializer (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) ;
void Creator_createInstanceInitializer (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) ;
void Creator_createMethodFunction (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theMethodList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) ;
void Creator_createFunctionHeader (struct Creator* self, struct CLString * theResult , struct CLString * theClassName , struct CLObjectList * theLine ) ;
void Creator_createFunctionLine (struct Creator* self, struct CLString * theResult , struct CLString * theClassName , struct CLObjectList * theLine ) ;
char Creator_parameterFollows (struct Creator* self, struct CLLink * theLink ) ;
void Creator_init (struct Creator* self ) ;
void Creator_destruct (struct Creator* self ) ;
void Creator_retain (struct Creator* self ) ;
void Creator_release (struct Creator* self ) ;
void Creator_describe (struct Creator* self ) ;
void Analyzer_CreateClass( );
struct Analyzer* Analyzer_alloc( );
void Analyzer_organizeTokens (struct Analyzer* self, struct CLObjectList * theLines , struct ClassElements * theElements , struct CLObjectList * theParentNamesList ) ;
void Analyzer_analyzeGeneral (struct Analyzer* self, struct Line * theLine , long theDepth , struct CLObjectList * * theMethodLines , struct CLObjectList * theMemberNames , struct CLObjectList * theMembers , struct CLObjectList * theMethodNames , struct CLObjectList * theMethods ) ;
void Analyzer_analyzeSetting (struct Analyzer* self, struct Line * theLine , long theDepth , struct CLObjectList * * theMethodLines , struct CLObjectList * theClassPool , struct CLObjectList * theMemberNames , struct CLObjectList * theMembers , struct CLObjectList * theSettingNames , struct CLObjectList * theSettings ) ;
void Analyzer_analyzeClassDef (struct Analyzer* self, struct Line * theLine , struct CLObjectList * theParentClassNamesList , struct CLObjectList * theUsedClassNamesList ) ;
struct CLString * Analyzer_extractClassName (struct Analyzer* self, struct CLObjectList * theTokens ) ;
struct CLString * Analyzer_extractMemberName (struct Analyzer* self, struct CLObjectList * theTokens ) ;
struct CLString * Analyzer_extractMethodName (struct Analyzer* self, struct CLObjectList * theTokens ) ;
void Analyzer_analyzeMembers (struct Analyzer* self, struct ClassElements * theElements ) ;
void Analyzer_analyzeMethods (struct Analyzer* self, struct ClassElements * theElements ) ;
void Analyzer_analyzeMethodDef (struct Analyzer* self, struct CLObjectList * theLine , struct CLObjectList * theScopeList , struct ClassElements * theElements ) ;
void Analyzer_analyzeLine (struct Analyzer* self, struct CLObjectList * theLine , struct CLObjectList * theMethodLines , struct CLObjectList * theScopeList , struct ClassElements * theElements ) ;
void Analyzer_analyzeForEachToken (struct Analyzer* self, struct CLLink * * theLinkAddress , struct Scope * theScope , struct CLObjectList * theMemberNames , struct CLObjectList * theClassNames , struct CLObjectList * theMethodLines ) ;
void Analyzer_addLinkStructAndVariable (struct Analyzer* self, struct CLString * theName , struct CLString * theClass , struct CLString * theLinkId , struct Scope * theScope , struct CLObjectList * theMethodLines ) ;
void Analyzer_analyzeAllocToken (struct Analyzer* self, struct Token * theToken , struct CLObjectList * theLine ) ;
void Analyzer_analyzeClassToken (struct Analyzer* self, struct CLLink * * theLinkAddress , struct Scope * theScope , struct ClassElements * theElements ) ;
void Analyzer_analyzeMethodToken (struct Analyzer* self, struct CLLink * * theLinkAddress ) ;
void Analyzer_analyzeMemberToken (struct Analyzer* self, struct CLLink * * theLinkAddress , long theMemberIndex , struct CLObjectList * theMembers ) ;
void Analyzer_analyzeInstanceToken (struct Analyzer* self, struct CLLink * * theLinkAddress , long theInstanceIndex , struct CLObjectList * theInstancesList ) ;
void Analyzer_analyzeInstanceList (struct Analyzer* self, struct CLLink * * theLinkAddress ) ;
void Analyzer_init (struct Analyzer* self ) ;
void Analyzer_destruct (struct Analyzer* self ) ;
void Analyzer_retain (struct Analyzer* self ) ;
void Analyzer_release (struct Analyzer* self ) ;
void Analyzer_describe (struct Analyzer* self ) ;
void Tokenizer_CreateClass( );
struct Tokenizer* Tokenizer_alloc( );
void Tokenizer_createLines (struct Tokenizer* self, struct CLString * theString , struct CLObjectList * theLines ) ;
void Tokenizer_resetActualLine (struct Tokenizer* self, struct Line * * theLinePointer , struct CLObjectList * theLines ) ;
void Tokenizer_createTokens (struct Tokenizer* self, struct CLString * theString , struct CLObjectList * theTokens ) ;
void Tokenizer_resetActualToken (struct Tokenizer* self, struct Token * * theTokenPointer , struct CLObjectList * theTokens ) ;
void Tokenizer_init (struct Tokenizer* self ) ;
void Tokenizer_destruct (struct Tokenizer* self ) ;
void Tokenizer_retain (struct Tokenizer* self ) ;
void Tokenizer_release (struct Tokenizer* self ) ;
void Tokenizer_describe (struct Tokenizer* self ) ;
void Constants_CreateClass( );
struct Constants* Constants_alloc( );
void Constants_init (struct Constants* self ) ;
void Constants_destruct (struct Constants* self ) ;
void Constants_retain (struct Constants* self ) ;
void Constants_release (struct Constants* self ) ;
void Constants_describe (struct Constants* self ) ;
void FileElements_CreateClass( );
struct FileElements* FileElements_alloc( );
void FileElements_init (struct FileElements* self ) ;
void FileElements_destruct (struct FileElements* self ) ;
void FileElements_describe (struct FileElements* self ) ;
void FileElements_retain (struct FileElements* self ) ;
void FileElements_release (struct FileElements* self ) ;
void ClassElements_CreateClass( );
struct ClassElements* ClassElements_alloc( );
void ClassElements_init (struct ClassElements* self, struct CLString * theName ) ;
void ClassElements_destruct (struct ClassElements* self ) ;
void ClassElements_describe (struct ClassElements* self ) ;
void ClassElements_retain (struct ClassElements* self ) ;
void ClassElements_release (struct ClassElements* self ) ;
void Token_CreateClass( );
struct Token* Token_alloc( );
void Token_init (struct Token* self ) ;
void Token_destruct (struct Token* self ) ;
void Token_setText (struct Token* self, struct CLString * theText ) ;
void Token_setLinkId (struct Token* self, struct CLString * theLinkId ) ;
void Token_setClassId (struct Token* self, struct CLString * theClassId ) ;
void Token_setVariableId (struct Token* self, struct CLString * theVariableId ) ;
void Token_setContainerId (struct Token* self, struct CLString * theContainerId ) ;
void Token_setInstanceList (struct Token* self, struct CLString * theList ) ;
void Token_describe (struct Token* self ) ;
void Token_retain (struct Token* self ) ;
void Token_release (struct Token* self ) ;
void Line_CreateClass( );
struct Line* Line_alloc( );
void Line_init (struct Line* self ) ;
void Line_destruct (struct Line* self ) ;
void Line_describe (struct Line* self ) ;
void Line_retain (struct Line* self ) ;
void Line_release (struct Line* self ) ;
void Scope_CreateClass( );
struct Scope* Scope_alloc( );
void Scope_init (struct Scope* self ) ;
void Scope_destruct (struct Scope* self ) ;
void Scope_setScopeLink (struct Scope* self, struct CLString * theLink ) ;
void Scope_setNextScopeLink (struct Scope* self, struct CLString * theLink ) ;
void Scope_retain (struct Scope* self ) ;
void Scope_release (struct Scope* self ) ;
void Scope_describe (struct Scope* self ) ;
#endif
