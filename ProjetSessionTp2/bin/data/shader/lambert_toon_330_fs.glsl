// IFT3100H19 ~ lambert_330_fs.glsl

#version 330

// attributs interpolés à partir des valeurs en sortie du shader de sommets
in vec3 surface_position;
in vec3 surface_normal;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
uniform vec3 color_ambient;
uniform vec3 color_diffuse;

// position d'une source de lumière
uniform vec3 light_position;

void main()
{
  // re-normaliser la normale après interpolation (n)
  vec3 n = normalize(surface_normal);

  // calculer direction surface vers caméra
  vec3 v = normalize(-surface_position);

  if(abs(dot(v, n)) < 0.2 ){
    fragment_color = vec4(0.0,0.0,0.0, 1.0);
  } else {

	  // reduce resolution
	  n = vec3(floor(n*10.0))/10.0;

	  // calculer la direction de la surface vers la lumière (l)
	  vec3 l = normalize(light_position - surface_position);

	  // calculer le niveau de réflexion diffuse (n • l)
	  float reflection_diffuse = max(dot(n, l), 0.0);

	  // déterminer la couleur du fragment
	  fragment_color = vec4(color_ambient + color_diffuse * reflection_diffuse, 1.0);
  }
}
