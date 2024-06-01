#include "Model_Render.h"

Mesh::Mesh(Meshinfo* meshinfo)
{
	std::vector<float> vertices = Model::load_model_from_file(meshinfo->filename, meshinfo->transform);
	vertexcount = int(vertices.size()) / 8;
	glCreateBuffers(1, &VBO);
	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
	glNamedBufferStorage(VBO, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	glEnableVertexArrayAttrib(VAO, 2);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0,0);
	glVertexArrayAttribBinding(VAO, 1,0);
	glVertexArrayAttribBinding(VAO, 2,0);

	//GL_DYNAMIC_STORAGE_BIT
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
