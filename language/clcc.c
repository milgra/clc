/*
Class-C compiler by Milan Toth.

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org>
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
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
struct CLChar
{

	char			character;
	struct CLChar*	next;
    
};
struct CLLink
{

	void*			data;
	struct CLLink*	next;
	
};
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
static struct Main_Class* Main_ClassInstance = NULL;
static struct CLObject_Class* CLObject_ClassInstance = NULL;
static struct CLString_Class* CLString_ClassInstance = NULL;
static struct CLObjectList_Class* CLObjectList_ClassInstance = NULL;
static struct CLStringObjectList_Class* CLStringObjectList_ClassInstance = NULL;
static struct Creator_Class* Creator_ClassInstance = NULL;
static struct Analyzer_Class* Analyzer_ClassInstance = NULL;
static struct Tokenizer_Class* Tokenizer_ClassInstance = NULL;
static struct Constants_Class* Constants_ClassInstance = NULL;
static struct FileElements_Class* FileElements_ClassInstance = NULL;
static struct ClassElements_Class* ClassElements_ClassInstance = NULL;
static struct Token_Class* Token_ClassInstance = NULL;
static struct Line_Class* Line_ClassInstance = NULL;
static struct Scope_Class* Scope_ClassInstance = NULL;
void Main_CreateClass( )
{
	Main_ClassInstance=malloc(sizeof(struct Main_Class));
	Main_ClassInstance->className="Main";
	Main_ClassInstance->classId=&Main_ClassInstance;
	Main_ClassInstance->init=Main_init;
	Main_ClassInstance->analyzeParameters=Main_analyzeParameters;
	Main_ClassInstance->compileClass=Main_compileClass;
	Main_ClassInstance->createAndOrganizeLines=Main_createAndOrganizeLines;
	Main_ClassInstance->getLinesForClass=Main_getLinesForClass;
	Main_ClassInstance->filterAndAddSettings=Main_filterAndAddSettings;
	Main_ClassInstance->writeFiles=Main_writeFiles;
	Main_ClassInstance->className_CLObject="CLObject";
	Main_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Main_ClassInstance->init_CLObject=Main_init;
	Main_ClassInstance->destruct=Main_destruct;
	Main_ClassInstance->retain=Main_retain;
	Main_ClassInstance->release=Main_release;
	Main_ClassInstance->describe=Main_describe;
	
}
struct Main* Main_alloc( )
{
	struct Main* result;
	if(Main_ClassInstance==NULL)Main_CreateClass( );
	result=malloc(sizeof(struct Main));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Main_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Main_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
int Main_init (struct Main* self, int theCount , const char * theTokens [ ] ) 
{
	struct CLLink*link0;
	struct CLObject* object;
	int paraCount;
	char**paraTokens;
	struct FileElements*fileElements;
	paraCount=theCount;
	paraTokens=(char**)theTokens;
	printf("clcc 0.7 by Milan Toth\n");
	if(paraCount>1)
	{
		self->creator=Creator_alloc( );
		Creator_init(self->creator );
		self->analyzer=Analyzer_alloc( );
		Analyzer_init(self->analyzer );
		self->tokenizer=Tokenizer_alloc( );
		Tokenizer_init(self->tokenizer );
		self->constants=Constants_alloc( );
		Constants_init(self->constants );
		self->collector=FileElements_alloc( );
		FileElements_init(self->collector );
		self->pathsList=CLObjectList_alloc( );
		CLObjectList_init(self->pathsList );
		self->targetPath=CLString_alloc( );
		CLString_init(self->targetPath );
		self->analyzer->constants=self->constants;
		Main_analyzeParameters( self, paraCount,paraTokens);
		link0=self->collector->classesList->head;while( link0!=NULL){object=link0->data; 
		
			fileElements=FileElements_alloc( );
			FileElements_init(fileElements );
			Main_compileClass( self, (cast_object( &CLString_ClassInstance , object)),fileElements);
			Main_filterAndAddSettings( self, fileElements->settingsList,fileElements->settingNamesList,self->collector->settingsList,self->collector->settingNamesList);
			CLStringObjectList_addStringsAsUnique(NULL,fileElements->classesList,self->collector->classesList);
			self->collector->functionsList->_class->addObjectsInObjectList( (void*) self->collector->functionsList->_components[0], fileElements->functionsList);
			self->collector->structuresList->_class->addObjectsInObjectList( (void*) self->collector->structuresList->_components[0], fileElements->structuresList);
			self->collector->functionHeadersList->_class->addObjectsInObjectList( (void*) self->collector->functionHeadersList->_components[0], fileElements->functionHeadersList);
			self->collector->structureHeadersList->_class->addObjectsInObjectList( (void*) self->collector->structureHeadersList->_components[0], fileElements->structureHeadersList);
			FileElements_release(fileElements );
		link0=link0->next;}
		Main_writeFiles( self, self->collector);
		Creator_release(self->creator );
		Analyzer_release(self->analyzer );
		Tokenizer_release(self->tokenizer );
		Constants_release(self->constants );
		FileElements_release(self->collector );
		CLObjectList_release(self->pathsList );
		CLString_release(self->targetPath );
	}
	else printf("Usage : clcc ClassNameA ClassNameB ClassNameN -p SourcePathA -p SourcePathB -p SourcePathN -o OutputPath");
	printf("\n");
	return 0;
}
void Main_analyzeParameters (struct Main* self, int theCount , char * * theTokens ) 
{
	int index;
	char*oneToken;
	struct CLString*onePath;
	struct CLString*oneFile;
	struct CLString*oneClass;
	index=1;
	printf("\n");
	for(index=1;
	index<theCount;
	index++)
	{
		printf("%s ",theTokens[index]);
		if(theTokens[index][0]!='-')printf("\n");
	}
	index=1;
	while(index<theCount)
	{
		oneToken=theTokens[index];
		if(oneToken[0]=='-')
		{
			if(oneToken[1]=='p'&&index<theCount-1)
			{
				onePath=CLString_alloc( );
				CLString_init(onePath );
				CLString_appendCString(onePath, theTokens[index+1]);
				CLObjectList_addObject(self->pathsList, (cast_object( &CLObject_ClassInstance , onePath)));
				CLString_release(onePath );
				index+=1;
			}
			else if(oneToken[1]=='o'&&index<theCount-1)
			{
				CLString_appendCString(self->targetPath, theTokens[index+1]);
				index+=1;
			}
		}
		else
		{
			oneFile=CLString_alloc( );
			CLString_init(oneFile );
			CLString_appendCString(oneFile, theTokens[index]);
			oneClass= CLString_stringByRemovingExtension(oneFile );
			self->collector->classesList->_class->addObject( (void*) self->collector->classesList->_components[0], (cast_object( &CLObject_ClassInstance , oneClass)));
			CLString_release(oneFile );
			CLString_release(oneClass );
		}
		index+=1;
	}
	if(self->pathsList->length==0)
	{
		onePath=CLString_alloc( );
		CLString_init(onePath );
		CLObjectList_addObject(self->pathsList, (cast_object( &CLObject_ClassInstance , onePath)));
	}
	if(self->targetPath->length==0||(self->targetPath->last)->character=='/'||(self->targetPath->last)->character=='\\')
	{
		self->targetPath->_class->appendCString( (void*) self->targetPath->_components[0], "clcsrc");
	}
}
void Main_compileClass (struct Main* self, struct CLString * theClassName , struct FileElements * theFileElements ) 
{
	struct CLLink*link1;
	struct CLObject* object;
	struct ClassElements*classElements;
	struct CLObjectList*parentNamesList;
	struct CLObjectList*parentElementsList;
	printf("\ncompiling class ");
	theClassName->_class->describe( (void*) theClassName->_components[0] );
	classElements=ClassElements_alloc( );
	ClassElements_init(classElements, theClassName);
	parentNamesList=CLObjectList_alloc( );
	CLObjectList_init(parentNamesList );
	parentElementsList=CLObjectList_alloc( );
	CLObjectList_init(parentElementsList );
	CLObjectList_addObject(parentNamesList, (cast_object( &CLObject_ClassInstance , theClassName)));
	link1=parentNamesList->head;while( link1!=NULL){object=link1->data; 
	
		Main_createAndOrganizeLines( self, (cast_object( &CLString_ClassInstance , object)),classElements,parentNamesList,parentElementsList);
	link1=link1->next;}
	classElements->unusedClassNamesList->_class->addObjectsInObjectList( (void*) classElements->unusedClassNamesList->_components[0], classElements->usedClassNamesList);
	CLStringObjectList_removeStrings(NULL,parentNamesList,classElements->unusedClassNamesList);
	Analyzer_analyzeMembers(self->analyzer, classElements);
	Analyzer_analyzeMethods(self->analyzer, classElements);
	Creator_createStructures(self->creator, classElements,parentNamesList,parentElementsList,theFileElements->structuresList,theFileElements->structureHeadersList);
	Creator_createFunctions(self->creator, classElements,parentNamesList,parentElementsList,theFileElements->functionsList,theFileElements->functionHeadersList);
	theFileElements->classesList->_class->addObjectsInObjectList( (void*) theFileElements->classesList->_components[0], classElements->usedClassNamesList);
	theFileElements->settingsList->_class->addObjectsInObjectList( (void*) theFileElements->settingsList->_components[0], classElements->settingTokensList);
	theFileElements->settingNamesList->_class->addObjectsInObjectList( (void*) theFileElements->settingNamesList->_components[0], classElements->settingNamesList);
	if(classElements->unusedClassNamesList->length>0)
	{
		printf("\nWARNING : Unused classses : ");
		classElements->unusedClassNamesList->_class->describe( (void*) classElements->unusedClassNamesList->_components[0] );
	}
	ClassElements_release(classElements );
	CLObjectList_release(parentNamesList );
	CLObjectList_release(parentElementsList );
	printf("\n");
	theClassName->_class->describe( (void*) theClassName->_components[0] );
	printf(" compiled");
}
void Main_createAndOrganizeLines (struct Main* self, struct CLString * theClassName , struct ClassElements * theElements , struct CLObjectList * theParentNamesList , struct CLObjectList * theParentElementsList ) 
{
	char nameExists;
	struct CLLink*nameLink;
	struct CLLink*dataLink;
	struct CLString*oneName;
	struct CLObjectList*lines;
	struct CLObjectList*parentNamesList;
	struct ClassElements*parentElements;
	lines=CLObjectList_alloc( );
	CLObjectList_init(lines );
	Main_getLinesForClass( self, theClassName,lines);
	if(lines->length>0)
	{
		parentElements=ClassElements_alloc( );
		parentNamesList=CLObjectList_alloc( );
		ClassElements_init(parentElements, theClassName);
		CLObjectList_init(parentNamesList );
		self->analyzer->_class->organizeTokens( (void*) self->analyzer->_components[0], lines,parentElements,parentNamesList);
		CLObjectList_addObject(theParentElementsList, (cast_object( &CLObject_ClassInstance , parentElements)));
		CLStringObjectList_addStringsAsUnique(NULL,parentNamesList,theParentNamesList);
		CLStringObjectList_addStringsAsUnique(NULL,parentElements->usedClassNamesList,theElements->usedClassNamesList);
		theElements->settingNamesList->_class->addObjectsInObjectList( (void*) theElements->settingNamesList->_components[0], parentElements->settingNamesList);
		theElements->settingTokensList->_class->addObjectsInObjectList( (void*) theElements->settingTokensList->_components[0], parentElements->settingTokensList);
		nameLink=parentElements->memberNamesList->head;
		dataLink=parentElements->memberTokensList->head;
		while(nameLink!=NULL)
		{
			oneName=(cast_object( &CLString_ClassInstance , nameLink->data));
			nameExists=CLStringObjectList_containsString(NULL,oneName,theElements->memberNamesList);
			if(nameExists==0|| CLString_equals(oneName, self->constants->settingString)==1)
			{
				theElements->memberNamesList->_class->addObject( (void*) theElements->memberNamesList->_components[0], nameLink->data);
				theElements->memberTokensList->_class->addObject( (void*) theElements->memberTokensList->_components[0], dataLink->data);
			}
			else printf("\nWARNING member collision : %s",oneName->_class->cString( (void*) oneName->_components[0] ));
			nameLink=nameLink->next;
			dataLink=dataLink->next;
		}
		nameLink=parentElements->methodNamesList->head;
		dataLink=parentElements->methodTokensList->head;
		while(nameLink!=NULL)
		{
			oneName=(cast_object( &CLString_ClassInstance , nameLink->data));
			nameExists=CLStringObjectList_containsString(NULL,oneName,theElements->methodNamesList);
			if(nameExists==0)
			{
				theElements->methodNamesList->_class->addObject( (void*) theElements->methodNamesList->_components[0], nameLink->data);
				theElements->methodTokensList->_class->addObject( (void*) theElements->methodTokensList->_components[0], dataLink->data);
			}
			nameLink=nameLink->next;
			dataLink=dataLink->next;
		}
		ClassElements_release(parentElements );
		CLObjectList_release(parentNamesList );
	}
	else exit(1);
	CLObjectList_release(lines );
}
void Main_getLinesForClass (struct Main* self, struct CLString * theClassName , struct CLObjectList * theLines ) 
{
	struct CLLink*link2;
	struct CLObject* object;
	char*cFilePath;
	FILE*classFile;
	struct CLString*onePath;
	struct CLString*filePath;
	struct CLString*classSource;
	link2=self->pathsList->head;while( link2!=NULL){object=link2->data; 
	
		onePath=(cast_object( &CLString_ClassInstance , object));
		filePath=CLString_alloc( );
		CLString_init(filePath );
		filePath->_class->appendString( (void*) filePath->_components[0], onePath);
		filePath->_class->appendString( (void*) filePath->_components[0], theClassName);
		filePath->_class->appendCString( (void*) filePath->_components[0], ".clc");
		cFilePath=filePath->_class->cString( (void*) filePath->_components[0] );
		classFile=fopen(cFilePath,"r");
		CLString_release(filePath );
		if(classFile!=NULL)
		{
			printf("\nReading ");
			theClassName->_class->describe( (void*) theClassName->_components[0] );
			printf(" at %s",cFilePath);
			classSource=CLString_alloc( );
			CLString_init(classSource );
			CLString_readFilePointer(classSource, classFile);
			fclose(classFile);
			self->tokenizer->_class->createLines( (void*) self->tokenizer->_components[0], classSource,theLines);
			free(cFilePath);
			CLString_release(classSource );
			return;
		}
		free(cFilePath);
	link2=link2->next;}
	printf("\nSource not found for class : %s",theClassName->_class->cString( (void*) theClassName->_components[0] ));
}
void Main_filterAndAddSettings (struct Main* self, struct CLObjectList * theCombinedSettingsList , struct CLObjectList * theCombinedSettingNamesList , struct CLObjectList * theSettingsList , struct CLObjectList * theSettingNamesList ) 
{
	char inIfdef;
	char hasIdfef;
	char hasEndif;
	char isClass;
	char isDuplicate;
	unsigned long ifdefIndex;
	unsigned long endifIndex;
	struct CLLink*nameLink;
	struct CLLink*lineLink;
	struct CLString*oneName;
	struct CLObjectList*oneLine;
	inIfdef=0;
	nameLink=theCombinedSettingNamesList->head;
	lineLink=theCombinedSettingsList->head;
	while(lineLink!=NULL)
	{
		oneName=(cast_object( &CLString_ClassInstance , nameLink->data));
		oneLine=(cast_object( &CLObjectList_ClassInstance , lineLink->data));
		isClass=oneName->_class->containsString( (void*) oneName->_components[0], self->constants->classString);
		if(isClass==0)
		{
			isDuplicate=CLStringObjectList_containsString(NULL,oneName,theSettingNamesList);
			hasIdfef=oneName->_class->containsString( (void*) oneName->_components[0], self->constants->ifdefString);
			ifdefIndex=oneName->_class->indexOfString( (void*) oneName->_components[0], self->constants->ifdefString);
			if(hasIdfef==1&&ifdefIndex==0)inIfdef=1;
			if(inIfdef==1||(inIfdef==0&&isDuplicate==0))
			{
				theSettingNamesList->_class->addObject( (void*) theSettingNamesList->_components[0], (cast_object( &CLObject_ClassInstance , oneName)));
				theSettingsList->_class->addObject( (void*) theSettingsList->_components[0], (cast_object( &CLObject_ClassInstance , oneLine)));
			}
			hasEndif=oneName->_class->containsString( (void*) oneName->_components[0], self->constants->endifString);
			endifIndex=oneName->_class->indexOfString( (void*) oneName->_components[0], self->constants->endifString);
			if(hasEndif==1&&endifIndex==0)inIfdef=0;
		}
		nameLink=nameLink->next;
		lineLink=lineLink->next;
	}
}
void Main_writeFiles (struct Main* self, struct FileElements * theFileElements ) 
{
	struct CLLink*link8;
	struct CLLink*link7;
	struct CLLink*link6;
	struct CLLink*link5;
	struct CLLink*link4;
	struct CLLink*link3;
	struct CLObject* object;
	struct CLString*filePath;
	char*fileCString;
	FILE*filePointer;
	struct CLString*oneLine;
	struct CLString*oneClass;
	struct CLString*oneFunction;
	filePath=CLString_alloc( );
	CLString_init(filePath );
	CLString_appendString(filePath, self->targetPath);
	CLString_appendCString(filePath, ".h");
	fileCString= CLString_cString(filePath );
	filePointer=fopen(fileCString,"w");
	if(filePointer==NULL)
	{
		printf("Cannot write header at %s, errno : %i",fileCString,errno);
		return;
	}
	else printf("\nWriting header to %s",fileCString);
	free(fileCString);
	CLString_release(filePath );
	fputs("#ifndef clcsrc_h\n",filePointer);
	fputs("#define clcsrc_h\n",filePointer);
	fputs("#include <stdio.h>\n",filePointer);
	fputs("#include <stdlib.h>\n",filePointer);
	link3=theFileElements->settingNamesList->head;while( link3!=NULL){object=link3->data; 
	
		oneLine=(cast_object( &CLString_ClassInstance , object));
		CLString_writeToFilePointer(oneLine, filePointer);
		fputs("\n",filePointer);
	link3=link3->next;}
	fputs( Creator_createGeneralStructs(self->creator ),filePointer);
	link4=theFileElements->structureHeadersList->head;while( link4!=NULL){object=link4->data; 
	
		oneLine=(cast_object( &CLString_ClassInstance , object));
		CLString_writeToFilePointer(oneLine, filePointer);
	link4=link4->next;}
	link5=theFileElements->structuresList->head;while( link5!=NULL){object=link5->data; 
	
		oneLine=(cast_object( &CLString_ClassInstance , object));
		CLString_writeToFilePointer(oneLine, filePointer);
	link5=link5->next;}
	fputs("void* cast_object( void* theObject , void* theId );\n",filePointer);
	fputs("void  free_object( void* theObject );\n",filePointer);
	link6=theFileElements->functionHeadersList->head;while( link6!=NULL){object=link6->data; 
	
		oneLine=(cast_object( &CLString_ClassInstance , object));
		CLString_writeToFilePointer(oneLine, filePointer);
	link6=link6->next;}
	fputs("#endif\n",filePointer);
	fclose(filePointer);
	filePath=CLString_alloc( );
	CLString_init(filePath );
	CLString_appendString(filePath, self->targetPath);
	CLString_appendCString(filePath, ".c");
	fileCString= CLString_cString(filePath );
	filePointer=fopen(fileCString,"w");
	if(filePointer==NULL)
	{
		printf("Cannot write implementation at %s, errno : %i",fileCString,errno);
		return;
	}
	else printf("\nWriting implementation to %s",fileCString);
	free(fileCString);
	CLString_release(filePath );
	fputs("#include \"clcsrc.h\"\n",filePointer);
	fputs( Creator_createCasterMethod(self->creator ),filePointer);
	fputs( Creator_createDeallocatorMethod(self->creator ),filePointer);
	link7=theFileElements->classesList->head;while( link7!=NULL){object=link7->data; 
	
		oneClass=(cast_object( &CLString_ClassInstance , object));
		fputs("static struct ",filePointer);
		CLString_writeToFilePointer(oneClass, filePointer);
		fputs("_Class* ",filePointer);
		CLString_writeToFilePointer(oneClass, filePointer);
		fputs("_ClassInstance = NULL;\n",filePointer);
	link7=link7->next;}
	link8=theFileElements->functionsList->head;while( link8!=NULL){object=link8->data; 
	
		oneFunction=(cast_object( &CLString_ClassInstance , object));
		CLString_writeToFilePointer(oneFunction, filePointer);
	link8=link8->next;}
	fclose(filePointer);
}
void Main_destruct (struct Main* self ) 
{

}
void Main_retain (struct Main* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Main_release (struct Main* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Main_describe (struct Main* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
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
void CLObjectList_CreateClass( )
{
	CLObjectList_ClassInstance=malloc(sizeof(struct CLObjectList_Class));
	CLObjectList_ClassInstance->className="CLObjectList";
	CLObjectList_ClassInstance->classId=&CLObjectList_ClassInstance;
	CLObjectList_ClassInstance->init=CLObjectList_init;
	CLObjectList_ClassInstance->destruct=CLObjectList_destruct;
	CLObjectList_ClassInstance->addObject=CLObjectList_addObject;
	CLObjectList_ClassInstance->addObjectAtIndex=CLObjectList_addObjectAtIndex;
	CLObjectList_ClassInstance->addObjectsInObjectList=CLObjectList_addObjectsInObjectList;
	CLObjectList_ClassInstance->removeObject=CLObjectList_removeObject;
	CLObjectList_ClassInstance->removeObjectAtIndex=CLObjectList_removeObjectAtIndex;
	CLObjectList_ClassInstance->removeAllObjects=CLObjectList_removeAllObjects;
	CLObjectList_ClassInstance->objectAtIndex=CLObjectList_objectAtIndex;
	CLObjectList_ClassInstance->containsObject=CLObjectList_containsObject;
	CLObjectList_ClassInstance->indexOfObject=CLObjectList_indexOfObject;
	CLObjectList_ClassInstance->firstObject=CLObjectList_firstObject;
	CLObjectList_ClassInstance->lastObject=CLObjectList_lastObject;
	CLObjectList_ClassInstance->describe=CLObjectList_describe;
	CLObjectList_ClassInstance->className_CLObject="CLObject";
	CLObjectList_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	CLObjectList_ClassInstance->init_CLObject=CLObjectList_init;
	CLObjectList_ClassInstance->destruct_CLObject=CLObjectList_destruct;
	CLObjectList_ClassInstance->retain=CLObjectList_retain;
	CLObjectList_ClassInstance->release=CLObjectList_release;
	CLObjectList_ClassInstance->describe_CLObject=CLObjectList_describe;
	
}
struct CLObjectList* CLObjectList_alloc( )
{
	struct CLObjectList* result;
	if(CLObjectList_ClassInstance==NULL)CLObjectList_CreateClass( );
	result=malloc(sizeof(struct CLObjectList));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(CLObjectList_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(CLObjectList_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void CLObjectList_init (struct CLObjectList* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
void CLObjectList_destruct (struct CLObjectList* self ) 
{
	CLObjectList_removeAllObjects( self );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void CLObjectList_addObject (struct CLObjectList* self, struct CLObject * theObject ) 
{
	struct CLLink*newLink;
	theObject->_class->retain( (void*) theObject->_components[0] );
	newLink=malloc(sizeof(struct CLLink));
	newLink->data=theObject;
	newLink->next=NULL;
	if(self->head==NULL)self->head=newLink;
	else self->last->next=newLink;
	self->last=newLink;
	self->length=self->length+1;
}
void CLObjectList_addObjectAtIndex (struct CLObjectList* self, struct CLObject * theObject , unsigned long theIndex ) 
{
	struct CLLink*link;
	struct CLLink*lastLink;
	struct CLLink*newLink;
	unsigned long position;
	lastLink=NULL;
	link=self->head;
	position=0;
	theObject->_class->retain( (void*) theObject->_components[0] );
	while(link!=NULL)
	{
		if(position==theIndex)
		{
			newLink=malloc(sizeof(struct CLLink));
			newLink->data=theObject;
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
void CLObjectList_addObjectsInObjectList (struct CLObjectList* self, struct CLObjectList * theObjectList ) 
{
	struct CLLink*link;
	if(theObjectList->length>0)
	{
		link=theObjectList->head;
		while(link!=NULL)
		{
			CLObjectList_addObject( self, link->data);
			link=link->next;
		}
	}
}
void CLObjectList_removeObject (struct CLObjectList* self, struct CLObject * theObject ) 
{
	struct CLLink*link;
	struct CLLink*prev;
	struct CLObject*oneObject;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		if(link->data==theObject)
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
			oneObject=link->data;
			oneObject->_class->release( (void*) oneObject->_components[0] );
			free(link);
			self->length-=1;
			return;
		}
		prev=link;
		link=link->next;
	}
}
struct CLObject * CLObjectList_removeObjectAtIndex (struct CLObjectList* self, unsigned long theIndex ) 
{
	struct CLObject*object;
	object=CLObjectList_objectAtIndex( self, theIndex);
	if(object!=NULL)CLObjectList_removeObject( self, object);
	return object;
}
void CLObjectList_removeAllObjects (struct CLObjectList* self ) 
{
	struct CLLink*link;
	struct CLLink*prev;
	struct CLObject*object;
	link=self->head;
	prev=NULL;
	while(link!=NULL)
	{
		prev=link;
		link=link->next;
		object=prev->data;
		object->_class->release( (void*) object->_components[0] );
		free(prev);
	}
	self->head=NULL;
	self->last=NULL;
	self->length=0;
}
struct CLObject * CLObjectList_objectAtIndex (struct CLObjectList* self, unsigned long theIndex ) 
{
	struct CLLink*link;
	unsigned long position;
	link=self->head;
	position=0;
	while(link!=NULL)
	{
		if(position==theIndex)return link->data;
		position+=1;
		link=link->next;
	}
	return NULL;
}
char CLObjectList_containsObject (struct CLObjectList* self, struct CLObject * theObject ) 
{
	struct CLLink*link;
	link=self->head;
	while(link!=NULL)
	{
		if(link->data==theObject)return 1;
		link=link->next;
	}
	return 0;
}
unsigned long CLObjectList_indexOfObject (struct CLObjectList* self, struct CLObject * theObject ) 
{
	unsigned long index;
	struct CLLink*link;
	index=0;
	link=self->head;
	while(link!=NULL)
	{
		if(link->data==theObject)return index;
		index+=1;
		link=link->next;
	}
	return 0;
}
struct CLObject * CLObjectList_firstObject (struct CLObjectList* self ) 
{
	if(self->head!=NULL)return self->head->data;
	return NULL;
}
struct CLObject * CLObjectList_lastObject (struct CLObjectList* self ) 
{
	if(self->last!=NULL)return self->last->data;
	return NULL;
}
void CLObjectList_describe (struct CLObjectList* self ) 
{
	struct CLLink*link;
	struct CLObject*object;
	link=self->head;
	while(link!=NULL)
	{
		object=link->data;
		object->_class->describe( (void*) object->_components[0] );
		printf(" ");
		link=link->next;
	}
}
void CLObjectList_retain (struct CLObjectList* self ) 
{
	self->retainCount=self->retainCount+1;
}
void CLObjectList_release (struct CLObjectList* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLStringObjectList_CreateClass( )
{
	CLStringObjectList_ClassInstance=malloc(sizeof(struct CLStringObjectList_Class));
	CLStringObjectList_ClassInstance->className="CLStringObjectList";
	CLStringObjectList_ClassInstance->classId=&CLStringObjectList_ClassInstance;
	CLStringObjectList_ClassInstance->containsString=CLStringObjectList_containsString;
	CLStringObjectList_ClassInstance->indexOfString=CLStringObjectList_indexOfString;
	CLStringObjectList_ClassInstance->removeString=CLStringObjectList_removeString;
	CLStringObjectList_ClassInstance->removeStrings=CLStringObjectList_removeStrings;
	CLStringObjectList_ClassInstance->addStringAsUnique=CLStringObjectList_addStringAsUnique;
	CLStringObjectList_ClassInstance->addStringsAsUnique=CLStringObjectList_addStringsAsUnique;
	CLStringObjectList_ClassInstance->splitStringByCharacter=CLStringObjectList_splitStringByCharacter;
	CLStringObjectList_ClassInstance->className_CLObject="CLObject";
	CLStringObjectList_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	CLStringObjectList_ClassInstance->init=CLStringObjectList_init;
	CLStringObjectList_ClassInstance->destruct=CLStringObjectList_destruct;
	CLStringObjectList_ClassInstance->retain=CLStringObjectList_retain;
	CLStringObjectList_ClassInstance->release=CLStringObjectList_release;
	CLStringObjectList_ClassInstance->describe=CLStringObjectList_describe;
	
}
struct CLStringObjectList* CLStringObjectList_alloc( )
{
	struct CLStringObjectList* result;
	if(CLStringObjectList_ClassInstance==NULL)CLStringObjectList_CreateClass( );
	result=malloc(sizeof(struct CLStringObjectList));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(CLStringObjectList_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(CLStringObjectList_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
char CLStringObjectList_containsString (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) 
{
	struct CLLink*link;
	struct CLString*string;
	link=theObjectList->head;
	while(link!=NULL)
	{
		string=(cast_object( &CLString_ClassInstance , link->data));
		if(theString->_class->equals( (void*) theString->_components[0], string)==1)return 1;
		link=link->next;
	}
	return 0;
}
unsigned long CLStringObjectList_indexOfString (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) 
{
	unsigned long index;
	struct CLLink*link;
	struct CLString*string;
	index=0;
	link=theObjectList->head;
	while(link!=NULL)
	{
		string=(cast_object( &CLString_ClassInstance , link->data));
		if(theString->_class->equals( (void*) theString->_components[0], string)==1)return index;
		index+=1;
		link=link->next;
	}
	return 0;
}
void CLStringObjectList_removeString (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) 
{
	struct CLLink*link;
	struct CLObject*result;
	struct CLString*string;
	link=theObjectList->head;
	result=NULL;
	while(link!=NULL)
	{
		string=(cast_object( &CLString_ClassInstance , link->data));
		if(theString->_class->equals( (void*) theString->_components[0], string)==1)
		{
			result=link->data;
			break;
		}
		link=link->next;
	}
	if(result!=NULL)theObjectList->_class->removeObject( (void*) theObjectList->_components[0], result);
}
void CLStringObjectList_removeStrings (struct CLStringObjectList* self, struct CLObjectList * theStringList , struct CLObjectList * theObjectList ) 
{
	struct CLLink*link;
	link=theStringList->head;
	while(link!=NULL)
	{
		struct CLString*string;
		string=(cast_object( &CLString_ClassInstance , link->data));
		CLStringObjectList_removeString( self, string,theObjectList);
		link=link->next;
	}
}
void CLStringObjectList_addStringAsUnique (struct CLStringObjectList* self, struct CLString * theString , struct CLObjectList * theObjectList ) 
{
	char contains;
	contains=CLStringObjectList_containsString( self, theString,theObjectList);
	if(contains==0)theObjectList->_class->addObject( (void*) theObjectList->_components[0], (cast_object( &CLObject_ClassInstance , theString)));
}
void CLStringObjectList_addStringsAsUnique (struct CLStringObjectList* self, struct CLObjectList * theStringList , struct CLObjectList * theObjectList ) 
{
	struct CLLink*link;
	link=theStringList->head;
	while(link!=NULL)
	{
		struct CLString*string;
		string=(cast_object( &CLString_ClassInstance , link->data));
		CLStringObjectList_addStringAsUnique( self, string,theObjectList);
		link=link->next;
	}
}
struct CLObjectList * CLStringObjectList_splitStringByCharacter (struct CLStringObjectList* self, struct CLString * theString , char theCharacter ) 
{
	struct CLChar*link;
	struct CLString*word;
	struct CLObjectList*result;
	result=CLObjectList_alloc( );
	word=CLString_alloc( );
	result->_class->init( (void*) result->_components[0] );
	word->_class->init( (void*) word->_components[0] );
	link=theString->head;
	while(link!=NULL)
	{
		if(link->character==theCharacter)
		{
			if(word->length>0)
			{
				CLObjectList_addObject(result, (cast_object( &CLObject_ClassInstance , word)));
				word->_class->release( (void*) word->_components[0] );
				word=CLString_alloc();
				word->_class->init( (void*) word->_components[0] );
			}
		}
		else
		{
			CLString_appendCharacter(word, link->character);
		}
		link=link->next;
	}
	if(word->length>0) CLObjectList_addObject(result, (cast_object( &CLObject_ClassInstance , word)));
	word->_class->release( (void*) word->_components[0] );
	return result;
}
void CLStringObjectList_init (struct CLStringObjectList* self ) 
{
	self->retainCount=1;
}
void CLStringObjectList_destruct (struct CLStringObjectList* self ) 
{

}
void CLStringObjectList_retain (struct CLStringObjectList* self ) 
{
	self->retainCount=self->retainCount+1;
}
void CLStringObjectList_release (struct CLStringObjectList* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void CLStringObjectList_describe (struct CLStringObjectList* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void Creator_CreateClass( )
{
	Creator_ClassInstance=malloc(sizeof(struct Creator_Class));
	Creator_ClassInstance->className="Creator";
	Creator_ClassInstance->classId=&Creator_ClassInstance;
	Creator_ClassInstance->createGeneralStructs=Creator_createGeneralStructs;
	Creator_ClassInstance->createCasterMethod=Creator_createCasterMethod;
	Creator_ClassInstance->createDeallocatorMethod=Creator_createDeallocatorMethod;
	Creator_ClassInstance->createStructures=Creator_createStructures;
	Creator_ClassInstance->createInstanceStruct=Creator_createInstanceStruct;
	Creator_ClassInstance->createClassStruct=Creator_createClassStruct;
	Creator_ClassInstance->createFunctions=Creator_createFunctions;
	Creator_ClassInstance->createClassInitializer=Creator_createClassInitializer;
	Creator_ClassInstance->createInstanceInitializer=Creator_createInstanceInitializer;
	Creator_ClassInstance->createMethodFunction=Creator_createMethodFunction;
	Creator_ClassInstance->createFunctionHeader=Creator_createFunctionHeader;
	Creator_ClassInstance->createFunctionLine=Creator_createFunctionLine;
	Creator_ClassInstance->parameterFollows=Creator_parameterFollows;
	Creator_ClassInstance->className_CLObject="CLObject";
	Creator_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Creator_ClassInstance->init=Creator_init;
	Creator_ClassInstance->destruct=Creator_destruct;
	Creator_ClassInstance->retain=Creator_retain;
	Creator_ClassInstance->release=Creator_release;
	Creator_ClassInstance->describe=Creator_describe;
	
}
struct Creator* Creator_alloc( )
{
	struct Creator* result;
	if(Creator_ClassInstance==NULL)Creator_CreateClass( );
	result=malloc(sizeof(struct Creator));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Creator_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Creator_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
const char * Creator_createGeneralStructs (struct Creator* self ) 
{
	const char*structs;
	structs="struct Class\n""{\n""\tchar*	className;\n""\tvoid*	classId;\n""};\n""struct Instance\n""{\n""\tstruct Class*	_class;\n""\tvoid**	_components;\n""};\n";
	return structs;
}
const char * Creator_createCasterMethod (struct Creator* self ) 
{
	const char*method;
	method="void* cast_object( void* theId , void* theObject )\n""{\n""\tvoid**components;\n""\tcomponents=(((struct Instance*)theObject)->_components);\n""\twhile(*components!=NULL)\n""\t{\n""\t\tif (((struct Instance*)*components)->_class->classId==theId) return((void*)*components);\n""\t\tcomponents += 1;\n""\t}\n""\t#ifdef DEBUG\n""\tcomponents=(((struct Instance*)theObject)->_components);\n""\tprintf(\"\\nClassId : %lx Not Found in ClassInstance : %s\" , (long) theObject , ((struct Instance*)*components)->_class->className );\n\n""\t#endif\n""\treturn NULL;\n""}\n";
	return method;
}
const char * Creator_createDeallocatorMethod (struct Creator* self ) 
{
	const char*method;
	method="void free_object( void* theObject )\n""{\n""\tstruct Instance* instance;\n""\tvoid*  original;\n""\tvoid** pointer;\n""\tvoid** components;\n""\tinstance   = theObject;\n""\toriginal   = instance->_components[ 0 ];\n""\tpointer    = &original;\n""\tcomponents = instance->_components;\n""\tfree( original );\n""\tfree( components );\n""\t*pointer = NULL;\n""}\n";
	return method;
}
void Creator_createStructures (struct Creator* self, struct ClassElements * theElements , struct CLObjectList * theParentNamesList , struct CLObjectList * theParentElementsList , struct CLObjectList * theStructuresTargetList , struct CLObjectList * theStructureHeadersTargetList ) 
{
	Creator_createInstanceStruct( self, theElements->className,theParentNamesList,theParentElementsList,theStructuresTargetList,theStructureHeadersTargetList);
	Creator_createClassStruct( self, theElements->className,theParentNamesList,theParentElementsList,theElements->methodTokensList,theElements->methodNamesList,theStructuresTargetList,theStructureHeadersTargetList);
}
void Creator_createInstanceStruct (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theStructuresTargetList , struct CLObjectList * theStructureHeadersTargetList ) 
{
	struct CLLink*tokenLink;
	struct CLLink*membersLink;
	struct CLLink*classesLink;
	struct CLLink*elementsLink;
	struct Token*oneToken;
	struct CLString*result;
	struct CLString*forward;
	struct CLString*className;
	struct CLObjectList*memberLine;
	struct CLObjectList*membersList;
	struct ClassElements*classElements;
	result=CLString_alloc( );
	CLString_init(result );
	forward=CLString_alloc( );
	CLString_init(forward );
	CLString_appendCString(result, "struct ");
	CLString_appendString(result, theClassName);
	CLString_appendString(forward, result);
	CLString_appendCString(forward, ";\n");
	CLString_appendCString(result, "\n{\n\t");
	classesLink=theClassNamesList->head;
	elementsLink=theClassElementsList->head;
	while(classesLink!=NULL)
	{
		className=(cast_object( &CLString_ClassInstance , classesLink->data));
		classElements=(cast_object( &ClassElements_ClassInstance , elementsLink->data));
		CLString_appendCString(result, "struct ");
		CLString_appendString(result, className);
		CLString_appendCString(result, "_Class* _class");
		if(classesLink!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, ";\n\t");
		CLString_appendCString(result, "void** _components");
		if(classesLink!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, ";\n\t");
		membersList=(cast_object( &CLObjectList_ClassInstance , classElements->memberTokensList));
		membersLink=membersList->head;
		while(membersLink!=NULL)
		{
			memberLine=(cast_object( &CLObjectList_ClassInstance , membersLink->data));
			tokenLink=memberLine->head;
			while(tokenLink!=NULL)
			{
				oneToken=(cast_object( &Token_ClassInstance , tokenLink->data));
				if(oneToken->subType==kTokenSubTypeClass) CLString_appendCString(result, "struct ");
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, " ");
				tokenLink=tokenLink->next;
			}
			CLString_appendCString(result, "\n\t");
			membersLink=membersLink->next;
		}
		classesLink=classesLink->next;
		elementsLink=elementsLink->next;
	}
	CLString_appendCString(result, "\n};\n");
	CLObjectList_addObject(theStructuresTargetList, (cast_object( &CLObject_ClassInstance , result)));
	CLObjectList_addObject(theStructureHeadersTargetList, (cast_object( &CLObject_ClassInstance , forward)));
	CLString_release(result );
	CLString_release(forward );
}
void Creator_createClassStruct (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theCombinedMethodsList , struct CLObjectList * theCombinedMethodNamesList , struct CLObjectList * theStructuresTargetList , struct CLObjectList * theStructureHeadersTargetList ) 
{
	char isOriginal;
	char isDuplicate;
	char firstParenthese;
	unsigned long originalIndex;
	unsigned long duplicateIndex;
	struct CLLink*tokenLink;
	struct CLLink*classesLink;
	struct CLLink*elementsLink;
	struct CLLink*methodsLink;
	struct CLLink*methodNamesLink;
	struct Token*token;
	struct CLString*result;
	struct CLString*forward;
	struct CLString*className;
	struct CLString*methodName;
	struct CLObject*firstObject;
	struct CLObjectList*oneMethod;
	struct CLObjectList*firstLine;
	struct CLObjectList*duplicates;
	struct CLObjectList*methodsList;
	struct CLObjectList*methodNamesList;
	struct ClassElements*classElements;
	result=CLString_alloc( );
	CLString_init(result );
	forward=CLString_alloc( );
	CLString_init(forward );
	duplicates=CLObjectList_alloc( );
	CLObjectList_init(duplicates );
	CLString_appendCString(result, "struct ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "_Class");
	CLString_appendString(forward, result);
	CLString_appendCString(forward, ";\n");
	CLString_appendCString(result, "\n{\n\t");
	classesLink=theClassNamesList->head;
	elementsLink=theClassElementsList->head;
	while(classesLink!=NULL)
	{
		className=(cast_object( &CLString_ClassInstance , classesLink->data));
		classElements=(cast_object( &ClassElements_ClassInstance , elementsLink->data));
		CLString_appendCString(result, "char* ");
		CLString_appendCString(result, "className");
		if(classesLink!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, ";\n\t");
		CLString_appendCString(result, "void* ");
		CLString_appendCString(result, "classId");
		if(classesLink!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, ";\n\t");
		methodsList=(cast_object( &CLObjectList_ClassInstance , classElements->methodTokensList));
		methodNamesList=(cast_object( &CLObjectList_ClassInstance , classElements->methodNamesList));
		methodsLink=methodsList->head;
		methodNamesLink=methodNamesList->head;
		while(methodsLink!=NULL)
		{
			methodName=(cast_object( &CLString_ClassInstance , methodNamesLink->data));
			oneMethod=(cast_object( &CLObjectList_ClassInstance , methodsLink->data));
			isDuplicate=CLStringObjectList_containsString(NULL,methodName,duplicates);
			if(isDuplicate==1)
			{
				duplicateIndex=CLStringObjectList_indexOfString(NULL,methodName,duplicates);
				isOriginal=CLStringObjectList_containsString(NULL,methodName,theCombinedMethodNamesList);
				if(isOriginal==1)
				{
					struct CLObject*methodObject;
					originalIndex=CLStringObjectList_indexOfString(NULL,methodName,theCombinedMethodNamesList);
					methodObject=theCombinedMethodsList->_class->objectAtIndex( (void*) theCombinedMethodsList->_components[0], originalIndex);
					oneMethod=(cast_object( &CLObjectList_ClassInstance , methodObject));
				}
			}
			firstParenthese=0;
			firstObject=oneMethod->_class->objectAtIndex( (void*) oneMethod->_components[0], 0);
			firstLine=(cast_object( &CLObjectList_ClassInstance , firstObject));
			tokenLink=firstLine->head;
			while(tokenLink!=NULL)
			{
				token=(cast_object( &Token_ClassInstance , tokenLink->data));
				if(token->mainType==kTokenMainTypeSymbol)
				{
					CLString_appendString(result, token->text);
					if((token->text->head)->character=='('&&firstParenthese==0)
					{
						firstParenthese=1;
						CLString_appendCString(result, "struct ");
						CLString_appendString(result, theClassName);
						CLString_appendCString(result, "*");
						if(tokenLink->next!=NULL)
						{
							struct Token*nextToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
							if((nextToken->text->head)->character!=')') CLString_appendCString(result, ",");
						}
					}
				}
				else if(token->mainType==kTokenMainTypeWord)
				{
					if(token->subType==kTokenSubTypeMethod)
					{
						CLString_appendCString(result, "\t(*");
						CLString_appendString(result, methodName);
						if(isDuplicate==1)
						{
							CLString_appendCString(result, "_");
							CLString_appendString(result, className);
						}
						CLString_appendCString(result, ")");
					}
					else if(token->subType==kTokenSubTypeClass)
					{
						CLString_appendCString(result, "struct ");
						CLString_appendString(result, token->text);
					}
					else if(token->subType!=kTokenSubTypeVariable)
					{
						CLString_appendString(result, token->text);
					}
				}
				CLString_appendCString(result, " ");
				tokenLink=tokenLink->next;
			}
			CLObjectList_addObject(duplicates, (cast_object( &CLObject_ClassInstance , methodName)));
			CLString_appendCString(result, ";\n\t");
			methodsLink=methodsLink->next;
			methodNamesLink=methodNamesLink->next;
		}
		classesLink=classesLink->next;
		elementsLink=elementsLink->next;
	}
	CLString_appendCString(result, "\n};\n");
	CLObjectList_addObject(theStructuresTargetList, (cast_object( &CLObject_ClassInstance , result)));
	CLObjectList_addObject(theStructureHeadersTargetList, (cast_object( &CLObject_ClassInstance , forward)));
	CLString_release(result );
	CLString_release(forward );
	CLObjectList_release(duplicates );
}
void Creator_createFunctions (struct Creator* self, struct ClassElements * theElements , struct CLObjectList * theParentNamesList , struct CLObjectList * theParentElementsList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) 
{
	struct CLLink*link9;
	struct CLObject* object;
	struct CLObjectList*method;
	Creator_createClassInitializer( self, theElements->className,theParentNamesList,theParentElementsList,theFunctionsTargetList,theFunctionHeadersTargetList);
	Creator_createInstanceInitializer( self, theElements->className,theParentNamesList,theParentElementsList,theFunctionsTargetList,theFunctionHeadersTargetList);
	link9=theElements->methodTokensList->head;while( link9!=NULL){object=link9->data; 
	
		method=(cast_object( &CLObjectList_ClassInstance , object));
		Creator_createMethodFunction( self, theElements->className,method,theFunctionsTargetList,theFunctionHeadersTargetList);
	link9=link9->next;}
}
void Creator_createClassInitializer (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) 
{
	char isDuplicate;
	struct CLLink*classesLink;
	struct CLLink*elementsLink;
	struct CLLink*methodsLink;
	struct CLLink*methodNamesLink;
	struct CLString*result;
	struct CLString*forward;
	struct CLString*instance;
	struct CLString*className;
	struct CLString*methodName;
	struct CLObjectList*duplicates;
	struct CLObjectList*methodsList;
	struct CLObjectList*methodNamesList;
	struct ClassElements*classElements;
	result=CLString_alloc( );
	CLString_init(result );
	forward=CLString_alloc( );
	CLString_init(forward );
	instance=CLString_alloc( );
	CLString_init(instance );
	duplicates=CLObjectList_alloc( );
	CLObjectList_init(duplicates );
	CLString_appendString(instance, theClassName);
	CLString_appendCString(instance, "_ClassInstance");
	CLString_appendCString(result, "void ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "_CreateClass( )");
	CLString_appendString(forward, result);
	CLString_appendCString(forward, ";\n");
	CLString_appendCString(result, "\n{\n\t");
	CLString_appendString(result, instance);
	CLString_appendCString(result, "=malloc(sizeof(struct ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "_Class));\n\t");
	classesLink=theClassNamesList->head;
	elementsLink=theClassElementsList->head;
	while(classesLink!=NULL)
	{
		className=(cast_object( &CLString_ClassInstance , classesLink->data));
		classElements=(cast_object( &ClassElements_ClassInstance , elementsLink->data));
		CLString_appendString(result, instance);
		CLString_appendCString(result, "->className");
		if(classesLink!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, "=\"");
		CLString_appendString(result, className);
		CLString_appendCString(result, "\";\n\t");
		CLString_appendString(result, instance);
		CLString_appendCString(result, "->classId");
		if(classesLink!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, "=&");
		CLString_appendString(result, className);
		CLString_appendCString(result, "_ClassInstance;\n\t");
		methodsList=(cast_object( &CLObjectList_ClassInstance , classElements->methodTokensList));
		methodNamesList=(cast_object( &CLObjectList_ClassInstance , classElements->methodNamesList));
		methodsLink=methodsList->head;
		methodNamesLink=methodNamesList->head;
		while(methodNamesLink!=NULL)
		{
			methodName=(cast_object( &CLString_ClassInstance , methodNamesLink->data));
			isDuplicate=CLStringObjectList_containsString(NULL,methodName,duplicates);
			CLString_appendString(result, instance);
			CLString_appendCString(result, "->");
			CLString_appendString(result, methodName);
			if(isDuplicate==1)
			{
				CLString_appendCString(result, "_");
				CLString_appendString(result, className);
			}
			CLString_appendCString(result, "=");
			CLString_appendString(result, theClassName);
			CLString_appendCString(result, "_");
			CLString_appendString(result, methodName);
			CLString_appendCString(result, ";\n\t");
			CLObjectList_addObject(duplicates, (cast_object( &CLObject_ClassInstance , methodName)));
			methodsLink=methodsLink->next;
			methodNamesLink=methodNamesLink->next;
		}
		classesLink=classesLink->next;
		elementsLink=elementsLink->next;
	}
	CLString_appendCString(result, "\n}\n");
	CLObjectList_addObject(theFunctionsTargetList, (cast_object( &CLObject_ClassInstance , result)));
	CLObjectList_addObject(theFunctionHeadersTargetList, (cast_object( &CLObject_ClassInstance , forward)));
	CLObjectList_release(duplicates );
	CLString_release(instance );
	CLString_release(forward );
	CLString_release(result );
}
void Creator_createInstanceInitializer (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theClassNamesList , struct CLObjectList * theClassElementsList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) 
{
	int counter;
	char decimal[3];
	struct CLLink*namesToken;
	struct CLString*result;
	struct CLString*forward;
	struct CLString*instance;
	struct CLString*className;
	result=CLString_alloc( );
	CLString_init(result );
	forward=CLString_alloc( );
	CLString_init(forward );
	instance=CLString_alloc( );
	CLString_init(instance );
	CLString_appendString(instance, theClassName);
	CLString_appendCString(instance, "_ClassInstance");
	CLString_appendCString(result, "struct ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "* ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "_alloc( )");
	CLString_appendString(forward, result);
	CLString_appendCString(forward, ";\n");
	CLString_appendCString(result, "\n{\n\t");
	CLString_appendCString(result, "struct ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "* result;\n\t");
	CLString_appendCString(result, "if(");
	CLString_appendString(result, instance);
	CLString_appendCString(result, "==NULL)");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "_CreateClass( );\n\t");
	CLString_appendCString(result, "result=malloc(sizeof(struct ");
	CLString_appendString(result, theClassName);
	CLString_appendCString(result, "));\n\t");
	sprintf(decimal,"%lu",theClassNamesList->length+1);
	CLString_appendCString(result, "result->_components=malloc(sizeof(void*)*");
	CLString_appendCString(result, decimal);
	CLString_appendCString(result, ");\n\t");
	CLString_appendCString(result, "result->_class=(void*)&(");
	CLString_appendString(result, instance);
	CLString_appendCString(result, "->className);\n\t");
	namesToken=(theClassNamesList->head)->next;
	while(namesToken!=NULL)
	{
		className=(cast_object( &CLString_ClassInstance , namesToken->data));
		CLString_appendCString(result, "result->_components_");
		CLString_appendString(result, className);
		CLString_appendCString(result, "=result->_components;\n\t");
		CLString_appendCString(result, "result->_class_");
		CLString_appendString(result, className);
		CLString_appendCString(result, "=(void*)&(");
		CLString_appendString(result, instance);
		CLString_appendCString(result, "->className_");
		CLString_appendString(result, className);
		CLString_appendCString(result, ");\n\t");
		namesToken=namesToken->next;
	}
	counter=0;
	namesToken=theClassNamesList->head;
	while(namesToken!=NULL)
	{
		className=(cast_object( &CLString_ClassInstance , namesToken->data));
		sprintf(decimal,"%i",counter);
		++counter;
		CLString_appendCString(result, "result->_components[");
		CLString_appendCString(result, decimal);
		CLString_appendCString(result, "]=&(result->_class");
		if(namesToken!=theClassNamesList->head)
		{
			CLString_appendCString(result, "_");
			CLString_appendString(result, className);
		}
		CLString_appendCString(result, ");\n\t");
		namesToken=namesToken->next;
	}
	sprintf(decimal,"%i",counter);
	++counter;
	CLString_appendCString(result, "result->_components[");
	CLString_appendCString(result, decimal);
	CLString_appendCString(result, "]=NULL;\n\t");
	CLString_appendCString(result, "return result;\n}\n");
	CLObjectList_addObject(theFunctionsTargetList, (cast_object( &CLObject_ClassInstance , result)));
	CLObjectList_addObject(theFunctionHeadersTargetList, (cast_object( &CLObject_ClassInstance , forward)));
	CLString_release(instance );
	CLString_release(forward );
	CLString_release(result );
}
void Creator_createMethodFunction (struct Creator* self, struct CLString * theClassName , struct CLObjectList * theMethodList , struct CLObjectList * theFunctionsTargetList , struct CLObjectList * theFunctionHeadersTargetList ) 
{
	int index;
	void*firstData;
	long blockDepth;
	struct CLLink*lineLink;
	struct Token*first;
	struct CLString*result;
	struct CLString*forward;
	struct CLObjectList*line;
	blockDepth=1;
	lineLink=theMethodList->head;
	result=CLString_alloc( );
	CLString_init(result );
	forward=CLString_alloc( );
	CLString_init(forward );
	while(lineLink!=NULL)
	{
		line=(cast_object( &CLObjectList_ClassInstance , lineLink->data));
		if(lineLink==theMethodList->head)
		{
			Creator_createFunctionHeader( self, result,theClassName,line);
			CLString_appendString(forward, result);
			CLString_appendCString(forward, ";\n");
			CLString_appendCString(result, "\n{\n");
		}
		else
		{
			firstData=(line->head)->data;
			first=(cast_object( &Token_ClassInstance , firstData));
			if(line->length==1&&(first->text->head)->character=='}')blockDepth-=1;
			for(index=0;
			index<blockDepth;
			index++) CLString_appendCString(result, "\t");
			Creator_createFunctionLine( self, result,theClassName,line);
			if(lineLink!=theMethodList->last) CLString_appendCString(result, "\n");
			if(line->length==1&&(first->text->head)->character=='{')blockDepth+=1;
		}
		lineLink=lineLink->next;
	}
	CLString_appendCString(result, "\n}\n");
	CLObjectList_addObject(theFunctionsTargetList, (cast_object( &CLObject_ClassInstance , result)));
	CLObjectList_addObject(theFunctionHeadersTargetList, (cast_object( &CLObject_ClassInstance , forward)));
	CLString_release(result );
	CLString_release(forward );
}
void Creator_createFunctionHeader (struct Creator* self, struct CLString * theResult , struct CLString * theClassName , struct CLObjectList * theLine ) 
{
	char firstParenthese;
	struct CLLink*tokenLink;
	struct Token*oneToken;
	tokenLink=theLine->head;
	firstParenthese=0;
	while(tokenLink!=NULL)
	{
		oneToken=(cast_object( &Token_ClassInstance , tokenLink->data));
		if(oneToken->mainType==kTokenMainTypeSymbol)
		{
			CLString_appendString(theResult, oneToken->text);
			if((oneToken->text->head)->character=='('&&firstParenthese==0)
			{
				firstParenthese=1;
				CLString_appendCString(theResult, "struct ");
				CLString_appendString(theResult, theClassName);
				CLString_appendCString(theResult, "* self");
				if(tokenLink->next!=NULL)
				{
					struct Token*nextToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
					if((nextToken->text->head)->character!=')') CLString_appendCString(theResult, ",");
				}
			}
		}
		else if(oneToken->mainType==kTokenMainTypeWord)
		{
			if(oneToken->subType==kTokenSubTypeMethod)
			{
				CLString_appendString(theResult, theClassName);
				CLString_appendCString(theResult, "_");
			}
			else if(oneToken->subType==kTokenSubTypeClass)
			{
				CLString_appendCString(theResult, "struct ");
			}
			CLString_appendString(theResult, oneToken->text);
		}
		CLString_appendCString(theResult, " ");
		tokenLink=tokenLink->next;
	}
}
void Creator_createFunctionLine (struct Creator* self, struct CLString * theResult , struct CLString * theClassName , struct CLObjectList * theLine ) 
{
	char inCasting;
	struct CLLink*tokenLink;
	struct Token*oneToken;
	struct Token*lastToken;
	struct CLString*result;
	result=theResult;
	tokenLink=theLine->head;
	inCasting=0;
	lastToken=NULL;
	while(tokenLink!=NULL)
	{
		oneToken=(cast_object( &Token_ClassInstance , tokenLink->data));
		if(oneToken->mainType==kTokenMainTypeWord)
		{
			if(lastToken!=NULL&&lastToken->mainType==oneToken->mainType) CLString_appendCString(result, " ");
			if(oneToken->subType==kTokenSubTypeClass)
			{
				CLString_appendCString(result, "struct ");
				CLString_appendString(result, oneToken->text);
			}
			else if(oneToken->subType==kTokenSubTypeCast)
			{
				CLString_appendCString(result, "cast_object( &");
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, "_ClassInstance , ");
				inCasting=1;
			}
			else if(oneToken->subType==kTokenSubTypeVariable)
			{
				if(oneToken->isMember) CLString_appendCString(result, "self->");
				CLString_appendString(result, oneToken->text);
			}
			else if(oneToken->subType==kTokenSubTypeInstance)
			{
				if(oneToken->isMember) CLString_appendCString(result, "self->");
				CLString_appendString(result, oneToken->text);
			}
			else if(oneToken->subType==kTokenSubTypeImplicitCall)
			{
				CLString_appendCString(result, "_class->");
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, "( (void*) ");
				CLString_appendString(result, oneToken->instanceList);
				CLString_appendCString(result, "_components[0]");
				if(Creator_parameterFollows( self, tokenLink)==1) CLString_appendCString(result, ",");
			}
			else if(oneToken->subType==kTokenSubTypeExplicitCall)
			{
				CLString_appendString(result, oneToken->classId);
				CLString_appendCString(result, "_");
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, "(");
				CLString_appendString(result, oneToken->instanceList);
				if(Creator_parameterFollows( self, tokenLink)==1) CLString_appendCString(result, ",");
			}
			else if(oneToken->subType==kTokenSubTypeExplicitAllocCall)
			{
				CLString_appendString(result, oneToken->instanceList);
				CLString_appendCString(result, "=");
				CLString_appendString(result, oneToken->classId);
				CLString_appendCString(result, "_");
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, "(");
			}
			else if(oneToken->subType==kTokenSubTypeExplicitClassCall)
			{
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, "(( cast_object( &");
				CLString_appendString(result, oneToken->classId);
				CLString_appendCString(result, "_ClassInstance ,");
				inCasting=1;
			}
			else if(oneToken->subType==kTokenSubTypeLocalCall)
			{
				CLString_appendString(result, theClassName);
				CLString_appendCString(result, "_");
				CLString_appendString(result, oneToken->text);
				CLString_appendCString(result, "( self");
				if(Creator_parameterFollows( self, tokenLink)==1) CLString_appendCString(result, ",");
			}
			else if(oneToken->subType==kTokenSubTypeLocalCallReference)
			{
				CLString_appendCString(result, "self->_class->");
				CLString_appendString(result, oneToken->text);
			}
			else if(oneToken->subType==kTokenSubTypeForEachCycle)
			{
				CLString_appendString(result, oneToken->linkId);
				CLString_appendCString(result, "=");
				CLString_appendString(result, oneToken->containerId);
				CLString_appendCString(result, "->head;while( ");
				CLString_appendString(result, oneToken->linkId);
				CLString_appendCString(result, "!=NULL){");
				CLString_appendString(result, oneToken->variableId);
				CLString_appendCString(result, "=");
				CLString_appendString(result, oneToken->linkId);
				CLString_appendCString(result, "->data;");
			}
			else
			{
				CLString_appendString(result, oneToken->text);
			}
		}
		else if(oneToken->mainType==kTokenMainTypeSymbol)
		{
			if(oneToken->subType==kTokenSubTypeImplicitAccessor)
			{
				CLString_appendCString(result, "->");
			}
			else if(oneToken->subType==kTokenSubTypeExplicitAccessor)
			{
				CLString_appendCString(result, "_");
			}
			else if(oneToken->subType==kTokenSubTypeStructAccessor)
			{
				CLString_appendString(result, oneToken->text);
			}
			else
			{
				if(inCasting==1) CLString_appendCString(result, "))");
				inCasting=0;
				if((oneToken->text->head)->character=='}'&&oneToken->linkId!=NULL)
				{
					CLString_appendString(result, oneToken->linkId);
					CLString_appendCString(result, "=");
					CLString_appendString(result, oneToken->linkId);
					CLString_appendCString(result, "->next;");
				}
				CLString_appendString(result, oneToken->text);
			}
		}
		else if(oneToken->mainType!=kTokenMainTypeUndefined)
		{
			if(inCasting==1) CLString_appendCString(result, "))");
			inCasting=0;
			CLString_appendString(result, oneToken->text);
		}
		else
		{
			if((result->last)->character!='\t'&&(result->last)->character!=' ') CLString_appendCString(result, " ");
		}
		lastToken=oneToken;
		tokenLink=tokenLink->next;
	}
}
char Creator_parameterFollows (struct Creator* self, struct CLLink * theLink ) 
{
	struct Token*nextToken;
	if(theLink->next!=NULL&&theLink->next->next!=NULL)
	{
		nextToken=(cast_object( &Token_ClassInstance , theLink->next->next->data));
		if((nextToken->text->head)->character!=')')return 1;
	}
	return 0;
}
void Creator_init (struct Creator* self ) 
{
	self->retainCount=1;
}
void Creator_destruct (struct Creator* self ) 
{

}
void Creator_retain (struct Creator* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Creator_release (struct Creator* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Creator_describe (struct Creator* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void Analyzer_CreateClass( )
{
	Analyzer_ClassInstance=malloc(sizeof(struct Analyzer_Class));
	Analyzer_ClassInstance->className="Analyzer";
	Analyzer_ClassInstance->classId=&Analyzer_ClassInstance;
	Analyzer_ClassInstance->organizeTokens=Analyzer_organizeTokens;
	Analyzer_ClassInstance->analyzeGeneral=Analyzer_analyzeGeneral;
	Analyzer_ClassInstance->analyzeSetting=Analyzer_analyzeSetting;
	Analyzer_ClassInstance->analyzeClassDef=Analyzer_analyzeClassDef;
	Analyzer_ClassInstance->extractClassName=Analyzer_extractClassName;
	Analyzer_ClassInstance->extractMemberName=Analyzer_extractMemberName;
	Analyzer_ClassInstance->extractMethodName=Analyzer_extractMethodName;
	Analyzer_ClassInstance->analyzeMembers=Analyzer_analyzeMembers;
	Analyzer_ClassInstance->analyzeMethods=Analyzer_analyzeMethods;
	Analyzer_ClassInstance->analyzeMethodDef=Analyzer_analyzeMethodDef;
	Analyzer_ClassInstance->analyzeLine=Analyzer_analyzeLine;
	Analyzer_ClassInstance->analyzeForEachToken=Analyzer_analyzeForEachToken;
	Analyzer_ClassInstance->addLinkStructAndVariable=Analyzer_addLinkStructAndVariable;
	Analyzer_ClassInstance->analyzeAllocToken=Analyzer_analyzeAllocToken;
	Analyzer_ClassInstance->analyzeClassToken=Analyzer_analyzeClassToken;
	Analyzer_ClassInstance->analyzeMethodToken=Analyzer_analyzeMethodToken;
	Analyzer_ClassInstance->analyzeMemberToken=Analyzer_analyzeMemberToken;
	Analyzer_ClassInstance->analyzeInstanceToken=Analyzer_analyzeInstanceToken;
	Analyzer_ClassInstance->analyzeInstanceList=Analyzer_analyzeInstanceList;
	Analyzer_ClassInstance->className_CLObject="CLObject";
	Analyzer_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Analyzer_ClassInstance->init=Analyzer_init;
	Analyzer_ClassInstance->destruct=Analyzer_destruct;
	Analyzer_ClassInstance->retain=Analyzer_retain;
	Analyzer_ClassInstance->release=Analyzer_release;
	Analyzer_ClassInstance->describe=Analyzer_describe;
	
}
struct Analyzer* Analyzer_alloc( )
{
	struct Analyzer* result;
	if(Analyzer_ClassInstance==NULL)Analyzer_CreateClass( );
	result=malloc(sizeof(struct Analyzer));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Analyzer_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Analyzer_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Analyzer_organizeTokens (struct Analyzer* self, struct CLObjectList * theLines , struct ClassElements * theElements , struct CLObjectList * theParentNamesList ) 
{
	struct CLLink*link10;
	struct CLObject* object;
	long depth;
	struct Line*oneLine;
	struct CLObjectList*methodLines;
	depth=0;
	methodLines=NULL;
	link10=theLines->head;while( link10!=NULL){object=link10->data; 
	
		oneLine=(cast_object( &Line_ClassInstance , object));
		if(oneLine->type==kLineTypeGeneral)
		{
			Analyzer_analyzeGeneral( self, oneLine,depth,&methodLines,theElements->memberNamesList,theElements->memberTokensList,theElements->methodNamesList,theElements->methodTokensList);
		}
		else if(oneLine->type==kLineTypeSetting)
		{
			Analyzer_analyzeSetting( self, oneLine,depth,&methodLines,theElements->usedClassNamesList,theElements->memberNamesList,theElements->memberTokensList,theElements->settingNamesList,theElements->settingTokensList);
		}
		else if(oneLine->type==kLineTypeClassDef)
		{
			Analyzer_analyzeClassDef( self, oneLine,theParentNamesList,theElements->usedClassNamesList);
		}
		else if(oneLine->type==kLineTypeBlockStart)
		{
			++depth;
			if(depth>2)methodLines->_class->addObject( (void*) methodLines->_components[0], (cast_object( &CLObject_ClassInstance , oneLine->tokens)));
		}
		else if(oneLine->type==kLineTypeBlockEnd)
		{
			if(depth>2)methodLines->_class->addObject( (void*) methodLines->_components[0], (cast_object( &CLObject_ClassInstance , oneLine->tokens)));
			--depth;
		}
	link10=link10->next;}
	if(methodLines!=NULL) CLObjectList_release(methodLines );
}
void Analyzer_analyzeGeneral (struct Analyzer* self, struct Line * theLine , long theDepth , struct CLObjectList * * theMethodLines , struct CLObjectList * theMemberNames , struct CLObjectList * theMembers , struct CLObjectList * theMethodNames , struct CLObjectList * theMethods ) 
{
	void*lastData;
	struct Token*lastToken;
	struct CLString*memberName;
	struct CLObjectList*methodLines;
	methodLines=*theMethodLines;
	if(theDepth>1)
	{
		methodLines->_class->addObject( (void*) methodLines->_components[0], (cast_object( &CLObject_ClassInstance , theLine->tokens)));
	}
	else if(theDepth==1)
	{
		lastData=(theLine->tokens->last)->data;
		lastToken=(cast_object( &Token_ClassInstance , lastData));
		if(lastToken->mainType==kTokenMainTypeSymbol&&(lastToken->text->head)->character==';')
		{
			memberName=Analyzer_extractMemberName( self, theLine->tokens);
			if(memberName!=NULL)
			{
				theMemberNames->_class->addObject( (void*) theMemberNames->_components[0], (cast_object( &CLObject_ClassInstance , memberName)));
				theMembers->_class->addObject( (void*) theMembers->_components[0], (cast_object( &CLObject_ClassInstance , theLine->tokens)));
			}
		}
		else
		{
			memberName=Analyzer_extractMethodName( self, theLine->tokens);
			if(memberName!=NULL)
			{
				if(methodLines!=NULL)methodLines->_class->release( (void*) methodLines->_components[0] );
				*theMethodLines=CLObjectList_alloc();
				methodLines=*theMethodLines;
				methodLines->_class->init( (void*) methodLines->_components[0] );
				methodLines->_class->addObject( (void*) methodLines->_components[0], (cast_object( &CLObject_ClassInstance , theLine->tokens)));
				theMethodNames->_class->addObject( (void*) theMethodNames->_components[0], (cast_object( &CLObject_ClassInstance , memberName)));
				theMethods->_class->addObject( (void*) theMethods->_components[0], (cast_object( &CLObject_ClassInstance , methodLines)));
			}
		}
	}
}
void Analyzer_analyzeSetting (struct Analyzer* self, struct Line * theLine , long theDepth , struct CLObjectList * * theMethodLines , struct CLObjectList * theClassPool , struct CLObjectList * theMemberNames , struct CLObjectList * theMembers , struct CLObjectList * theSettingNames , struct CLObjectList * theSettings ) 
{
	struct Token*token;
	struct CLString*className;
	struct CLObjectList*tokens;
	struct CLObjectList*methodLines;
	if(theDepth==0)
	{
		theSettings->_class->addObject( (void*) theSettings->_components[0], (cast_object( &CLObject_ClassInstance , theLine->tokens)));
		theSettingNames->_class->addObject( (void*) theSettingNames->_components[0], (cast_object( &CLObject_ClassInstance , theLine->text)));
		className=Analyzer_extractClassName( self, theLine->tokens);
		if(className!=NULL)
		{
			CLStringObjectList_addStringAsUnique(NULL,className,theClassPool);
			CLString_release(className );
		}
	}
	else if(theDepth==1)
	{
		token=Token_alloc( );
		tokens=CLObjectList_alloc( );
		token->_class->init( (void*) token->_components[0] );
		tokens->_class->init( (void*) tokens->_components[0] );
		token->mainType=kTokenMainTypeSetting;
		token->_class->setText( (void*) token->_components[0], theLine->text);
		tokens->_class->addObject( (void*) tokens->_components[0], (cast_object( &CLObject_ClassInstance , token)));
		theMembers->_class->addObject( (void*) theMembers->_components[0], (cast_object( &CLObject_ClassInstance , tokens)));
		theMemberNames->_class->addObject( (void*) theMemberNames->_components[0], (cast_object( &CLObject_ClassInstance , self->constants->settingString)));
		Token_release(token );
		CLObjectList_release(tokens );
	}
	else if(theDepth>1)
	{
		token=Token_alloc( );
		tokens=CLObjectList_alloc( );
		token->_class->init( (void*) token->_components[0] );
		tokens->_class->init( (void*) tokens->_components[0] );
		token->mainType=kTokenMainTypeSetting;
		token->_class->setText( (void*) token->_components[0], theLine->text);
		tokens->_class->addObject( (void*) tokens->_components[0], (cast_object( &CLObject_ClassInstance , token)));
		methodLines=*theMethodLines;
		methodLines->_class->addObject( (void*) methodLines->_components[0], (cast_object( &CLObject_ClassInstance , tokens)));
		Token_release(token );
		CLObjectList_release(tokens );
	}
}
void Analyzer_analyzeClassDef (struct Analyzer* self, struct Line * theLine , struct CLObjectList * theParentClassNamesList , struct CLObjectList * theUsedClassNamesList ) 
{
	struct CLLink*link11;
	struct CLObject* object;
	struct Token*oneToken;
	link11=theLine->tokens->head;while( link11!=NULL){object=link11->data; 
	
		oneToken=(cast_object( &Token_ClassInstance , object));
		if(oneToken->mainType==kTokenMainTypeWord)
		{
			CLObjectList_addObject(theParentClassNamesList, (cast_object( &CLObject_ClassInstance , oneToken->text)));
			CLObjectList_addObject(theUsedClassNamesList, (cast_object( &CLObject_ClassInstance , oneToken->text)));
		}
	link11=link11->next;}
}
struct CLString * Analyzer_extractClassName (struct Analyzer* self, struct CLObjectList * theTokens ) 
{
	struct CLLink*link12;
	struct CLObject* object;
	char isClass;
	struct Token*token;
	struct CLString*result;
	result=NULL;
	link12=theTokens->head;while( link12!=NULL){object=link12->data; 
	
		token=(cast_object( &Token_ClassInstance , object));
		isClass=token->text->_class->containsString( (void*) token->text->_components[0], self->constants->clcString);
		if(token->mainType==kTokenMainTypeString&&isClass==1)
		{
			result=token->text->_class->stringByRemovingExtension( (void*) token->text->_components[0] );
			break;
		}
	link12=link12->next;}
	return result;
}
struct CLString * Analyzer_extractMemberName (struct Analyzer* self, struct CLObjectList * theTokens ) 
{
	struct CLLink*link13;
	struct CLObject* object;
	struct Token*oneToken;
	struct CLString*lastWord;
	lastWord=NULL;
	link13=theTokens->head;while( link13!=NULL){object=link13->data; 
	
		oneToken=(cast_object( &Token_ClassInstance , object));
		if(oneToken->mainType==kTokenMainTypeSymbol)
		{
			if((oneToken->text->head)->character==';'||(oneToken->text->head)->character=='['||(oneToken->text->head)->character==')')return lastWord;
		}
		else if(oneToken->mainType==kTokenMainTypeWord)lastWord=oneToken->text;
	link13=link13->next;}
	return NULL;
}
struct CLString * Analyzer_extractMethodName (struct Analyzer* self, struct CLObjectList * theTokens ) 
{
	struct CLLink*link14;
	struct CLObject* object;
	struct Token*oneToken;
	struct CLString*lastWord;
	lastWord=NULL;
	link14=theTokens->head;while( link14!=NULL){object=link14->data; 
	
		oneToken=(cast_object( &Token_ClassInstance , object));
		if(oneToken->mainType==kTokenMainTypeSymbol&&(oneToken->text->head)->character=='(')return lastWord;
		else if(oneToken->mainType==kTokenMainTypeWord)lastWord=oneToken->text;
	link14=link14->next;}
	return NULL;
}
void Analyzer_analyzeMembers (struct Analyzer* self, struct ClassElements * theElements ) 
{
	struct CLLink*link16;
	struct CLObject* tokenObject;
	struct CLLink*link15;
	struct CLObject* membersObject;
	char isUsed;
	char isUnused;
	unsigned long unusedIndex;
	struct Token*oneToken;
	struct Token*lastToken;
	struct Token*lastClassToken;
	struct CLObjectList*memberTokens;
	link15=theElements->memberTokensList->head;while( link15!=NULL){membersObject=link15->data; 
	
		memberTokens=(cast_object( &CLObjectList_ClassInstance , membersObject));
		lastToken=NULL;
		lastClassToken=NULL;
		link16=memberTokens->head;while( link16!=NULL){tokenObject=link16->data; 
		
			oneToken=(cast_object( &Token_ClassInstance , tokenObject));
			if(oneToken->mainType==kTokenMainTypeWord)
			{
				isUsed=CLStringObjectList_containsString(NULL,oneToken->text,theElements->usedClassNamesList);
				if(isUsed==1)
				{
					oneToken->_class->setClassId( (void*) oneToken->_components[0], oneToken->text);
					oneToken->subType=kTokenSubTypeClass;
					isUnused=CLStringObjectList_containsString(NULL,oneToken->text,theElements->unusedClassNamesList);
					if(isUnused==1)
					{
						unusedIndex=CLStringObjectList_indexOfString(NULL,oneToken->text,theElements->unusedClassNamesList);
						theElements->unusedClassNamesList->_class->removeObject( (void*) theElements->unusedClassNamesList->_components[0], theElements->unusedClassNamesList->_class->objectAtIndex( (void*) theElements->unusedClassNamesList->_components[0], unusedIndex));
					}
					lastClassToken=oneToken;
				}
			}
			else if(oneToken->mainType==kTokenMainTypeSymbol)
			{
				if((oneToken->text->head)->character==';'||(oneToken->text->head)->character=='['||(oneToken->text->head)->character==')')
				{
					lastToken->subType=kTokenSubTypeVariable;
					lastToken->isMember=1;
					if(lastClassToken!=NULL)
					{
						lastToken->_class->setClassId( (void*) lastToken->_components[0], lastClassToken->text);
						lastToken->subType=kTokenSubTypeInstance;
					}
				}
			}
			lastToken=oneToken;
		link16=link16->next;}
	link15=link15->next;}
}
void Analyzer_analyzeMethods (struct Analyzer* self, struct ClassElements * theElements ) 
{
	struct CLLink*link17;
	struct CLObject* object;
	struct CLLink*lineLink;
	struct Scope*scope;
	struct Token*selfToken;
	struct CLObjectList*oneLine;
	struct CLObjectList*oneMethod;
	struct CLObjectList*scopeList;
	selfToken=Token_alloc( );
	Token_init(selfToken );
	Token_setClassId(selfToken, theElements->className);
	selfToken->mainType=kTokenMainTypeWord;
	selfToken->subType=kTokenSubTypeInstance;
	scopeList=CLObjectList_alloc( );
	CLObjectList_init(scopeList );
	link17=theElements->methodTokensList->head;while( link17!=NULL){object=link17->data; 
	
		oneMethod=(cast_object( &CLObjectList_ClassInstance , object));
		scope=Scope_alloc( );
		Scope_init(scope );
		scope->type=kScopeTypeNormal;
		scope->instancesList->_class->addObject( (void*) scope->instancesList->_components[0], (cast_object( &CLObject_ClassInstance , selfToken)));
		scope->instanceNamesList->_class->addObject( (void*) scope->instanceNamesList->_components[0], (cast_object( &CLObject_ClassInstance , self->constants->selfString)));
		CLObjectList_addObject(scopeList, (cast_object( &CLObject_ClassInstance , scope)));
		lineLink=oneMethod->head;
		while(lineLink!=NULL)
		{
			oneLine=(cast_object( &CLObjectList_ClassInstance , lineLink->data));
			if(lineLink==oneMethod->head)
			{
				Analyzer_analyzeMethodDef( self, oneLine,scopeList,theElements);
			}
			else
			{
				Analyzer_analyzeLine( self, oneLine,oneMethod,scopeList,theElements);
			}
			lineLink=lineLink->next;
		}
		CLObjectList_removeObject(scopeList, (cast_object( &CLObject_ClassInstance , scope)));
		Scope_release(scope );
	link17=link17->next;}
	Token_release(selfToken );
	CLObjectList_release(scopeList );
}
void Analyzer_analyzeMethodDef (struct Analyzer* self, struct CLObjectList * theLine , struct CLObjectList * theScopeList , struct ClassElements * theElements ) 
{
	struct CLLink*link18;
	struct CLObject* object;
	void*scopeData;
	char isUsedClass;
	char isUnusedClass;
	unsigned long unusedIndex;
	struct Scope*scope;
	struct Token*oneToken;
	struct Token*lastToken;
	struct Token*lastClassToken;
	scopeData=(theScopeList->last)->data;
	scope=(cast_object( &Scope_ClassInstance , scopeData));
	oneToken=NULL;
	lastToken=NULL;
	lastClassToken=NULL;
	link18=theLine->head;while( link18!=NULL){object=link18->data; 
	
		oneToken=(cast_object( &Token_ClassInstance , object));
		if(oneToken->mainType==kTokenMainTypeWord)
		{
			isUsedClass=CLStringObjectList_containsString(NULL,oneToken->text,theElements->usedClassNamesList);
			if(isUsedClass==1)
			{
				oneToken->subType=kTokenSubTypeClass;
				oneToken->_class->setClassId( (void*) oneToken->_components[0], oneToken->text);
				lastClassToken=oneToken;
				isUnusedClass=CLStringObjectList_containsString(NULL,oneToken->text,theElements->unusedClassNamesList);
				if(isUnusedClass==1)
				{
					unusedIndex=CLStringObjectList_indexOfString(NULL,oneToken->text,theElements->unusedClassNamesList);
					theElements->unusedClassNamesList->_class->removeObjectAtIndex( (void*) theElements->unusedClassNamesList->_components[0], unusedIndex);
				}
			}
			else
			{
				if(lastClassToken!=NULL)
				{
					oneToken->subType=kTokenSubTypeInstance;
					oneToken->_class->setClassId( (void*) oneToken->_components[0], lastClassToken->text);
					scope->instancesList->_class->addObject( (void*) scope->instancesList->_components[0], (cast_object( &CLObject_ClassInstance , oneToken)));
					scope->instanceNamesList->_class->addObject( (void*) scope->instanceNamesList->_components[0], (cast_object( &CLObject_ClassInstance , oneToken->text)));
					lastClassToken=NULL;
				}
			}
		}
		else if(oneToken->mainType==kTokenMainTypeSymbol&&lastToken!=NULL)
		{
			if(lastToken->mainType==kTokenMainTypeWord)
			{
				if((oneToken->text->head)->character=='(')
				{
					lastToken->subType=kTokenSubTypeMethod;
					lastToken->_class->setClassId( (void*) lastToken->_components[0], theElements->className);
				}
				if((oneToken->text->head)->character==','||(oneToken->text->head)->character=='['||(oneToken->text->head)->character==')')
				{
					lastToken->subType=kTokenSubTypeVariable;
				}
			}
		}
		lastToken=oneToken;
	link18=link18->next;}
}
void Analyzer_analyzeLine (struct Analyzer* self, struct CLObjectList * theLine , struct CLObjectList * theMethodLines , struct CLObjectList * theScopeList , struct ClassElements * theElements ) 
{
	char isFor;
	char isAlloc;
	char hasClass;
	char hasMethod;
	char hasMember;
	char hasInstance;
	char isStructChain;
	unsigned long memberIndex;
	unsigned long instanceIndex;
	struct CLLink*tokenLink;
	struct Scope*scope;
	struct Scope*oneScope;
	struct Token*oneToken;
	struct Token*nextToken;
	struct CLObject*scopeData;
	tokenLink=theLine->head;
	scopeData=theScopeList->_class->lastObject( (void*) theScopeList->_components[0] );
	scope=(cast_object( &Scope_ClassInstance , scopeData));
	isStructChain=0;
	while(tokenLink!=NULL)
	{
		oneToken=(cast_object( &Token_ClassInstance , tokenLink->data));
		if(oneToken->subType==kTokenSubTypeUndefined)
		{
			if(oneToken->mainType==kTokenMainTypeWord)
			{
				if(isStructChain==0)
				{
					isFor=self->constants->forString->_class->equals( (void*) self->constants->forString->_components[0], oneToken->text);
					isAlloc=self->constants->allocString->_class->equals( (void*) self->constants->allocString->_components[0], oneToken->text);
					hasClass=CLStringObjectList_containsString(NULL,oneToken->text,theElements->usedClassNamesList);
					hasMethod=CLStringObjectList_containsString(NULL,oneToken->text,theElements->methodNamesList);
					hasMember=CLStringObjectList_containsString(NULL,oneToken->text,theElements->memberNamesList);
					hasInstance=CLStringObjectList_containsString(NULL,oneToken->text,scope->instanceNamesList);
					if(isFor==1)Analyzer_analyzeForEachToken( self, &tokenLink,scope,theElements->memberNamesList,theElements->usedClassNamesList,theMethodLines);
					else if(isAlloc==1)Analyzer_analyzeAllocToken( self, oneToken,theLine);
					else if(hasClass==1)Analyzer_analyzeClassToken( self, &tokenLink,scope,theElements);
					else if(hasMethod==1)Analyzer_analyzeMethodToken( self, &tokenLink);
					else if(hasMember==1)
					{
						memberIndex=CLStringObjectList_indexOfString(NULL,oneToken->text,theElements->memberNamesList);
						Analyzer_analyzeMemberToken( self, &tokenLink,memberIndex,theElements->memberTokensList);
					}
					else if(hasInstance==1)
					{
						instanceIndex=CLStringObjectList_indexOfString(NULL,oneToken->text,scope->instanceNamesList);
						Analyzer_analyzeInstanceToken( self, &tokenLink,instanceIndex,scope->instancesList);
					}
				}
				else isStructChain=0;
			}
			else if(oneToken->mainType==kTokenMainTypeSymbol)
			{
				if((oneToken->text->head)->character=='-')
				{
					if(tokenLink->next!=NULL)
					{
						nextToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
						if(nextToken->mainType==kTokenMainTypeSymbol&&(nextToken->text->head)->character=='>')
						{
							oneToken->subType=kTokenSubTypeStructAccessor;
							nextToken->subType=kTokenSubTypeStructAccessor;
							isStructChain=1;
							tokenLink=tokenLink->next;
						}
					}
				}
				else
				{
					if((oneToken->text->head)->character=='{')
					{
						oneScope=Scope_alloc( );
						Scope_init(oneScope );
						oneScope->type=scope->nextScopeType;
						if(scope->nextScopeLink!=NULL)
						{
							oneScope->_class->setScopeLink( (void*) oneScope->_components[0], scope->nextScopeLink);
							oneToken->mainType=kTokenMainTypeUndefined;
						}
						oneScope->instancesList->_class->addObjectsInObjectList( (void*) oneScope->instancesList->_components[0], scope->instancesList);
						oneScope->instanceNamesList->_class->addObjectsInObjectList( (void*) oneScope->instanceNamesList->_components[0], scope->instanceNamesList);
						CLObjectList_addObject(theScopeList, (cast_object( &CLObject_ClassInstance , oneScope)));
						scope=oneScope;
					}
					else if((oneToken->text->head)->character=='}')
					{
						if(scope->scopeLink!=NULL)oneToken->_class->setLinkId( (void*) oneToken->_components[0], scope->scopeLink);
						CLObjectList_removeObject(theScopeList, (cast_object( &CLObject_ClassInstance , scope)));
						Scope_release(scope );
						scopeData=theScopeList->_class->lastObject( (void*) theScopeList->_components[0] );
						scope=(cast_object( &Scope_ClassInstance , scopeData));
						scope->nextScopeType=kScopeTypeNormal;
						scope->_class->setNextScopeLink( (void*) scope->_components[0], NULL);
					}
					isStructChain=0;
				}
			}
		}
		tokenLink=tokenLink->next;
	}
}
void Analyzer_analyzeForEachToken (struct Analyzer* self, struct CLLink * * theLinkAddress , struct Scope * theScope , struct CLObjectList * theMemberNames , struct CLObjectList * theClassNames , struct CLObjectList * theMethodLines ) 
{
	char contains;
	char decimal[5];
	struct CLLink*tokenLink;
	struct CLLink*chainLink;
	struct Token*token;
	struct Token*oneToken;
	struct Token*dbleToken;
	struct Token*openToken;
	struct Token*typeToken;
	struct Token*starToken;
	struct Token*nameToken;
	struct Token*chainToken;
	struct CLString*classId;
	struct CLString*containerId;
	struct CLString*linkIdString;
	tokenLink=*theLinkAddress;
	token=(cast_object( &Token_ClassInstance , tokenLink->data));
	if(tokenLink->next!=NULL&&tokenLink->next->next!=NULL&&tokenLink->next->next->next!=NULL&&tokenLink->next->next->next->next!=NULL&&tokenLink->next->next->next->next->next!=NULL&&tokenLink->next->next->next->next->next->next!=NULL&&tokenLink->next->next->next->next->next->next->next!=NULL)
	{
		dbleToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->next->next->next->data));
		if((dbleToken->text->head)->character==':')
		{
			openToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
			typeToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->data));
			starToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->next->data));
			nameToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->next->next->data));
			chainToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->next->next->next->next->data));
			classId=CLString_alloc( );
			CLString_init(classId );
			containerId=CLString_alloc( );
			CLString_init(containerId );
			linkIdString=CLString_alloc( );
			CLString_initWithCString(linkIdString, "link");
			contains=CLStringObjectList_containsString(NULL,chainToken->text,theMemberNames);
			if(contains==1) CLString_appendCString(containerId, "self->");
			CLString_appendString(containerId, chainToken->text);
			contains=CLStringObjectList_containsString(NULL,typeToken->text,theClassNames);
			if(contains==1) CLString_appendCString(classId, "struct ");
			CLString_appendString(classId, typeToken->text);
			if(tokenLink->next->next->next->next->next->next->next!=NULL)
			{
				chainLink=tokenLink->next->next->next->next->next->next->next;
				while(chainLink!=NULL)
				{
					oneToken=(cast_object( &Token_ClassInstance , chainLink->data));
					if(oneToken->mainType==kTokenMainTypeWord)
					{
						CLString_appendString(containerId, oneToken->text);
						oneToken->mainType=kTokenMainTypeUndefined;
					}
					else if(oneToken->mainType==kTokenMainTypeSymbol&&(oneToken->text->head)->character=='.')
					{
						CLString_appendCString(containerId, "->");
						oneToken->mainType=kTokenMainTypeUndefined;
					}
					else
					{
						oneToken->mainType=kTokenMainTypeUndefined;
						break;
					}
					chainLink=chainLink->next;
				}
				*theLinkAddress=chainLink;
			}
			openToken->mainType=kTokenMainTypeUndefined;
			typeToken->mainType=kTokenMainTypeUndefined;
			starToken->mainType=kTokenMainTypeUndefined;
			nameToken->mainType=kTokenMainTypeUndefined;
			dbleToken->mainType=kTokenMainTypeUndefined;
			chainToken->mainType=kTokenMainTypeUndefined;
			sprintf(decimal,"%lu",self->constants->linkId++);
			CLString_appendCString(linkIdString, decimal);
			token->subType=kTokenSubTypeForEachCycle;
			token->_class->setLinkId( (void*) token->_components[0], linkIdString);
			token->_class->setClassId( (void*) token->_components[0], classId);
			token->_class->setVariableId( (void*) token->_components[0], nameToken->text);
			token->_class->setContainerId( (void*) token->_components[0], containerId);
			theScope->nextScopeType=kScopeTypeForEach;
			theScope->_class->setNextScopeLink( (void*) theScope->_components[0], linkIdString);
			Analyzer_addLinkStructAndVariable( self, nameToken->text,classId,linkIdString,theScope,theMethodLines);
			CLString_release(classId );
			CLString_release(containerId );
			CLString_release(linkIdString );
		}
	}
}
void Analyzer_addLinkStructAndVariable (struct Analyzer* self, struct CLString * theName , struct CLString * theClass , struct CLString * theLinkId , struct Scope * theScope , struct CLObjectList * theMethodLines ) 
{
	struct Token*linkToken;
	struct Token*variableToken;
	struct CLObjectList*linkLine;
	struct CLObjectList*variableLine;
	if(CLStringObjectList_containsString(NULL,theName,theScope->forEachList)==0)
	{
		variableLine=CLObjectList_alloc( );
		CLObjectList_init(variableLine );
		variableToken=Token_alloc( );
		variableToken->_class->init( (void*) variableToken->_components[0] );
		variableToken->mainType=kTokenMainTypeWord;
		variableToken->mainType=kTokenSubTypeUndefined;
		variableToken->_class->setText( (void*) variableToken->_components[0], theClass);
		variableToken->text->_class->appendCString( (void*) variableToken->text->_components[0], "* ");
		variableToken->text->_class->appendString( (void*) variableToken->text->_components[0], theName);
		variableToken->text->_class->appendCString( (void*) variableToken->text->_components[0], ";");
		CLObjectList_addObject(variableLine, (cast_object( &CLObject_ClassInstance , variableToken)));
		CLObjectList_addObjectAtIndex(theMethodLines, (cast_object( &CLObject_ClassInstance , variableLine)),1);
		CLStringObjectList_addStringAsUnique(NULL,theName,theScope->forEachList);
		CLObjectList_release(variableLine );
		Token_release(variableToken );
	}
	linkLine=CLObjectList_alloc( );
	CLObjectList_init(linkLine );
	linkToken=Token_alloc( );
	linkToken->_class->init( (void*) linkToken->_components[0] );
	linkToken->mainType=kTokenMainTypeWord;
	linkToken->mainType=kTokenSubTypeUndefined;
	linkToken->text->_class->appendString( (void*) linkToken->text->_components[0], self->constants->linkString);
	linkToken->text->_class->appendString( (void*) linkToken->text->_components[0], theLinkId);
	linkToken->text->_class->appendCString( (void*) linkToken->text->_components[0], ";");
	CLObjectList_addObject(linkLine, (cast_object( &CLObject_ClassInstance , linkToken)));
	CLObjectList_addObjectAtIndex(theMethodLines, (cast_object( &CLObject_ClassInstance , linkLine)),1);
	CLObjectList_release(linkLine );
	Token_release(linkToken );
}
void Analyzer_analyzeAllocToken (struct Analyzer* self, struct Token * theToken , struct CLObjectList * theLine ) 
{
	if(theToken->classId==NULL)
	{
		printf("\nWARNING : missing includes for : ");
		theLine->_class->describe( (void*) theLine->_components[0] );
	}
}
void Analyzer_analyzeClassToken (struct Analyzer* self, struct CLLink * * theLinkAddress , struct Scope * theScope , struct ClassElements * theElements ) 
{
	char isUnused;
	unsigned long unusedIndex;
	struct CLLink*tokenLink;
	struct Token*token;
	struct Token*nextToken;
	struct Token*wordToken;
	struct Token*nullToken;
	struct Token*openToken;
	tokenLink=*theLinkAddress;
	token=(cast_object( &Token_ClassInstance , tokenLink->data));
	token->_class->setClassId( (void*) token->_components[0], token->text);
	token->subType=kTokenSubTypeClass;
	isUnused=CLStringObjectList_containsString(NULL,token->text,theElements->unusedClassNamesList);
	if(isUnused==1)
	{
		unusedIndex=CLStringObjectList_indexOfString(NULL,token->text,theElements->unusedClassNamesList);
		theElements->unusedClassNamesList->_class->removeObjectAtIndex( (void*) theElements->unusedClassNamesList->_components[0], unusedIndex);
	}
	if(tokenLink->next!=NULL&&tokenLink->next->next!=NULL)
	{
		nextToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
		wordToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->data));
		if((nextToken->text->head)->character==':'&&wordToken->mainType==kTokenMainTypeWord)
		{
			token->subType=kTokenSubTypeExplicitCallClass;
			nextToken->subType=kTokenSubTypeExplicitAccessor;
			wordToken->subType=kTokenSubTypeMethod;
			*theLinkAddress=tokenLink->next->next;
			if(wordToken->text->_class->equals( (void*) wordToken->text->_components[0], self->constants->allocString)==0)
			{
				wordToken->subType=kTokenSubTypeExplicitClassCall;
				wordToken->_class->setClassId( (void*) wordToken->_components[0], token->text);
				if(tokenLink->next->next->next!=NULL)
				{
					openToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->next->data));
					openToken->mainType=kTokenMainTypeUndefined;
					*theLinkAddress=tokenLink->next->next->next;
					if(tokenLink->next->next->next->next!=NULL)
					{
						nullToken=(cast_object( &Token_ClassInstance , tokenLink->next->next->next->next->data));
						if(nullToken->text->_class->equals( (void*) nullToken->text->_components[0], self->constants->nullString)==1)
						{
							wordToken->subType=kTokenSubTypeMethod;
							openToken->mainType=kTokenMainTypeSymbol;
							*theLinkAddress=tokenLink->next->next->next->next;
						}
					}
				}
			}
		}
		else if((nextToken->text->head)->character=='*'&&wordToken->mainType==kTokenMainTypeWord)
		{
			wordToken->_class->setClassId( (void*) wordToken->_components[0], token->text);
			wordToken->subType=kTokenSubTypeInstance;
			theScope->instancesList->_class->addObject( (void*) theScope->instancesList->_components[0], (cast_object( &CLObject_ClassInstance , wordToken)));
			theScope->instanceNamesList->_class->addObject( (void*) theScope->instanceNamesList->_components[0], (cast_object( &CLObject_ClassInstance , wordToken->text)));
			*theLinkAddress=tokenLink->next->next;
		}
		else if((nextToken->text->head)->character=='*'&&(wordToken->text->head)->character==')')
		{
			token->subType=kTokenSubTypeCast;
			nextToken->mainType=kTokenMainTypeUndefined;
			wordToken->mainType=kTokenMainTypeUndefined;
			*theLinkAddress=tokenLink->next->next;
		}
	}
}
void Analyzer_analyzeMethodToken (struct Analyzer* self, struct CLLink * * theLinkAddress ) 
{
	struct CLLink*tokenLink;
	struct Token*token;
	struct Token*nextToken;
	tokenLink=*theLinkAddress;
	token=(cast_object( &Token_ClassInstance , tokenLink->data));
	token->subType=kTokenSubTypeLocalCall;
	if(tokenLink->next!=NULL)
	{
		nextToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
		if(nextToken->mainType==kTokenMainTypeSymbol&&(nextToken->text->head)->character=='(')
		{
			nextToken->mainType=kTokenMainTypeUndefined;
		}
		else token->subType=kTokenSubTypeLocalCallReference;
	}
	else token->subType=kTokenSubTypeLocalCallReference;
}
void Analyzer_analyzeMemberToken (struct Analyzer* self, struct CLLink * * theLinkAddress , long theMemberIndex , struct CLObjectList * theMembers ) 
{
	struct CLLink*link19;
	struct CLObject* object;
	struct CLLink*tokenLink;
	struct Token*token;
	struct Token*oneToken;
	struct CLObject*lineObject;
	struct CLObjectList*lineList;
	tokenLink=*theLinkAddress;
	token=(cast_object( &Token_ClassInstance , tokenLink->data));
	token->isMember=1;
	token->subType=kTokenSubTypeVariable;
	lineObject=theMembers->_class->objectAtIndex( (void*) theMembers->_components[0], theMemberIndex);
	lineList=(cast_object( &CLObjectList_ClassInstance , lineObject));
	link19=lineList->head;while( link19!=NULL){object=link19->data; 
	
		oneToken=(cast_object( &Token_ClassInstance , object));
		if(oneToken->text->_class->equals( (void*) oneToken->text->_components[0], token->text)==1&&oneToken->subType==kTokenSubTypeInstance)
		{
			token->_class->setClassId( (void*) token->_components[0], oneToken->classId);
			token->subType=kTokenSubTypeInstance;
		}
	link19=link19->next;}
	Analyzer_analyzeInstanceList( self, theLinkAddress);
}
void Analyzer_analyzeInstanceToken (struct Analyzer* self, struct CLLink * * theLinkAddress , long theInstanceIndex , struct CLObjectList * theInstancesList ) 
{
	struct CLLink*tokenLink;
	struct Token*token;
	struct Token*instanceToken;
	struct CLObject*instanceObject;
	tokenLink=*theLinkAddress;
	token=(cast_object( &Token_ClassInstance , tokenLink->data));
	instanceObject=theInstancesList->_class->objectAtIndex( (void*) theInstancesList->_components[0], theInstanceIndex);
	instanceToken=(cast_object( &Token_ClassInstance , instanceObject));
	token->subType=kTokenSubTypeInstance;
	token->_class->setClassId( (void*) token->_components[0], instanceToken->classId);
	Analyzer_analyzeInstanceList( self, theLinkAddress);
}
void Analyzer_analyzeInstanceList (struct Analyzer* self, struct CLLink * * theLinkAddress ) 
{
	char isImplicit;
	struct CLLink*tokenLink;
	struct Token*theToken;
	struct Token*oneToken;
	struct Token*nextToken;
	struct Token*startToken;
	struct CLString*instanceChain;
	tokenLink=*theLinkAddress;
	theToken=(cast_object( &Token_ClassInstance , tokenLink->data));
	startToken=theToken;
	if(theToken->subType==kTokenSubTypeInstance)
	{
		isImplicit=0;
		instanceChain=CLString_alloc( );
		CLString_init(instanceChain );
		if(theToken->isMember==1) CLString_appendCString(instanceChain, "self->");
		CLString_appendString(instanceChain, theToken->text);
		tokenLink=tokenLink->next;
		while(tokenLink!=NULL)
		{
			oneToken=(cast_object( &Token_ClassInstance , tokenLink->data));
			if(oneToken->mainType==kTokenMainTypeSymbol&&(oneToken->text->head)->character==':')
			{
				oneToken->subType=kTokenSubTypeExplicitAccessor;
				oneToken->mainType=kTokenMainTypeUndefined;
				isImplicit=0;
				startToken->mainType=kTokenMainTypeUndefined;
			}
			else if(oneToken->mainType==kTokenMainTypeSymbol&&(oneToken->text->head)->character=='.')
			{
				oneToken->subType=kTokenSubTypeImplicitAccessor;
				isImplicit=1;
				CLString_appendCString(instanceChain, "->");
			}
			else if(oneToken->mainType==kTokenMainTypeWord)
			{
				oneToken->subType=kTokenSubTypeUndefined;
				if(tokenLink->next!=NULL)
				{
					nextToken=(cast_object( &Token_ClassInstance , tokenLink->next->data));
					if(nextToken->mainType==kTokenMainTypeSymbol&&(nextToken->text->head)->character=='(')
					{
						nextToken->mainType=kTokenMainTypeUndefined;
						if(isImplicit==1)oneToken->subType=kTokenSubTypeImplicitCall;
						else
						{
							oneToken->subType=kTokenSubTypeExplicitCall;
							if(self->constants->allocString->_class->equals( (void*) self->constants->allocString->_components[0], oneToken->text))oneToken->subType=kTokenSubTypeExplicitAllocCall;
						}
					}
				}
				if(oneToken->subType==kTokenSubTypeUndefined) CLString_appendString(instanceChain, oneToken->text);
				else
				{
					oneToken->_class->setInstanceList( (void*) oneToken->_components[0], instanceChain);
					oneToken->_class->setClassId( (void*) oneToken->_components[0], startToken->classId);
				}
			}
			else break;
			tokenLink=tokenLink->next;
		}
		*theLinkAddress=tokenLink;
		CLString_release(instanceChain );
	}
}
void Analyzer_init (struct Analyzer* self ) 
{
	self->retainCount=1;
}
void Analyzer_destruct (struct Analyzer* self ) 
{

}
void Analyzer_retain (struct Analyzer* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Analyzer_release (struct Analyzer* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Analyzer_describe (struct Analyzer* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void Tokenizer_CreateClass( )
{
	Tokenizer_ClassInstance=malloc(sizeof(struct Tokenizer_Class));
	Tokenizer_ClassInstance->className="Tokenizer";
	Tokenizer_ClassInstance->classId=&Tokenizer_ClassInstance;
	Tokenizer_ClassInstance->createLines=Tokenizer_createLines;
	Tokenizer_ClassInstance->resetActualLine=Tokenizer_resetActualLine;
	Tokenizer_ClassInstance->createTokens=Tokenizer_createTokens;
	Tokenizer_ClassInstance->resetActualToken=Tokenizer_resetActualToken;
	Tokenizer_ClassInstance->className_CLObject="CLObject";
	Tokenizer_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Tokenizer_ClassInstance->init=Tokenizer_init;
	Tokenizer_ClassInstance->destruct=Tokenizer_destruct;
	Tokenizer_ClassInstance->retain=Tokenizer_retain;
	Tokenizer_ClassInstance->release=Tokenizer_release;
	Tokenizer_ClassInstance->describe=Tokenizer_describe;
	
}
struct Tokenizer* Tokenizer_alloc( )
{
	struct Tokenizer* result;
	if(Tokenizer_ClassInstance==NULL)Tokenizer_CreateClass( );
	result=malloc(sizeof(struct Tokenizer));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Tokenizer_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Tokenizer_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Tokenizer_createLines (struct Tokenizer* self, struct CLString * theString , struct CLObjectList * theLines ) 
{
	char inChar;
	char inChars;
	char inClass;
	char inEscape;
	struct CLChar*actualChar;
	struct Line*actualLine;
	struct Line**actualLinePointer;
	actualLine=Line_alloc( );
	Line_init(actualLine );
	actualLine->type=kLineTypeGeneral;
	actualLinePointer=&actualLine;
	inChar=0;
	inChars=0;
	inClass=0;
	inEscape=0;
	actualChar=theString->head;
	while(actualChar!=NULL)
	{
		if(actualLine->type==kLineTypeSetting||actualLine->type==kLineTypeComment)
		{
			if(actualChar->character=='\n'||actualChar->character=='\r')
			{
				Tokenizer_resetActualLine( self, actualLinePointer,theLines);
				actualLine=*actualLinePointer;
			}
			else actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
		}
		else if(actualLine->type==kLineTypeGeneral)
		{
			if(inChars==1||inChar==1)
			{
				if(inEscape==0)
				{
					if(actualChar->character=='\\')inEscape=1;
					if(inChar==1&&actualChar->character=='\'')inChar=0;
					if(inChars==1&&actualChar->character=='"')inChars=0;
				}
				else inEscape=0;
				actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
			}
			else
			{
				if(actualChar->character=='#')
				{
					if(actualLine->text->length==0)actualLine->type=kLineTypeSetting;
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
				}
				else if(actualChar->character=='/')
				{
					if(actualLine->text->length==0)actualLine->type=kLineTypeComment;
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
				}
				else if(actualChar->character==';')
				{
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
					Tokenizer_resetActualLine( self, actualLinePointer,theLines);
					actualLine=*actualLinePointer;
				}
				else if(actualChar->character=='{')
				{
					if(inClass==0)
					{
						actualLine->type=kLineTypeClassDef;
						inClass=1;
					}
					Tokenizer_resetActualLine( self, actualLinePointer,theLines);
					actualLine->type=kLineTypeBlockStart;
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
					Tokenizer_resetActualLine( self, actualLinePointer,theLines);
					actualLine=*actualLinePointer;
				}
				else if(actualChar->character=='}')
				{
					Tokenizer_resetActualLine( self, actualLinePointer,theLines);
					actualLine->type=kLineTypeBlockEnd;
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
					Tokenizer_resetActualLine( self, actualLinePointer,theLines);
					actualLine=*actualLinePointer;
				}
				else if(actualChar->character=='\''||actualChar->character=='"')
				{
					if(actualChar->character=='\'')inChar=1;
					if(actualChar->character=='"')inChars=1;
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
				}
				else if(actualChar->character==' '||actualChar->character=='\t')
				{
					if(actualLine->text->length>0)actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
				}
				else if(actualChar->character!='\r'&&actualChar->character!='\n')
				{
					actualLine->text->_class->appendCharacter( (void*) actualLine->text->_components[0], actualChar->character);
				}
			}
		}
		actualChar=actualChar->next;
	}
	Tokenizer_resetActualLine( self, actualLinePointer,theLines);
	actualLine=*actualLinePointer;
	Line_release(actualLine );
}
void Tokenizer_resetActualLine (struct Tokenizer* self, struct Line * * theLinePointer , struct CLObjectList * theLines ) 
{
	struct Line*actualLine;
	actualLine=*theLinePointer;
	if(actualLine->text->length>0)
	{
		Tokenizer_createTokens( self, actualLine->text,actualLine->tokens);
		theLines->_class->addObject( (void*) theLines->_components[0], (cast_object( &CLObject_ClassInstance , actualLine)));
		actualLine->_class->release( (void*) actualLine->_components[0] );
		*theLinePointer=Line_alloc();
		actualLine=*theLinePointer;
		Line_init(actualLine );
		actualLine->type=kLineTypeGeneral;
	}
}
void Tokenizer_createTokens (struct Tokenizer* self, struct CLString * theString , struct CLObjectList * theTokens ) 
{
	char inChar;
	char inChars;
	char inEscape;
	struct CLChar*actualChar;
	struct Token*actualToken;
	struct Token**actualTokenPointer;
	actualToken=Token_alloc( );
	Token_init(actualToken );
	actualToken->mainType=kTokenMainTypeWord;
	actualTokenPointer=&actualToken;
	inChar=0;
	inChars=0;
	inEscape=0;
	actualChar=theString->head;
	while(actualChar!=NULL)
	{
		if(inChars==1||inChar==1)
		{
			if(inEscape==0)
			{
				if(actualChar->character=='\\')inEscape=1;
				if(inChar==1&&actualChar->character=='\'')
				{
					inChar=0;
					Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
					actualToken=*actualTokenPointer;
					actualToken->mainType=kTokenMainTypeSymbol;
				}
				if(inChars==1&&actualChar->character=='"')
				{
					inChars=0;
					Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
					actualToken=*actualTokenPointer;
					actualToken->mainType=kTokenMainTypeSymbol;
				}
			}
			else inEscape=0;
			actualToken->text->_class->appendCharacter( (void*) actualToken->text->_components[0], actualChar->character);
		}
		else
		{
			if(actualChar->character=='\''||actualChar->character=='"')
			{
				if(actualChar->character=='\'')inChar=1;
				if(actualChar->character=='"')inChars=1;
				actualToken->mainType=kTokenMainTypeSymbol;
				actualToken->text->_class->appendCharacter( (void*) actualToken->text->_components[0], actualChar->character);
				Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
				actualToken=*actualTokenPointer;
				actualToken->mainType=kTokenMainTypeString;
			}
			else if(actualChar->character==' '||actualChar->character=='\t'||actualChar->character=='\n'||actualChar->character=='\r')
			{
				Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
				actualToken=*actualTokenPointer;
			}
			else if(actualChar->character=='*'||actualChar->character=='/'||actualChar->character=='+'||actualChar->character=='-'||actualChar->character=='='||actualChar->character=='|'||actualChar->character=='&'||actualChar->character=='.'||actualChar->character==','||actualChar->character==':'||actualChar->character==';'||actualChar->character=='<'||actualChar->character=='>'||actualChar->character=='{'||actualChar->character=='}'||actualChar->character=='['||actualChar->character==']'||actualChar->character=='('||actualChar->character==')'||actualChar->character=='^'||actualChar->character=='!'||actualChar->character=='#'||actualChar->character=='?'||actualChar->character=='%')
			{
				Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
				actualToken=*actualTokenPointer;
				actualToken->mainType=kTokenMainTypeSymbol;
				actualToken->text->_class->appendCharacter( (void*) actualToken->text->_components[0], actualChar->character);
				Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
				actualToken=*actualTokenPointer;
			}
			else
			{
				actualToken->mainType=kTokenMainTypeWord;
				actualToken->text->_class->appendCharacter( (void*) actualToken->text->_components[0], actualChar->character);
			}
		}
		actualChar=actualChar->next;
	}
	Tokenizer_resetActualToken( self, actualTokenPointer,theTokens);
	actualToken=*actualTokenPointer;
	Token_release(actualToken );
}
void Tokenizer_resetActualToken (struct Tokenizer* self, struct Token * * theTokenPointer , struct CLObjectList * theTokens ) 
{
	struct Token*actualToken;
	actualToken=*theTokenPointer;
	if(actualToken->text->length>0)
	{
		theTokens->_class->addObject( (void*) theTokens->_components[0], (cast_object( &CLObject_ClassInstance , actualToken)));
		actualToken->_class->release( (void*) actualToken->_components[0] );
		*theTokenPointer=Token_alloc();
		actualToken=*theTokenPointer;
		Token_init(actualToken );
		actualToken->mainType=kTokenMainTypeWord;
	}
}
void Tokenizer_init (struct Tokenizer* self ) 
{
	self->retainCount=1;
}
void Tokenizer_destruct (struct Tokenizer* self ) 
{

}
void Tokenizer_retain (struct Tokenizer* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Tokenizer_release (struct Tokenizer* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Tokenizer_describe (struct Tokenizer* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void Constants_CreateClass( )
{
	Constants_ClassInstance=malloc(sizeof(struct Constants_Class));
	Constants_ClassInstance->className="Constants";
	Constants_ClassInstance->classId=&Constants_ClassInstance;
	Constants_ClassInstance->init=Constants_init;
	Constants_ClassInstance->destruct=Constants_destruct;
	Constants_ClassInstance->className_CLObject="CLObject";
	Constants_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Constants_ClassInstance->init_CLObject=Constants_init;
	Constants_ClassInstance->destruct_CLObject=Constants_destruct;
	Constants_ClassInstance->retain=Constants_retain;
	Constants_ClassInstance->release=Constants_release;
	Constants_ClassInstance->describe=Constants_describe;
	
}
struct Constants* Constants_alloc( )
{
	struct Constants* result;
	if(Constants_ClassInstance==NULL)Constants_CreateClass( );
	result=malloc(sizeof(struct Constants));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Constants_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Constants_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Constants_init (struct Constants* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->linkId=0;
	self->clcString=CLString_alloc( );
	CLString_initWithCString(self->clcString, "clc");
	self->forString=CLString_alloc( );
	CLString_initWithCString(self->forString, "for");
	self->selfString=CLString_alloc( );
	CLString_initWithCString(self->selfString, "self");
	self->nullString=CLString_alloc( );
	CLString_initWithCString(self->nullString, "NULL");
	self->linkString=CLString_alloc( );
	CLString_initWithCString(self->linkString, "struct CLLink*");
	self->ifdefString=CLString_alloc( );
	CLString_initWithCString(self->ifdefString, "#if");
	self->endifString=CLString_alloc( );
	CLString_initWithCString(self->endifString, "#endif");
	self->classString=CLString_alloc( );
	CLString_initWithCString(self->classString, ".clc");
	self->allocString=CLString_alloc( );
	CLString_initWithCString(self->allocString, "alloc");
	self->settingString=CLString_alloc( );
	CLString_initWithCString(self->settingString, "_setting");
}
void Constants_destruct (struct Constants* self ) 
{
	CLString_release(self->clcString );
	CLString_release(self->forString );
	CLString_release(self->selfString );
	CLString_release(self->nullString );
	CLString_release(self->linkString );
	CLString_release(self->ifdefString );
	CLString_release(self->endifString );
	CLString_release(self->classString );
	CLString_release(self->allocString );
	CLString_release(self->settingString );
}
void Constants_retain (struct Constants* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Constants_release (struct Constants* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Constants_describe (struct Constants* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
void FileElements_CreateClass( )
{
	FileElements_ClassInstance=malloc(sizeof(struct FileElements_Class));
	FileElements_ClassInstance->className="FileElements";
	FileElements_ClassInstance->classId=&FileElements_ClassInstance;
	FileElements_ClassInstance->init=FileElements_init;
	FileElements_ClassInstance->destruct=FileElements_destruct;
	FileElements_ClassInstance->describe=FileElements_describe;
	FileElements_ClassInstance->className_CLObject="CLObject";
	FileElements_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	FileElements_ClassInstance->init_CLObject=FileElements_init;
	FileElements_ClassInstance->destruct_CLObject=FileElements_destruct;
	FileElements_ClassInstance->retain=FileElements_retain;
	FileElements_ClassInstance->release=FileElements_release;
	FileElements_ClassInstance->describe_CLObject=FileElements_describe;
	
}
struct FileElements* FileElements_alloc( )
{
	struct FileElements* result;
	if(FileElements_ClassInstance==NULL)FileElements_CreateClass( );
	result=malloc(sizeof(struct FileElements));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(FileElements_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(FileElements_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void FileElements_init (struct FileElements* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->classesList=CLObjectList_alloc( );
	self->settingsList=CLObjectList_alloc( );
	self->settingNamesList=CLObjectList_alloc( );
	self->functionsList=CLObjectList_alloc( );
	self->functionHeadersList=CLObjectList_alloc( );
	self->structuresList=CLObjectList_alloc( );
	self->structureHeadersList=CLObjectList_alloc( );
	CLObjectList_init(self->classesList );
	CLObjectList_init(self->settingsList );
	CLObjectList_init(self->settingNamesList );
	CLObjectList_init(self->functionsList );
	CLObjectList_init(self->functionHeadersList );
	CLObjectList_init(self->structuresList );
	CLObjectList_init(self->structureHeadersList );
}
void FileElements_destruct (struct FileElements* self ) 
{
	CLObjectList_release(self->classesList );
	CLObjectList_release(self->settingsList );
	CLObjectList_release(self->settingNamesList );
	CLObjectList_release(self->functionsList );
	CLObjectList_release(self->functionHeadersList );
	CLObjectList_release(self->structuresList );
	CLObjectList_release(self->structureHeadersList );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void FileElements_describe (struct FileElements* self ) 
{
	printf("\nCLASSES : ");
	self->classesList->_class->describe( (void*) self->classesList->_components[0] );
	printf("\nSETTING NAMES : ");
	self->settingNamesList->_class->describe( (void*) self->settingNamesList->_components[0] );
	printf("\nSTRUCTURE HEADERS : ");
	self->structureHeadersList->_class->describe( (void*) self->structureHeadersList->_components[0] );
	printf("\nFUNCTION HEADERS : ");
	self->functionHeadersList->_class->describe( (void*) self->functionHeadersList->_components[0] );
	printf("\nSTRUCTRUES : ");
	self->structuresList->_class->describe( (void*) self->structuresList->_components[0] );
	printf("\nFUNCTIONS : ");
	self->functionsList->_class->describe( (void*) self->functionsList->_components[0] );
}
void FileElements_retain (struct FileElements* self ) 
{
	self->retainCount=self->retainCount+1;
}
void FileElements_release (struct FileElements* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void ClassElements_CreateClass( )
{
	ClassElements_ClassInstance=malloc(sizeof(struct ClassElements_Class));
	ClassElements_ClassInstance->className="ClassElements";
	ClassElements_ClassInstance->classId=&ClassElements_ClassInstance;
	ClassElements_ClassInstance->init=ClassElements_init;
	ClassElements_ClassInstance->destruct=ClassElements_destruct;
	ClassElements_ClassInstance->describe=ClassElements_describe;
	ClassElements_ClassInstance->className_CLObject="CLObject";
	ClassElements_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	ClassElements_ClassInstance->init_CLObject=ClassElements_init;
	ClassElements_ClassInstance->destruct_CLObject=ClassElements_destruct;
	ClassElements_ClassInstance->retain=ClassElements_retain;
	ClassElements_ClassInstance->release=ClassElements_release;
	ClassElements_ClassInstance->describe_CLObject=ClassElements_describe;
	
}
struct ClassElements* ClassElements_alloc( )
{
	struct ClassElements* result;
	if(ClassElements_ClassInstance==NULL)ClassElements_CreateClass( );
	result=malloc(sizeof(struct ClassElements));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(ClassElements_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(ClassElements_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void ClassElements_init (struct ClassElements* self, struct CLString * theName ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->className=theName;
	CLString_retain(self->className );
	self->memberNamesList=CLObjectList_alloc( );
	self->methodNamesList=CLObjectList_alloc( );
	self->settingNamesList=CLObjectList_alloc( );
	self->memberTokensList=CLObjectList_alloc( );
	self->methodTokensList=CLObjectList_alloc( );
	self->settingTokensList=CLObjectList_alloc( );
	self->usedClassNamesList=CLObjectList_alloc( );
	self->unusedClassNamesList=CLObjectList_alloc( );
	CLObjectList_init(self->memberNamesList );
	CLObjectList_init(self->methodNamesList );
	CLObjectList_init(self->settingNamesList );
	CLObjectList_init(self->memberTokensList );
	CLObjectList_init(self->methodTokensList );
	CLObjectList_init(self->settingTokensList );
	CLObjectList_init(self->usedClassNamesList );
	CLObjectList_init(self->unusedClassNamesList );
}
void ClassElements_destruct (struct ClassElements* self ) 
{
	self->className->_class->release( (void*) self->className->_components[0] );
	CLObjectList_release(self->memberNamesList );
	CLObjectList_release(self->methodNamesList );
	CLObjectList_release(self->settingNamesList );
	CLObjectList_release(self->memberTokensList );
	CLObjectList_release(self->methodTokensList );
	CLObjectList_release(self->settingTokensList );
	CLObjectList_release(self->usedClassNamesList );
	CLObjectList_release(self->unusedClassNamesList );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void ClassElements_describe (struct ClassElements* self ) 
{
	struct CLLink*ids;
	struct CLLink*line;
	struct CLLink*names;
	struct CLLink*members;
	struct CLLink*methods;
	struct CLLink*settings;
	struct CLString*name;
	struct CLObjectList*lines;
	printf("\nClassName :");
	self->className->_class->describe( (void*) self->className->_components[0] );
	printf("\nusedClassMames :");
	self->usedClassNamesList->_class->describe( (void*) self->usedClassNamesList->_components[0] );
	printf("\nunusedClassMames :");
	self->unusedClassNamesList->_class->describe( (void*) self->unusedClassNamesList->_components[0] );
	printf("\n\nSettings :\n\n");
	settings=self->settingTokensList->head;
	while(settings!=NULL)
	{
		struct CLObjectList*chain=(cast_object( &CLObjectList_ClassInstance , settings->data));
		chain->_class->describe( (void*) chain->_components[0] );
		printf("\n");
		settings=settings->next;
	}
	printf("\nMembers :\n\n");
	names=self->memberNamesList->head;
	members=self->memberTokensList->head;
	while(names!=NULL)
	{
		name=(cast_object( &CLString_ClassInstance , names->data));
		lines=(cast_object( &CLObjectList_ClassInstance , members->data));
		name->_class->describe( (void*) name->_components[0] );
		printf(" : ");
		lines->_class->describe( (void*) lines->_components[0] );
		printf("\n");
		names=names->next;
		members=members->next;
	}
	printf("\nMethods : \n");
	ids=self->methodNamesList->head;
	methods=self->methodTokensList->head;
	while(ids!=NULL)
	{
		name=(cast_object( &CLString_ClassInstance , ids->data));
		lines=(cast_object( &CLObjectList_ClassInstance , methods->data));
		printf("\nMETHOD ");
		name->_class->describe( (void*) name->_components[0] );
		printf(":\n");
		line=lines->head;
		while(line!=NULL)
		{
			struct CLObjectList*lineList=(cast_object( &CLObjectList_ClassInstance , line->data));
			lineList->_class->describe( (void*) lineList->_components[0] );
			printf("\n");
			line=line->next;
		}
		printf("\n");
		ids=ids->next;
		methods=methods->next;
	}
}
void ClassElements_retain (struct ClassElements* self ) 
{
	self->retainCount=self->retainCount+1;
}
void ClassElements_release (struct ClassElements* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Token_CreateClass( )
{
	Token_ClassInstance=malloc(sizeof(struct Token_Class));
	Token_ClassInstance->className="Token";
	Token_ClassInstance->classId=&Token_ClassInstance;
	Token_ClassInstance->init=Token_init;
	Token_ClassInstance->destruct=Token_destruct;
	Token_ClassInstance->setText=Token_setText;
	Token_ClassInstance->setLinkId=Token_setLinkId;
	Token_ClassInstance->setClassId=Token_setClassId;
	Token_ClassInstance->setVariableId=Token_setVariableId;
	Token_ClassInstance->setContainerId=Token_setContainerId;
	Token_ClassInstance->setInstanceList=Token_setInstanceList;
	Token_ClassInstance->describe=Token_describe;
	Token_ClassInstance->className_CLObject="CLObject";
	Token_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Token_ClassInstance->init_CLObject=Token_init;
	Token_ClassInstance->destruct_CLObject=Token_destruct;
	Token_ClassInstance->retain=Token_retain;
	Token_ClassInstance->release=Token_release;
	Token_ClassInstance->describe_CLObject=Token_describe;
	
}
struct Token* Token_alloc( )
{
	struct Token* result;
	if(Token_ClassInstance==NULL)Token_CreateClass( );
	result=malloc(sizeof(struct Token));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Token_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Token_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Token_init (struct Token* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->linkId=NULL;
	self->classId=NULL;
	self->variableId=NULL;
	self->containerId=NULL;
	self->instanceList=NULL;
	self->mainType=kTokenMainTypeUndefined;
	self->subType=kTokenSubTypeUndefined;
	self->isMember=0;
	self->text=CLString_alloc( );
	CLString_init(self->text );
}
void Token_destruct (struct Token* self ) 
{
	CLString_release(self->text );
	if(self->linkId!=NULL) CLString_release(self->linkId );
	if(self->classId!=NULL) CLString_release(self->classId );
	if(self->variableId!=NULL) CLString_release(self->variableId );
	if(self->containerId!=NULL) CLString_release(self->containerId );
	if(self->instanceList!=NULL) CLString_release(self->instanceList );
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
}
void Token_setText (struct Token* self, struct CLString * theText ) 
{
	if(self->text!=NULL)self->text->_class->release( (void*) self->text->_components[0] );
	self->text=theText;
	if(self->text!=NULL)self->text->_class->retain( (void*) self->text->_components[0] );
}
void Token_setLinkId (struct Token* self, struct CLString * theLinkId ) 
{
	if(self->linkId!=NULL)self->linkId->_class->release( (void*) self->linkId->_components[0] );
	self->linkId=theLinkId;
	if(self->linkId!=NULL)self->linkId->_class->retain( (void*) self->linkId->_components[0] );
}
void Token_setClassId (struct Token* self, struct CLString * theClassId ) 
{
	if(self->classId!=NULL)self->classId->_class->release( (void*) self->classId->_components[0] );
	self->classId=theClassId;
	if(self->classId!=NULL)self->classId->_class->retain( (void*) self->classId->_components[0] );
}
void Token_setVariableId (struct Token* self, struct CLString * theVariableId ) 
{
	if(self->variableId!=NULL)self->variableId->_class->release( (void*) self->variableId->_components[0] );
	self->variableId=theVariableId;
	if(self->variableId!=NULL)self->variableId->_class->retain( (void*) self->variableId->_components[0] );
}
void Token_setContainerId (struct Token* self, struct CLString * theContainerId ) 
{
	if(self->containerId!=NULL)self->containerId->_class->release( (void*) self->containerId->_components[0] );
	self->containerId=theContainerId;
	if(self->containerId!=NULL)self->containerId->_class->retain( (void*) self->containerId->_components[0] );
}
void Token_setInstanceList (struct Token* self, struct CLString * theList ) 
{
	if(self->instanceList!=NULL)self->instanceList->_class->release( (void*) self->instanceList->_components[0] );
	self->instanceList=theList;
	if(self->instanceList!=NULL)self->instanceList->_class->retain( (void*) self->instanceList->_components[0] );
}
void Token_describe (struct Token* self ) 
{
	if(self->text!=NULL)self->text->_class->describe( (void*) self->text->_components[0] );
	printf("|");
	printf("%i",self->mainType);
	printf("%i",self->subType);
	if(self->isMember==1)printf("M");
	if(self->classId!=NULL)self->classId->_class->describe( (void*) self->classId->_components[0] );
	if(self->variableId!=NULL)self->variableId->_class->describe( (void*) self->variableId->_components[0] );
	if(self->linkId!=NULL)self->linkId->_class->describe( (void*) self->linkId->_components[0] );
	if(self->containerId!=NULL)self->containerId->_class->describe( (void*) self->containerId->_components[0] );
	printf("|");
}
void Token_retain (struct Token* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Token_release (struct Token* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Line_CreateClass( )
{
	Line_ClassInstance=malloc(sizeof(struct Line_Class));
	Line_ClassInstance->className="Line";
	Line_ClassInstance->classId=&Line_ClassInstance;
	Line_ClassInstance->init=Line_init;
	Line_ClassInstance->destruct=Line_destruct;
	Line_ClassInstance->describe=Line_describe;
	Line_ClassInstance->className_CLObject="CLObject";
	Line_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Line_ClassInstance->init_CLObject=Line_init;
	Line_ClassInstance->destruct_CLObject=Line_destruct;
	Line_ClassInstance->retain=Line_retain;
	Line_ClassInstance->release=Line_release;
	Line_ClassInstance->describe_CLObject=Line_describe;
	
}
struct Line* Line_alloc( )
{
	struct Line* result;
	if(Line_ClassInstance==NULL)Line_CreateClass( );
	result=malloc(sizeof(struct Line));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Line_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Line_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Line_init (struct Line* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->type=0;
	self->text=CLString_alloc( );
	self->tokens=CLObjectList_alloc( );
	CLString_init(self->text );
	CLObjectList_init(self->tokens );
}
void Line_destruct (struct Line* self ) 
{
	CLString_release(self->text );
	CLObjectList_release(self->tokens );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void Line_describe (struct Line* self ) 
{
	self->text->_class->describe( (void*) self->text->_components[0] );
	printf("(%i)\n",self->type);
}
void Line_retain (struct Line* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Line_release (struct Line* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Scope_CreateClass( )
{
	Scope_ClassInstance=malloc(sizeof(struct Scope_Class));
	Scope_ClassInstance->className="Scope";
	Scope_ClassInstance->classId=&Scope_ClassInstance;
	Scope_ClassInstance->init=Scope_init;
	Scope_ClassInstance->destruct=Scope_destruct;
	Scope_ClassInstance->setScopeLink=Scope_setScopeLink;
	Scope_ClassInstance->setNextScopeLink=Scope_setNextScopeLink;
	Scope_ClassInstance->className_CLObject="CLObject";
	Scope_ClassInstance->classId_CLObject=&CLObject_ClassInstance;
	Scope_ClassInstance->init_CLObject=Scope_init;
	Scope_ClassInstance->destruct_CLObject=Scope_destruct;
	Scope_ClassInstance->retain=Scope_retain;
	Scope_ClassInstance->release=Scope_release;
	Scope_ClassInstance->describe=Scope_describe;
	
}
struct Scope* Scope_alloc( )
{
	struct Scope* result;
	if(Scope_ClassInstance==NULL)Scope_CreateClass( );
	result=malloc(sizeof(struct Scope));
	result->_components=malloc(sizeof(void*)*3);
	result->_class=(void*)&(Scope_ClassInstance->className);
	result->_components_CLObject=result->_components;
	result->_class_CLObject=(void*)&(Scope_ClassInstance->className_CLObject);
	result->_components[0]=&(result->_class);
	result->_components[1]=&(result->_class_CLObject);
	result->_components[2]=NULL;
	return result;
}
void Scope_init (struct Scope* self ) 
{
	CLObject_init(( cast_object( &CLObject_ClassInstance , self)));
	self->type=kScopeTypeNormal;
	self->scopeLink=NULL;
	self->nextScopeLink=NULL;
	self->forEachList=CLObjectList_alloc( );
	self->instancesList=CLObjectList_alloc( );
	self->instanceNamesList=CLObjectList_alloc( );
	CLObjectList_init(self->forEachList );
	CLObjectList_init(self->instancesList );
	CLObjectList_init(self->instanceNamesList );
}
void Scope_destruct (struct Scope* self ) 
{
	if(self->scopeLink!=NULL)self->scopeLink->_class->release( (void*) self->scopeLink->_components[0] );
	if(self->nextScopeLink!=NULL)self->nextScopeLink->_class->release( (void*) self->nextScopeLink->_components[0] );
	CLObjectList_release(self->forEachList );
	CLObjectList_release(self->instancesList );
	CLObjectList_release(self->instanceNamesList );
	CLObject_destruct(( cast_object( &CLObject_ClassInstance , self)));
}
void Scope_setScopeLink (struct Scope* self, struct CLString * theLink ) 
{
	if(self->scopeLink!=NULL) CLString_release(self->scopeLink );
	self->scopeLink=theLink;
	if(self->scopeLink!=NULL)self->scopeLink->_class->retain( (void*) self->scopeLink->_components[0] );
}
void Scope_setNextScopeLink (struct Scope* self, struct CLString * theLink ) 
{
	if(self->nextScopeLink!=NULL) CLString_release(self->nextScopeLink );
	self->nextScopeLink=theLink;
	if(self->nextScopeLink!=NULL)self->nextScopeLink->_class->retain( (void*) self->nextScopeLink->_components[0] );
}
void Scope_retain (struct Scope* self ) 
{
	self->retainCount=self->retainCount+1;
}
void Scope_release (struct Scope* self ) 
{
	self->retainCount=self->retainCount-1;
	if(self->retainCount==0)
	{
		self->_class->destruct( (void*) self->_components[0] );
		free_object(self);
	}
}
void Scope_describe (struct Scope* self ) 
{
	printf("\nObject %li retainCount %li",(long)self,self->retainCount);
}
int main( 	int			theCount , 
			const char* theTokens[ ] )
{
	struct Main* main;
	int result;

	main	= Main_alloc( );
    result	= Main_init( main , theCount , theTokens );

    Main_release( main );
    return result;
}

