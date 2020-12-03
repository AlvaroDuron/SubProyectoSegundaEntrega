#include "Estructura.h"

Estructura::Estructura()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Cargar texturas
	glGenTextures(1, &this->pisoTexture);
	glBindTexture(GL_TEXTURE_2D, this->pisoTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("piso.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &this->paredTexture);
	glBindTexture(GL_TEXTURE_2D, this->paredTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("pared.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &this->viasTexture);
	glBindTexture(GL_TEXTURE_2D, this->viasTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("vias.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &this->viasSoloTexture);
	glBindTexture(GL_TEXTURE_2D, this->viasSoloTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("viasSolo.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glGenTextures(1, &this->techoTexture);
	glBindTexture(GL_TEXTURE_2D, this->techoTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	data = stbi_load("techo.jpg", &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
}

GLuint* Estructura::getVao()
{
	return &this->VAO;
}

GLuint* Estructura::getVbo()
{
	return &this->VBO;
}

glm::vec3 Estructura::getPisoPosition(unsigned int index)
{
	return this->pisoPositions[index];
}

glm::vec3 Estructura::getTechoPosition(unsigned int index)
{
	return this->techoPositions[index];
}

glm::vec3 Estructura::getParedPosition(unsigned int index)
{
	return this->paredPositions[index];
}

glm::vec3 Estructura::getParedInicialPosition(unsigned int index)
{
	return this->paredInicialPositions[index];
}

glm::vec3 Estructura::getParedFinalPosition(unsigned int index)
{
	return this->paredFinalPositions[index];
}

glm::vec3 Estructura::getParedViasInicialPosition(unsigned int index)
{
	return this->paredViasInicialPositions[index];
}

glm::vec3 Estructura::getParedViasFinalPosition(unsigned int index)
{
	return this->paredViasFinalPositions[index];
}

glm::vec3 Estructura::getViasPosition(unsigned int index)
{
	return this->viasPositions[index];
}

void Estructura::PintarEstructura(Sombreador ourShader, Camera camera)
{
	ourShader.use();

	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
	ourShader.setMat4("projection", projection);

	glm::mat4 view = camera.GetViewMatrix();
	ourShader.setMat4("view", view);

	glBindTexture(GL_TEXTURE_2D, this->pisoTexture);
	glBindVertexArray(*this->getVao());

	for (int i = 0; i < 72; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getPisoPosition(i));

		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindTexture(GL_TEXTURE_2D, this->techoTexture);

	for (int i = 0; i < 148; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getTechoPosition(i));

		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindTexture(GL_TEXTURE_2D, this->paredTexture);

	for (int i = 0; i < 48; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getParedPosition(i));

		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	for (int i = 0; i < 24; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getParedViasInicialPosition(i));

		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	for (int i = 0; i < 72; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getParedViasFinalPosition(i));

		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	for (int i = 0; i < 6; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getParedInicialPosition(i));

		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	for (int i = 0; i < 6; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getParedFinalPosition(i));

		model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	for (int i = 0; i < 72; i++)
	{
		if (this->getViasPosition(i).x == 8.0f)
			glBindTexture(GL_TEXTURE_2D, this->viasSoloTexture);
		else
			glBindTexture(GL_TEXTURE_2D, this->viasTexture);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->getViasPosition(i));

		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		ourShader.setMat4("model", model);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}