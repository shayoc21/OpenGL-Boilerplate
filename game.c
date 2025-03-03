#include "game.h"

//private function declarations
void pollInputs(Game* game);
int isGameRunning(Game* game);

void initGame(Game* game)
{
	printf("Initializing Game...\n");

	initWindow(&game->window);
	initGL();

	initScene(&game->scene);
	//initHUD(&game->HUD);
	
	initCamera(&game->playerCamera, vector(10.0f, 5.0f, 0.0f), vector(-1.0f, -0.25f, 0.0f), 90);
	currentCamera = &game->playerCamera;

	printf("	...Game Initialized\n");
}

void runGame(Game* game)
{
	printf("Running Game...\n");
	int frameCount;
	float previousTime = glfwGetTime();
	while (isGameRunning(game))
	{
	 	float currentTime = glfwGetTime();
		frameCount++;
		pollInputs(game);

		clearScreen();

		//draw screen
		drawScene(&game->scene);
		//drawHUD(&game->HUD);

		//swap buffers
		glfwSwapBuffers(game->window);

		GLenum err = glGetError();
		while (err != GL_NO_ERROR)
		{
			printf("OpenGL Error: %d\n", err);
		}

		if (currentTime - previousTime >= 1.0)
		{
			printf("	...FPS : %d\n", frameCount);
			frameCount = 0;
			previousTime = currentTime;
		}	
	}
}

void closeGame(Game* game)
{
	printf("Closing Game...\n");
	destroyScene(&game->scene);
	//destroyHUD(&game->hud);
	//destroyCamera(&game->playerCamera);
	glfwTerminate();
	printf("	...Game Closed\n");
}

// ===========Private function Definitions (disgusting code)===============//

void pollInputs(Game* game)
{
	glfwPollEvents();
	float velocity = 0.2;
	if (glfwGetKey(game->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		velocity = 0.35;
	}
	if (glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(game->window, 1);
	}
	if (glfwGetKey(game->window, GLFW_KEY_W) == GLFW_PRESS)
	{
		vec3 movement = scaleVec3(currentCamera->front, velocity);
	
		moveCamera(currentCamera, movement);
	}
	if (glfwGetKey(game->window, GLFW_KEY_S) == GLFW_PRESS)
	{
		vec3 movement = scaleVec3(currentCamera->front, -velocity);
		moveCamera(currentCamera, movement);
	}
	if (glfwGetKey(game->window, GLFW_KEY_A) == GLFW_PRESS)
	{
		vec3 movement = scaleVec3(currentCamera->right, -velocity);
		moveCamera(currentCamera, movement);
	}
	if (glfwGetKey(game->window, GLFW_KEY_D) == GLFW_PRESS)
	{
		vec3 movement = scaleVec3(currentCamera->right, velocity);
		moveCamera(currentCamera, movement);
	}
	if (glfwGetKey(game->window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		vec3 movement = scaleVec3(currentCamera->up, velocity);
		moveCamera(currentCamera, movement);
	}
	if (glfwGetKey(game->window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		vec3 movement = scaleVec3(currentCamera->up, -velocity);
		moveCamera(currentCamera, movement);
	}
	if (glfwGetKey(game->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		rotateCamera(currentCamera, quat(currentCamera->up, 0.5f));
	}
	if (glfwGetKey(game->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		rotateCamera(currentCamera, quat(currentCamera->up, -0.5f));
	}
	if (glfwGetKey(game->window, GLFW_KEY_E) == GLFW_PRESS)
	{
		rotateCamera(currentCamera, quat(currentCamera->front, 0.5f));
	}
	if (glfwGetKey(game->window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		rotateCamera(currentCamera, quat(currentCamera->front, -0.5f));
	}
	if (glfwGetKey(game->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		rotateCamera(currentCamera, quat(currentCamera->right, 0.5f));
	}
	if (glfwGetKey(game->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		rotateCamera(currentCamera, quat(currentCamera->right, -0.5f));
	}
	if (glfwGetKey(game->window, GLFW_KEY_P) == GLFW_PRESS)
	{
		printf("CAMERADIR : %f %f %f\n", currentCamera->front.x, currentCamera->front.y, currentCamera->front.z);
		printf("CAMERAPOS : %f %f %f\n", currentCamera->position.x, currentCamera->position.y, currentCamera->position.z);
	}
}

int isGameRunning(Game* game)
{
	return !glfwWindowShouldClose(game->window);
}

