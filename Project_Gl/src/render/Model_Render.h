#pragma once
#include <tinyobjloader/tiny_obj_loader.h>
#include "Model_Loader.h"
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

struct Meshinfo
{
	const char* filename;
	glm::mat4 transform;
};

class Mesh
{
public:
	unsigned int VAO, VBO, vertexcount;
	Mesh(Meshinfo* meshinfo);
	~Mesh();
};