#pragma once

#include <glm/glm.hpp>

class CoordinateSystem {
public :
    static glm::vec4 cartesian2Cylindrical(glm::vec4 position);
    static glm::vec4 cylindrical2Cartesian(glm::vec4 position);

};