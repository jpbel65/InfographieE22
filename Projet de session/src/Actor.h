#pragma once

#include "Object.h"
#include <list>
#include <stack>
#include <glm/glm.hpp>

/* Composite Actor. 
*  Actor est une classe de base pour cr�er une arboressance de transformation
*/
class Actor : public Object
{
	std::stack<glm::mat4> redoTransformStack;
protected:

public:
	glm::mat4 transformHeritage;		  // Transformation courante du parent
	Actor *parent;
	std::list<Actor*> childrens;
	std::stack<glm::mat4> transformStack; // Transformations de l'objet
	

	Actor(float x= 0.0f, float y=0.0f, float z=0.0f, float w=1.0f);
	~Actor();

	void adopt(Actor *newChild);
	void transform(glm::mat4 matrix);
	glm::vec4 applyTransform(glm::vec4 point);
	void undoTransform();
	void redoTransform();
	virtual void draw() = 0;
};

