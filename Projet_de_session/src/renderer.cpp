// IFT3100H19_Triptyque/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(60);

  // couleur de l'arrière-plan
  ofSetBackgroundColor(31);

  // mode d'échantillonage des coordonnées de texture
  ofDisableArbTex();

  // définir la valeur de l'espacement vertical et horizontal
  offset_vertical = 80;
  offset_horizontal = 80;

  // importer l'image source
  image_source.load("");

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
    FV1.addListener(this, &Renderer::fv1_maison);
    FV2.addListener(this, &Renderer::fv2_fleche);
    FV3.addListener(this, &Renderer::fv3_sapin);
    FV4.addListener(this, &Renderer::fv4_bateau);
	Forme_3D_1.addListener(this, &Renderer::Forme3D_De_4);
	Forme_3D_2.addListener(this, &Renderer::Forme3D_De_6);
    
    HSVpickStroke.addListener(this, &Renderer::saveHSVStroke);
    HSVpickFill.addListener(this, &Renderer::saveHSVFill);
    RGBpickStroke.addListener(this, &Renderer::saveRGBStroke);
    RGBpickFill.addListener(this, &Renderer::saveRGBFill);

  gui.setup("Panel");
	  group_Pvector.setup("Type de forme");
      group_Pvector.add(strokeSize.setup("Stroke Size",1,0,100));
	  group_Pvector.add(PV1.setup("line"));
	  group_Pvector.add(PV2.setup("carre"));
	  group_Pvector.add(PV3.setup("ellipse"));
	  group_Pvector.add(PV4.setup("triangle"));
	  group_Pvector.add(PV5.setup("point"));
      group_Pvector.add(FV1.setup("maison"));
      group_Pvector.add(FV2.setup("bonhomme"));
      group_Pvector.add(FV3.setup("sapin"));
      group_Pvector.add(FV4.setup("bateau"));
  gui.add(Lmport.setup("Drag for Import", "Picture"));
  gui.add(ExportBut.setup("Export"));
  gui.add(CleanBut.setup("Clean"));
  textbox_fonction.set("Fonction active", "4.2");
  gui.add(textbox_fonction);
  gui.add(&group_Pvector);
  textbox_pv.set("Forme Primitive", text_pv);
  gui.add(textbox_pv);
    
  // selection couleur RGB HSV
    groupeCouleur.setup("Selection de couleur");
    // RGB
    groupeCouleur.add(Rslider.setup("R",1, 0, 255));
    groupeCouleur.add(Gslider.setup("G",1, 0, 255));
    groupeCouleur.add(Bslider.setup("B",1, 0, 255));
    groupeCouleur.add(RGBpickStroke.setup("Save stroke RGB"));
    groupeCouleur.add(RGBpickFill.setup("Save fill RGB"));
    // HSV
    groupeCouleur.add(Hslider.setup("Hue",1, 0, 360));
    groupeCouleur.add(Sslider.setup("Saturation",1, 0, 100));
    groupeCouleur.add(Vslider.setup("Value",1, 0, 100));
    groupeCouleur.add(HSVpickStroke.setup("Save stroke HSV"));
    groupeCouleur.add(HSVpickFill.setup("Save fill HSV"));
    
    gui.add(&groupeCouleur);
  
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


  gui.draw();


  // ajuster la résolution de la fenêtre en fonction de la résolution de l'image source et des espacements
  ofSetWindowShape(
    1200,
    900);
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
void Renderer::saveHSVStroke() {
    
    int Hvalue = stoi(Hslider.getParameter().toString())*255/360;
    int Svalue = stoi(Sslider.getParameter().toString())*255/100;
    int Vvalue = stoi(Vslider.getParameter().toString())*255/100;
    pickedColor.setHsb(Hvalue,Svalue,Vvalue);
    ofSetColor(pickedColor2);
}
void Renderer::saveRGBStroke() {
    int Rvalue = stoi(Rslider.getParameter().toString());
    int Gvalue = stoi(Gslider.getParameter().toString());
    int Bvalue = stoi(Bslider.getParameter().toString());
    pickedColor.set(Rvalue, Gvalue, Bvalue);
    ofSetColor(pickedColor2);
}
void Renderer::saveHSVFill() {
    
    int Hvalue = stoi(Hslider.getParameter().toString())*255/360;
    int Svalue = stoi(Sslider.getParameter().toString())*255/100;
    int Vvalue = stoi(Vslider.getParameter().toString())*255/100;
    pickedColor2.setHsb(Hvalue,Svalue,Vvalue);
    ofSetColor(pickedColor);
}
void Renderer::saveRGBFill() {
    int Rvalue = stoi(Rslider.getParameter().toString());
    int Gvalue = stoi(Gslider.getParameter().toString());
    int Bvalue = stoi(Bslider.getParameter().toString());
    pickedColor2.set(Rvalue, Gvalue, Bvalue);
    ofSetColor(pickedColor);
}

