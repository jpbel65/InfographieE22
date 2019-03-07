#version 330 core

layout(location=0) in vec4 position;
layout(location=2) in vec2 tex;
out vec2 textureCoord;

void main(){
	gl_Position = position;
	textureCoord = tex;
}
