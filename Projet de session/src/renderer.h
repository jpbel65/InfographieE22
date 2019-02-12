// IFT3100H19_Triptyque/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"

enum class VectorPrimitiveType { none, pixel, point, line, rectangle, ellipse };

struct VectorPrimitive
{
	VectorPrimitiveType type;            // 1 * 4 = 4  octets
	float                  position1[2];    // 2 * 4 = 8  octets
	float                  position2[2];    // 2 * 4 = 8  octets
	float                  stroke_width;    // 1 * 4 = 4  octets
	unsigned char          stroke_color[4]; // 4 * 1 = 4  octets
	unsigned char          fill_color[4];   // 4 * 1 = 4  octets
};

class Renderer
{
public:
	VectorPrimitiveType draw_mode;
	VectorPrimitive* shapes;

	ofxButton ExportBut;
	void Export();
	ofxLabel Lmport;
	ofxButton CleanBut;
	void Clean();



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

  int mouse_current_x;
  int mouse_current_y;

  bool filter;

  void setup();
  void draw();
  void image_export(const string name, const string extension) const;
  void dragEvent(ofDragInfo dragInfo);


};
