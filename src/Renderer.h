#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Vector.h"
#include "Matrix.h"
#include "Vertex.h"
#include "Color.h"
#include "Texture.h"
#include "Mesh.h"
#include <vector>
#include <string>

#define INT2CHAR_BIT(num, bit) (unsigned char)(((num) >> (bit)) & 0xff)
#define INT2CHAR(num) INT2CHAR_BIT((num),0), INT2CHAR_BIT((num),8), INT2CHAR_BIT((num),16), INT2CHAR_BIT((num),24)

enum RenderState 
{ 
	RENDER_STATE_WIREFRAME,
	RENDER_STATE_COLOR, 
	RENDER_STATE_TEXTURE 
};

class Renderer
{
public:
	Renderer(int w, int h);

	void clearBuffer();
	
	void setRenderState(RenderState rs);
	void setTexture(const Texture& tex);

	void setTranslation(float x, float y, float z);
	void setRotation(float x, float y, float z, float angle);
	void setScale(float x, float y, float z);

	void setWorld(const Matrix& worldMatrix);
	void setCamera(const Vector& eye, const Vector& at, const Vector& up);
	void setFrustum(float fovy, float aspect, float zn, float zf);

	void drawPoint(int x, int y, const Color& color);
	void drawPoint(int x, int y, float z, const Color& color);
	void drawPoint(const Vector& p, const Color& color);
	void drawPoint(const Vertex& v);

	void drawLine(int x1, int y1, int x2, int y2, const Color& color);
	void drawLine(const Vector& p1, const Vector& p2, const Color& color);
	void drawLine(const Vertex& v1, const Vertex& v2);

	void drawTriangle(const Vector& p1, const Vector& p2, const Vector& p3, const Color& color);
	void drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	void drawMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices);
	void drawMesh(const Mesh& mesh);

	void loadObj(const std::string& file);

	void saveBmp(const std::string& file) const;

private:
	void updateTransform();

	Vector transformPosition(const Vector& p) const;
	Vertex transformPosition(const Vertex& v) const;

	int checkCVV(const Vector& v) const;

private:
	RenderState renderState;
	Texture texture;
	Matrix world, view, projection, transform;
	int width, height;
	std::vector<std::vector<Color>> frameBuffer;
	std::vector<std::vector<float>> depthBuffer;
};

#endif