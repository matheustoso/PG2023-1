#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Classe shader
#include "shader/Shader.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
int setupGeometry();
const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista 3", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER); 
	const GLubyte* version = glGetString(GL_VERSION); 
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	Shader shader("shader/shader.vs", "shader/shader.fs");

	GLuint VAO = setupGeometry();
		
	glUseProgram(shader.ID);
	glm::mat4 projection = glm::ortho(0.0, 800.0, 0.0, 600.0, -1.0, 1.0);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glViewport(0, 0, width, height);

		glClearColor(0.7f, 0.7f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(1);
		glPointSize(5);

		glBindVertexArray(VAO); 

		//Matriz de modelo -- transformações na geometria 
		glm::mat4 model = glm::mat4(1); //matriz identidade
		float angle = glfwGetTime();
		model = glm::translate(model, glm::vec3(abs(sin(angle))*800.0, abs(sin(angle))*600.0, 0.0));
		model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(100.0, 100.0, 1.0));
		GLint modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_POINTS, 0, 3);

		//Matriz de modelo -- transformações na geometria 
		model = glm::mat4(1); //matriz identidade
		model = glm::translate(model, glm::vec3(600.0, 450.0, 0.0));
		angle = glfwGetTime();
		model = glm::rotate(model, sin(angle), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(100.0, sin(angle)*100, 1.0));
		modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_POINTS, 0, 3);

		//Matriz de modelo -- transformações na geometria 
		model = glm::mat4(1); //matriz identidade
		model = glm::translate(model, glm::vec3(200.0, 450.0, 0.0));
		angle = glfwGetTime();
		model = glm::rotate(model, sin(-angle), glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(sin(angle)*100, 100.0, 1.0));
		modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_POINTS, 0, 3);

		//Matriz de modelo -- transformações na geometria 
		model = glm::mat4(1); //matriz identidade
		model = glm::translate(model, glm::vec3(600.0, 150.0, 0.0));
		angle = glfwGetTime();
		model = glm::rotate(model, angle, glm::vec3(0.0, 0.0, 1.0));
		model = glm::scale(model, glm::vec3(sin(angle)*100, sin(angle)*100, 1.0));
		modelLoc = glGetUniformLocation(shader.ID, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_LINE_LOOP, 0, 3);
		glDrawArrays(GL_POINTS, 0, 3);

		glBindVertexArray(0); 
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int setupGeometry()
{
	GLfloat vertices[] = {
		//x   y     z    r    g    b
		-0.5 , -0.5 , 0.0, 1.0, 0.0, 0.0, //v0
		 0.5 , -0.5 , 0.0, 0.0, 1.0, 0.0, //v1
		 0.0 , 0.5 ,  0.0, 0.0, 0.0, 1.0  //v2
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	return VAO;
}

