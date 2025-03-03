#ifndef _OBJECT
#define _OBJECT

#include "objparser.h"
#include <GL/glew.h>
#include "mathlibrary/maths.h"
#include "camera.h"

struct Object
{
	GLuint VAO;
	GLuint TEXTURE;
	GLuint SHADER;
	GLuint vertexCount;
	mat4 modelMatrix;
	vec3 position;
	quaternion rotation;
	vec3 scale;
};
typedef struct Object Object;

void initObject
(
	Object* object, 
	vec3 position, 
	vec3 scale, 
	quaternion rotation, 
	const char* objectFile, 
	const char* textureFile
);
void initSkybox(Object* object, const char* texturePrefix);
void duplicateObject(Object* object, Object* objectTemplate, vec3 position, vec3 scale, quaternion rotation);
void drawObject(Object* object);
void drawSkybox(Object* object);
void destroyObject(Object* object);

#endif
