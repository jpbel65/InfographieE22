// IFT3100H19_Triptyque/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);
  ofEnableLighting();

  // couleur de l'arrière-plan
  ofSetBackgroundColor(31);

  // mode d'échantillonage des coordonnées de texture
  ofDisableArbTex();

  // définir la valeur de l'espacement vertical et horizontal
  offset_vertical = 80;
  offset_horizontal = 80;

  // importer l'image source
  image_source.load("");
  obj1.loadModel("bunny.obj");
  obj2.loadModel("buddha.obj");
  obj3.loadModel("dragon.obj");


  light.setAmbientColor(ofColor(255, 255, 255));
  light.setDiffuseColor(ofColor(255, 255, 255));
  light.setPosition(0.0f, 0.0f, 1000.0f);
  light.enable();


  

  // définir la résolution des images de destination
  image_width = image_source.getWidth();
  image_height = image_source.getHeight();

  

  ExportBut.addListener(this, &Renderer::Export);
  CleanBut.addListener(this, &Renderer::Clean);
	PV1.addListener(this, &Renderer::pv1_line);
	PV2.addListener(this, &Renderer::pv2_square);
	PV3.addListener(this, &Renderer::pv3_ellipse);
	PV4.addListener(this, &Renderer::pv4_triangle);
	PV5.addListener(this, &Renderer::pv5_point);
	Forme_3D_1.addListener(this, &Renderer::Forme3D_De_4);
	Forme_3D_2.addListener(this, &Renderer::Forme3D_De_6);


  gui.setup("Panel");
	  group_Pvector.setup("Type de forme");
	  group_Pvector.add(PV1.setup("line"));
	  group_Pvector.add(PV2.setup("carre"));
	  group_Pvector.add(PV3.setup("ellipse"));
	  group_Pvector.add(PV4.setup("triangle"));
	  group_Pvector.add(PV5.setup("point"));
  gui.add(Lmport.setup("Drag for Import", "Picture"));
  gui.add(ExportBut.setup("Export"));
  gui.add(CleanBut.setup("Clean"));
  textbox_fonction.set("Fonction active", "4.3");
  gui.add(textbox_fonction);
  gui.add(&group_Pvector);
  textbox_pv.set("Forme Primitive", text_pv);
  gui.add(textbox_pv);
  
  //gui.draw();

  arborescence.setup("Graphe de scene");
  textbox_selected_PV.set("PV actif No:", "-1");
	arborescence.add(textbox_selected_PV);
	group_Pv_line.setup("line");
	group_Pv_carre.setup("carre");
	group_Pv_ellipse.setup("ellipse");
	group_Pv_triangle.setup("triangle"); 
	group_Pv_point.setup("point");
	group_Pv_other.setup("autre");

	

  arborescence.add(&group_Pv_line);
  arborescence.add(&group_Pv_carre);
  arborescence.add(&group_Pv_ellipse);
  arborescence.add(&group_Pv_triangle);
  arborescence.add(&group_Pv_point);
  arborescence.add(&group_Pv_other);
  gui.add(&arborescence);

  Forme3D_groupe.setup("Type de P.Geometrique");
  Forme3D_groupe.add(Forme_3D_1.setup("De 4"));
  Forme3D_groupe.add(Forme_3D_2.setup("De 6"));
  gui.add(&Forme3D_groupe);

  group_tran.setup("Transformation Geometrique");
  textbox_transfo.set("Effect de transformation:", "0,0,0");
  group_tran.add(textbox_transfo);
  transfo_transation.addListener(this, &Renderer::func_transation);
  transfo_rotation.addListener(this, &Renderer::func_rotation);
  transfo_scale.addListener(this, &Renderer::func_scale);
  group_tran.add(transfo_transation.setup("Translation"));
  group_tran.add(transfo_rotation.setup("Rotation de 45"));
  group_tran.add(transfo_scale.setup("Proportion"));
  gui.add(&group_tran);

  gui.draw();


  // ajuster la résolution de la fenêtre en fonction de la résolution de l'image source et des espacements
  ofSetWindowShape(
    image_source.getWidth() + offset_horizontal * 2,
    image_source.getHeight() + offset_vertical * 2);
  // copier les pixels de la section de l'image source vers les images de destination
  /*image_left.cropFrom(image_source, image_width * 0, 0, image_width, image_height);
  image_center.cropFrom(image_source, image_width * 1, 0, image_width, image_height);
  image_right.cropFrom(image_source, image_width * 2, 0, image_width, image_height);*/

  // chargement du code source des shaders
  shader.load(
    "image_tint_330_vs.glsl",
    "image_tint_330_fs.glsl");

	histogramme.calculateHistograms(image_source);
}

