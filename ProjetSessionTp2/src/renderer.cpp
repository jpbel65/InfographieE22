// IFT3100H19_CameraTransform/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"
#include <math.h>
#include "utils.h"


void Renderer::function_7_1_setup()
{
	// désactiver le matériau par défaut du modèle
	teapot.disableMaterials();

	// select a shader
	shader_name = "lambert";
	shader = &shader_lambert;
}

void Renderer::function_7_1_draw()
{

	shader_name = "Lambert";
	shader = &shader_lambert_toon;//&shader_lambert;
	shader->begin();
	shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
	shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	// activer le shader
	shader->begin();

	// dimension du teapot
	teapot.setScale(
		0.5f,
		-0.5f,
		0.5f);

	// positionner le teapot
	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.2f),
		(float)(ofGetWindowHeight()* 0.50f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();

	shader_name = "Gouraud";
	shader = &shader_gouraud;
	shader->begin();
	shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
	shader->setUniform3f("color_specular", 0.5f, 0.5f, 0.5f);
	shader->setUniform1f("brightness", 0.5f);
	shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	shader->begin();

	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.5f),
		(float)(ofGetWindowHeight()* 0.50f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();

	shader_name = "Blinn-Phong";
	shader = &shader_blinn_phong;
	shader->begin();
	shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
	shader->setUniform3f("color_specular", 0.5f, 0.5f, 0.5f);
	shader->setUniform1f("brightness", 0.5f);
	shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.8f),
		(float)(ofGetWindowHeight()* 0.50f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();
}

void Renderer::function_7_1_update()
{
	light[0].setGlobalPosition(
		ofMap(ofGetMouseX() / (float)ofGetWidth(), 0.0f, 1.0f, -ofGetWidth() / 2.0f, ofGetWidth() / 2.0f),
		ofMap(ofGetMouseY() / (float)ofGetHeight(), 0.0f, 1.0f, -ofGetHeight() / 2.0f, ofGetHeight() / 2.0f),
		-0.5f * 1.5f);
}


//===

void Renderer::function_7_2_setup()
{
	// désactiver le matériau par défaut du modèle
	teapot.disableMaterials();

	// select a shader
	shader_name = "Blinn-Phong";
	shader = &shader_blinn_phong;
}

void Renderer::function_7_2_draw()
{

	shader->begin();
	shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("color_diffuse", 0.0f, 0.6f, 0.6f);
	shader->setUniform3f("color_specular", 0.0f, 0.0f, 0.0f);
	shader->setUniform1f("brightness", 0.1f);
	shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	// dimension du teapot
	teapot.setScale(
		0.5f,
		-0.5f,
		0.5f);

	// positionner le teapot
	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.2f),
		(float)(ofGetWindowHeight()* 0.50f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();

	shader->begin();
	shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("color_diffuse", 0.6f, 0.6f, 0.0f);
	shader->setUniform3f("color_specular", 0.5f, 0.5f, 0.0f);
	shader->setUniform1f("brightness", 0.0f);
	shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	shader->begin();

	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.5f),
		(float)(ofGetWindowHeight()* 0.50f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();

	shader->begin();
	shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
	shader->setUniform3f("color_diffuse", 0.6f, 0.6f, 0.6f);
	shader->setUniform3f("color_specular", 1.0f, 1.0f, 1.0f);
	shader->setUniform1f("brightness", 0.0f);
	shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

	shader->begin();

	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.8f),
		(float)(ofGetWindowHeight()* 0.50f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();
}

void Renderer::function_7_2_update()
{
	light[0].setGlobalPosition(
		ofMap(ofGetMouseX() / (float)ofGetWidth(), 0.0f, 1.0f, -ofGetWidth() / 2.0f, ofGetWidth() / 2.0f),
		ofMap(ofGetMouseY() / (float)ofGetHeight(), 0.0f, 1.0f, -ofGetHeight() / 2.0f, ofGetHeight() / 2.0f),
		-0.5f * 1.5f);
}
//====



void Renderer::function_7_4_setup()
{
	// désactiver le matériau par défaut du modèle
	teapot.enableMaterials();

	//angle_7_4 = 0.0f;
	rotationSpeed_7_4 = 0.01f;
}

void Renderer::function_7_4_draw()
{
	ofEnableLighting();

	light[0].setDiffuseColor(ofFloatColor(0.7f, 0.1f, 0.1f));
	light[0].setSpecularColor(ofColor(0.0f, 0.0f, 0.0f));
	light[0].setAmbientColor(ofColor(0.0f, 0.0f, 0.0f));

	light[1].setDiffuseColor(ofFloatColor(0.1f, 0.7f, 0.1f));
	light[1].setSpecularColor(ofColor(0.0f, 0.0f, 0.0f));
	light[1].setAmbientColor(ofColor(0.0f, 0.0f, 0.0f));

	light[2].setDiffuseColor(ofFloatColor(0.0f, 0.0f, 1.0f));
	light[2].setSpecularColor(ofColor(0.0f, 0.0f, 0.0f));
	light[2].setAmbientColor(ofColor(0.0f, 0.0f, 0.0f));

	light[3].setDiffuseColor(ofFloatColor(1.0f, 0.0f, 1.0f));
	light[3].setSpecularColor(ofColor(0.0f, 0.0f, 0.0f));
	light[3].setAmbientColor(ofColor(0.0f, 0.0f, 0.0f));

	light[3].setSpotlight();
	light[3].lookAt(light[2].getPosition());
	light[3].setAttenuation(1.0f, 0.02f, 0.001f);

	light[2].setSpotlight();
	light[2].lookAt(light[3].getPosition());
	light[2].setAttenuation(1.0f, 0.005f, 0.001f);

	for (int i = 0; i < 4; i++)
	{
		light[i].setPointLight();
		light[i].enable();
	}

	shader = &shader_default_of;

	// activer le shader
	shader->begin();

	// dimension du teapot
	teapot.setScale(
		0.5f,
		-0.5f,
		0.5f);

	// positionner le teapot
	teapot.setPosition(
		(float)(ofGetWindowWidth()* 0.0f),
		(float)(ofGetWindowHeight()* 0.0f),
		-100.0f);

	// dessiner un teapot
	teapot.draw(OF_MESH_FILL);

	shader->end();

	for (int i = 0; i < 4; i++)
		light[i].disable();

	ofDisableLighting();
}

