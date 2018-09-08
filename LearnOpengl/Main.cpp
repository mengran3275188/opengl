#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, Light, NumVAOs };
enum EBO_IDs { Indexes, NumEBOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vNormal, vUV };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBOs[NumEBOs];

GLuint Program;
GLuint LightProgram;

const GLuint NumVertices = 6;

const GLuint Width = 800, Height = 600;

glm::vec3 CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 CameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = TRUE;
GLfloat lastX = 400, lastY = 300;



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void do_movement();

Camera camera(glm::vec3(0.0f, 0.0f, 7.0f));
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void
init(void)
{
	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

		0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenBuffers(NumBuffers, Buffers);
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumEBOs, EBOs);

	// VAO
	glBindVertexArray(VAOs[Triangles]);

	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

	// EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[Indexes]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vPosition);
	glEnableVertexAttribArray(vNormal);
	glEnableVertexAttribArray(vUV);


	// light
	glBindVertexArray(VAOs[Light]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	glBindVertexArray(0);


	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "media/shaders/light/box.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/light/box.frag" },
		{ GL_NONE, NULL }
	};

	Program = LoadShaders(shaders);
	glUseProgram(Program);
	// texture wall
	int width, height;
	unsigned char* image = SOIL_load_image("media/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	GLuint texture0;
	glGenTextures(1, &texture0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(Program, "OurTexture0"), 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	// texture face
	image = SOIL_load_image("media/awesomeface.png", &width, &height, 0, SOIL_LOAD_RGB);
	GLuint texture1;
	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(Program, "OurTexture1"), 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);



	glm::mat4 projection;
	projection = glm::perspective(camera.Zoom, (float)Width / (float)Height, 0.1f, 1000.0f);

	GLuint projectionLoc = glGetUniformLocation(Program, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
	GLint lightColorLoc = glGetUniformLocation(Program, "LightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);

	GLuint lightPosLoc = glGetUniformLocation(Program, "LightPos");
	glUniform3f(lightPosLoc, 1.2f, 1.0f, 2.0f);

	ShaderInfo  lightShaders[] =
	{
		{ GL_VERTEX_SHADER, "media/shaders/light/light.vert" },
		{ GL_FRAGMENT_SHADER, "media/shaders/light/light.frag" },
		{ GL_NONE, NULL }
	};

	LightProgram = LoadShaders(lightShaders);
	glUseProgram(LightProgram);
	GLuint lightProjectionLoc = glGetUniformLocation(LightProgram, "projection");
	glUniformMatrix4fv(lightProjectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
void
display(void)
{
	GLfloat currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	do_movement();

	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBindVertexArray(VAOs[Triangles]);
	glUseProgram(Program);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glm::mat4 view;
	view = camera.GetViewMatrix();
	GLuint viewLoc = glGetUniformLocation(Program, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	GLuint viewPosLoc = glGetUniformLocation(Program, "ViewPos");
	glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::mat4 model;
	model = glm::translate(model, cubePosition);
	GLfloat angle = 0;
	model = glm::rotate(model, angle * (GLfloat)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
	GLuint modelLoc = glGetUniformLocation(Program, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawArrays(GL_TRIANGLES, 0, 36);


	glBindVertexArray(VAOs[Light]);
	glUseProgram(LightProgram);
	GLuint lightViewLoc = glGetUniformLocation(LightProgram, "view");
	glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 lightModel = glm::mat4();
	glm::vec3 lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
	lightModel = glm::translate(lightModel, lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));
	GLuint lightModelLoc = glGetUniformLocation(LightProgram, "model");
	glUniformMatrix4fv(lightModelLoc, 1, GL_FALSE, glm::value_ptr(lightModel));
	glDrawArrays(GL_TRIANGLES, 0, 36);
}

#ifdef _WIN32
int CALLBACK WinMain(
	_In_ HINSTANCE hInstance,
	_In_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmdLine,
	_In_ int       nCmdShow
)
#else
int
main(int argc, char** argv)
#endif
{
	glfwInit();

	GLFWwindow * window = glfwCreateWindow(Width, Height, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	gl3wInit();

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glViewport(0, 0, Width, Height);

	init();

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}

void
key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS)
		keys[key] = true;
	else if (action == GLFW_RELEASE)
		keys[key] = false;
}

void
mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
void
scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
void
do_movement()
{
	GLfloat cameraSpeed = 0.05f;
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
		CameraPos -= cameraSpeed * CameraFront;
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}