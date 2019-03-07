#include "CoordinateSystem.h"
#include <glm/glm.hpp>
#include <math.h>

glm::vec4 CoordinateSystem::cartesian2Cylindrical(glm::vec4 position){
    double angle = atan2(position.y, position.x);
    float r = sqrt(pow(position.x, 2) + pow(position.y, 2));
    return glm::vec4(r, (float)(angle + M_PI/2), position.z, position.w);
}

glm::vec4 CoordinateSystem::cylindrical2Cartesian(glm::vec4 position){
    return glm::vec4(position.x*cos(position.y), position.x*sin(position.y), position.z, position.w);
}