void Renderer::function_7_4_update()
{
	angle_7_4 += rotationSpeed_7_4 + 0.01;
	if (angle_7_4 > 360.0f)
		angle_7_4 -= 360.0f;

	distace_7_4 = 20.0f + 0.5f * sinf(angle_7_4);

	for (int i = 0; i < 4; i++) {
		light[i].setGlobalPosition(
			0.0f*512.0f + distace_7_4 * cosf(angle_7_4 + (((float)i) *90.0f)),
			0.0f*256.0f + distace_7_4 * sinf(angle_7_4 + (((float)i) *90.0f)),
			50.f + 50.0f * sinf(angle_7_4));
	}

	attenuation_7_4[0] = 0.99f;
	attenuation_7_4[1] = 0.0f;
	attenuation_7_4[2] = 0.0000f + 0.0000f * cosf(angle_7_4);
	ofLog() << angle_7_4;
	attenuation_7_4[2] = 0.0f;
}


void Renderer::setup()
{
    //triangulation
    imageTri.load("jobs.jpg");

    
    //listener pour boutons
    cam1.addListener(this, &Renderer::enableCamTop);
    cam2.addListener(this, &Renderer::enableCamDown);
    cam3.addListener(this, &Renderer::enableCamFront);
    cam4.addListener(this, &Renderer::enableCamBack);
    cam5.addListener(this, &Renderer::enableCamLeft);
    cam6.addListener(this, &Renderer::enableCamRight);
    pers.addListener(this, &Renderer::enableProjPers);
    orth.addListener(this, &Renderer::enableProjOrth);
    tria.addListener(this, &Renderer::enableDelaunay);
    showimg.addListener(this, &Renderer::enableDelaunayImage);
    showpoints.addListener(this, &Renderer::enableDelaunayPoints);
    but_ambi.addListener(this, &Renderer::toggleAmbLight);
    but_direc.addListener(this, &Renderer::toggleDirecLight);
    but_spot.addListener(this, &Renderer::toggleSpotLight);
    but_point.addListener(this, &Renderer::togglePointLight);
    raytracer_button.addListener(this, &Renderer::raytrace);
    
    
    
    
    
    
  ofSetFrameRate(60);
  ofSetBackgroundColor(31);
  //ofEnableDepthTest();


  gui.setup("Panel");
  textbox_fonction.set("Fonction active", "6.1");
  gui.add(textbox_fonction);
  
    
    
    
    
    //gui pour camera
    group_camera.setup("Gestion Cam");
    group_camera.add(cam1.setup("Enable Cam Top"));
    group_camera.add(cam2.setup("Enable Cam Down"));
    group_camera.add(cam3.setup("Enable Cam Front"));
    group_camera.add(cam4.setup("Enable Cam Back"));
    group_camera.add(cam5.setup("Enable Cam Left"));
    group_camera.add(cam6.setup("Enable Cam Right"));
    group_camera.add(pers.setup("Enable Perspective"));
    group_camera.add(orth.setup("Enable Orthogonale"));
    gui.add(&group_camera);
    
    //gui pour triangulation
    group_triangulation.setup("Triangulation Delaunay");
    group_triangulation.add(showimg.setup("Enable Image"));
    group_triangulation.add(showpoints.setup("Enable Points"));
    group_triangulation.add(tria.setup("Enable Delaunay"));
    gui.add(&group_triangulation);
    
    //gui pour lumiere
    group_illumination.setup("Illumination");
    group_illumination.add(but_ambi.setup("Toggle ambiante"));
    group_illumination.add(slider_ambi.setup(color_ambi));
    group_illumination.add(but_direc.setup("Toggle Directional"));
    group_illumination.add(slider_direc.setup(color_direc));
    group_illumination.add(slider_dirX.setup("Rotation X", 0, -180, 180));
    group_illumination.add(slider_dirY.setup("Rotation Y", 0, -180, 180));
    group_illumination.add(slider_dirZ.setup("Rotation Z", 0, -180, 180));
    group_illumination.add(but_spot.setup("Toggle Spot"));
    group_illumination.add(slider_spot.setup(color_spot));
    group_illumination.add(spot_rotX.setup("Rotation X", 0, -180, 180));
    group_illumination.add(spot_rotY.setup("Rotation Y", 0, -180, 180));
    group_illumination.add(spot_rotZ.setup("Rotation Z", 0, -180, 180));
    group_illumination.add(spot_posX.setup("Position X", 0, -500, 500));
    group_illumination.add(spot_posY.setup("Position Y",  0, -500, 500));
    group_illumination.add(spot_posZ.setup("Position Z",  0, -500, 500));
    group_illumination.add(spot_cons.setup("Concentration",  0, 0, 127));
    group_illumination.add(spot_cutoff.setup("Cutoff",  100, 0, 500));
    group_illumination.add(but_point.setup("Toggle Point"));
    group_illumination.add(slider_point.setup(color_point));
    group_illumination.add(point_posX.setup("Position X", 0, -500, 500));
    group_illumination.add(point_posY.setup("Position Y",  0, -500, 500));
    group_illumination.add(point_posZ.setup("Position Z",  0, -500, 500));
    gui.add(&group_illumination);

    gui.add(&group_camera);

    raytracer_group.setup("Raytracer");
    raytracer_group.add(raytracer_button.setup("Lancer le raytracing"));

    gui.add(&raytracer_group);
 

  lapin.loadModel("bunny.obj");
    lapin.disableMaterials();
    

	// setup lumiere classique
		// chargement d'un modèle 3D
	teapot.loadModel("geometry/teapot.obj");
	// charger, compiler et linker les sources des shaders
	shader_color_fill.load(
		"shader/color_fill_330_vs.glsl",
		"shader/color_fill_330_fs.glsl");

	shader_lambert.load(
		"shader/lambert_330_vs.glsl",
		"shader/lambert_330_fs.glsl");

	shader_gouraud.load(
		"shader/gouraud_330_vs.glsl",
		"shader/gouraud_330_fs.glsl");

	shader_phong.load(
		"shader/phong_330_vs.glsl",
		"shader/phong_330_fs.glsl");

	shader_blinn_phong.load(
		"shader/blinn_phong_330_vs.glsl",
		"shader/blinn_phong_330_fs.glsl");

	shader_blinn_phong_anisotropique.load(
		"shader/blinn_phong_anisotropique_330_vs.glsl",
		"shader/blinn_phong_anisotropique_330_fs.glsl");

	shader_lambert_toon.load(
		"shader/lambert_toon_330_vs.glsl",
		"shader/lambert_toon_330_fs.glsl");

	function_7_1_setup();
	function_7_4_setup();
	angle_7_4 = 0.0f;


	//9.1
	Z_profond.setup("Z", 0.0f, -100.0f, 100.0f);
	group_bezier.setup("9.1 & 9.2");
	group_bezier.add(&Z_profond);
	gui.add(&group_bezier);

	//gui pour camera
	group_camera.setup("Gestion Cam");

	//obj de test

	//9.1
	for (int index = 0; index <= 100; ++index) {
		line_renderer.addVertex(ofPoint());
	}

  // paramètres
  camera_position = {0.0f, 0.0f, 0.0f};
  camera_target = {0.0f, 0.0f, 0.0f};

  camera_near = 50.0f;
  camera_far = 1750.0f;

  camera_fov = 60.0f;
  camera_fov_delta = 16.0f;

  speed_delta = 250.0f;

  offset_cube = 64.0f;

  cube_count = 7;

  is_visible_axes = false;
  is_visible_grid = false;
  is_visible_camera = false;
  is_visible_box = true;
  is_visible_locator = false;
  is_visible_text = false;

  is_camera_move_left = false;
  is_camera_move_right = false;
  is_camera_move_up = false;
  is_camera_move_down = false;
  is_camera_move_forward = false;
  is_camera_move_backward = false;

  is_camera_tilt_up = false;
  is_camera_tilt_down = false;
  is_camera_pan_left = false;
  is_camera_pan_right = false;
  is_camera_roll_left = false;
  is_camera_roll_right = false;

  is_camera_fov_narrow = false;
  is_camera_fov_wide = false;

  is_camera_perspective = true;

  use_color_fill = true;

  draw_as_checkerboard = false;

  reset();

  setup_camera();
}

