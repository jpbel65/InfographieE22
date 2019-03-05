#include "Object.h"

std::map<UUID, Object*> Object::ids;

Object::Object() {
	UUID* tmp = &id;
	id = *tmp;
	Object::ids.insert(std::pair<UUID, Object*>(id, this));
}
Object::~Object() {
	ids.erase(id);
}

Object* Object::findID(UUID objectID) {
	auto it = ids.find(objectID);
	if (it != ids.end()) {
		return it->second;
	}
	else {
		return nullptr;
	}
}

UUID Object::getID() {
	return id;
}