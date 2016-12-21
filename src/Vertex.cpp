#include "Vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(const Vector& pos, const Color& color, float u, float v)
  : pos_(pos), color_(color), u_(u), v_(v)
{
}

Vertex::Vertex(const Vertex& other) 
  : pos_(other.pos_), color_(other.color_), u_(other.u_), v_(other.v_)
{
}

Vertex& Vertex::operator=(const Vertex& other)
{
	if (this != &other)
	{
		pos_ = other.pos_;
		color_ = other.color_;
		u_ = other.u_;
		v_ = other.v_;
	}
	return *this;
}

Vertex::~Vertex()
{
}

Vertex Vertex::interpolate(const Vertex& vertex, float factor) const
{
	Vector pos = pos_.interpolate(vertex.pos_, factor);
	Color color = color_.interpolate(vertex.color_, factor);
	float u = u_ + (vertex.u_ - u_) * factor;
	float v = v_ + (vertex.v_ - v_) * factor;
	return Vertex(pos, color, u, v);
}

Vector Vertex::pos() const
{
	return pos_;
}

Color Vertex::color() const
{
	return color_;
}

float Vertex::u() const
{
	return u_;
}

float Vertex::v() const
{
	return v_;
}