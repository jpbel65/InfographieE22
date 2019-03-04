// IFT3100H19_Triptyque/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Renderer
{
public:
	ofxButton ExportBut;
	void Export();
	ofxLabel Lmport;
    
    // différent fonction de l'app Example: pour 2.3 -> 23
    
    int appFunction = 0;
    
    // rgb/hsv picker 1.4
    float H,S,V;
    ofColor colorFromPicker;
    ofxButton returnBut;
    ofxButton RGBsaveBut;
    ofxButton HSVsaveBut;
    void RGBsave();
    void HSVsave();
    ofxColorSlider ColorRGB;
    
    // changement de curseur 2.1
    
    string appMode = "normal";



	ofxPanel gui;

  ofImage image_source;
  ofImage image_source1;
  ofImage image_source2;
  ofImage image_source3;
  ofImage image_source4;

  ofImage image_left;
  ofImage image_center;
  ofImage image_right;

  ofShader shader;
  ofShader shader_tint;
  ofShader shader_invert;

  int image_width;
  int image_height;

  int offset_vertical;
  int offset_horizontal;

  bool filter;

  void setup();
  void draw();
  void image_export(const string name, const string extension) const;


};