void Renderer::update() {
	text_fonction = textbox_fonction;
	textbox_pv = text_pv;
	text_transfo = textbox_transfo;
	//obj1.setPosition(ofGetWidth() / 4, 3 * ofGetHeight() / 4, 0);
	//obj2.setPosition(ofGetWidth() / 2, 3 * ofGetHeight() / 4, 0);
	//obj3.setPosition(3 * ofGetWidth() / 4, 3 * ofGetHeight() / 4, 0);
	

	
}

void Renderer::draw()
{
	ofSetColor(255,255,255);
	image_source.draw(
		offset_horizontal,
		offset_vertical,
		image_width,
		image_height);

	ofPushMatrix();
	for (int i = 0; i < Vector_tranfo.size(); i++) {
		transfo trans = Vector_tranfo[i];
		if (trans.type == "t")ofTranslate(trans.effect);
		if (trans.type == "r")ofRotate(ofGetElapsedTimef() * 45.0, trans.effect.x, trans.effect.y, trans.effect.z);
		if (trans.type == "s")ofScale(trans.effect);
	}

	if (text_fonction == "4.3") {
		ofPushMatrix();
		ofScale(0.3f);
		ofTranslate(ofGetWidth() / 2, 6 * ofGetHeight() / 3, 0);
		obj1.draw(OF_MESH_FILL);
		ofPopMatrix();
		ofPushMatrix();
		ofScale(0.5f);
		ofTranslate(ofGetWidth(), 6 * ofGetHeight() / 4, 0);
		obj2.draw(OF_MESH_FILL);
		ofPopMatrix();
		ofPushMatrix();
		ofScale(0.5f);
		ofTranslate(6 * ofGetWidth() / 4, 6 * ofGetHeight() / 4, 0);
		obj3.draw(OF_MESH_FILL);
		ofPopMatrix();
	}
	for (int i = 0; i < Pvector.size(); i++) {
		draw_PVector(Pvector[i]);
	}
	
	if (text_fonction == "4.2") {
		ofPushMatrix();
		ofTranslate(mouse_press_x, mouse_press_y, 100);
		ofRotate(ofGetElapsedTimef() * 20.0, 1, 1, 0);
		glPointSize(10.f);
		VBO.drawElements(GL_TRIANGLES, 36);
		ofPopMatrix();
	}
	ofPopMatrix();
	gui.draw();
	//histogramme.draw();
}

void Renderer::image_export(const string name, const string extension) const
{
	ofImage image;

	// extraire des données temporelles formatées
	string time_stamp = ofGetTimestampString("-%y%m%d-%H%M%S-%i");

	// générer un nom de fichier unique et ordonné
	string file_name = name + time_stamp + "." + extension;

	// capturer le contenu du framebuffer actif
	image.grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());

	// sauvegarder le fichier image
	image.save(file_name);

	ofLog() << "<export image: " << file_name << ">";
}

void Renderer::Export() {
	
	image_export("render", "png");
	ofLogNotice() << "export: true" << endl;
}

void Renderer::Clean() {

	//image_source.load("");
	ofLogNotice() << "clean: true" << endl;
}

