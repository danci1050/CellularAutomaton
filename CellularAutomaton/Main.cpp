#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <regex>

#include"shaderClass.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"
#include "CellularAutomata.h";


/*Generates the verices for the cellular automata visualization*/
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
/*Generates the indicies(the order the vertices are connected)*/
std::vector <GLuint> indicesCellularAutomata(int numberOfVertices) {
	std::vector <GLuint> squeres;
	for (int i = 0; i < numberOfVertices; i++)
	{
		squeres.insert(squeres.end(), {(unsigned int) 2 + 4 * i,(unsigned int)1 + 4 * i,(unsigned int)0 + 4 * i,(unsigned int)2 + 4 * i,(unsigned int)1 + 4 * i,(unsigned int) 3 + 4 * i });
	}
	return squeres;
}

/*Opens a new window and shows the 1D cellular Automata visualization*/
int CellularAutomata1DGrapics(std::vector <std::string> result) {
	glfwInit();
	
	/*setting the version of opengl*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	/*generating vertices and indices*/
	std::vector <GLfloat> vertices = verticesCellularAutomata(result);
	std::vector <GLuint> indices = indicesCellularAutomata(result.size()*result.at(0).size());


	/*creating new window*/
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);

	/*checking if the window was created successfully*/
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	/*setting initial view port values*/
	glViewport(0,0,800,800);
	/*creating shader program*/
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	/*creating VBO*/
	VBO VBO1(vertices, vertices.size()*sizeof(GLfloat));

	/*creating EBO*/
	EBO EBO1(indices, indices.size()*sizeof(GLuint));

	/*creating VAO*/
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	/*drawing the output*/
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
	/*Clean up*/
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
	/*setting the version of opengl*/
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

	/*Creating new window*/
	glViewport(0, 0, 800, 800);
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	/*creating VBO*/
	VBO VBO1(vertices, vertices.size() * sizeof(GLfloat));
	/*creating EBO*/
	EBO EBO1(indices, indices.size() * sizeof(GLuint));
	
	/*creating VAO*/
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	/*Draws the output end refreshes it*/
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
		/*regenerating the verticies and inidices*/
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
	/*Clean up*/
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


int Other2DGrapics(vector <string> startingState) {
	glfwInit();
	/*setting the version of opengl*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	std::vector <std::string> result = CellularAutomata::Other2D(startingState);
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

	/*Creating new window*/
	glViewport(0, 0, 800, 800);
	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();
	/*creating VBO*/
	VBO VBO1(vertices, vertices.size() * sizeof(GLfloat));
	/*creating EBO*/
	EBO EBO1(indices, indices.size() * sizeof(GLuint));

	/*creating VAO*/
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	/*Draws the output end refreshes it*/
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
		/*regenerating the verticies and inidices*/
		result = CellularAutomata::Other2D(result);
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
	/*Clean up*/
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

/*Displays the menu*/
void MainMenu() {
	string choice;
	int num;
	string s;
	vector <string> startingState;
	stringstream ss;
	while (true) {
		cout << endl;
		std::vector <std::string> CellAutoResult;
		cout << "1. 1D Cellular Automata\n2. Game of life\n3.Load Cellular Automaton from file\n4. Other 2D Cellular Automata\n5. Decimal to binary\n6.Binary to decimal\n7. Exit" << endl;
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
			/*Input verification*/
			while (true) {
				cout << "Enter the starting state (lines are divided by ',' e.g 0000,0100,0100,0100): ";
				cin >> choice;
				if (regex_match(choice, regex("^([0-1]|[,])*$"))) {
					ss = stringstream(choice);
					startingState.clear();
					while (ss.good()) {
						getline(ss, s, ',');
						startingState.push_back(s);
					}
					num = startingState[0].size();
					for (string i : startingState)
					{
						if (i.size() != num) {
							num = -1;
							break;
						}
					}
					if (startingState.size() == startingState.at(0).size() && num != -1) {
						break;
					}
				}
				cout << "Wrong input" << endl;
			}
			GameOfLifeGrapics(startingState);
			break;
		case 3:
			cout << "Enter the name of the file: ";
			cin >> choice;
			CellAutoResult = CellularAutomata::ImportFile(choice);
			CellularAutomata1DGrapics(CellAutoResult);
			break;
		case 4:
			while (true) {
				cout << "Enter the starting state (lines are divided by ',' e.g 0000,0100,0100,0100): ";
				cin >> choice;
				if (regex_match(choice, regex("^([0-1]|[,])*$"))) {
					ss = stringstream(choice);
					startingState.clear();
					while (ss.good()) {
						getline(ss, s, ',');
						startingState.push_back(s);
					}
					num = startingState[0].size();
					for (string i : startingState)
					{
						if (i.size() != num) {
							num = -1;
							break;
						}
					}
					if (startingState.size() == startingState.at(0).size() && num != -1) {
						break;
					}
				}
				cout << "Wrong input" << endl;
			}
			Other2DGrapics(startingState);
			break;
		case 5:
			cout << "Enter a decimal number: ";
			cin >> choice;
			if (regex_match(choice, regex("^([0-9])*$"))) {
				if (std::stoi(choice) > INT_MAX) {
					cout << CellularAutomata::DecimalToBinary(std::stoi(choice)) << endl;
				}
				else {
					cout << "The decimal number was too large" << endl;;
				}
			}
			else {
				cout << "Wrong input"<<endl;;
			}
			break;
		case 6:
			
			cout << "Enter a binary number: ";
			cin >> choice;
			if (regex_match(choice, regex("^([0-1])*$"))) {
				if (choice.length() < 31) {
					cout << CellularAutomata::BinaryToDecimal(std::stoi(choice)) << endl;
				}
				else {
					cout << "The bianry number was too big";
				}
			}
			else {
				cout << "Wrong input" << endl;
			}
			break;
		case 7:
			exit(0);
			break;
		default:
			cout << "Invalid option " + num << endl;
			break;
		}
	}
}

/*main function*/
int main() {
	MainMenu();
	return 0;
}