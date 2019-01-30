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
	ofLog() << "<app::keyReleased: " << key << ">";

	// valider si la touche du clavier est la barre d'espacement (spacebar)
	if (key == ' ') renderer.image_export("render", "png"); //Export Classique vient exemple plus pauffinage
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
	renderer.image_source.load(dragInfo.files.at(0));
	renderer.image_width = renderer.image_source.getWidth();
	renderer.image_height = renderer.image_source.getHeight();
	// redimensionner la fenêtre selon la résolution de l'image
	if (renderer.image_source.getWidth() > 0 && renderer.image_source.getHeight() > 0)
		ofSetWindowShape(renderer.image_source.getWidth() + renderer.offset_horizontal *2 , renderer.image_source.getHeight() + renderer.offset_vertical *2 );
}

void ofApp::exit()
{
	ofLog() << "<app::exit>";
}
