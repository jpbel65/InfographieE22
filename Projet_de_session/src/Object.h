#pragma once

#include <list>

class Object
{
public:
	std::list<Object*> childrens;

	Object();
	~Object();
};

