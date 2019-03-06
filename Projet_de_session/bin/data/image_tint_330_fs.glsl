// IFT3100H19 ~ image_tint_330_fs.glsl

#version 330

// attributs uniformes
uniform sampler2D image_filtre;

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  // échantillonner la texture
  vec4 texture_sample = texture(image_filtre, surface_texcoord);
  // vec4 texture_sample_left = texture(image, vec2(surface_texcoord.x - 1, surface_texcoord.y));
  // vec4 texture_sample_right = texture(image, vec2(surface_texcoord.x + 1, surface_texcoord.y));
  // vec4 texture_sample_bottom = texture(image, vec2(surface_texcoord.x, surface_texcoord.y - 1));
  // vec4 texture_sample_top = texture(image, vec2(surface_texcoord.x, surface_texcoord.y + 1));

  // mixage avec la teinte de couleur
  // vec4 filtered_color = 5 * texture_sample - texture_sample_left - texture_sample_right - texture_sample_bottom - texture_sample_top;
  // int r = 5 * texture_sample.r - texture_sample_left.r - texture_sample_right.r - texture_sample_bottom.r - texture_sample_top.r;
  // int g = 5 * texture_sample.g - texture_sample_left.g - texture_sample_right.g - texture_sample_bottom.g - texture_sample_top.g;
  // int b = 5 * texture_sample.b - texture_sample_left.b - texture_sample_right.b - texture_sample_bottom.b - texture_sample_top.b;

  // couleur finale du fragment
  // fragment_color = texture_sample;
  fragment_color = vec4(1.0,1.0,1.0,1.0);
}
