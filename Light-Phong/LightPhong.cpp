#include "vgl.h"
#include "LoadShaders.h"
#include "Shader.h"
#include "Texture.h"

enum VAO_IDs { Triangles, Light, NumVAOs };
enum EBO_IDs { Indexes, NumEBOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition, vNormal, vUV };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBOs[NumEBOs];

Shader* Program;
Shader* LightProgram;
Texture* DiffuseMap;
Texture* SpecularMap;

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

void TestDai(int(*a)[4])
{
}

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

void
init(void)
{
	int(*a)[4] = new int{ 1, 2,3,4 };
	GLfloat vertices[] = {
		// postions           // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	glGenBuffers(NumBuffers, Buffers);
	glGenVertexArrays(NumVAOs, VAOs);
	glGenBuffers(NumEBOs, EBOs);


	// VBO
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);

	// VAO
	glBindVertexArray(VAOs[Triangles]);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vUV, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(vUV);


	// light
	glBindVertexArray(VAOs[Light]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);

	glBindVertexArray(0);

	Program = new Shader("media/shaders/light/phong/box.vert", "media/shaders/light/phong/box.frag");
	LightProgram = new Shader("media/shaders/light/phong/light.vert", "media/shaders/light/phong/light.frag");

	DiffuseMap = new Texture("media/container2.png");
	SpecularMap = new Texture("media/container2_specular.png");
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

	Program->use();
	glm::mat4 projection;
	projection = glm::perspective(camera.Zoom, (float)Width / (float)Height, 0.1f, 1000.0f);

	Program->setMatrix4fv("projection", projection);

	glm::vec3 lightColor;
	lightColor.x = sin(glfwGetTime() * 2.0f);
	lightColor.y = sin(glfwGetTime() * 0.7f);
	lightColor.z = sin(glfwGetTime() * 1.3f);

	glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
	glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

	Program->setFloat3("light.ambient", 0.2f, 0.2f, 0.2f);
	Program->setFloat3("light.diffuse", 0.5f, 0.5f, 0.5f);
	Program->setFloat3("light.specular", 1.0f, 1.0f, 1.0f);

	//Program->setFloat3("material.ambient", 0.2f, 0.2f, 0.2f);
	//Program->setFloat3("material.diffuse", 0.5f, 0.5f, 0.5f);
	Program->setFloat3("material.specular", 1.0f, 1.0f, 1.0f);
	Program->setFloat("material.shininess", 64.0f);

	LightProgram->use();
	LightProgram->setMatrix4fv("projection", projection);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBindVertexArray(VAOs[Triangles]);
	Program->use();

	glm::mat4 view;
	view = camera.GetViewMatrix();

	Program->setMatrix4fv("view", view);
	Program->setFloat3("ViewPos", camera.Position.x, camera.Position.y, camera.Position.z);

	glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
	glm::vec4 viewLightPos = view * glm::vec4(lightPos, 1.0f);
	Program->setFloat3("LightPos", viewLightPos.x, viewLightPos.y, viewLightPos.z);

	glm::vec3 cubePosition = glm::vec3(0.0f, 0.0f, 0.0f);

	glm::mat4 model;
	model = glm::translate(model, cubePosition);
	GLfloat angle = 0;
	//model = glm::rotate(model, angle * (GLfloat)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
	Program->setMatrix4fv("model", model);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, DiffuseMap->ID);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, SpecularMap->ID);


	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(VAOs[Light]);
	LightProgram->use();
	LightProgram->setMatrix4fv("view", view);

	glm::mat4 lightModel = glm::mat4();
	lightModel = glm::translate(lightModel, lightPos);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));
	LightProgram->setMatrix4fv("model", lightModel);
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