void Renderer::reset()
{
  // initialisation des variables
  cube_size = offset_cube / 2.0f;
  offset_scene = cube_count * offset_cube / 2.0f * -1.0f + cube_size;
  offset_color = 255.0f / cube_count;
  offset_camera = offset_scene * 3.5f * -1.0f;

  // position initiale de chaque caméra
  camera_front.setPosition(0, 0, -offset_camera);
  camera_back.setPosition(0, 0, offset_camera);
  camera_left.setPosition(-offset_camera, 0, 0);
  camera_right.setPosition(offset_camera, 0, 0);
  camera_top.setPosition(0, offset_camera, 0);
  camera_down.setPosition(0, -offset_camera, 0);

  camera_front.setOrientation(ofVec3f(0, 0, 180));
  //camera_back.setOrientation(ofVec3f(0, -180, 0));
  //camera_left.setOrientation(ofVec3f(0, 180, 0));
  //camera_right.setOrientation(ofVec3f(0, 180, 0));
  //camera_top.setOrientation(ofVec3f(0, 180, 0));
  //camera_down.setOrientation(ofVec3f(0, 180, 0));

  // orientation de chaque caméra
  camera_front.lookAt(camera_target);
  camera_back.lookAt(camera_target);
  camera_left.lookAt(camera_target);
  camera_right.lookAt(camera_target);
  camera_top.lookAt(camera_target, ofVec3f(1, 0, 0));
  camera_down.lookAt(camera_target, ofVec3f(1, 0, 0));

  // caméra par défaut
  camera_active = Camera::front;

  ofLog() << "<reset>";
}

