#version 330 core

in vec2 textureCoord;

uniform sampler2D texture0;

layout(location=0) out vec4 color;

void main(){
	color = texture(texture0, textureCoord);
	//color.g = textureCoord.x;
}