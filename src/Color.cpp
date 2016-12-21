#include "Color.h"
#include <cstdlib>

Color::Color() : r_(0.0f), g_(0.0f), b_(0.0f) 
{
}

Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) 
{
}

Color::Color(const Color& other) : r_(other.r_), g_(other.g_), b_(other.b_) 
{
}

Color& Color::operator=(const Color& other)
{
	if (this != &other)
	{
		r_ = other.r_;
		g_ = other.g_;
		b_ = other.b_;
	}
	return *this;
}

Color::~Color()
{
}

Color Color::interpolate(const Color& color, float factor) const
{
	float r = r_ + (color.r_ - r_) * factor;
	float g = g_ + (color.g_ - g_) * factor;
	float b = b_ + (color.b_ - b_) * factor;
	return Color(r, g, b);
}

int Color::toInt() const
{
	int R = static_cast<int>(r_ * 255.0f);
	int G = static_cast<int>(g_ * 255.0f);
	int B = static_cast<int>(b_ * 255.0f);
	return (R << 16) | (G << 8) | B;
}

float Color::r() const
{
	return r_;
}

float Color::g() const
{
	return g_;
}

float Color::b() const
{
	return b_;
}

Color Color::randomColor()
{
	float r = static_cast<float>(rand() % 255) / 255.0f;
	float g = static_cast<float>(rand() % 255) / 255.0f;
	float b = static_cast<float>(rand() % 255) / 255.0f;
	return Color(r, g, b);
}