void Renderer::update() {
	text_fonction = textbox_fonction;
	textbox_pv = text_pv;
}

void Renderer::draw()
{
	ofSetColor(255,255,255);
	if (image_source.getHeight() > 0 && image_source.getWidth() > 0)  {
		image_source.draw(
			offset_horizontal,
			offset_vertical,
			image_width,
			image_height);
		histogramme.draw();
	}
	for (int i = 0; i < Pvector.size(); i++) {
		draw_PVector(Pvector[i]);
	}
	gui.draw();
	
	//ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 100);
	//ofRotate(ofGetElapsedTimef() * 20.0, 1, 1, 0);
	glPointSize(10.f);
	VBO.drawElements(GL_TRIANGLES, 36);
    
    
    // if case pour mode (curseur de l'utilisateur)
    if (appMode == "normal"){
        ofShowCursor();
        mouseDrawing.clear();
        
    }
    else if (appMode == "drawing"){
        ofHideCursor();
        ofSetColor(255,255,255);
        mouseDrawing.load("cursor_drawing.png");
        mouseDrawing.draw(ofGetMouseX(),ofGetMouseY(),30,30);
        
    }
    else if (appMode == "bonhomme"){
        ofHideCursor();
        ofSetColor(255,255,255);
        mouseDrawing.load("cursor_bonhomme.png");
        mouseDrawing.draw(ofGetMouseX(),ofGetMouseY(),30,30);
        
    }
    else if (appMode == "maison"){
        ofHideCursor();
        ofSetColor(204,136,0);
        mouseDrawing.load("cursor_maison.png");
        mouseDrawing.draw(ofGetMouseX(),ofGetMouseY(),30,30);
        
    }
    else if (appMode == "sapin"){
        ofHideCursor();
        ofSetColor(51,153,0);
        mouseDrawing.load("cursor_sapin.png");
        mouseDrawing.draw(ofGetMouseX(),ofGetMouseY(),30,30);
        
    }
    else if (appMode == "bateau"){
        ofHideCursor();
        ofSetColor(102,179,255);
        mouseDrawing.load("cursor_bateau.png");
        mouseDrawing.draw(ofGetMouseX(),ofGetMouseY(),30,30);
        
    }
    else{
        ofLog() << "<app::WARNING APPMODE INVALID: " << appMode << ">";
    }
    
    
    
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
    appMode = "drawing";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv2_square() {
	text_pv = "carre";
    appMode = "drawing";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv3_ellipse() {
	text_pv = "ellipse";
    appMode = "drawing";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv4_triangle() {
	text_pv = "triangle";
    appMode = "drawing";
	textbox_pv.set("Forme Primitive", text_pv);
}

void Renderer::pv5_point() {
	text_pv = "point";
    appMode = "drawing";
	textbox_pv.set("Forme Primitive", text_pv);
}
void Renderer::fv1_maison() {
    text_pv = "maison";
    appMode = "maison";
    textbox_pv.set("Forme Vectorielle", text_pv);
}
void Renderer::fv2_fleche() {
    text_pv = "bonhomme";
    appMode = "bonhomme";
    textbox_pv.set("Forme Vectorielle", text_pv);
}
void Renderer::fv3_sapin() {
    text_pv = "sapin";
    appMode = "sapin";
    textbox_pv.set("Forme Vectorielle", text_pv);
}
void Renderer::fv4_bateau() {
    text_pv = "bateau";
    appMode = "bateau";
    textbox_pv.set("Forme Vectorielle", text_pv);
}

void Renderer::add_PVector() {
	PVector pv = PVector(text_pv, mouse_press_x, mouse_press_y, mouse_current_x, mouse_current_y, stoi(strokeSize.getParameter().toString()), 0, 255,pickedColor2,pickedColor);
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
    if (text_pv == "maison") {
        ofParameter<string> line;
        group_Pv_other.add(line.set("maison", to_string(Pvector.size() - 1)));
        std::cout << "line" << endl;
    }
    if (text_pv == "bonhomme") {
        ofParameter<string> line;
        group_Pv_other.add(line.set("bonhomme", to_string(Pvector.size() - 1)));
        std::cout << "line" << endl;
    }
    if (text_pv == "sapin") {
        ofParameter<string> line;
        group_Pv_other.add(line.set("sapin", to_string(Pvector.size() - 1)));
        std::cout << "line" << endl;
    }
    if (text_pv == "bateau") {
        ofParameter<string> line;
        group_Pv_other.add(line.set("bateau", to_string(Pvector.size() - 1)));
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
		ofSetColor(pv.m_fill_color_rgb);
		ofDrawLine(pv.m_position1_x, pv.m_position1_y, pv.m_position2_x, pv.m_position2_y);
	}
	else if ((pv.m_name == "carre")){
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(pv.m_fill_color_rgb);
		ofRectRounded(pv.m_position1_x, pv.m_position1_y, pv.m_position2_x-pv.m_position1_x, pv.m_position2_y-pv.m_position1_y,pv.m_stroke_width/2);
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(pv.m_stroke_color_rgb);
		ofRectRounded(pv.m_position1_x, pv.m_position1_y, pv.m_position2_x - pv.m_position1_x, pv.m_position2_y - pv.m_position1_y, pv.m_stroke_width / 2);
	}
	else if ((pv.m_name == "ellipse")) {
		float diameter_x = pv.m_position2_x - pv.m_position1_x;
		float diameter_y = pv.m_position2_y - pv.m_position1_y;
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(pv.m_fill_color_rgb);
		ofDrawEllipse(pv.m_position1_x + diameter_x / 2.0f, pv.m_position1_y + diameter_y / 2.0f, diameter_x, diameter_y);
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(pv.m_stroke_color_rgb);
		ofDrawEllipse(pv.m_position1_x + diameter_x / 2.0f, pv.m_position1_y + diameter_y / 2.0f, diameter_x, diameter_y);
	}
	else if ((pv.m_name == "triangle")) {
		ofFill();
		ofSetLineWidth(0);
		ofSetColor(pv.m_fill_color_rgb);
		ofDrawTriangle(pv.m_position1_x, pv.m_position1_y,pv.m_position1_x, pv.m_position2_y,pv.m_position2_x,pv.m_position2_y);
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(pv.m_stroke_color_rgb);
		ofDrawTriangle(pv.m_position1_x, pv.m_position1_y, pv.m_position1_x, pv.m_position2_y, pv.m_position2_x, pv.m_position2_y);
	}
	else if ((pv.m_name == "point")) {
		ofNoFill();
		ofSetLineWidth(pv.m_stroke_width);
		ofSetColor(pv.m_stroke_color_rgb);
		ofDrawEllipse(pv.m_position2_x, pv.m_position2_y, pv.m_stroke_width, pv.m_stroke_width);
	}
    else if ((pv.m_name == "maison")){
        float rectLarg = pv.m_position2_x - pv.m_position1_x;
        float rectHaut = pv.m_position2_y - pv.m_position1_y;
        float topmaisonY = pv.m_position1_y - rectLarg/4;
        float topmaisonX = pv.m_position1_x + rectLarg/2;
        
        ofFill();
        ofSetLineWidth(0);
        ofSetColor(150,75,0);
        ofDrawRectangle(pv.m_position1_x, pv.m_position1_y, rectLarg, rectHaut);
        ofSetColor(77, 40, 0);
        ofDrawTriangle(pv.m_position1_x, pv.m_position1_y, pv.m_position1_x + rectLarg, pv.m_position1_y, topmaisonX, topmaisonY);
    }
    else if ((pv.m_name == "bonhomme")){
        ofFill();
        ofSetLineWidth(0);
        ofSetColor(255,255,255);
        float diameter_x = pv.m_position2_x - pv.m_position1_x;
        float diameter_y = pv.m_position2_y - pv.m_position1_y;
        float diameter = 0;
        if (diameter_x > diameter_y){diameter = diameter_x;}
        if (diameter_y > diameter_x){diameter = diameter_y;}
        
        ofDrawCircle(pv.m_position1_x, pv.m_position1_y, diameter);
        ofDrawCircle(pv.m_position1_x, pv.m_position1_y - diameter, diameter/1.5);
        ofDrawCircle(pv.m_position1_x, pv.m_position1_y - diameter - diameter/1.5, diameter/3);
        
        float posHeadY = pv.m_position1_y - diameter - diameter/1.5;
        // nez
        ofSetColor(255, 128, 0);
        ofDrawCircle(pv.m_position1_x, posHeadY, diameter/12);
        
        // yeux
        ofSetColor(0, 0, 0);
        ofDrawCircle(pv.m_position1_x-diameter/12, posHeadY-diameter/15, diameter/18);
        ofDrawCircle(pv.m_position1_x+diameter/12, posHeadY-diameter/15, diameter/18);
        ofSetColor(255, 255, 255);
    }
    else if ((pv.m_name == "bateau")){
        ofFill();
        ofSetLineWidth(0);
        float diameter_x = pv.m_position2_x - pv.m_position1_x;
        float diameter_y = pv.m_position2_y - pv.m_position1_y;
        float diameter = 0;
        if (diameter_x > diameter_y){diameter = diameter_x;}
        if (diameter_y > diameter_x){diameter = diameter_y;}
        
        ofSetColor(77, 40, 0);
        ofDrawTriangle(pv.m_position1_x-diameter*2, pv.m_position1_y+diameter, pv.m_position1_x+diameter*2, pv.m_position1_y+diameter, pv.m_position1_x, pv.m_position1_y+diameter*2);
        ofDrawRectangle(pv.m_position1_x-diameter/8, pv.m_position1_y-diameter/8, diameter/4, diameter*2);
        
        ofSetColor(255,255,255);
        ofDrawTriangle(pv.m_position1_x-diameter, pv.m_position1_y, pv.m_position1_x+diameter, pv.m_position1_y, pv.m_position1_x, pv.m_position1_y-diameter);

    }
    else if ((pv.m_name == "sapin")){
        ofFill();
        ofSetLineWidth(0);
        float diameter_x = pv.m_position2_x - pv.m_position1_x;
        float diameter_y = pv.m_position2_y - pv.m_position1_y;
        float diameter = 0;
        if (diameter_x > diameter_y){diameter = diameter_x;}
        if (diameter_y > diameter_x){diameter = diameter_y;}
        
        //tronc
        ofSetColor(77, 40, 0);
        ofDrawRectangle(pv.m_position1_x-diameter/8, pv.m_position1_y-diameter/8, diameter/4, diameter*2.5);
        
        // gros
        ofSetColor(51,77,0);
        ofDrawTriangle(pv.m_position1_x-diameter*2, pv.m_position1_y+diameter*2, pv.m_position1_x+diameter*2, pv.m_position1_y+diameter*2, pv.m_position1_x, pv.m_position1_y+2*diameter/3);
        
        //moyen
        ofSetColor(68,102,0);
        ofDrawTriangle(pv.m_position1_x-diameter*1.5, pv.m_position1_y+diameter, pv.m_position1_x+diameter*1.5, pv.m_position1_y+diameter, pv.m_position1_x, pv.m_position1_y-diameter/3);
        
        //petit
        ofSetColor(85,128,0);
        ofDrawTriangle(pv.m_position1_x-diameter, pv.m_position1_y, pv.m_position1_x+diameter, pv.m_position1_y, pv.m_position1_x, pv.m_position1_y-diameter);
        
        
        
        
        
        
        
        
        
        
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
