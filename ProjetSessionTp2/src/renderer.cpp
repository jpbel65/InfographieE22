// IFT3100H19_CameraTransform/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"
#include "utils.h"

void Renderer::setup()
{
    //listener pour boutons
    cam1.addListener(this, &Renderer::enableCamTop);
    cam2.addListener(this, &Renderer::enableCamDown);
    cam3.addListener(this, &Renderer::enableCamFront);
    cam4.addListener(this, &Renderer::enableCamBack);
    cam5.addListener(this, &Renderer::enableCamLeft);
    cam6.addListener(this, &Renderer::enableCamRight);
    pers.addListener(this, &Renderer::enableProjPers);
    orth.addListener(this, &Renderer::enableProjOrth);
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

    raytracer_group.setup("Raytracer");
    raytracer_group.add(raytracer_button.setup("Lancer le raytracing"));

    gui.add(&raytracer_group);
 

  lapin.loadModel("bunny.obj");
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
	  ofRotate(180);
	  lapin.draw(OF_MESH_FILL);
	  ofPopMatrix();
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

void Renderer::raytrace() {
  std::vector<raytracer::Sphere> spheres;
  std::vector<raytracer::Point_light> lights;
  raytracer::Color ambiant_color(0.05,0.05,0.05);
  std::map<string, raytracer::Material> materials;

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

