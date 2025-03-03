#include "scene.h"

void addObjectToScene(Scene* scene, Object* object)
{
	Object* copiedObject = (Object*)malloc(sizeof(Object));
	*copiedObject = *object;

	scene->worldObjectCount++;
	scene->worldObjects = (Object**)realloc(scene->worldObjects, scene->worldObjectCount * sizeof(Object*));
	scene->worldObjects[scene->worldObjectCount-1] = copiedObject;
}

void initWorldmap(Scene* scene)
{
	Object worldObject;
	printf("		...Initializing Objects\n");
	initObject(&worldObject, vector(15.0f, 0.0f, 2.0f), vector(2.0, 2.0, 2.0), quat(vector(0.0, 1.0, 0.0), 120.0f), "./models/tree.obj", "./textures/cube.png");	
	addObjectToScene(scene, &worldObject);
	duplicateObject(&worldObject, &worldObject, vector(-12.0f, 0.0f, 10.0f), vector(1.0, 1.0, 1.0), quat(vector(0.0,1.0,0.0), 22.0f));
	addObjectToScene(scene, &worldObject);
	printf("			...Done\n");
	printf("		...Initializing Skybox\n");
	initSkybox(&scene->skybox, "./textures/skybox/day");
	printf("			...Done\n");
}

void initScene(Scene* scene)
{
	printf("	...Initializing Scene\n");
	scene->worldObjects = (Object**)malloc(sizeof(Object*));
	scene->worldObjectCount = 0;

	initWorldmap(scene);
	printf("		...Done\n");
}

void drawScene(Scene* scene)
{
	drawSkybox(&scene->skybox);
	for (int i = 0; i < scene->worldObjectCount; i++)
	{
		drawObject(scene->worldObjects[i]);
	}
}

void destroyScene(Scene* scene)
{
	for (int i = 0; i < scene->worldObjectCount; i++)
	{
		destroyObject(scene->worldObjects[i]);
		free(scene->worldObjects[i]);
	}
	destroyObject(&scene->skybox);
	free(scene->worldObjects);
}
		
