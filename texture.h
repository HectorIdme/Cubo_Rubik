#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "std_image.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Texture{

	public:
        int width, height, nrChannels;
        unsigned char* data;

		Texture::Texture(const char* texturePath, unsigned int &ID,bool format=0) {
            glBindTexture(GL_TEXTURE_2D, ID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            stbi_set_flip_vertically_on_load(true);
            data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
            if (data) {
                if (format) glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                else glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else { std::cout << "Failed to load texture\n"; }
            stbi_image_free(data);
		}

};
#endif