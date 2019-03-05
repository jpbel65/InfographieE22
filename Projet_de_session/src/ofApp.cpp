#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Session Project");

	ofLog() << "<app::setup>";

	event = InputEvent::getInstance();
	renderer.setup();
    
}

//--------------------------------------------------------------
void ofApp::update(){
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();
    
    // if case pour fonction en cours
    if (renderer.appFunction == 0){
        // pas de fonction en particulier
        
    }
    else if (renderer.appFunction == 101){
        
    }
    else if (renderer.appFunction == 102){
        
    }
    else if (renderer.appFunction == 103){
        
    }
    else if (renderer.appFunction == 104){
        
    }
    else{
        ofLog() << "<app::ERROR APPFUNCTION INVALID: " << renderer.appFunction << ">";
    }
    
    // if case pour mode (curseur de l'utilisateur)
    if (renderer.appMode == "normal"){
        ofShowCursor();
        mouseDrawing.clear();
        
        
    }
    else if (renderer.appMode == "drawing"){
        ofHideCursor();
        mouseDrawing.load("cursor_drawing.png");
        mouseDrawing.draw(ofGetMouseX(),ofGetMouseY(),30,30);
        
    }
    else{
        ofLog() << "<app::WARNING APPMODE INVALID: " << renderer.appMode << ">";
    }
}

ofApp::ofApp() {
	//setup();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    event->updateKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    event->updateKeyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    event->updateMouseMoved(x, y);
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    event->updateMouseDragged(x, y, button);
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    event->updateMousePressed(x, y, button);
	renderer.is_mouse_button_pressed = true;
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	renderer.mouse_press_x = x;
	renderer.mouse_press_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    event->updateMouseReleased(x, y, button);
	renderer.is_mouse_button_pressed = false;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	if (renderer.text_fonction == "2.3")renderer.add_PVector();
	if (renderer.text_fonction == "4.2")renderer.Add_forme_vbo();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    event->updateMouseEntered(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    event->updateMouseExited(x, y);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    if (event == nullptr)
	{
		event = InputEvent::getInstance();
	}
	event->updateWindowResized(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	renderer.dragEvent(dragInfo);
}

void ofApp::exit()
{
	ofLog() << "<app::exit>";
}
