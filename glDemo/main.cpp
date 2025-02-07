
#include "core.h"


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void updateScene();
void DrawPolygon(int _x, int _y);
void drawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points);


int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Real-Time Computer Graphics", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black
	

	//
	// 2. Main loop
	// 
	
	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}



// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render objects here...
	drawStar(0.0f, 0.0f, 0.2f, 0.4f, 10);

}

void DrawPolygon(int _x, int _y)
{
	glColor3f(0.3, 0.5, 0.6);
	glBegin(GL_POLYGON); // Draw A Quad
	glVertex2f(_x-0.5f,_y + 1.0f); // Top Left
	glVertex2f(_x-1.0f, _y+0.0f); // Left
	glVertex2f(_x-0.5f,_y+ 0.7f); // Bottom Left
	glVertex2f(_x+0.5f, _y+0.7f); // Top Right
	glVertex2f(_x + 0.4f,_y + 0.0f); // Right
	glVertex2f(_x+0.5f, _y+0.7f); // Bottom Right
	glEnd();
}
// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}

void drawStar(float _atX, float _atY, float _innerRadius, float _outerRadius, int _points)
{
	float angle = 2.0f * 3.14159265359f / _points;  // Angle between points of the star
	float halfAngle = angle / 2.0f;

	glBegin(GL_TRIANGLE_FAN);
	//centre of the star
	glVertex2f(_atX, _atY);

	for (int i = 0; i <= _points; i++)
	{
		
		// Outer point
		glColor3f((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX));
		glVertex2f(_atX + cos(i * angle) * _outerRadius, _atY + sin(i * angle) * _outerRadius);

		// Inner point
		glColor3f((float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX), (float)rand() / (RAND_MAX));
		glVertex2f(_atX + cos(i * angle + halfAngle) * _innerRadius, _atY + sin(i * angle + halfAngle) * _innerRadius);
	}
	glEnd();
}

// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() {

}

