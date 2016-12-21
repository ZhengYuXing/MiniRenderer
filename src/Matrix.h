#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "Vector.h"

class Matrix
{
public:
	Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	float* operator[](int i);
	const float* operator[](int i) const;

	Matrix operator+(const Matrix& rhs) const;
	Matrix operator-(const Matrix& rhs) const;
	Matrix operator*(const Matrix& rhs) const;
	Matrix operator*(float factor) const;
	Vector operator*(const Vector& v) const;

	void identity();
	void zero();

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void translate(float x, float y, float z);
	void scale(float x, float y, float z);
	void rotate(float x, float y, float z);
	void rotate(float x, float y, float z, float angle);

	void lookAt(const Vector& eye, const Vector& at, const Vector& up);
	void perspective(float fovy, float aspect, float zn, float zf);

private:
	float m[4][4];
};

#endif