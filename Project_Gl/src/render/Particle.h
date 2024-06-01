#pragma once
#include <glad/glad.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <iostream>
#include <vector>

class Particle {
public:
	Particle() {};
	Particle(const glm::vec3& position, const glm::vec3& oreintation, const glm::vec3& scale, const glm::vec4& color);


	glm::mat4 getM()const { return matrix; };

	bool update(const float deltatime);

	glm::vec4 getcolor() const { return m_color; };
	void setcolor(const glm::vec4& color);

	glm::vec3 getposition() const { return m_position; };
	void setposition(const glm::vec3& position);

	glm::vec3 getorientation() const { return m_orientation; };
	void setorientation(const glm::vec3& oreintation);

	glm::vec3 getscale() const { return m_scale; };
	void setscale(const glm::vec3& scale);

private:
	glm::vec3 m_position = glm::vec3(0, 0, 0);
	glm::vec3 m_orientation = glm::vec3(0, 0, 0);
	glm::vec3 m_scale = glm::vec3(0, 0, 0);
	glm::vec4 m_color = glm::vec4(0, 0, 0, 0);

	glm::mat4 matrix = glm::mat4(1.0f);
	bool transformchange = false;

};


