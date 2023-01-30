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

    struct Normal{
        glm::dvec3 dir;
    };

    template<class V = Point>
    void setVertexPosition(V* _vertex, glm::dvec3 _pos)
    {
        if constexpr(std::is_base_of_v<Point, V>)
        {
            Point* p = _vertex;
            p->pos = _pos;
        }
    }

    template<class N = Normal>
    void setVertexNormal(N* _vertex, glm::dvec3 _dir)
    {
        if constexpr(std::is_base_of_v<Normal, N>)
        {
            Normal* p = _vertex;
            p->dir = _dir;
        }
    }

    template<class V = Point>
    void debugVertexPosition(V* _vertex)
    {
        if constexpr(std::is_base_of_v<Point, V>)
        {
            Point* p = _vertex;
            std::cout << "x: " << p->pos.x << " y: "<< p->pos.y << " z: "<< p->pos.z << std::endl;
        }
    }

    template<class N = Normal>
    void debugVertexNormal(N* _vertex)
    {
        if constexpr(std::is_base_of_v<Normal, N>)
        {
            Normal* p = _vertex;
            std::cout << "x: " << p->dir.x << " y: "<< p->dir.y << " z: "<< p->dir.z << std::endl;
        }
    }



} // Flow

#endif //FLOWENGINE_VERTEX_H
