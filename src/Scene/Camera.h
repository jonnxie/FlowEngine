//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_CAMERA_H
#define FLOWENGINE_CAMERA_H

#include "Macro/Macro.h"
#include "glm.hpp"

namespace Flow {

    enum class CameraMode{
        Perspective,
        Orthographic
    };

    class Camera {
    public:
        Camera() = default;
    public:
        void setTarget(glm::vec3 _target);
        void setPos(glm::vec3 _pos);
        void setNF(float _near, float _far);
        void setWH(float _width, float _height);
    private:
        void generateVPMatrix(glm::mat4* _matrix);
    private:
        glm::vec3 target{};
        glm::vec3 pos{};
        float near, far;
        float width, height;
        CameraMode mode{};
    };

} // Flow

#endif //FLOWENGINE_CAMERA_H
