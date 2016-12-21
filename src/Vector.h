#ifndef __VECTOR_H__
#define __VECTOR_H__

class Vector
{
public:
	Vector();
	Vector(float x, float y, float z, float w = 1.0f);
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	Vector operator+(const Vector& rhs) const;
	Vector operator-(const Vector& rhs) const;
	Vector operator*(float factor) const;

	float length() const;
	void normalize();
	float dot(const Vector& v) const;
	Vector cross(const Vector& v) const;
	Vector interpolate(const Vector& v, float factor) const;

	float x() const;
	float y() const;
	float z() const;
	float w() const;

private:
	float x_, y_, z_, w_;
};

#endif