void Renderer::dragEvent(ofDragInfo dragInfo) {
	image_source.load(dragInfo.files.at(0));
	image_width = image_source.getWidth();
	image_height = image_source.getHeight();
	// redimensionner la fenêtre selon la résolution de l'image
	if (image_source.getWidth() > 0 && image_source.getHeight() > 0)
		ofSetWindowShape(image_source.getWidth() + offset_horizontal * 2, image_source.getHeight() + offset_vertical * 2);
	histogramme.calculateHistograms(image_source);
}

void Renderer::pv1_line() {
	text_pv = "line";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv2_square() {
	text_pv = "carre";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv3_ellipse() {
	text_pv = "ellipse";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv4_triangle() {
	text_pv = "triangle";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv5_point() {
	text_pv = "point";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::add_PVector() {
	PVector pv = PVector(text_pv, mouse_press_x, mouse_press_y, mouse_current_x, mouse_current_y, 10, 0, 255);
	Pvector.push_back(pv);
	std::cout << Pvector.size() <<std::endl;
	if (text_pv == "line") {
		ofParameter<string> line;
		group_Pv_line.add(line.set("line",to_string(Pvector.size()-1)));
	}
	if (text_pv == "carre") {
		ofParameter<string> line;
		group_Pv_carre.add(line.set("carre", to_string(Pvector.size() - 1)));
	}
	if (text_pv == "ellipse") {
		ofParameter<string> line;
		group_Pv_ellipse.add(line.set("ellipse", to_string(Pvector.size() - 1)));
		std::cout << "line" << endl;
	}
	if (text_pv == "triangle") {
		ofParameter<string> line;
		group_Pv_triangle.add(line.set("triangle", to_string(Pvector.size() - 1)));
		std::cout << "line" << endl;
	}
	if (text_pv == "point") {
		ofParameter<string> line;
		group_Pv_point.add(line.set("point", to_string(Pvector.size() - 1)));
		std::cout << "line" << endl;
	}
	if (text_pv == "other") {
		ofParameter<string> line;
		group_Pv_other.add(line.set("autre", to_string(Pvector.size() - 1)));
		std::cout << "line" << endl;
	}
}

void Renderer::draw_PVector(PVector pv) {
	if (pv.m_name == "line") {
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(
			pv.m_stroke_color,
			pv.m_stroke_color,
			pv.m_stroke_color);
		ofDrawLine(pv.m_position1_x, pv.m_position1_y, pv.m_position2_x, pv.m_position2_y);
	}
	else if ((pv.m_name == "carre")){
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			pv.m_fill_color,
			pv.m_fill_color,
			pv.m_fill_color);
		ofRectRounded(pv.m_position1_x, pv.m_position1_y, pv.m_position2_x-pv.m_position1_x, pv.m_position2_y-pv.m_position1_y,pv.m_stroke_width/2);
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(
			pv.m_stroke_color,
			pv.m_stroke_color,
			pv.m_stroke_color);
		ofRectRounded(pv.m_position1_x, pv.m_position1_y, pv.m_position2_x - pv.m_position1_x, pv.m_position2_y - pv.m_position1_y, pv.m_stroke_width / 2);
	}
	else if ((pv.m_name == "ellipse")) {
		float diameter_x = pv.m_position2_x - pv.m_position1_x;
		float diameter_y = pv.m_position2_y - pv.m_position1_y;
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			pv.m_fill_color,
			pv.m_fill_color,
			pv.m_fill_color);
		ofDrawEllipse(pv.m_position1_x + diameter_x / 2.0f, pv.m_position1_y + diameter_y / 2.0f, diameter_x, diameter_y);
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(
			pv.m_stroke_color,
			pv.m_stroke_color,
			pv.m_stroke_color);
		ofDrawEllipse(pv.m_position1_x + diameter_x / 2.0f, pv.m_position1_y + diameter_y / 2.0f, diameter_x, diameter_y);
	}
	else if ((pv.m_name == "triangle")) {
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(
			pv.m_fill_color,
			pv.m_fill_color,
			pv.m_fill_color);
		ofDrawTriangle(pv.m_position1_x, pv.m_position1_y,pv.m_position1_x, pv.m_position2_y,pv.m_position2_x,pv.m_position2_y);
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(
			pv.m_stroke_color,
			pv.m_stroke_color,
			pv.m_stroke_color);
		ofDrawTriangle(pv.m_position1_x, pv.m_position1_y, pv.m_position1_x, pv.m_position2_y, pv.m_position2_x, pv.m_position2_y);
	}
	else if ((pv.m_name == "point")) {
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(
			pv.m_stroke_color,
			pv.m_stroke_color,
			pv.m_stroke_color);
		ofDrawEllipse(pv.m_position2_x, pv.m_position2_y, pv.m_stroke_width, pv.m_stroke_width);
	}
}

void Renderer::Forme3D_De_4() {
	Forme3D = "De 4";
	cout << "De 4" << endl;
}

void Renderer::Forme3D_De_6() {
	Forme3D = "De 6";
	cout << "De 6" << endl;
}

void Renderer::Add_forme_vbo() {
	if (Forme3D == "De 4") {
		cout << "vbo add d4" << endl;
		const ofIndexType Faces[] = {
			0, 1, 2,
			2, 3, 0,
			0, 4, 1,
			1, 4, 2,
			2, 3, 4,
			4, 0, 3,
		};
		const float Verts[] = {
			-0.500f,  -0.500f,  -0.500f,
			0.500f,  -0.500f,  -0.500f,
			0.500f,  -0.500f,  0.500f,
			-0.500f,  -0.500f,  0.500f,
			0.000f,  0.500f,  0.000f,
		};
		ofVec3f v[5];
		ofVec3f n[12];
		ofFloatColor c[5];
		int i, j = 0;
		for (i = 0; i < 5; i++)
		{

			c[i].r = ofRandom(1.0);
			c[i].g = ofRandom(1.0);
			c[i].b = ofRandom(1.0);

			v[i][0] = Verts[j] * 100.f;
			j++;
			v[i][1] = Verts[j] * 100.f;
			j++;
			v[i][2] = Verts[j] * 100.f;
			j++;

		}

		VBO.setVertexData(&v[0], 5, GL_STATIC_DRAW);
		VBO.setColorData(&c[0], 5, GL_STATIC_DRAW);
		VBO.setIndexData(&Faces[0], 18, GL_STATIC_DRAW);
		//mouse_current_x, mouse_current_y}
	}
	if (Forme3D == "De 6") {
		cout << "vbo add d6" << endl;
		const ofIndexType Faces[] = {
			0, 1, 2,   2, 3, 0,    // v0-v1-v2, v2-v3-v0 (front)
			4, 5, 6,   6, 7, 4,    // v0-v3-v4, v4-v5-v0 (right)
			8, 9,10,  10,11, 8,    // v0-v5-v6, v6-v1-v0 (top)
			12,13,14,  14,15,12,    // v1-v6-v7, v7-v2-v1 (left)
			16,17,18,  18,19,16,    // v7-v4-v3, v3-v2-v7 (bottom)
			20,21,22,  22,23,20     // v4-v7-v6, v6-v5-v4 (back)
		};
		const float Verts[] = {
			.5f, .5f, .5f,  -.5f, .5f, .5f,  -.5f,-.5f, .5f,  .5f,-.5f, .5f, // v0,v1,v2,v3 (front)
			.5f, .5f, .5f,   .5f,-.5f, .5f,   .5f,-.5f,-.5f,  .5f, .5f,-.5f, // v0,v3,v4,v5 (right)
			.5f, .5f, .5f,   .5f, .5f,-.5f,  -.5f, .5f,-.5f, -.5f, .5f, .5f, // v0,v5,v6,v1 (top)
			-.5f, .5f, .5f,  -.5f, .5f,-.5f,  -.5f,-.5f,-.5f, -.5f,-.5f, .5f, // v1,v6,v7,v2 (left)
			-.5f,-.5f,-.5f,   .5f,-.5f,-.5f,   .5f,-.5f, .5f, -.5f,-.5f, .5f, // v7,v4,v3,v2 (bottom)
			.5f,-.5f,-.5f,  -.5f,-.5f,-.5f,  -.5f, .5f,-.5f,  .5f, .5f,-.5f  // v4,v7,v6,v5 (back)
		};
		ofVec3f v[24];
		ofVec3f n[12];
		ofFloatColor c[24];
		int i, j = 0;
		for (i = 0; i < 24; i++)
		{

			c[i].r = ofRandom(1.0);
			c[i].g = ofRandom(1.0);
			c[i].b = ofRandom(1.0);

			v[i][0] = Verts[j] * 100.f;
			j++;
			v[i][1] = Verts[j] * 100.f;
			j++;
			v[i][2] = Verts[j] * 100.f;
			j++;

		}

		VBO.setVertexData(&v[0], 24, GL_STATIC_DRAW);
		VBO.setColorData(&c[0], 24, GL_STATIC_DRAW);
		VBO.setIndexData(&Faces[0], 36, GL_STATIC_DRAW);
	}
}

void Renderer::find_bound_mesh(ofxAssimpModelLoader obj, vector<GLfloat> A) {
	GLfloat
		min_x, max_x,
		min_y, max_y,
		min_z, max_z;
	min_x = max_x = obj.getMesh(0).getVertex(0).x;
	min_y = max_y = obj.getMesh(0).getVertex(0).y;
	min_z = max_z = obj.getMesh(0).getVertex(0).z;
	for (int i = 0; i < obj.getMesh(0).getNumVertices(); i++) {
		ofDefaultVec3 test = obj.getMesh(0).getVertex(i);
		if (test.x < min_x) {
			min_x = test.x;
		}
		else if (test.x > max_x) {
			max_x = test.x;
		}
		if (test.y < min_y) {
			min_y = test.y;
		}
		else if (test.y > max_y) {
			max_y = test.y;
		}
		if (test.z < min_z) {
			min_z = test.z;
		}
		else if (test.z > max_z) {
			max_z = test.z;
		}
	}
	A.push_back(max_x);
	A.push_back(min_x);
	A.push_back(max_y);
	A.push_back(min_y);
	A.push_back(max_z);
	A.push_back(min_z);
}

void Renderer::func_transation() {
	string cuter = text_transfo;
	vector<string>vtoken;
	string delimiter = ",";
	size_t pos = 0;
	string token;
	while ((pos = cuter.find(delimiter)) != string::npos) {
		token = cuter.substr(0, pos);
		vtoken.push_back(token);
		cuter.erase(0, pos + delimiter.length());
	}
	vtoken.push_back(cuter);
	transfo trans;
	trans.effect.x = stof(vtoken[0]);
	trans.effect.y = stof(vtoken[1]);
	trans.effect.z = stof(vtoken[2]);
	trans.type = "t";
	Vector_tranfo.push_back(trans);
};

void Renderer::func_rotation() {
	string cuter = text_transfo;
	vector<string>vtoken;
	string delimiter = ",";
	size_t pos = 0;
	string token;
	while ((pos = cuter.find(delimiter)) != string::npos) {
		token = cuter.substr(0, pos);
		vtoken.push_back(token);
		cuter.erase(0, pos + delimiter.length());
	}
	vtoken.push_back(cuter);
	transfo trans;
	trans.effect.x = stof(vtoken[0]);
	trans.effect.y = stof(vtoken[1]);
	trans.effect.z = stof(vtoken[2]);
	trans.type = "r";
	Vector_tranfo.push_back(trans);
};

void Renderer::func_scale() {
	string cuter = text_transfo;
	vector<string>vtoken;
	string delimiter = ",";
	size_t pos = 0;
	string token;
	while ((pos = cuter.find(delimiter)) != string::npos) {
		token = cuter.substr(0, pos);
		vtoken.push_back(token);
		cuter.erase(0, pos + delimiter.length());
	}
	vtoken.push_back(cuter);
	transfo trans;
	trans.effect.x = stof(vtoken[0]);
	trans.effect.y = stof(vtoken[1]);
	trans.effect.z = stof(vtoken[2]);
	trans.type = "s";
	Vector_tranfo.push_back(trans);
}; 