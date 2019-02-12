// IFT3100H19_Triptyque/renderer.cpp
// Classe responsable du rendu de l'application.

#include "renderer.h"

void Renderer::setup()
{
  ofSetFrameRate(0);

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


  gui.setup("Panel");
  gui.add(Lmport.setup("Drag for Import", "Picture"));
  gui.add(ExportBut.setup("Export"));
  gui.add(CleanBut.setup("Clean"));
  

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
}

void Renderer::draw()
{
	image_source.draw(
		offset_horizontal,
		offset_vertical,
		image_width,
		image_height);

	gui.draw();
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
}

