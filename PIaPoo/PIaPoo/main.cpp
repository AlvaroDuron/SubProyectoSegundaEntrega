#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "Sombreador.h"
#include "Camara.h"
#include "Estructura.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 3.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Sombreador objectShader("vertex.txt", "fragment.txt");

	Model* contenedor = new Model("assets/basura/contenedor.obj");

	Model* maquina[2];
	for (int i = 0; i < 2; i++)
		maquina[i] = new Model("assets/maquina expendedora/maquina.obj");

	Model* banca[5];
	for (int i = 0; i < 5; i++)
		banca[i] = new Model("assets/banca/banca.obj");

	Model* telefono[2];
	for (int i = 0; i < 2; i++)
		telefono[i] = new Model("assets/telefono/telefono.obj");

	Model* lampara[4];
	for (int i = 0; i < 4; i++)
		lampara[i] = new Model("assets/lampara/lampara.obj");

	Estructura* estructura = new Estructura();

	objectShader.use();
	objectShader.setInt("texture_diffuse1", 0);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		estructura->PintarEstructura(objectShader, camera);

		glm::mat4 model1 = glm::mat4(1.0f);
		model1 = glm::translate(model1, glm::vec3(-0.5f, 1.0f, -46.0f));
		model1 = glm::scale(model1, glm::vec3(0.04f, 0.04f, 0.04f));
		objectShader.setMat4("model", model1);
		maquina[0]->Draw(objectShader);

		glm::mat4 model2 = glm::mat4(1.0f);
		model2 = glm::translate(model2, glm::vec3(1.5f, 1.0f, -46.0f));
		model2 = glm::scale(model2, glm::vec3(0.04f, 0.04f, 0.04f));
		objectShader.setMat4("model", model2);
		maquina[1]->Draw(objectShader);

		for (int i = 0; i < 5; i++)
		{
			glm::mat4 modelBanca = glm::mat4(1.0f);
			modelBanca = glm::translate(modelBanca, glm::vec3(-0.5f, 1.7f, -30.0f + (i * 5.0f)));
			modelBanca = glm::rotate(modelBanca, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			modelBanca = glm::scale(modelBanca, glm::vec3(0.05f, 0.05f, 0.05f));
			objectShader.setMat4("model", modelBanca);
			banca[i]->Draw(objectShader);
		}

		glm::mat4 modelBasura = glm::mat4(1.0f);
		modelBasura = glm::translate(modelBasura, glm::vec3(0.0f, 1.0f, -35.0f));
		modelBasura = glm::scale(modelBasura, glm::vec3(0.03f, 0.03f, 0.03f));
		objectShader.setMat4("model", modelBasura);
		contenedor->Draw(objectShader);

		for (int i = 0; i < 2; i++) {
			glm::mat4 modelTelefono = glm::mat4(1.0f);
			modelTelefono = glm::translate(modelTelefono, glm::vec3(-0.8f, 1.1f, -5.0f - (i * 1.0f)));
			modelTelefono = glm::scale(modelTelefono, glm::vec3(0.5f, 0.5f, 0.5f));
			objectShader.setMat4("model", modelTelefono);
			telefono[i]->Draw(objectShader);
		}

		for (int i = 0; i < 4; i++)
		{
			glm::mat4 modelLampara = glm::mat4(1.0f);
			modelLampara = glm::translate(modelLampara, glm::vec3(2.0f, 4.5f, -5.0f - (i * 10.0)));
			modelLampara = glm::scale(modelLampara, glm::vec3(0.08f, 0.08f, 0.08f));
			objectShader.setMat4("model", modelLampara);
			lampara[i]->Draw(objectShader);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, estructura->getVao());
	glDeleteBuffers(1, estructura->getVbo());

	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}