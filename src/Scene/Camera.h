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
    private:
        glm::vec3 target{};
        glm::vec3 pos{};
        CameraMode mode{};
    };

} // Flow

#endif //FLOWENGINE_CAMERA_H
