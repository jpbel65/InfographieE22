#include "Histogramme.h"

void Histogramme::calculateHistograms(ofImage p_img) {
    img = p_img;
	gradient.load("gradientBW.png"); 
	vector<int> Hist(256, 0);
	int counter = 0;
    vector<ofxGPoint> points;

	for (int x = 0; x < img.getWidth(); x++) {
		for (int y = 0; y < img.getHeight(); y++) {
			ofColor c = img.getColor(x, y);
            int grey = (c.r + c.g + c.b) / 3;
			Hist[grey]++;
			++counter;
		}
	}

    points.clear();

    for(size_t i = 0; i < Hist.size(); i++)
    {
        points.emplace_back(i, Hist[i]);
    }

	// Set the plot title and the axis labels
	plot.setTitleText("Histogramme");

	// Add the points
    plot.setPoints(points);
}

void Histogramme::draw() {
	plot.setPos(ofGetWindowWidth() - 430, 5);
    plot.beginDraw();
	plot.drawTitle();
    plot.drawBox();
    plot.drawLines();
	plot.drawHistograms();
    plot.endDraw();
	gradient.draw(ofGetWindowWidth() - 334, 220, 295, 10);
}
