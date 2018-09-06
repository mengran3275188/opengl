#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum EBO_IDs { Indexes, NumEBOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint EBOs[NumEBOs];

const GLuint NumVertices = 6;

void
init(void)
{
	GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glCreateBuffers(NumBuffers, Buffers);
	glGenBuffers(NumEBOs, EBOs);
	glGenVertexArrays(NumVAOs, VAOs);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[Indexes]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBindVertexArray(VAOs[Triangles]);

	glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 0);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(vPosition, 3, GL_FLOAT,
		GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
	glBindVertexArray(0);


	ShaderInfo  shaders[] =
	{
		{ GL_VERTEX_SHADER, "media/shaders/triangles/triangles.vert" },
	{ GL_FRAGMENT_SHADER, "media/shaders/triangles/triangles_blue.frag" },
	{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

}
void
display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	int width, height;
	unsigned char* image = SOIL_load_image("media/wall.jpg", &width, &height, 0, SOIL_LOAD_RGB);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);


	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBindVertexArray(VAOs[Triangles]);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

	GLFWwindow * window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	gl3wInit();

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