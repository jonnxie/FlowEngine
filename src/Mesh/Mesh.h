//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_MESH_H
#define FLOWENGINE_MESH_H

#include <vector>
#include <cstdint>
#include "Vertex.h"

namespace Flow {

    class Mesh {
    public:

    private:

    };

    template<typename V>
    class IndexMesh : public Mesh{
    public:
        std::vector<V> vertices{};
        std::vector<uint32_t> indices{};
    };

    template<typename V>
    class Quad : public IndexMesh<V>{
    public:
        Quad(double size = 1.0f);
    };

    template<typename V>
    Quad<V>::Quad(double size) {
        IndexMesh<V>::vertices.resize(4);
        IndexMesh<V>::indices = {0, 1, 2, 0, 0, 2, 3};
        double half_size = size / 2.0;
        setVertexPosition<V>(&IndexMesh<V>::vertices[0], glm::dvec3(-half_size, -half_size, 0.0f));
        setVertexPosition<V>(&IndexMesh<V>::vertices[1], glm::dvec3(half_size, -half_size, 0.0f));
        setVertexPosition<V>(&IndexMesh<V>::vertices[2], glm::dvec3(half_size, half_size, 0.0f));
        setVertexPosition<V>(&IndexMesh<V>::vertices[3], glm::dvec3(-half_size, half_size, 0.0f));

        setVertexNormal<V>(&IndexMesh<V>::vertices[0], glm::dvec3(0, 0, 1.0f));
        setVertexNormal<V>(&IndexMesh<V>::vertices[1], glm::dvec3(0, 0, 1.0f));
        setVertexNormal<V>(&IndexMesh<V>::vertices[2], glm::dvec3(0, 0, 1.0f));
        setVertexNormal<V>(&IndexMesh<V>::vertices[3], glm::dvec3(0, 0, 1.0f));
    }

} // Flow

#endif //FLOWENGINE_MESH_H
