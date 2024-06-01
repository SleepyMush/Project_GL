#pragma once
#include <tinyobjloader/tiny_obj_loader.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace Model {
	std::vector<float> load_model_from_file(const char* filename, glm::mat4 transform);
}