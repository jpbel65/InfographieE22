#pragma once
#include <string>
#include "ofMain.h"

class PVector
{
public:

	PVector(std::string p_name,
		float p_position1_x,
		float p_position1_y,
		float p_position2_x,
		float p_position2_y,
		float p_stroke_width,
		unsigned char p_stroke_color,
		unsigned char p_fill_color,
        ofColor p_fill_color_rgb,
        ofColor p_stroke_color_rgb);
	~PVector();

	std::string m_name;
	float m_position1_x;
	float m_position1_y;
	float m_position2_x;
	float m_position2_y;
	float m_stroke_width;
	unsigned char m_stroke_color;
	unsigned char m_fill_color;
    ofColor m_fill_color_rgb;
    ofColor m_stroke_color_rgb;
};

