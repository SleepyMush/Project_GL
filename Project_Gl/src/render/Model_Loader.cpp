#include "Model_Loader.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include <tinyobjloader/tiny_obj_loader.h>

std::vector<float> Model::load_model_from_file(const char* filename, glm::mat4 ptransform)
{
    std::vector<float> vertices;

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warning, error;
    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warning, &error, filename)) {
        std::cout << warning << error << '\n';
    }

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            glm::vec4 pos = {
            attributes.vertices[3 * index.vertex_index],
            attributes.vertices[3 * index.vertex_index + 1],
            attributes.vertices[3 * index.vertex_index + 2],
            1
            };
            pos = ptransform * pos;

            glm::vec3 normal = {
              attributes.normals[3 * index.normal_index],
              attributes.normals[3 * index.normal_index + 1],
              attributes.normals[3 * index.normal_index + 2],
            };

            normal = glm::normalize(glm::mat3(ptransform) * normal);


            glm::vec2 texture_coord = {
              attributes.texcoords[2 * index.texcoord_index],
              attributes.texcoords[2 * index.texcoord_index + 1],
            };

            vertices.push_back(pos.x);
            vertices.push_back(pos.y);
            vertices.push_back(pos.z);
            vertices.push_back(texture_coord.x);
            vertices.push_back(texture_coord.y);
            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);
        }
    }

    for (const auto& material : materials) {

    }

    return vertices;
}


