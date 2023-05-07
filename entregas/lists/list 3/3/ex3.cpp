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
int setupGeometry(glm::vec3 rgb);
void drawSquare(Shader shader, GLuint VAO, int x, int y);
const GLuint WIDTH = 600, HEIGHT = 600;
glm::vec3 charPos;

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
		
	glUseProgram(shader.ID);
	glm::mat4 projection = glm::ortho(0.0, 600.0, 0.0, 600.0, -1.0, 1.0);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	GLuint VAO = setupGeometry(glm::vec3(1.0,0.0,1.0));

	charPos.x = 100.0;
	charPos.y = 100.0;
	charPos.z = 0.0;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glViewport(0, 0, width, height);

		glClearColor(0.7f, 0.7f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(1);
		glPointSize(5);

		drawSquare(shader, VAO, charPos.x, charPos.y);

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

	if (key == GLFW_KEY_D || key == GLFW_KEY_RIGHT)
		charPos.x += 5.0;
	
	if (key == GLFW_KEY_A || key == GLFW_KEY_LEFT)
		charPos.x -= 5.0;
	
	if (key == GLFW_KEY_W || key == GLFW_KEY_UP)
		charPos.y += 5.0;
	
	if (key == GLFW_KEY_S || key == GLFW_KEY_DOWN)
		charPos.y -= 5.0;
	
}

int setupGeometry(glm::vec3 rgb)
{
	GLfloat vertices[] = {
		0.0 , 0.0 , 0.0, rgb.x, rgb.y, rgb.z,
		1.0 , 0.0 , 0.0, rgb.x, rgb.y, rgb.z,
		0.0 , 1.0 , 0.0, rgb.x, rgb.y, rgb.z,
		1.0 , 1.0 , 0.0, rgb.x, rgb.y, rgb.z 
	};

	GLuint indices[] = {
		0,1,2,
		1,2,3,
	};

	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	glBindVertexArray(0); 

	return VAO;
}

void drawSquare(Shader shader, GLuint VAO, int x, int y) {
	glBindVertexArray(VAO);
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, glm::vec3(x, y, 0.0));
	model = glm::scale(model, glm::vec3(100.0, 100.0, 1.0));
	GLint modelLoc = glGetUniformLocation(shader.ID, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0); 
}