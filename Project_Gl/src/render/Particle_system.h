#pragma once
#include <vector>
#include "Particle.h"

struct VertexInfo
{
	glm::vec3 pos;
};

class Particle_system
{
public:
	std::vector<VertexInfo> vert;
	unsigned int VBO, VAO;

	Particle_system() {};
	~Particle_system();
	void UpdateParticle(const float deltatime);
	void CreateParticle(const glm::vec3& position, const glm::vec3& oreintation, const glm::vec3& scale, const glm::vec4& color);
	void DrawParticle(const unsigned int shaderID, const glm::mat4& view, const glm::mat4& projection);

	Particle particle;
	std::vector<Particle> particles;

private:
	std::vector<Particle> m_particles;
	std::vector<glm::vec4> m_color;
	std::vector < glm::mat4> m_matrix;
};

