#pragma once

#include "Actor.h"
#include <vector>
#include <glm/glm.hpp>

class VectorPrimitives : public Actor {

public :

    std::vector<glm::vec4> points;
    VectorPrimitives(float x=0.0, float y=0.0, float z=0.0, float w=1.0);
    virtual void draw() = 0;

    glm::vec4 getPosition(int index);
    glm::vec4 getRelativePosition(int index);
    glm::vec4 getCylindricalPosition(int index);
    glm::vec4 getCylindricalRelativePosition(int index);
    glm::vec4& operator[](int index){return points[index];};

};

class Circle : public VectorPrimitives {

public :
    float radius;
    Circle(glm::vec4 origin, float radius);
    Circle();
    ~Circle();
    virtual void draw();

};