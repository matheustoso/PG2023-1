#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

// GLM
#include <glm/glm.hpp>

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

//Classe shader
#include "shader/Shader.h"


// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
int setupGeometry();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 800, HEIGHT = 800;


// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Ola Triangulo Colorido!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	glfwSetKeyCallback(window, key_callback);

	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);


	// Compilando e buildando o programa de shader
	Shader shader("shader/shader.vs", "shader/shader.fs");

	// Gerando um buffer simples, com a geometria de um triângulo
	GLuint VAO = setupGeometry();
	
	
	glUseProgram(shader.ID);

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Limpa o buffer de cor
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(10);
		glPointSize(20);

		glBindVertexArray(VAO); //Conectando ao buffer de geometria

		// Chamada de desenho - drawcall
		// Poligono Preenchido - GL_TRIANGLES

		glDrawArrays(GL_TRIANGLES, 0, 30);

		// Chamada de desenho - drawcall
		// CONTORNO - GL_LINE_LOOP
		// PONTOS - GL_POINTS

		//glDrawArrays(GL_LINE_LOOP, 0, 30);

		//glDrawArrays(GL_POINTS, 0, 30);
		

		glBindVertexArray(0); //Desconectando o buffer de geometria

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}
	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

// Função de callback de teclado - só pode ter uma instância (deve ser estática se
// estiver dentro de uma classe) - É chamada sempre que uma tecla for pressionada
// ou solta via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// Esta função está bastante harcoded - objetivo é criar os buffers que armazenam a 
// geometria de um triângulo
// Apenas atributo coordenada nos vértices
// 1 VBO com as coordenadas, VAO com apenas 1 ponteiro para atributo
// A função retorna o identificador do VAO
int setupGeometry()
{
	// Aqui setamos as coordenadas x, y e z do triângulo e as armazenamos de forma
	// sequencial, já visando mandar para o VBO (Vertex Buffer Objects)
	// Cada atributo do vértice (coordenada, cores, coordenadas de textura, normal, etc)
	// Pode ser arazenado em um VBO único ou em VBOs separados
    float pi = 2*acos(0.0f);
    float centerX = 0.0f;
    float centerY = 0.0f;
    float r = 0.3f;
    int triangles = 5;
    float angle = 2.0f*pi/triangles;
    
    GLfloat vertices[triangles*36];
    
    float x = centerX;
    float y = centerY + r;
    
    for(int i = 1; i <= triangles ; i++) {
        int j = (i-1)*18;
        
        float newX = r*sinf(angle*float(i));
        float newY = r*cosf(angle*float(i));
        
        vertices[j] = 0.0f;
        vertices[j+1] = 0.0f;
        vertices[j+2] = 0.0f;
        
        vertices[j+3] = 0.0f;
        vertices[j+4] = 0.0f;
        vertices[j+5] = 0.0f;
        
        vertices[j+6] = x;
        vertices[j+7] = y;
        vertices[j+8] = 0.0f;

        vertices[j+9] = 0.0f;
        vertices[j+10] = 0.0f;
        vertices[j+11] = 0.0f;
        
        vertices[j+12] = newX;
        vertices[j+13] = newY;
        vertices[j+14] = 0.0f;
        
        vertices[j+15] = 0.0f;
        vertices[j+16] = 0.0f;
        vertices[j+17] = 0.0f;
        
        x = newX;
        y = newY;
    }

    for(int i = 6; i < triangles*18; i+=18) {
        int j = i-6;
        GLfloat newPointX = vertices[i]+vertices[i+6];
        GLfloat newPointY = vertices[i+1]+vertices[i+7];
        
        vertices[triangles*18+j] = newPointX*1.62;
        vertices[triangles*18+j+1] = newPointY*1.62;
        vertices[triangles*18+j+2] = 0.0f;
        
        vertices[triangles*18+j+2] = 0.0f;
        vertices[triangles*18+j+3] = 0.0f;
        vertices[triangles*18+j+4] = 0.0f;

        vertices[triangles*18+j+6] = vertices[i];
        vertices[triangles*18+j+7] = vertices[i+1];
        vertices[triangles*18+j+8] = 0.0f;

        vertices[triangles*18+j+9] = 0.0f;
        vertices[triangles*18+j+10] = 0.0f;
        vertices[triangles*18+j+11] = 0.0f;
        
        vertices[triangles*18+j+12] = vertices[i+6];
        vertices[triangles*18+j+13] = vertices[i+7];
        vertices[triangles*18+j+14] = 0.0f;

        vertices[triangles*18+j+15] = 0.0f;
        vertices[triangles*18+j+16] = 0.0f;
        vertices[triangles*18+j+17] = 0.0f;
    }

	GLuint VBO, VAO;

	//Geração do identificador do VBO
	glGenBuffers(1, &VBO);
	//Faz a conexão (vincula) do buffer como um buffer de array
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Envia os dados do array de floats para o buffer da OpenGl
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Geração do identificador do VAO (Vertex Array Object)
	glGenVertexArrays(1, &VAO);
	// Vincula (bind) o VAO primeiro, e em seguida  conecta e seta o(s) buffer(s) de vértices
	// e os ponteiros para os atributos 
	glBindVertexArray(VAO);
	//Para cada atributo do vertice, criamos um "AttribPointer" (ponteiro para o atributo), indicando: 
	// Localização no shader * (a localização dos atributos devem ser correspondentes no layout especificado no vertex shader)
	// Numero de valores que o atributo tem (por ex, 3 coordenadas xyz) 
	// Tipo do dado
	// Se está normalizado (entre zero e um)
	// Tamanho em bytes 
	// Deslocamento a partir do byte zero 

	//Atributo posição
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Atributo cor
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Observe que isso é permitido, a chamada para glVertexAttribPointer registrou o VBO como o objeto de buffer de vértice 
	// atualmente vinculado - para que depois possamos desvincular com segurança
	glBindBuffer(GL_ARRAY_BUFFER, 0); 

	// Desvincula o VAO (é uma boa prática desvincular qualquer buffer ou array para evitar bugs medonhos)
	glBindVertexArray(0); 

	return VAO;
}