void Renderer::update()
{
    
    if(text_fonction == "7.1")
		function_7_1_update();

	if(text_fonction == "7.2" || text_fonction == "7.5")
		function_7_2_update();

	if (text_fonction == "7.4")
		function_7_4_update();
    
    
    
    
    
  text_fonction = textbox_fonction;
	
  time_current = ofGetElapsedTimef();
  time_elapsed = time_current - time_last;
  time_last = time_current;

	time_current = ofGetElapsedTimef();
	time_elapsed = time_current - time_last;
	time_last = time_current;

	speed_translation = speed_delta * time_elapsed;
	speed_rotation = speed_translation / 8.0f;

	if (is_camera_move_left)
		camera->truck(-speed_translation);
	if (is_camera_move_right)
		camera->truck(speed_translation);

	if (is_camera_move_up)
		camera->boom(speed_translation);
	if (is_camera_move_down)
		camera->boom(-speed_translation);

	if (is_camera_move_forward)
		camera->dolly(-speed_translation);
	if (is_camera_move_backward)
		camera->dolly(speed_translation);

	if (is_camera_tilt_up)
		camera->tiltDeg(-speed_rotation);
	if (is_camera_tilt_down)
		camera->tiltDeg(speed_rotation);

	if (is_camera_pan_left)
		camera->panDeg(speed_rotation);
	if (is_camera_pan_right)
		camera->panDeg(-speed_rotation);

	if (is_camera_roll_left)
		camera->rollDeg(-speed_rotation);
	if (is_camera_roll_right)
		camera->rollDeg(speed_rotation);

	if (is_camera_perspective)
	{
		if (is_camera_fov_narrow)
		{
			camera_fov = std::max(camera_fov -= camera_fov_delta * time_elapsed, 0.0f);
			camera->setFov(camera_fov);
		}

		if (is_camera_fov_wide)
		{
			camera_fov = std::min(camera_fov += camera_fov_delta * time_elapsed, 180.0f);
			camera->setFov(camera_fov);
		}
	}
	//9.1
	if (pointCurve.size() >= 4) {
		for (int index = 0; index <= 100; ++index)
		{
			line_renderer[index] = Renderer::return_position_bezier(index / 100.0f);
		}
	}
	if (pointCurve.size() >= 16) {
		pointSurface.clear();
		for (int index = 0; index <= 10; ++index)
		{
			for (int j = 0; j <= 10; ++j) {
				pointSurface.push_back(Renderer::return_position_bezier_surface(index / 10.0f, j / 10.0f));
			}
		}
	}


}

