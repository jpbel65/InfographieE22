#version 330 core

uniform float amplitude;
layout(triangles) in;
layout(triangle_strip, max_vertices=9) out; //output 3 triangles
in vec2 textureCoord[3];
out vec2 g_textureCoord;

void main(){
	vec3 normal = cross(vec3(gl_in[0].gl_Position), vec3(gl_in[2].gl_Position));
	//normal = normalize(normal);
	vec4 center = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) + amplitude*vec4(normal, 0.0);
	gl_Position = gl_in[0].gl_Position;
	g_textureCoord = textureCoord[0];
	EmitVertex();
	gl_Position = center;
	g_textureCoord = textureCoord[2];
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	g_textureCoord = textureCoord[0];
	EmitVertex();
	EndPrimitive();

	gl_Position = gl_in[1].gl_Position;
	g_textureCoord = textureCoord[0];
	EmitVertex();
	gl_Position = center;
	g_textureCoord = textureCoord[2];
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	g_textureCoord = textureCoord[0];
	EmitVertex();
	EndPrimitive();

	gl_Position = gl_in[2].gl_Position;
	g_textureCoord = textureCoord[0];
	EmitVertex();
	gl_Position = center;
	g_textureCoord = textureCoord[2];
	EmitVertex();
	gl_Position = gl_in[0].gl_Position;
	g_textureCoord = textureCoord[0];
	EmitVertex();
	EndPrimitive();
}