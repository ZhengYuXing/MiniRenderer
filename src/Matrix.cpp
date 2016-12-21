#include "Matrix.h"
#include <cmath>

Matrix::Matrix()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = 0.0f;
		}
	}
}

Matrix::Matrix(const Matrix& other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = other.m[i][j];
		}
	}
}

Matrix& Matrix::operator=(const Matrix& other)
{
	if (this != &other)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m[i][j] = other.m[i][j];
			}
		}
	}
	return *this;
}

Matrix::~Matrix()
{
}

float* Matrix::operator[](int i)
{
	return m[i];
}

const float* Matrix::operator[](int i) const
{
	return m[i];
}

Matrix Matrix::operator+(const Matrix& rhs) const
{
	Matrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = m[i][j] + rhs.m[i][j];
		}
	}
	return mat;	
}

Matrix Matrix::operator-(const Matrix& rhs) const
{
	Matrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = m[i][j] - rhs.m[i][j];
		}
	}
	return mat;	
}

Matrix Matrix::operator*(float factor) const
{
	Matrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = m[i][j] * factor;
		}
	}
	return mat;	
}

Matrix Matrix::operator*(const Matrix& rhs) const
{
	Matrix mat;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			mat.m[i][j] = m[i][0] * rhs.m[0][j] +
				          m[i][1] * rhs.m[1][j] +
				          m[i][2] * rhs.m[2][j] +
				          m[i][3] * rhs.m[3][j];
		}
	}
	return mat;	
}

Vector Matrix::operator*(const Vector& v) const
{
	float x = v.x(), y = v.y(), z = v.z(), w = v.w();
	float X = x * m[0][0] + y * m[1][0] + z * m[2][0] + w * m[3][0];
	float Y = x * m[0][1] + y * m[1][1] + z * m[2][1] + w * m[3][1];
	float Z = x * m[0][2] + y * m[1][2] + z * m[2][2] + w * m[3][2];
	float W = x * m[0][3] + y * m[1][3] + z * m[2][3] + w * m[3][3];
	return Vector(X, Y, Z, W);
}

void Matrix::identity()
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
	m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;
}

void Matrix::zero()
{
	m[0][0] = m[0][1] = m[0][2] = m[0][3] = 0.0f;
	m[1][0] = m[1][1] = m[1][2] = m[1][3] = 0.0f;
	m[2][0] = m[2][1] = m[2][2] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0.0f;
}

void Matrix::rotateX(float angle)
{
	identity();
	float s = sin(angle);
	float c = cos(angle);
	m[1][1] = c;
	m[1][2] = s;
	m[2][1] = -s;
	m[2][2] = c;
}

void Matrix::rotateY(float angle)
{
	identity();
	float s = sin(angle);
	float c = cos(angle);
	m[0][0] = c;
	m[0][2] = -s;
	m[2][0] = s;
	m[2][2] = c;
}

void Matrix::rotateZ(float angle)
{
	identity();
	float s = sin(angle);
	float c = cos(angle);
	m[0][0] = c;
	m[0][1] = s;
	m[1][0] = -s;
	m[1][1] = c;

}

void Matrix::translate(float x, float y, float z)
{
	identity();
	m[3][0] = x;
	m[3][1] = y;
	m[3][2] = z;
}

void Matrix::scale(float x, float y, float z)
{
	identity();
	m[0][0] = x;
	m[1][1] = y;
	m[2][2] = z;
}

void Matrix::rotate(float x, float y, float z)
{
	Matrix a, b, c;
	a.rotateX(x);
	b.rotateY(y);
	c.rotateZ(z);
	*this = a * b * c;
}

// ???
void Matrix::rotate(float x, float y, float z, float angle)
{
	float qsin = sin(angle * 0.5f);
	float qcos = cos(angle * 0.5f);
	Vector vec(x, y, z);
	vec.normalize();
	x = vec.x() * qsin;
	y = vec.y() * qsin;
	z = vec.z() * qsin;
	float w = qcos;
	m[0][0] = 1 - 2 * y * y - 2 * z * z;
	m[1][0] = 2 * x * y - 2 * w * z;
	m[2][0] = 2 * x * z + 2 * w * y;
	m[0][1] = 2 * x * y + 2 * w * z;
	m[1][1] = 1 - 2 * x * x - 2 * z * z;
	m[2][1] = 2 * y * z - 2 * w * x;
	m[0][2] = 2 * x * z - 2 * w * y;
	m[1][2] = 2 * y * z + 2 * w * x;
	m[2][2] = 1 - 2 * x * x - 2 * y * y;
	m[0][3] = m[1][3] = m[2][3] = 0.0f;
	m[3][0] = m[3][1] = m[3][2] = 0.0f;	
	m[3][3] = 1.0f;
}

void Matrix::lookAt(const Vector& eye, const Vector& at, const Vector& up)
{
	Vector axisZ = at - eye;
	axisZ.normalize();
	Vector axisY = up.cross(axisZ);
	axisY.normalize();
	Vector axisX = axisZ.cross(axisY);

	m[0][0] = axisX.x();
	m[1][0] = axisX.y();
	m[2][0] = axisX.z();
	m[3][0] = -axisX.dot(eye);

	m[0][1] = axisY.x();
	m[1][1] = axisY.y();
	m[2][1] = axisY.z();
	m[3][1] = -axisY.dot(eye);

	m[0][2] = axisZ.x();
	m[1][2] = axisZ.y();
	m[2][2] = axisZ.z();
	m[3][2] = -axisZ.dot(eye);

	m[0][3] = m[1][3] = m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

void Matrix::perspective(float fovy, float aspect, float zn, float zf)
{
	zero();
	float yScale = 1.0f / tan(fovy * 0.5f);
	m[0][0] = yScale / aspect;
	m[1][1] = yScale;
	m[2][2] = zf / (zf - zn);
	m[3][2] = - zn * zf / (zf - zn);
	m[2][3] = 1.0f;
}