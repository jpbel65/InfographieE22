#include "Actor.h"
#include <glm/glm.hpp>

Actor::Actor(float x, float y, float z, float w) {
	parent = nullptr;
	glm::mat4 origin(1.0);
	origin[0][3] = x;
	origin[1][3] = y;
	origin[2][3] = z;
	origin[3][3] = w;
	transform(origin);
	transformHeritage = glm::mat4(1.0f);
}

Actor::Actor()
{
	parent = nullptr;
	glm::mat4 origin(1.0);
	transform(origin);
	transformHeritage = glm::mat4(1.0f);
}


Actor::~Actor()
{
}

void Actor::adopt(Actor *newChild) {
	childrens.emplace_back(newChild);
}

void Actor::transform(glm::mat4 matrix) {
	if (! this->transformStack.empty()) {
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
		return this->transformStack.top() * transformHeritage * point;
	}
	else {
		return this->transformStack.top() * point;
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