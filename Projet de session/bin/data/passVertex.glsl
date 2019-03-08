#version 330 core

layout(location=0) in vec3 position; //in vec4
layout(location=2) in vec2 tex;
out vec2 textureCoord;

void main(){
	gl_Position = vec4(position,1.0);//gl_Position = position;
	textureCoord = tex;
}
