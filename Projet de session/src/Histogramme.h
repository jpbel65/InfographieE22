#pragma once

#include "ofMain.h"
#include "ofxGrafica.h"

class Histogramme {
public:

    // void setup(ofImage p_img);
	void draw();

	ofxGPlot plot;
	ofImage img;
	ofImage gradient;
	vector<ofxGPoint> redHistPoints;
	ofPoint imgPos;
	ofRectangle rect;
	void calculateHistograms(ofImage p_img);
};
