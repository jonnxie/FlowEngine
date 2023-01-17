//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_VERTEX_H
#define FLOWENGINE_VERTEX_H

#include "glm.hpp"
#include <iostream>

namespace Flow {

    struct Point{
        glm::dvec3 pos;
    };

    template<class V = Point>
    void setVertex(V* _vertex, glm::dvec3 _pos)
    {
        if constexpr(std::is_same_v<Point, V>)
        {
            Point* p = _vertex;
            p->pos = _pos;
        }
    }

    template<class V = Point>
    void debugVertex(V* _vertex)
    {
        if constexpr(std::is_same_v<Point, V>)
        {
            Point* p = _vertex;
            std::cout << "x: " << p->pos.x << " y: "<< p->pos.y << " z: "<< p->pos.z << std::endl;
        }
    }




} // Flow

#endif //FLOWENGINE_VERTEX_H
