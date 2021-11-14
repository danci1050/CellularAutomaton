#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "CellularAutomata.h";



std::vector <GLfloat> verticesCellularAutomata(std::vector <std::string> output) {
	
	int horizontalLenght = output.at(0).length();
	float horizontalModifier = 2.0f / (float)horizontalLenght;
	int verticalLength = output.size();
	float verticalModifier = 2.0f / (float)verticalLength;
	GLfloat currenthorizontalPosition = -1;
	GLfloat currentverticalPosition = 1;
	std::vector <GLfloat> ver;
	for (int i = 0; i < verticalLength; i++)
	{
		for (int j = 0; j < horizontalLenght; j++) {
			if (output.at(i).at(j) == '1') {
				ver.insert(ver.end(), { currenthorizontalPosition ,currentverticalPosition, 0.0f,     1.0f, 1.0f,  1.0f });
				ver.insert(ver.end(), { currenthorizontalPosition + horizontalModifier,currentverticalPosition, 0.0f,     1.0f, 1.0f,  1.0f });
				ver.insert(ver.end(), { currenthorizontalPosition ,currentverticalPosition - verticalModifier , 0.0f,     1.0f, 1.0f,  1.0f });
				ver.insert(ver.end(), { currenthorizontalPosition + horizontalModifier,currentverticalPosition - verticalModifier , 0.0f,     1.0f, 1.0f,  1.0f });
			}
			else {
				ver.insert(ver.end(), { currenthorizontalPosition ,currentverticalPosition, 0.0f,     0.0f, 0.0f,  0.0f });
				ver.insert(ver.end(), { currenthorizontalPosition + horizontalModifier,currentverticalPosition, 0.0f,     0.0f, 0.0f,  0.0f });
				ver.insert(ver.end(), { currenthorizontalPosition ,currentverticalPosition - verticalModifier , 0.0f,     0.0f, 0.0f,  0.0f });
				ver.insert(ver.end(), { currenthorizontalPosition +horizontalModifier,currentverticalPosition - verticalModifier , 0.0f,     0.0f, 0.0f,  0.0f });
			}
			currenthorizontalPosition += horizontalModifier;
		}
		currenthorizontalPosition = -1;
		currentverticalPosition -= verticalModifier;
	}
	return ver;
}

std::vector <GLuint> indicesCellularAutomata(int numberOfVertices) {
	std::vector <GLuint> squeres;
	for (int i = 0; i < numberOfVertices; i++)
	{
		squeres.insert(squeres.end(), {(unsigned int) 2 + 4 * i,(unsigned int)1 + 4 * i,(unsigned int)0 + 4 * i,(unsigned int)2 + 4 * i,(unsigned int)1 + 4 * i,(unsigned int) 3 + 4 * i });
	}
	return squeres;
}

int CellularAutomata1DGrapics(std::vector <std::string> result) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	std::vector <GLfloat> vertices = verticesCellularAutomata(result);
	std::vector <GLuint> indices = indicesCellularAutomata(result.size()*result.at(0).size());



	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0,0,800,800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, vertices.size()*sizeof(GLfloat));

	EBO EBO1(indices, indices.size()*sizeof(GLuint));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	while (!glfwWindowShouldClose(window)) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glPointSize(6);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glClearColor(1.00f, 0.00f, 0.00f, 0.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 4000000, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

int GameOfLifeGrapics(vector <string> startingState) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	std::vector <std::string> result = CellularAutomata::GameOfLife(startingState);
	std::vector <GLfloat> vertices = verticesCellularAutomata(result);
	std::vector <GLuint> indices = indicesCellularAutomata(result.size() * result.at(0).size());

	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glViewport(0, 0, 800, 800);
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, vertices.size() * sizeof(GLfloat));

	EBO EBO1(indices, indices.size() * sizeof(GLuint));

	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();


	while (!glfwWindowShouldClose(window)) {

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glPointSize(6);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glClearColor(1.00f, 0.00f, 0.00f, 0.00f);
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.Activate();
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, 4000000, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();

		result = CellularAutomata::GameOfLife(result);
		vertices.clear();
		vertices = verticesCellularAutomata(result);
		indices.clear();
		indices = indicesCellularAutomata(result.size() * result.at(0).size());

		VAO1.Bind();
		VBO1 = VBO(vertices, vertices.size() * sizeof(GLfloat));
		EBO1 = EBO(indices, indices.size() * sizeof(GLuint));
		VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
		VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		VAO1.Unbind();
		VBO1.Unbind();
		EBO1.Unbind();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

int main() {
	string choice;
	int num;
	vector <string> startingState;
	while (true) {
		std::vector <std::string> CellAutoResult;
		cout << "1. 1D Cellular Automata\n2. Game of life\n3.Load Cellular Automaton from file\n4. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		num = std::stoi(choice);
		switch (num)
		{
		case 1:
			CellAutoResult = CellularAutomata::CellularAutomata1D();
			CellularAutomata1DGrapics(CellAutoResult);
			break;
		case 2:

			startingState.insert(startingState.end(), { "00000000000","00000000000","00000000000","00000100000","00000010000","00001110000","00000000000","00000000000","00000000000", "00000000000","00000000000", });
			GameOfLifeGrapics(startingState);
			break;
		case 3:
			cout << "Enter the name of the file: ";
			cin >> choice;
			CellAutoResult = CellularAutomata::ImportFile(choice);
			CellularAutomata1DGrapics(CellAutoResult);
			break;
		case 4:
			exit(0);
			break;
		default:
			cout << "Invalid option " + num << endl;
			break;
		}
	}
	return 0;
}

