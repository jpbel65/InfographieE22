#pragma once

#include "Object.h"
#include <list>
#include "vec.h"
#include <stack>
#include <glm/glm.hpp>

/* Composite Actor. 
*  Actor est une classe de base pour créer une arboressance de transformation
*/
class Actor : Object
{
	std::stack<glm::mat4> redoTransformStack;
protected:
	glm::mat4 transformHeritage;		  // Transformation courante du parent
public:
	Actor *parent;
	std::list<Actor*> childrens;
	std::stack<glm::mat4> transformStack; // Transformations de l'objet
	

	Actor(float x= 0.0f, float y=0.0f, float z=0.0f, float w=1.0f);
	Actor();
	~Actor();

	void adopt(Actor *newChild);
	void transform(glm::mat4 matrix);
	glm::vec4 applyTransform(glm::vec4 point);
	void undoTransform();
	void redoTransform();
};