void Renderer::draw()
{
    
    
    
    //lumiere
    color_ambi.set(slider_ambi.getParameter().cast<ofColor>());
    light_ambi.setAmbientColor(color_ambi);
    color_direc.set(slider_direc.getParameter().cast<ofColor>());
    dir_rot = ofVec3f(slider_dirX.getParameter().cast<int>(), slider_dirY.getParameter().cast<int>(), slider_dirZ.getParameter().cast<int>());
    light_direc.setSpecularColor(color_direc);
    light_direc.setDiffuseColor(color_direc);
    setLightOrientation(light_direc, dir_rot);
    
    
    color_spot.set(slider_spot.getParameter().cast<ofColor>());
    light_spot.setDiffuseColor(color_spot);
    light_spot.setSpecularColor(color_spot);
  
    light_spot.setSpotlight();
    light_spot.setSpotConcentration(spot_cons.getParameter().cast<int>());
    light_spot.setSpotlightCutOff(spot_cutoff.getParameter().cast<int>());
    light_spot.setPosition(spot_posX, spot_posY, spot_posZ);
    spot_rot = ofVec3f(spot_rotX.getParameter().cast<int>(), spot_rotY.getParameter().cast<int>(), spot_rotZ.getParameter().cast<int>());
    setLightOrientation(light_spot, spot_rot);
    
    color_point.set(slider_point.getParameter().cast<ofColor>());
    light_point.setPointLight();
    light_point.setPosition(point_posX.getParameter().cast<int>(), point_posY.getParameter().cast<int>(), point_posZ.getParameter().cast<int>());
    light_point.setAmbientColor(color_point);
    light_point.setDiffuseColor(color_point);
    
    
    // triangulation
    if(enableImage){
        text_fonction = "9.4";
        ofSetColor(255,255,255);
        imageTri.draw(220, 0);
    }
    if(enablePoints){
        Renderer::drawAllPoints();
    }
    
    if (enableTrig) {
        text_fonction = "9.4";
        ofSetColor(0,255,0);
        ofNoFill();
        triangulation.draw();
    }
    else{
        ofFill();
        ofSetColor(255,255,255);
    }
    
  // activer la caméra
  camera->begin();

  // dessiner une grille
  if (is_visible_grid)
    ofDrawGrid(64);

  // dessiner un gizmo pour les axes de la scène
  if (is_visible_axes)
    ofDrawRotationAxes(64);

  // dessiner un gizmo pour toutes les caméras sauf celle qui est active
  if (is_visible_camera)
  {
    if (camera_active != Camera::front)
      camera_front.draw();
    if (camera_active != Camera::back)
      camera_back.draw();
    if (camera_active != Camera::left)
      camera_left.draw();
    if (camera_active != Camera::right)
      camera_right.draw();
    if (camera_active != Camera::top)
      camera_top.draw();
    if (camera_active != Camera::down)
      camera_down.draw();
  }

  // dessiner une zone de texte avec le nom des caméras
  if (is_visible_text)
  {
    if (camera_active != Camera::front)
      ofDrawBitmapString(" camera front", camera_front.getPosition());
    if (camera_active != Camera::back)
      ofDrawBitmapString(" camera back", camera_back.getPosition());
    if (camera_active != Camera::left)
      ofDrawBitmapString(" camera left", camera_left.getPosition());
    if (camera_active != Camera::right)
      ofDrawBitmapString(" camera right", camera_right.getPosition());
    if (camera_active != Camera::top)
      ofDrawBitmapString(" camera top", camera_top.getPosition());
    if (camera_active != Camera::down)
      ofDrawBitmapString(" camera down", camera_down.getPosition());
  }
  if (text_fonction == "6.1") {
	  lapin.setPosition(camera_target.x, camera_target.y, camera_target.z);
	  ofPushMatrix();
      ofRotate(180);
	  lapin.draw(OF_MESH_FILL);
	  ofPopMatrix();
  }
  if (text_fonction == "9.1") {
	  ofSetColor(0, 255, 0);
	  ofSetLineWidth(10);
	  line_renderer.draw();
	  ofSetColor(63, 63, 63);
	  float radius = 25;
	  for (int i = 0; i < pointCurve.size(); i++) {
		  ofDrawSphere(pointCurve[i].x, pointCurve[i].y, pointCurve[i].z, radius / 2);
	  }
    if(text_fonction == "8.3"){

  }
  if (text_fonction == "9.2") {
	  ofSetColor(0, 255, 0);
	  ofSetLineWidth(10);
	  ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	  ofBeginShape();
	  for (int i = 0; i < pointSurface.size(); i++) {
		  ofVertex(pointSurface[i]);
	  }
	  ofEndShape();
	  ofSetColor(63, 63, 63);
	  float radius = 25;
	  for (int i = 0; i < pointCurve.size() && i < 16; i++) {
		  ofDrawSphere(pointCurve[i].x, pointCurve[i].y, pointCurve[i].z, radius / 2);
	  }

  }


    }

  // dessiner le contenu de la scène
  /*if (is_visible_box)
  {
    for (index_x = 0; index_x < cube_count; ++index_x)
    {
      for (index_y = 0; index_y < cube_count; ++index_y)
      {
        for (index_z = 0; index_z < cube_count; ++index_z)
        {
          if (index_x % 2 == index_y % 2 == index_z % 2 || !draw_as_checkerboard)
          {
            ofSetColor(
              index_x * offset_color,
              index_y * offset_color,
              index_z * offset_color);

            ofDrawBox(
              offset_scene + index_x * offset_cube,
              offset_scene + index_y * offset_cube,
              offset_scene + index_z * offset_cube,
              cube_size);
          }
        }
      }
    }
  }
  */

	if (text_fonction == "7.5") {
		teapot.disableMaterials();
		ofEnableDepthTest();

		shader_name = "Blinn-Phong-anisotropique";
		shader = &shader_blinn_phong_anisotropique;
		shader->begin();
		shader->setUniform3f("color_ambient", 0.1f, 0.1f, 0.1f);
		shader->setUniform3f("color_diffuse", 0.2f, 0.2f, 0.2f);
		shader->setUniform3f("color_specular", 0.5f, 0.5f, 0.5f);
		shader->setUniform1f("brightness", 2.0f);
		shader->setUniform1f("anisotropique_factor", 2.0f);
		shader->setUniform3f("light_position", glm::vec4(light[0].getGlobalPosition(), 0.0f) * ofGetCurrentMatrix(OF_MATRIX_MODELVIEW));

		// dimension du teapot
		teapot.setScale(
			0.7f,
			-0.7f,
			0.7f);

		// positionner le teapot
		teapot.setPosition(
			(float)(ofGetWindowWidth()* 0.5f),
			(float)(ofGetWindowHeight()* 0.50f),
			-100.0f);

		// dessiner un teapot
		teapot.draw(OF_MESH_FILL);


		shader->end();

		teapot.enableMaterials();
		ofDisableDepthTest();
	}

	if (text_fonction == "7.1") {
		ofEnableDepthTest();
		ofEnableLighting();
		function_7_1_setup();
		function_7_1_draw();
		ofDisableLighting();
		ofDisableDepthTest();
	}

	if (text_fonction == "7.2") {
		ofEnableDepthTest();
		ofEnableLighting();
		function_7_2_setup();
		function_7_2_draw();
		ofDisableLighting();
		ofDisableDepthTest();
	}

	if (text_fonction == "7.4") {
		ofEnableDepthTest();
		ofEnableLighting();
		function_7_4_setup();
		function_7_4_draw();
		ofDisableLighting();
		ofDisableDepthTest();
	}


  camera->end();

  if (raytraced_image.getHeight() > 0 && raytraced_image.getWidth() > 0 && text_fonction == "8")  {
    raytraced_image.draw(
        80,
        80,
        raytraced_image.getWidth(),
        raytraced_image.getHeight());
  }

  gui.draw();
}

// fonction de configuration de la caméra active
void Renderer::setup_camera()
{
  switch (camera_active)
  {
    case Camera::front:
      camera = &camera_front;
      camera_name = "avant";
      break;

    case Camera::back:
      camera = &camera_back;
      camera_name = "arrière";
      break;

    case Camera::left:
      camera = &camera_left;
      camera_name = "gauche";
      break;

    case Camera::right:
      camera = &camera_right;
      camera_name = "droite";
      break;

    case Camera::top:
      camera = &camera_top;
      camera_name = "haut";
      break;

    case Camera::down:
      camera = &camera_down;
      camera_name = "bas";
      break;

    default:
      break;
  }

  camera_position = camera->getPosition();
  camera_orientation = camera->getOrientationQuat();

  // mode de projection de la caméra
  if (is_camera_perspective)
  {
    camera->disableOrtho();
    camera->setupPerspective(false, camera_fov, camera_near, camera_far, ofVec2f(0, 0));
    camera_projection = "perspective";
  }
  else
  {
    camera->enableOrtho();
    camera_projection = "orthogonale";
  }

  camera->setPosition(camera_position);
  camera->setOrientation(camera_orientation);

  
 

}

