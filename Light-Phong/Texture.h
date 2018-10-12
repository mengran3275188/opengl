#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>

#include <GL3/gl3w.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	unsigned int ID;
	GLenum Format;
	Texture(const char* path)
	{
		glGenTextures(1, &ID);

		int width, height, nrComponents;
		unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
		if (data)
		{
			if (nrComponents == 1)
				Format = GL_RED;
			else if (nrComponents == 3)
				Format = GL_RGB;
			else if (nrComponents == 4)
				Format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, Format, width, height, 0, Format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else {
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}
	}
};
#endif