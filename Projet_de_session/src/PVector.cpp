#include "PVector.h"

PVector::PVector(std::string p_name,
	float p_position1_x,
	float p_position1_y,
	float p_position2_x,
	float p_position2_y,
	float p_stroke_width,
	unsigned char p_stroke_color,
	unsigned char p_fill_color)
{
	m_name = p_name;
	m_position1_x = p_position1_x;
	m_position1_y = p_position1_y;
	m_position2_x = p_position2_x;
	m_position2_y = p_position2_y;
	m_stroke_width = p_stroke_width;
	m_stroke_color = p_stroke_color;
	m_fill_color = p_fill_color;
};


PVector::~PVector()
{
}