void Renderer::enableCamFront(){
    camera_active = Camera::back;
    setup_camera();
}
void Renderer::enableCamBack(){
    camera_active = Camera::front;
    setup_camera();
}
void Renderer::enableCamTop(){
    camera_active = Camera::top;
    setup_camera();
}
void Renderer::enableCamDown(){
    camera_active = Camera::down;
    setup_camera();
}
void Renderer::enableCamLeft(){
    camera_active = Camera::left;
    setup_camera();
}
void Renderer::enableCamRight(){
    camera_active = Camera::right;
    setup_camera();
}
void Renderer::enableProjPers(){
    is_camera_perspective = true;
    setup_camera();
}
void Renderer::enableProjOrth(){
    is_camera_perspective = false;
    setup_camera();
    
}
void Renderer::enableDelaunayImage(){
    enableImage = !enableImage;
}
void Renderer::enableDelaunayPoints(){
    enablePoints = !enablePoints;
}

void Renderer::raytrace() {
  std::vector<raytracer::Sphere> spheres;
  std::vector<raytracer::Point_light> lights;
  raytracer::Color ambiant_color(0.05,0.05,0.05);
  std::map<string, raytracer::Material> materials;
void Renderer::enableDelaunay(){
    
    enableTrig = !enableTrig;
    triangulation.reset();
    
    ofMesh mesh = lapin.getMesh(0);
    
    cout << "tex coords count: " << mesh.getNumVertices() << " : " << endl;
    const vector <glm::vec3> Coords = mesh.getVertices();
    for (int i=0; i<Coords.size(); i++){
        cout << Coords[i] << endl;
    }
    cout << "end tex coords" << endl;
    triangulation.addPoint(500.737,168.9074,0);
    triangulation.addPoint(573.0323,168.9074,0);
    triangulation.addPoint(548.033,159.4482,0);
    triangulation.addPoint(572.3566,152.6916,0);
    triangulation.addPoint(593.302,160.7995,0);
    triangulation.addPoint(475.7378,162.8265,0);
    triangulation.addPoint(496.6831,153.3673,0);
    triangulation.addPoint(515.6015,160.1238,0);
    triangulation.addPoint(535.1955,223.6356,0);
    triangulation.addPoint(512.8989,214.1764,0);
    triangulation.addPoint(560.8705,212.1494,0);
    triangulation.addPoint(535.1955,202.0145,0);
    triangulation.addPoint(534.5199,160.7995,0);
    triangulation.addPoint(498.7101,249.3105,0);
    triangulation.addPoint(536.5468,249.3105,0);
    triangulation.addPoint(574.3836,248.6348,0);
    triangulation.addPoint(535.8712,262.148,0);
    triangulation.addPoint(540.6008,323.6327,0);
    triangulation.addPoint(492.6292,306.7413,0);
    triangulation.addPoint(592.6263,302.0117,0);
    triangulation.addPoint(466.2786,275.6611,0);
    triangulation.addPoint(619.6526,272.9585,0);
    triangulation.addPoint(454.7924,237.8243,0);
    triangulation.addPoint(631.8144,239.8513,0);
    triangulation.addPoint(439.2523,214.852,0);
    triangulation.addPoint(652.7598,218.2303,0);
    triangulation.addPoint(435.1984,186.4744,0);
    triangulation.addPoint(658.8407,188.5014,0);
    triangulation.addPoint(650.7328,157.4212,0);
    triangulation.addPoint(437.2253,153.3673,0);
    triangulation.addPoint(451.4141,164.1778,0);
    triangulation.addPoint(637.8953,164.1778,0);
    triangulation.addPoint(449.3872,112.1522,0);
    triangulation.addPoint(465.6029,78.3694,0);
    triangulation.addPoint(496.0075,44.5866,0);
    triangulation.addPoint(537.8982,33.1004,0);
    triangulation.addPoint(575.7349,37.1544,0);
    triangulation.addPoint(604.7881,58.7754,0);
    triangulation.addPoint(627.0848,87.1529,0);
    triangulation.addPoint(640.5979,126.341,0);
    triangulation.addPoint(479.7917,56.0727,0);
    triangulation.addPoint(498.0344,98.6391,0);
    triangulation.addPoint(537.8982,85.126,0);
    triangulation.addPoint(582.4915,104.72,0);
    triangulation.addPoint(495.3318,181.7449,0);
    triangulation.addPoint(577.7619,181.7449,0);
    triangulation.addPoint(596.6803,173.637,0);
    triangulation.addPoint(475.7378,169.583,0);
    triangulation.addPoint(500.0614,135.1246,0);
    triangulation.addPoint(577.7619,132.4219,0);
    triangulation.triangulate();
}
void Renderer::drawAllPoints(){
    ofDrawCircle(500.737,168.9074,3);
    ofDrawCircle(573.0323,168.9074,3);
    ofDrawCircle(548.033,159.4482,3);
    ofDrawCircle(572.3566,152.6916,3);
    ofDrawCircle(593.302,160.7995,3);
    ofDrawCircle(475.7378,162.8265,3);
    ofDrawCircle(496.6831,153.3673,3);
    ofDrawCircle(515.6015,160.1238,3);
    ofDrawCircle(535.1955,223.6356,3);
    ofDrawCircle(512.8989,214.1764,3);
    ofDrawCircle(560.8705,212.1494,3);
    ofDrawCircle(535.1955,202.0145,3);
    ofDrawCircle(534.5199,160.7995,3);
    ofDrawCircle(498.7101,249.3105,3);
    ofDrawCircle(536.5468,249.3105,3);
    ofDrawCircle(574.3836,248.6348,3);
    ofDrawCircle(535.8712,262.148,3);
    ofDrawCircle(540.6008,323.6327,3);
    ofDrawCircle(492.6292,306.7413,3);
    ofDrawCircle(592.6263,302.0117,3);
    ofDrawCircle(466.2786,275.6611,3);
    ofDrawCircle(619.6526,272.9585,3);
    ofDrawCircle(454.7924,237.8243,3);
    ofDrawCircle(631.8144,239.8513,3);
    ofDrawCircle(439.2523,214.852,3);
    ofDrawCircle(652.7598,218.2303,3);
    ofDrawCircle(435.1984,186.4744,3);
    ofDrawCircle(658.8407,188.5014,3);
    ofDrawCircle(650.7328,157.4212,3);
    ofDrawCircle(437.2253,153.3673,3);
    ofDrawCircle(451.4141,164.1778,3);
    ofDrawCircle(637.8953,164.1778,3);
    ofDrawCircle(449.3872,112.1522,3);
    ofDrawCircle(465.6029,78.3694,3);
    ofDrawCircle(496.0075,44.5866,3);
    ofDrawCircle(537.8982,33.1004,3);
    ofDrawCircle(575.7349,37.1544,3);
    ofDrawCircle(604.7881,58.7754,3);
    ofDrawCircle(627.0848,87.1529,3);
    ofDrawCircle(640.5979,126.341,3);
    ofDrawCircle(479.7917,56.0727,3);
    ofDrawCircle(498.0344,98.6391,3);
    ofDrawCircle(537.8982,85.126,3);
    ofDrawCircle(582.4915,104.72,3);
    ofDrawCircle(495.3318,181.7449,3);
    ofDrawCircle(577.7619,181.7449,3);
    ofDrawCircle(596.6803,173.637,3);
    ofDrawCircle(475.7378,169.583,3);
    ofDrawCircle(500.0614,135.1246,3);
    ofDrawCircle(577.7619,132.4219,3);
}
void Renderer::setLightOrientation(ofLight &light, ofVec3f rot){
    ofVec3f xax(1, 0, 0);
    ofVec3f yax(0, 1, 0);
    ofVec3f zax(0, 0, 1);
    ofQuaternion q;
    q.makeRotate(rot.x, xax, rot.y, yax, rot.z, zax);
    light.setOrientation(q);
}

  ofBuffer myfile = ofBufferFromFile("raytraycer.txt");
  // std::ifstream myfile ("raytraycer.txt");
  if (myfile.size() > 0)
  {
      for ( auto line : myfile.getLines() )
      {
          std::vector<string> obj;
          boost::split(obj, line, boost::is_any_of(" "));
          if (obj[0] == "s") {
              raytracer::Material m = materials.find(obj[5])->second;
              raytracer::Sphere s (stof(obj[1]), stof(obj[2]), stof(obj[3]), stof(obj[4]), m);
              spheres.push_back(s);
          } else if (obj[0] == "l") {
              raytracer::Point_light light(linalg::vec<float, 3>(stof(obj[1]), stof(obj[2]), stof(obj[3])), stof(obj[4]));
              lights.push_back(light);
          } else if (obj[0] == "m") {
              linalg::vec<float, 4> albedo(stof(obj[5]),stof(obj[6]),stof(obj[7]),stof(obj[8]));
              raytracer::Material m(raytracer::Color(stof(obj[2]),stof(obj[3]),stof(obj[4])), albedo, stof(obj[9]), stof(obj[10]));
              materials.insert({obj[1], m});
          } else if (obj[0] == "a") {
              ambiant_color = raytracer::Color(stof(obj[1]), stof(obj[2]), stof(obj[3]));
          }
      }
      // myfile.close();
  }

  else {
      std::cout << "[warning] Impossible de lire le fichier de scène. La scène par défaut sera utilisée." << std::endl;
      linalg::vec<float, 4> albedo1(0.6,  0.3, 0.1, 0);
      linalg::vec<float, 4> albedo2(0.9,  0.1, 0.0, 0);
      linalg::vec<float, 4> albedo3(0.0, 10.0, 0.8, 0);
      linalg::vec<float, 4> albedo4(0.0,  0.5, 0.1, 0.8);

      raytracer::Material m1(raytracer::Color(0.4,0.4,0.8), albedo1,   50, 1.0);
      raytracer::Material m2(raytracer::Color(0.5,0.1,0.1), albedo2,   10, 1.0);
      raytracer::Material m3(raytracer::Color(1.0,1.0,1.0), albedo3, 1425, 1.0);
      raytracer::Material m4(raytracer::Color(0. ,0. ,0. ), albedo4,  125, 1.5);

      raytracer::Sphere s (-5  ,  0  , -24, 2, m1);
      raytracer::Sphere s2(-1.0, -1.5, -12, 2, m4);
      raytracer::Sphere s3( 1.5, -0.5, -18, 3, m2);
      raytracer::Sphere s4( 7  ,  5  , -18, 4, m3);
      raytracer::Sphere s5(-3  , -4  , -16, 2, m1);
      raytracer::Sphere s6(-5  ,  6  , -16, 3, m3);
      raytracer::Sphere s7( 5  ,  6  , -24, 3, m2);

      spheres.push_back(s);
      spheres.push_back(s2);
      spheres.push_back(s3);
      spheres.push_back(s4);
      spheres.push_back(s5);
      spheres.push_back(s6);
      spheres.push_back(s7);

      
      lights.push_back(raytracer::Point_light(linalg::vec<float, 3>(-20,20, 20), 1.5));
      lights.push_back(raytracer::Point_light(linalg::vec<float, 3>(30, 50, -25), 1.8));
      lights.push_back(raytracer::Point_light(linalg::vec<float, 3>(30, 20, 30), 1.7));
  }

  /*ofPixels pixels = */raytracer::render(spheres, lights, ambiant_color, 1024, 768);
  raytraced_image.load("raytrace.ppm");
  textbox_fonction.set("8");
}



