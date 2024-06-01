#include "Particle_system.h"

Particle_system particleSystem;

void Particle_system::UpdateParticle(const float deltaTime)
{
	for (int i = 0; i < m_particles.size(); i++) {
		if (m_particles[i].update(deltaTime)) {
			m_matrix[i] = m_particles[i].getM();
		}
	}

}

void Particle_system::CreateParticle(const glm::vec3& position, const glm::vec3& oreintation, const glm::vec3& scale, const glm::vec4& color)
{
	VertexInfo v0;
	VertexInfo v1;
	VertexInfo v2;
	VertexInfo v3;
	v0.pos = glm::vec3(-0.5f, -0.5f, -0.5f);
	v1.pos = glm::vec3(0.5f, -0.5f, -0.5f);
	v2.pos = glm::vec3(0.5f, 0.5f, -0.5f);
	v3.pos = glm::vec3(-0.5f, 0.5f, -0.5f);

	vert.push_back(v0);
	vert.push_back(v1);
	vert.push_back(v3);
	vert.push_back(v1);
	vert.push_back(v2);
	vert.push_back(v3);

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vert.size() * sizeof(VertexInfo), vert.data(), GL_STATIC_DRAW);
	
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (void*)offsetof(VertexInfo, pos));
	glEnableVertexAttribArray(0);

	m_particles.emplace_back(position, oreintation, scale, color);
	m_matrix.emplace_back(1.0f);
	m_color.emplace_back(color);
}

Particle_system::~Particle_system()
{
	glDeleteVertexArrays(1, &particleSystem.VAO);
	glDeleteBuffers(1, &particleSystem.VBO);
}

void Particle_system::DrawParticle(const unsigned int shaderID, const glm::mat4& view, const glm::mat4& projection)
{

	glUniform4fv(glGetUniformLocation(shaderID, "color"),m_color.size(), &m_color[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shaderID, "model"),m_matrix.size(), GL_FALSE, &m_matrix[0][0][0]);

	glBindVertexArray(particleSystem.VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, particleSystem.vert.size(), m_matrix.size());
}
