#include "Actor.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "ofMain.h"

Actor::Actor(float x, float y, float z, float w) {
	parent = nullptr;
	glm::mat4 origin(1.0);
	//origin[0].w = x;
	//origin[1].w = y;
	//origin[2].w = z;
	//origin[3].w = w;
	transform(origin);
	transformHeritage = glm::mat4(1.0f);
}


Actor::~Actor()
{
}

void Actor::adopt(Actor *newChild) {
	childrens.emplace_back(newChild);
	newChild->parent = this;
	newChild->transformHeritage = this->transformStack.top() * transformHeritage;
}

void Actor::transform(glm::mat4 matrix) {
	//ofLog() << "========================";
	//ofLog() <<  this->transformStack.empty();
	if (! this->transformStack.empty()) {
		//ofLog() << "matrix arg : \n" << matrix << std::endl << "===";
		//ofLog() << "matrix before : \n" << this->transformStack.top() << std::endl << "===";
		//ofLog() << "matrix stacked : \n" << matrix * this->transformStack.top() << std::endl << "===";
		this->transformStack.push(matrix * this->transformStack.top());
	}
	else {
		this->transformStack.push(matrix);
	}

	for (auto child = childrens.cbegin(); child != childrens.cend(); ++child) {
		(*child)->transformHeritage = transformHeritage * this->transformStack.top();
	}
}

glm::vec4 Actor::applyTransform(glm::vec4 point) {
	if (this->parent != nullptr) {
		glm::mat4 tmp = (this->transformStack.top() * transformHeritage);
		//ofLog() << "intermediate matrix transform : " << glm::to_string(tmp);
		return point * tmp;
	}
	else {
		//ofLog() << "direct applied matrix : " << this->transformStack.top();
		//ofLog() << "point : " << glm::to_string(point) << " * matrix = " << glm::to_string(point * this->transformStack.top());

		return point * this->transformStack.top();
	}
}

void Actor::undoTransform() {
	redoTransformStack.push(transformStack.top());
	transformStack.pop();
}

void Actor::redoTransform() {
	transformStack.push(redoTransformStack.top());
	redoTransformStack.pop();
}