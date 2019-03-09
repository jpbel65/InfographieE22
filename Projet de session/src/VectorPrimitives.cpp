#include "VectorPrimitives.h"
#include "ofMain.h"
#include <iostream>
#include <glm/ext.hpp>
#include <math.h>
#include "CoordinateSystem.h"

    VectorPrimitives::VectorPrimitives(float x, float y, float z, float w) : Actor(x,y,z,w){

    }

    glm::vec4 VectorPrimitives::getCylindricalPosition(int index){
        glm::vec4 position = getPosition(index);
        return CoordinateSystem::cartesian2Cylindrical(position);

    }

    glm::vec4 VectorPrimitives::getCylindricalRelativePosition(int index){
        glm::vec4 relative = getRelativePosition(index);
        ofLog() << relative;
        return relative = CoordinateSystem::cartesian2Cylindrical(relative);
    }

    glm::vec4 VectorPrimitives::getPosition(int index){
        return applyTransform(points[index]);
    }

    glm::vec4 VectorPrimitives::getRelativePosition(int index){
        if(parent != nullptr){

            glm::vec4 relative = getPosition(index);
	        glm::vec4 posC0 = ((VectorPrimitives *) parent)->getPosition(0);
	        relative.x -= posC0.x;
	        relative.y -= posC0.y;
            return relative;
        } else {
            glm::vec4 relative = getPosition(index);
	        glm::vec4 posC0 = getPosition(0);
	        relative.x -= posC0.x;
	        relative.y -= posC0.y;
            return relative;
        }
    }


    Circle::Circle(glm::vec4 origin, float radius) : VectorPrimitives(origin.x, origin.y, origin.z, origin.w){
        points.push_back(glm::vec4(0.0,0.0,0.0,1.0));
        this->radius = radius;
        //ofLog() << "Origin : x" << origin.x << " y " << origin.y << " z " << origin.y << " w " << origin.w;
    }

    Circle::Circle(){

    }

    Circle::~Circle(){


    }

    void Circle::draw(){
        glm::vec4 transformed = points[0];
        //ofLog() << "Input : x " << transformed.x << " y " << transformed.y << " z " << transformed.z;
        transformed = this->applyTransform(transformed);
        ofDrawEllipse(transformed.x, transformed.y, radius, radius);
        //ofLog() << "Output : x " << transformed.x << " y " << transformed.y << " z " << transformed.z;

        //ofLog() << "Matrix : " << glm::to_string(this->transformHeritage);
    }