//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_MESH_H
#define FLOWENGINE_MESH_H

#include <vector>
#include <cstdint>

namespace Flow {

    class Mesh {
    public:

    private:

    };

    template<typename V>
    class IndexMesh : public Mesh{
    private:
        std::vector<V> vertices;
        std::vector<uint32_t> indices;
    };

    template<typename V>
    class Quad : public IndexMesh<V>{
    public:
        Quad(double size = 1.0f);
    };

} // Flow

#endif //FLOWENGINE_MESH_H
