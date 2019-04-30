// IFT3100H19_CameraTransform/renderer.h
// Classe responsable du rendu de l'application.

#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxGui.h"
#include "ofxDelaunay.h"
#include <string>

enum class Camera {front, back, left, right, top, down};

class Renderer
{
public:

	//gui
	ofxPanel gui;
	ofParameter<string> textbox_fonction;
	string text_fonction = "8.3";
    
    //gestion camera
    ofxGuiGroup group_camera;
    ofxButton cam1,cam2,cam3,cam4,cam5,cam6,pers,orth;
    void enableCamFront();
    void enableCamBack();
    void enableCamTop();
    void enableCamDown();
    void enableCamLeft();
    void enableCamRight();
    void enableProjPers();
    void enableProjOrth();
    
    //triangulation
    bool enableTrig = false;
    bool enablePoints = false;
    bool enableImage = false;
    ofImage imageTri;
    void enableDelaunay();
    void enableDelaunayImage();
    void enableDelaunayPoints();
    void drawAllPoints();
    ofxGuiGroup group_triangulation;
    ofxDelaunay triangulation;
    ofxButton tria,showimg,showpoints;
    
    //illumination
    bool enableambi = false;
    bool enablespot = false;
    bool enabledirec = false;
    bool enablepoint = false;
    void toggleAmbLight();
    void toggleDirecLight();
    void toggleSpotLight();
    void togglePointLight();
    
    void setLightOrientation(ofLight &light, ofVec3f rot);
    ofLight light_ambi,light_direc,light_spot,light_point;
    ofColor color_ambi,color_direc,color_spot,color_point;
    ofxGuiGroup group_illumination;
    ofxButton but_ambi,but_direc,but_spot,but_point;
    ofxColorSlider slider_ambi,slider_direc,slider_spot,slider_point;
    ofEventListener colorListener;
    ofVec3f dir_rot,spot_rot;
    ofxIntSlider slider_dirX,slider_dirY,slider_dirZ;
    ofxIntSlider spot_rotX,spot_rotY,spot_rotZ;
    ofxIntSlider spot_posX,spot_posY,spot_posZ,spot_cons,spot_cutoff;
    ofxIntSlider point_posX,point_posY,point_posZ;
    
    
    // variables impl/mentation fonctioin 7
	ofShader shader_default_of;

	// shaders
	ofShader shader_color_fill;
	ofShader shader_lambert;
	ofShader shader_gouraud;
	ofShader shader_phong;
	ofShader shader_blinn_phong;
	ofShader shader_blinn_phong_anisotropique;

	// shaders data
	std::string shader_name;
	ofShader *shader;

	// scene objects
	ofxAssimpModelLoader teapot;
	ofLight light[4];

	// function 7_4 parameter
	float angle_7_4;
	float rotationSpeed_7_4;
	float distace_7_4;
	float attenuation_7_4[3];
	// ===================================

    
    
    
    
    //random shidellzz

	ofImage image;
	ofImage image2;
	ofxAssimpModelLoader lapin;
  Camera camera_active;

  ofCamera camera_front;
  ofCamera camera_back;
  ofCamera camera_left;
  ofCamera camera_right;
  ofCamera camera_top;
  ofCamera camera_down;

  ofCamera* camera;

  ofQuaternion camera_orientation;

  ofVec3f camera_position;
  ofVec3f camera_target;

  string camera_name;
  string camera_projection;

  float camera_near;
  float camera_far;

  float camera_fov;
  float camera_fov_delta;

  float offset_camera;
  float offset_color;
  float offset_scene;
  float offset_cube;

  float speed_delta;
  float speed_translation;
  float speed_rotation;

  float time_current;
  float time_last;
  float time_elapsed;

  float cube_size;

  int cube_count;

  int index_x;
  int index_y;
  int index_z;

  bool is_visible_axes;
  bool is_visible_grid;
  bool is_visible_camera;
  bool is_visible_box;
  bool is_visible_locator;
  bool is_visible_text;

  bool is_camera_move_left;
  bool is_camera_move_right;
  bool is_camera_move_up;
  bool is_camera_move_down;
  bool is_camera_move_forward;
  bool is_camera_move_backward;

  bool is_camera_tilt_up;
  bool is_camera_tilt_down;
  bool is_camera_pan_left;
  bool is_camera_pan_right;
  bool is_camera_roll_left;
  bool is_camera_roll_right;

  bool is_camera_fov_narrow;
  bool is_camera_fov_wide;

  bool is_camera_perspective;

  bool use_color_fill;

  bool draw_as_checkerboard;

  void setup();
  void reset();
  void update();
  void draw();

  void function_7_1_setup();
  void function_7_1_update();
  void function_7_1_draw();

  void function_7_2_setup();
  void function_7_2_update();
  void function_7_2_draw();


  void function_7_4_setup();
  void function_7_4_draw();
  void function_7_4_update();

  void setup_camera();
};