void Renderer::toggleAmbLight(){
    enableambi = !enableambi;
    if(enableambi){
        ofEnableLighting();
        light_ambi.setAmbientColor(color_ambi);
        light_ambi.enable();
        cout << color_ambi << endl;
        cout << slider_ambi.getParameter() << endl;
    }
    else{
        light_ambi.disable();
    }
}
void Renderer::toggleDirecLight(){
    enabledirec = !enabledirec;
    if(enabledirec){
        ofEnableLighting();
        light_direc.setDirectional();
        light_direc.enable();
    }
    else{
        light_direc.disable();
    }
}
void Renderer::toggleSpotLight(){
    enablespot = !enablespot;
    if(enablespot){
        ofEnableLighting();
        light_spot.setSpotlight();
        light_spot.enable();
    }
    else{
        light_spot.disable();
    }
}
void Renderer::togglePointLight(){
    enablepoint = !enablepoint;
    if(enablepoint){
        ofEnableLighting();
        light_point.setPointLight();
        light_point.enable();
    }
    else{
        light_point.disable();
    }
}




ofVec3f Renderer::return_position_bezier(float t) {
	ofVec3f pos(0,0,0);
	float u = 1 - t;
	float uu = u * u;
	float uuu = uu * u;
	float tt = t * t;
	float ttt = tt * t;

	//pos.x = uuu * pointCurve[0].x + 3 * uu * t * pointCurve[1].x + 3 * u * tt * pointCurve[2].x + ttt * pointCurve[3].x;
	for (float i = 0.0f; i < pointCurve.size(); i++) {
		pos.x += pow(u, pointCurve.size() - 1 -i)*pow(t,i)*pointCurve[i].x * (facto(pointCurve.size() - 1)/facto(i)/facto(pointCurve.size() - 1 - i));
		pos.y += pow(u, pointCurve.size() - 1 - i)*pow(t, i)*pointCurve[i].y * (facto(pointCurve.size() - 1) / facto(i) / facto(pointCurve.size() - 1 - i));
		pos.z += pow(u, pointCurve.size() - 1 - i)*pow(t, i)*pointCurve[i].z * (facto(pointCurve.size() - 1) / facto(i) / facto(pointCurve.size() - 1 - i));
	}
	//pos.y = uuu * pointCurve[0].y + 3 * uu * t * pointCurve[1].y + 3 * u * tt * pointCurve[2].y + ttt * pointCurve[3].y;
	//pos.z = uuu * pointCurve[0].z + 3 * uu * t * pointCurve[1].z + 3 * u * tt * pointCurve[2].z + ttt * pointCurve[3].z;
	//ofLog() << pos.x << pos.y << pos.z;
	return pos;
}

