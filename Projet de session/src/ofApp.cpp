#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Session Project");

	ofLog() << "<app::setup>";

	renderer.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

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
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	renderer.mouse_current_x = x;
	renderer.mouse_current_y = y;
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
