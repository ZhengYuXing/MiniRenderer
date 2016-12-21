#include "Vector.h"
#include <cmath>

Vector::Vector() : x_(0.0f), y_(0.0f), z_(0.0f), w_(1.0f)
{
}

Vector::Vector(float x, float y, float z, float w)
  : x_(x), y_(y), z_(z), w_(w)
{
}

Vector::Vector(const Vector& other) 
  : x_(other.x_), y_(other.y_), z_(other.z_), w_(other.w_)
{
}

Vector& Vector::operator=(const Vector& other)
{
	if (this != &other)
	{
		x_ = other.x_;
		y_ = other.y_;
		z_ = other.z_;
		w_ = other.w_;
	}
	return *this;
}

Vector::~Vector()
{
}

Vector Vector::operator+(const Vector& rhs) const
{
	return Vector(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_, 1.0f);
}

Vector Vector::operator-(const Vector& rhs) const
{
	return Vector(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_, 1.0f);
}

Vector Vector::operator*(float factor) const
{
	return Vector(x_ * factor, y_ * factor, z_ * factor, 1.0f);
}

float Vector::length() const
{
	return sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

void Vector::normalize()
{
	if (length() != 0.0f)
	{
		float factor = 1.0f / length();
		x_ *= factor;
		y_ *= factor;
		z_ *= factor;
	}
}

float Vector::dot(const Vector& v) const
{
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vector Vector::cross(const Vector& v) const
{
	float x = y_ * v.z_ - z_ * v.y_;
	float y = z_ * v.x_ - x_ * v.z_;
	float z = x_ * v.y_ - y_ * v.x_;
	return Vector(x, y, z, 1.0f);
}

Vector Vector::interpolate(const Vector& v, float factor) const
{
	return *this + (v - *this) * factor;
}

float Vector::x() const
{
	return x_;
}

float Vector::y() const
{
	return y_;
}

float Vector::z() const
{
	return z_;
}

float Vector::w() const
{
	return w_;
}