void Renderer::add_pointCurve(int x, int y) {
	ofVec3f pos;
	pos = camera->worldToScreen(ofVec3f(x, y, 0));
	pos.z = Z_profond;
	ofLog() << pos;
	pointCurve.push_back(pos);
}

float Renderer::facto(float x) {
	float r = 1.0f;
	for (float i = x; i > 0; i--) {
		r = r * i;
	}
	return r;
}

ofVec3f Renderer::return_position_bezier_surface(float t, float v) {
	ofVec3f pos(0,0,0);
	float w = 1 - v;
	float u = 1 - t;
	ofVec3f matri[4][4];
	int taille = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matri[i][j] = pointCurve[taille];
			taille++;
		}
	}

	for (int i = 0.0f; i < 4; i++) {
		float x = pow(u, 4 - 1 - i)*pow(t, i) * (facto(4 - 1) / facto(i) / facto(4 - 1 - i));
		float y = pow(u, 4 - 1 - i)*pow(t, i) * (facto(4 - 1) / facto(i) / facto(4 - 1 - i));
		float z = pow(u, 4 - 1 - i)*pow(t, i) * (facto(4 - 1) / facto(i) / facto(4 - 1 - i));
		for (int j = 0.0f; j < 4; j++) {
			pos.x += x * pow(w, 4 - 1 - j)*pow(v, j)*matri[i][j].x * (facto(4 - 1) / facto(j) / facto(4 - 1 - j));
			pos.y += y * pow(w, 4 - 1 - j)*pow(v, j)*matri[i][j].y * (facto(4 - 1) / facto(j) / facto(4 - 1 - j));
			pos.z += z * pow(w, 4 - 1 - j)*pow(v, j)*matri[i][j].z * (facto(4 - 1) / facto(j) / facto(4 - 1 - j));
		}
	}
	ofLog() << pos;
	return pos;
}
