#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Session Project");

	ofLog() << "<app::setup>";

	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	renderer.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	renderer.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	renderer.is_mouse_button_pressed = true;
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
	renderer.mouse_press_x = x;
	renderer.mouse_press_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	renderer.is_mouse_button_pressed = false;

	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;

	if (renderer.text_fonction == "2.3")renderer.add_PVector();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

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
