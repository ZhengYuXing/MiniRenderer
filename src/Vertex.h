#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Vector.h"
#include "Color.h"

class Vertex
{
public:
	Vertex();
	Vertex(const Vector& pos, const Color& color, float u, float v);
	Vertex(const Vertex& other);
	Vertex& operator=(const Vertex& other);
	~Vertex();

	Vertex& operator+=(const Vertex& vertex);

	Vertex interpolate(const Vertex& vertex, float factor) const;

	Vector pos() const;
	Color color() const;

	float u() const;
	float v() const;

private:
	Vector pos_;
	Color color_;
	float u_, v_;
};

#endif