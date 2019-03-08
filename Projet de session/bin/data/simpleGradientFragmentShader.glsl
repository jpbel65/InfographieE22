#version 330 core

//uniform sampler1D texturel;

layout(location=0) out vec4 color;
in vec2 g_textureCoord;

void main(){
	color = vec4(g_textureCoord.x, 0.0, 0.0, 1.0);
}