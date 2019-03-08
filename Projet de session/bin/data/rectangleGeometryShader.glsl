#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices=4) out; // 2 triangles formant un rectangle

in vec2 textureCoord[3];
out vec2 g_textureCoord;

void man() {
	vec4 v0 = gl_in[0] - gl_in[1];
	vec4 v1 = gl_in[0] - gl_in[2];
	vec4 point = gl_in[0] + v0 + v1;

	vec4 c0 = textureCoord[0] - textureCoord[1];
	vec4 c1 = textureCoord[0] - textureCoord[2];
	vec4 tex = textureCoord[0] + c0 + c1;

	for(int i = 0; i < 3; i++){
		gl_Position = gl_in[i];
		g_textureCoord = textureCoord[i];
		EmitVertex();
	}
	gl_Position = point;
	g_textureCoord = tex;
	EmitVertex();
	EndPrimitive();

}