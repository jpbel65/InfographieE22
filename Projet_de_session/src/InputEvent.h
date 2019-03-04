#pragma once

#define KEY_RELEASED 0
#define KEY_PRESSED 1
#define MOUSE_RELEASED 0
#define MOUSE_PRESSED 1
#define ANY 1025



#include <unordered_map>

typedef struct Function {
	void(*function)(void *);
	void *param;
} Function;

// singleton event handler
class InputEvent
{

	InputEvent();
	static InputEvent *instance;
	std::unordered_multimap<int, Function> keyPressed;
	std::unordered_multimap<int, Function> keyReleased;

	std::unordered_multimap<int, Function> mouseMoved;
	std::unordered_multimap<int, Function> mouseDragged;
	std::unordered_multimap<int, Function> mousePressed;
	std::unordered_multimap<int, Function> mouseReleased;
	std::unordered_multimap<int, Function> mouseEntered;
	std::unordered_multimap<int, Function> mouseExited;

	std::unordered_multimap<int, Function> windowResized;

public:
	int keyState[1024] = { KEY_RELEASED };
	int mousePadState[256] = { MOUSE_RELEASED };
	int mouseButtonState[256] = { MOUSE_RELEASED };
	struct MousePosition { int x; int y; } mousePosition;
	struct WindowSize { int w; int h; } windowSize;
	

	//--------------------------------------------------------------
	void onKeyPressed(int key, Function function);

	//--------------------------------------------------------------
	void onKeyReleased(int key, Function function);

	//--------------------------------------------------------------
	void onMouseMoved(Function function);

	//--------------------------------------------------------------
	void onMouseDragged(int button, Function function);

	//--------------------------------------------------------------
	void onMousePressed(int button, Function function);

	//--------------------------------------------------------------
	void onMouseReleased(int button, Function function);

	//--------------------------------------------------------------
	void onMouseEntered(Function function);

	//--------------------------------------------------------------
	void onMouseExited(Function function);

	//--------------------------------------------------------------
	void onWindowResized(Function function);

	//--------------------------------------------------------------
	void updateKeyPressed(int key);

	//--------------------------------------------------------------
	void updateKeyReleased(int key);

	//--------------------------------------------------------------
	void updateMouseMoved(int x, int y);

	//--------------------------------------------------------------
	void updateMouseDragged(int x, int y, int button);

	//--------------------------------------------------------------
	void updateMousePressed(int x, int y, int button);

	//--------------------------------------------------------------
	void updateMouseReleased(int x, int y, int button);

	//--------------------------------------------------------------
	void updateMouseEntered(int x, int y);

	//--------------------------------------------------------------
	void updateMouseExited(int x, int y);

	//--------------------------------------------------------------
	void updateWindowResized(int w, int h);

	void caller(std::unordered_multimap<int, Function> *mapToCall, int keyToCall);

	//--------------------------------------------------------------
	//void onGotMessage(ofMessage msg);

	//--------------------------------------------------------------
	//void onDragEvent(ofDragInfo dragInfo);

	static InputEvent *getInstance(); //singleton
	~InputEvent();
};


