// IFT3100H19_Triptyque/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "PVector.h"
#include "Histogramme.h"
#include <string>

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
	//1.5
	Histogramme histogramme;

	int appFunction = 101;
	string appMode = "normal";
	vector<PVector> Pvector;
	VectorPrimitiveType draw_mode;
	VectorPrimitive* shapes;

	ofxButton ExportBut;
	void Export();
	ofxLabel Lmport;
	ofxButton CleanBut;
	void Clean();

	ofParameter<string> textbox_fonction;
	string text_fonction;
    
    //2.2
    ofImage mouseDrawing;

	//2.3
	ofxGuiGroup group_Pvector;
	ofxButton PV1;
	void pv1_line();
	ofxButton PV2;
	void pv2_square();
	ofxButton PV3;
	void pv3_ellipse();
	ofxButton PV4;
	void pv4_triangle();
	ofxButton PV5;
	void pv5_point();
    ofxButton FV1;
    void fv1_maison();
    ofxButton FV2;
    void fv2_fleche();
    ofxButton FV3;
    void fv3_sapin();
    ofxButton FV4;
    void fv4_bateau();
	ofParameter<string> textbox_pv;
	string text_pv = "line";

	ofxPanel gui;
    
    //1.4
    ofxGuiGroup groupeCouleur;
    ofxIntSlider strokeSize;
    ofColor pickedColor = (0,0,0);
    ofColor pickedColor2 = (0,0,0);
    ofxIntSlider Rslider,Gslider,Bslider,Hslider,Sslider,Vslider;
    ofxButton HSVpickStroke;
    ofxButton HSVpickFill;
    ofxButton RGBpickStroke;
    ofxButton RGBpickFill;
    void saveRGBStroke();
    void saveRGBFill();
    void saveHSVStroke();
    void saveHSVFill();
    
    // gui pour antho
    ofxGuiGroup groupeCercleA,groupeCercleB;
    ofxFloatSlider cercleAx,cercleAy,cercleAz,cercleAdist,cercleAz2;
    ofxFloatSlider cercleBx,cercleBy,cercleBz,cercleBdist,cercleBz2;
    ofxFloatSlider cercleAangle,cercleBangle;
    
	//3.1
	ofParameter<string> textbox_selected_PV;
	string text_selected_PV;
	ofxGuiGroup group_Pv_line;
	ofxGuiGroup group_Pv_carre;
	ofxGuiGroup group_Pv_ellipse;
	ofxGuiGroup group_Pv_triangle; 
	ofxGuiGroup group_Pv_point;
	ofxGuiGroup group_Pv_other;

	ofxGuiGroup arborescence;

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

  //4.2
  ofVbo VBO;
  ofxGuiGroup Forme3D_groupe;
  ofxButton Forme_3D_1;
  void Forme3D_De_4();
  ofxButton Forme_3D_2;
  void Forme3D_De_6();
  string Forme3D = "De 4";
  void Add_forme_vbo();

  int image_width;
  int image_height;

  int offset_vertical;
  int offset_horizontal;

  bool is_mouse_button_pressed;
  int mouse_current_x;
  int mouse_current_y;
  int mouse_press_x;
  int mouse_press_y;

  bool filter;

  void setup();
  void draw();
  void update();
  void image_export(const string name, const string extension) const;
  void dragEvent(ofDragInfo dragInfo);
  void add_PVector();
  void draw_PVector(PVector pv);


};
