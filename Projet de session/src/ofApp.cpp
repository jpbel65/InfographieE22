#include "ofApp.h"
#include "InputEvent.h"

// fonction exemple
void pr(void *param) {
	InputEvent *event = InputEvent::getInstance();
	ofLog() << "x : " << event->mousePosition.x << ", y : " << event->mousePosition.y << std::endl;
};

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Session Project");

	ofLog() << "<app::setup>";

    //exemple d'initialisation d'event
	InputEvent *event = InputEvent::getInstance();
	Function f;
	f.function = pr;
	f.param = this;
	event->onMouseMoved(f);

	renderer.setup();

}

//--------------------------------------------------------------
void ofApp::update(){

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

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    event->updateKeyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    event->updateKeyReleased(key);
	ofLog() << "<app::keyReleased: " << key << ">";

	// valider si la touche du clavier est la barre d'espacement (spacebar)
	if (key == ' ') renderer.image_export("render", "png"); //Export Classique vient exemple plus pauffinage
    else if(key == 'z'){
        renderer.appMode = "drawing";
    }
    else if(key == 'x'){
        renderer.appMode = "normal";
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    event->updateMouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    event->updateMouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    event->updateMousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    event->updateMouseReleased(x, y, button);
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
