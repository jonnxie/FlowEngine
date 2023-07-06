//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_CAMERA_H
#define FLOWENGINE_CAMERA_H

#include "Macro/Macro.h"
#include "glm.hpp"
#include <gtc/matrix_transform.hpp>

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
        void setFovy(float _fovy);
        void setCameraMode(CameraMode _mode);
    public:
        void move(glm::vec3 _movement);
        void rotate(glm::vec3 _center, glm::vec3 _axis, float _angle);
    private:
        void generateVPMatrix(glm::mat4* _matrix);
    private:
        glm::vec3 target{};
        glm::vec3 pos{};
        glm::vec3 up{};
        float near, far;
        float width, height;
        float fovy = glm::radians(45.0f);
        CameraMode mode{};
    };

} // Flow

#endif //FLOWENGINE_CAMERA_H
