//
// Created by hasee on 2022/7/2.
//

#include "Camera.h"

namespace Flow {
    void Camera::setTarget(glm::vec3 _target) {
        target = _target;
    }

    void Camera::setPos(glm::vec3 _pos) {
        pos = _pos;
    }

    void Camera::generateVPMatrix(glm::mat4 *_matrix) {
    }

    void Camera::setWH(float _width, float _height) {
        width = _width;
        height = _height;
    }

    void Camera::setNF(float _near, float _far) {
        near = _near;
        far = _far;
    }
} // Flow