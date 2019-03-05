#pragma once

#include <list>
#include <vector>
#include <map>
#include <string>

typedef int* UUID;

class Object
{
	// pointeur unique comme id
	UUID id;
protected:
	static std::map<UUID, Object*> ids;
public:
	std::list<Object*> childrens;
	

	Object();
	~Object();


	static Object* findID(UUID objectID);
	UUID getID();
};

