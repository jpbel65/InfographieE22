#include "test.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <iostream>

Test::Test(){

    c0 = Circle(glm::vec4(0.0, 0.0, 0.0, 1.0), 0.1*255);
    c1 = Circle(glm::vec4(0.0, 0.0, 0.0, 1.0), 0.1*255);
    translate = glm::transpose( glm::translate(glm::mat4(1.0), 2*glm::vec3(255, 255, 255)) );
    rotate = glm::rotate(glm::mat4(1.0), 3.1415f/100, glm::vec3(0.0,0.0,1.0));
    scale = glm::scale(glm::mat4(1.0), glm::vec3(255.0,255.0,255.0));
}