// IFT3100H19_CameraTransform/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
	ofSetFrameRate(60);
	ofSetBackgroundColor(31);
	//ofEnableDepthTest();


	gui.setup("Panel");
	textbox_fonction.set("Fonction active", "9.1");
	gui.add(textbox_fonction);
	//9.1
	Z_profond.setup("Z", 0.0f, -100.0f, 100.0f);
	group_bezier.setup("9.1 & 9.2");
	group_bezier.add(&Z_profond);
	gui.add(&group_bezier);

	//gui pour camera
	group_camera.setup("Gestion Cam");

	//obj de test
	lapin.loadModel("bunny.obj");

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
	text_fonction = textbox_fonction;

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
	  ofSetColor(255, 255, 255);
	  //ofRotate(180);
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
  camera->end();
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

  ofLog() << "<setup camera: " << camera_name << ">";
 

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
