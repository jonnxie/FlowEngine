//
// Created by hasee on 2022/7/2.
//

#ifndef FLOWENGINE_TRANSFORM_H
#define FLOWENGINE_TRANSFORM_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtx/quaternion.hpp"

namespace Flow {

    struct Transform {
        Transform() = default;
        Transform(const Transform&) = default;

        glm::vec3 translation = {0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = {0.0f, 0.0f, 0.0f };
        glm::vec3 scale = {1.0f, 1.0f, 1.0f };
        glm::mat4 getMatrix() const {
            return glm::translate(glm::mat4(1.0f), translation)
                   * glm::toMat4(glm::quat(rotation))
                   * glm::scale(glm::mat4(1.0f), scale);
        }
    };

} // Fow

#endif //FLOWENGINE_TRANSFORM_H
