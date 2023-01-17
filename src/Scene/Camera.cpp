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
        glm::mat4 view = glm::lookAt(pos, target, up);
        glm::mat4 proj;
        if (mode == CameraMode::Perspective)
        {
            float aspect = width / height;
            float reverse_aspect = 1.0f / aspect;
            proj = glm::perspective(fovy, aspect, near, far);
        } else {
            proj = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, near, far);
        }
        proj[1][1] *= -1;
        *_matrix = proj * view;
    }

    void Camera::setWH(float _width, float _height) {
        width = _width;
        height = _height;
    }

    void Camera::setNF(float _near, float _far) {
        near = _near;
        far = _far;
    }


    void Camera::setCameraMode(CameraMode _mode) {
        mode = _mode;
    }

    void Camera::setFovy(float _fovy) {
        fovy = _fovy;
    }

} // Flow