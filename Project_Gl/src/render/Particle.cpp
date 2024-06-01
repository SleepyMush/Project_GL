#include "Particle.h"

void Particle::particle(const glm::vec3& position, const glm::vec3& oreintation, const glm::vec3& scale, const glm::vec4& color)
{
	m_position = position;
	m_orientation = oreintation;
	m_scale = scale;
	transformchange = true;
	m_color = color;
}

void Particle::setposition(const glm::vec3& position)
{
	if (position != m_position) {
		m_position = position;
		transformchange = true;
	}

}

void Particle::setorientation(const glm::vec3& oreintation)
{
	if (oreintation != m_orientation) {
		m_orientation = oreintation;
		transformchange = true;
	}
}

void Particle::setscale(const glm::vec3& scale)
{
	if (scale != m_scale) {
		m_scale = scale;
		transformchange = true;
	}
}

void Particle::setcolor(const glm::vec4& color) {
	m_color = color;
}

bool Particle::update(const float deltatime)
{
	if (transformchange) {
		matrix = translate(glm::mat4(1.0f), m_position) * glm::eulerAngleXYZ(m_orientation.x, m_orientation.y, m_orientation.z) * glm::scale(glm::mat4(1.0f), m_scale);
		transformchange = false;
		return true;
	}
	return false;
}



