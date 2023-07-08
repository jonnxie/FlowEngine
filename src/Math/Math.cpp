#include "Math.h"

glm::mat4 Flow::Math::generateRoateMatrix(glm::vec3 _center, glm::vec3 _axis, float _angle)
{
    glm::mat4 matrix(1.0f);
    matrix[0][3] = _center.x;
    matrix[1][3] = _center.y;
    matrix[2][3] = _center.z;
    return matrix;
}
