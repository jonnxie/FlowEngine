#ifndef FLOWENGINE_MATH_H
#define FLOWENGINE_MATH_H

#include "glm.hpp"


namespace Flow {

class Math{
    public:
        static glm::mat4 generateRoateMatrix(glm::vec3 _center, glm::vec3 _axis, float _angle);
};

}

#endif //FLOWENGINE_CAMERA_H
