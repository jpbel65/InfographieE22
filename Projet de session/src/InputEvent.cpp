#include "InputEvent.h"

InputEvent* InputEvent::instance = nullptr;

InputEvent::InputEvent()
{
}



InputEvent::~InputEvent()
{
}


//--------------------------------------------------------------
void InputEvent::onKeyPressed(int key, Function function) {
	std::pair<int, Function> pair(key, function);
	keyPressed.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onKeyReleased(int key, Function function) {
	std::pair<int, Function> pair(key, function);
	keyReleased.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onMouseMoved(Function function) {
	std::pair<int, Function> pair(0, function);
	mouseMoved.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onMouseDragged(int button, Function function) {
	std::pair<int, Function> pair(button, function);
	mouseDragged.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onMousePressed(int button, Function function) {
	std::pair<int, Function> pair(button, function);
	mousePressed.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onMouseReleased(int button, Function function) {
	std::pair<int, Function> pair(button, function);
	mouseReleased.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onMouseEntered(Function function) {
	std::pair<int, Function> pair(0, function);
	mouseEntered.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onMouseExited(Function function) {
	std::pair<int, Function> pair(0, function);
	mouseExited.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::onWindowResized(Function function) {
	std::pair<int, Function> pair(0, function);
	windowResized.insert(pair);
}

//--------------------------------------------------------------
void InputEvent::updateKeyPressed(int key) {
	this->keyState[key] = KEY_PRESSED;
	caller(&keyPressed, key);
}

//--------------------------------------------------------------
void InputEvent::updateKeyReleased(int key) {
	this->keyState[key] = KEY_RELEASED;
	caller(&keyReleased, key);
}

//--------------------------------------------------------------
void InputEvent::updateMouseMoved(int x, int y) {
	this->mousePosition.x = x;
	this->mousePosition.y = y;
	caller(&mouseMoved, 0);
}

//--------------------------------------------------------------
void InputEvent::updateMouseDragged(int x, int y, int button) {
	this->mousePosition.x = x;
	this->mousePosition.y = y;
	caller(&mouseDragged, button);
}

//--------------------------------------------------------------
void InputEvent::updateMousePressed(int x, int y, int button) {
	this->mousePosition.x = x;
	this->mousePosition.y = y;
	this->mouseButtonState[button] = MOUSE_PRESSED;
	caller(&mousePressed, button);
}

//--------------------------------------------------------------
void InputEvent::updateMouseReleased(int x, int y, int button) {
	this->mousePosition.x = x;
	this->mousePosition.y = y;
	this->mouseButtonState[button] = MOUSE_RELEASED;
	caller(&mouseReleased, button);
}

//--------------------------------------------------------------
void InputEvent::updateMouseEntered(int x, int y) {
	this->mousePosition.x = x;
	this->mousePosition.y = y;
	caller(&mouseEntered, 0);
}

//--------------------------------------------------------------
void InputEvent::updateMouseExited(int x, int y) {
	this->mousePosition.x = x;
	this->mousePosition.y = y;
	caller(&mouseExited, 0);
}

//--------------------------------------------------------------
void InputEvent::updateWindowResized(int w, int h) {
	this->windowSize.w = w;
	this->windowSize.h = h;
	caller(&windowResized, 0);
}

void InputEvent::caller(std::unordered_multimap<int, Function> *mapToCall, int keyToCall) {
	auto range = mapToCall->equal_range(keyToCall);
	if (range.first != range.second) {
		for (auto it = range.first; it != range.second; ++it)
		{
			Function functionStruct = it->second;
			functionStruct.function(functionStruct.param);
		}
	}
}

//--------------------------------------------------------------
//void onGotMessage(ofMessage msg);

//--------------------------------------------------------------
//void onDragEvent(ofDragInfo dragInfo);

InputEvent* InputEvent::getInstance() {
	if (instance == nullptr) {
		instance = new InputEvent();
	}

	return instance;
}