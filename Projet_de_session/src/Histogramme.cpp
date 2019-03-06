#include "Histogramme.h"


// void Histogramme::setup(ofImage p_img) {
//     int nPoints = 100;
// 	vector<ofxGPoint> points;

// 	for (int i = 0; i < nPoints; ++i) {
// 		points.emplace_back(i, 10 * ofNoise(0.1 * i));
// 	}

// 	// Set the plot position on the screen
// 	plot.setPos(25, 25);

// 	// Set the plot title and the axis labels
// 	plot.setTitleText("A very simple example");
// 	plot.getXAxis().setAxisLabelText("x axis");
// 	plot.getYAxis().setAxisLabelText("y axis");

// 	// Add the points
//     plot.setPoints(points);
// }

void Histogramme::calculateHistograms(ofImage p_img) {
    img = p_img;
	// Calculate the color histograms
	vector<int> Hist(255, 0);
	// int xStart = ofClamp(rect.getX() - imgPos.x, 0, img.getWidth());
	// int yStart = ofClamp(rect.getY() - imgPos.y, 0, img.getHeight());
	// int xEnd = ofClamp(rect.getX() + rect.getWidth() - imgPos.x, 0, img.getWidth());
	// int yEnd = ofClamp(rect.getY() + rect.getHeight() - imgPos.y, 0, img.getHeight());
	int counter = 0;
    vector<ofxGPoint> points;

	for (int x = 0; x < img.getWidth(); ++x) {
		for (int y = 0; y < img.getHeight(); ++y) {
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
    

    plot.setPos(25, 25);

	// Set the plot title and the axis labels
	plot.setTitleText("A very simple example");
	plot.getXAxis().setAxisLabelText("x axis");
	plot.getYAxis().setAxisLabelText("y axis");

	// Add the points
    plot.setPoints(points);
}

void Histogramme::draw() {
    plot.beginDraw();
    plot.drawBox();
    plot.drawLines();
	plot.drawHistograms();
    plot.endDraw();
}
