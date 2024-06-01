#include "../src/core/Window.h"
#include "../src/render/Shader.h"
#include "../src/render/Camera.h"
#include "../src/render/Texture.h"
#include "../src/render/Model_Render.h"
#include "../src/render/Particle_System.h"
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texcoords;
};
GLuint VBO, VAO, EBO;
std::vector<Vertex> vertices(24);

Window window;
Shader shader;
Shader instance;
Texture texture;
Meshinfo meshinfo;
Mesh* Import_Model;
Particle_system p;

void process_input(GLFWwindow* window);
void cleanup();
void Update(const float deltatime);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = window.screen_width / 2.0f;
float lastY = window.screen_height / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float LO = -2.0f;
float HI = 2.0f;

float Low = 0.0f;
float high = 0.256f;

void InitalizeParticle()
{
	//p.particle.push_back(p.m_particles);
	float r3 = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
	float r4 = LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
	glm::vec3 random_output = glm::vec3(r3, 1, r4);

	std::default_random_engine generator(std::random_device{}());
	std::uniform_real_distribution<float> distribution(Low, high);
	float r = distribution(generator); // Red component
	float g = distribution(generator); // Green component
	float b = distribution(generator); // Blue component
	float a = distribution(generator); // Alpha component
	glm::vec4 randomColor = glm::vec4(r, g, b, a);

	p.particle.particle(random_output, random_output, glm::vec3(1, 1, 1), randomColor);

};


int main()
{
	window.init();

	shader.load("res/Shader/shader.vert", "res/Shader/shader.frag");
	instance.load("res/Shader/particle.vert", "res/Shader/particle.frag");
	texture.loadtexture("res/Texture/NumGrid_ALB.png");

	//Mesh
	meshinfo.filename = "res/model/Teapot.obj";
	meshinfo.transform = 0.1f * glm::mat4(1.0);
	Import_Model = new Mesh(&meshinfo);

	//Front
	vertices[0] = { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) };
	vertices[1] = { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f) };
	vertices[2] = { glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 0.0f) };
	vertices[3] = { glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 0.0f) };

	// Back face
	vertices[4] = { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 1.0f) };
	vertices[5] = { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 1.0f) };
	vertices[6] = { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f) };
	vertices[7] = { glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f) };

	// Top face
	vertices[8] = { glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f) };
	vertices[9] = { glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f) };
	vertices[10] = { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f) };
	vertices[11] = { glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.0f, 0.0f) };

	// Bottom face
	vertices[12] = { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) };
	vertices[13] = { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f) };
	vertices[14] = { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.0f, 0.0f) };
	vertices[15] = { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) };

	// Left face
	vertices[16] = { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) };
	vertices[17] = { glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f) };
	vertices[18] = { glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f) };
	vertices[19] = { glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) };

	// Right face
	vertices[20] = { glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) };
	vertices[21] = { glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f) };
	vertices[22] = { glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.0f, 0.0f) };
	vertices[23] = { glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) };

	std::vector<unsigned int> indices = {
		// Front face
		0, 1, 2,
		0, 2, 3,

		// Back face
		4, 5, 6,
		4, 6, 7,

		// Top face
		8, 9, 10,
		8, 10, 11,

		// Bottom face
		12, 13, 14,
		12, 14, 15,

		// Left face
		16, 17, 18,
		16, 18, 19,

		// Right face
		20, 21, 22,
		20, 22, 23,
	};

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices), indices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	//Texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoords));
	glEnableVertexAttribArray(1);

	texture.bind(0);

	InitalizeParticle();

	while (!glfwWindowShouldClose(window))
	{
		process_input(window);
		glfwPollEvents();

		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//Render
		glClearColor(0.6f, 0.3f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//cube
		shader.use();
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(camera.Zoom), (float)window.screen_width/ (float)window.screen_height, 0.1f, 100.0f);
		shader.setMat4("projection", projection);

		view = camera.GetViewMatrix();
		shader.setMat4("view", view);

		shader.setMat4("model", model);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//model
		glBindVertexArray(Import_Model->VAO);
		glDrawArrays(GL_TRIANGLES, 0, Import_Model->vertexcount);

		instance.setMat4("projection", projection);
		instance.setMat4("view", view);
		Update(deltaTime);
		p.DrawParticle(instance.ID, view, projection);
		

		glfwSwapBuffers(window);
	}
	cleanup();
	return 0;
}

void cleanup() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	texture.cleanUp();
	Import_Model->~Mesh();
	glfwTerminate();
}

void Update(const float deltatime)
{
	p.UpdateParticle(deltaTime);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

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
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}



