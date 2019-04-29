// IFT3100H19_CameraTransform/main.cpp
// Exemple d'une scène avec différentes caméras interactives.

#include "ofMain.h"
#include "application.h"

int main()
{
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	ofGLWindowSettings windowSettings;
	windowSettings.setSize(1024, 512);
	windowSettings.setGLVersion(3, 3);
	ofCreateWindow(windowSettings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
  ofRunApp(new Application());
}
