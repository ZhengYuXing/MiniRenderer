#include "Renderer.h"
#include <limits>
#include <algorithm>
#include <fstream>
#include <sstream>

Renderer::Renderer(int w, int h) 
  : width(w), height(h), renderState(RENDER_STATE_WIREFRAME),
    frameBuffer(h, std::vector<Color>(w, Color())), 
	depthBuffer(h, std::vector<float>(w, std::numeric_limits<float>::max()))
{
	world.identity();
	view.identity();
	projection.identity();
	transform.identity();
}

void Renderer::clearBuffer()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			frameBuffer[i][j] = Color();
			depthBuffer[i][j] = std::numeric_limits<float>::max();
		}
	}
}

void Renderer::setRenderState(RenderState rs)
{
	renderState = rs;
}

void Renderer::setTexture(const Texture& tex)
{
	texture = tex;
}

void Renderer::setTranslation(float x, float y, float z)
{
	Matrix matrix;
	matrix.translate(x, y, z);
	world = world * matrix;
	updateTransform();
}

void Renderer::setRotation(float x, float y, float z, float angle)
{
	Matrix matrix;
	matrix.rotate(x, y, z, angle);
	world = world * matrix;
	updateTransform();
}

void Renderer::setScale(float x, float y, float z)
{
	Matrix matrix;
	matrix.scale(x, y, z);
	world = world * matrix;
	updateTransform();
}

void Renderer::setWorld(const Matrix& worldMatrix)
{
	world = worldMatrix;
	updateTransform();
}

void Renderer::setCamera(const Vector& eye, const Vector& at, const Vector& up)
{
	view.lookAt(eye, at, up);
	updateTransform();
}

void Renderer::setFrustum(float fovy, float aspect, float zn, float zf)
{
	projection.perspective(fovy, aspect, zn, zf);
	updateTransform();
}

void Renderer::drawPoint(int x, int y, const Color& color)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		frameBuffer[y][x] = color;
	}
}

void Renderer::drawPoint(int x, int y, float z, const Color& color)
{
	if (x >= 0 && x < width && y >= 0 && y < height && z <= depthBuffer[y][x])
	{
		frameBuffer[y][x] = color;
		depthBuffer[y][x] = z;
	}
}

void Renderer::drawPoint(const Vector& p, const Color& color)
{
	int x = static_cast<int>(p.x());
	int y = static_cast<int>(p.y());
	drawPoint(x, y, p.z(), color);
}

void Renderer::drawPoint(const Vertex& v)
{
	if (renderState == RENDER_STATE_COLOR)
	{
		drawPoint(v.pos(), v.color());
	}
	else if (renderState == RENDER_STATE_TEXTURE)
	{
		drawPoint(v.pos(), texture.sample(v.u(), v.v()));
	}
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, const Color& color)
{
	if (x1 == x2 && y1 == y2)
	{
		drawPoint(x1, y1, color);
	}
	else if (x1 == x2)
	{
		int inc = y1 < y2 ? 1 : -1;
		for (int y = y1; y != y2; y += inc)
		{
			drawPoint(x1, y, color);
		}
		drawPoint(x2, y2, color);
	}
	else if (y1 == y2)
	{
		int inc = x1 < x2 ? 1 : -1;
		for (int x = x1; x != x2; x += inc)
		{
			drawPoint(x, y1, color);
		}
		drawPoint(x2, y2, color);
	}
	else
	{
		int dx = x1 < x2 ? x2 - x1 : x1 - x2;
		int dy = y1 < y2 ? y2 - y1 : y1 - y2;
		if (dx >= dy)
		{
			if (x2 < x1)
			{
				std::swap(x1, x2);
				std::swap(y1, y2);
			}
			int rem = 0;
			for (int x = x1, y = y1; x <= x2; x++)
			{
				drawPoint(x, y, color);
				rem += dy;
				if (rem >= dx)
				{
					rem -= dx;
					y += y1 < y2 ? 1 : -1;
					drawPoint(x, y, color);
				}
			}
			drawPoint(x2, y2, color);
		}
		else
		{
			if (y2 < y1)
			{
				std::swap(x1, x2);
				std::swap(y1, y2);
			}
			int rem = 0;
			for (int x = x1, y = y1; y <= y2; y++)
			{
				drawPoint(x, y, color);
				rem += dx;
				if (rem >= dy)
				{
					rem -= dy;
					x += x1 < x2 ? 1 : -1;
					drawPoint(x, y, color);
				}
			}
			drawPoint(x2, y2, color);
		}
	}
}

void Renderer::drawLine(const Vector& p1, const Vector& p2, const Color& color)
{
	int x1 = static_cast<int>(p1.x());
	int y1 = static_cast<int>(p1.y());
	int x2 = static_cast<int>(p2.x());
	int y2 = static_cast<int>(p2.y());
	float z1 = p1.z();
	float z2 = p2.z();

	if (x1 == x2 && y1 == y2)
	{
		drawPoint(x1, y1, z1, color);
		//drawPoint(x1, y1, color);
	}
	else if (x1 == x2)
	{
		int inc = y1 < y2 ? 1 : -1;
		for (int y = y1; y != y2; y += inc)
		{
			float factor = static_cast<float>(y - y1) / static_cast<float>(y2 - y1);
			float z = z1 + (z2 - z1) * factor;
			drawPoint(x1, y, z, color);
			//drawPoint(x1, y, color);
		}
		drawPoint(x2, y2, z2, color);
		//drawPoint(x2, y2, color);
	}
	else if (y1 == y2)
	{
		int inc = x1 < x2 ? 1 : -1;
		for (int x = x1; x != x2; x += inc)
		{
			float factor = static_cast<float>(x - x1) / static_cast<float>(x2 - x1);
			float z = z1 + (z2 - z1) * factor;
			drawPoint(x, y1, z, color);
			//drawPoint(x, y1, color);
		}
		drawPoint(x2, y2, z2, color);
		//drawPoint(x2, y2, color);
	}
	else
	{
		int dx = x1 < x2 ? x2 - x1 : x1 - x2;
		int dy = y1 < y2 ? y2 - y1 : y1 - y2;
		if (dx >= dy)
		{
			int inc = x1 < x2 ? 1 : -1;
			for (int x = x1; x != x2; x += inc)
			{
				float factor = static_cast<float>(x - x1) / static_cast<float>(x2 - x1);
				int y = y1 + (y2 - y1) * factor;
				float z = z1 + (z2 - z1) * factor;
				drawPoint(x, y, z, color);
				//drawPoint(x, y, color);
			}
			drawPoint(x2, y2, z2, color);
			//drawPoint(x2, y2, color);
		}
		else
		{
			int inc = y1 < y2 ? 1 : -1;
			for (int y = y1; y != y2; y += inc)
			{
				float factor = static_cast<float>(y - y1) / static_cast<float>(y2 - y1);
				int x = x1 + (x2 - x1) * factor;
				float z = z1 + (z2 - z1) * factor;
				drawPoint(x, y, z, color);
				//drawPoint(x, y, color);
			}
			drawPoint(x2, y2, z2, color);
			//drawPoint(x2, y2, color);
		}
	}
}

void Renderer::drawLine(const Vertex& v1, const Vertex& v2)
{
	int x1 = static_cast<int>(v1.pos().x());
	int y1 = static_cast<int>(v1.pos().y());
	int x2 = static_cast<int>(v2.pos().x());
	int y2 = static_cast<int>(v2.pos().y());

	if (x1 == x2 && y1 == y2)
	{
		drawPoint(v1);
	}
	else if (x1 == x2)
	{
		int inc = y1 < y2 ? 1 : -1;
		for (int y = y1; y != y2; y += inc)
		{
			float factor = static_cast<float>(y - y1) / static_cast<float>(y2 - y1);
			Vertex v = v1.interpolate(v2, factor);
			drawPoint(v);
		}
		drawPoint(v2);
	}
	else if (y1 == y2)
	{
		int inc = x1 < x2 ? 1 : -1;
		for (int x = x1; x != x2; x += inc)
		{
			float factor = static_cast<float>(x - x1) / static_cast<float>(x2 - x1);
			Vertex v = v1.interpolate(v2, factor);
			drawPoint(v);
		}
		drawPoint(v2);
	}
	else
	{
		int dx = x1 < x2 ? x2 - x1 : x1 - x2;
		int dy = y1 < y2 ? y2 - y1 : y1 - y2;
		if (dx >= dy)
		{
			int inc = x1 < x2 ? 1 : -1;
			for (int x = x1; x != x2; x += inc)
			{
				float factor = static_cast<float>(x - x1) / static_cast<float>(x2 - x1);
				Vertex v = v1.interpolate(v2, factor);
				drawPoint(v);
			}
			drawPoint(v2);
		}
		else
		{
			int inc = y1 < y2 ? 1 : -1;
			for (int y = y1; y != y2; y += inc)
			{
				float factor = static_cast<float>(y - y1) / static_cast<float>(y2 - y1);
				Vertex v = v1.interpolate(v2, factor);
				drawPoint(v);
			}
			drawPoint(v2);
		}
	}
}

void Renderer::drawTriangle(const Vector& p1, const Vector& p2, const Vector& p3, const Color& color)
{
	Vector a = transformPosition(p1);
	Vector b = transformPosition(p2);
	Vector c = transformPosition(p3);

	drawLine(a, b, color);
	drawLine(b, c, color);
	drawLine(c, a, color);
}

void Renderer::drawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	Vertex p1 = transformPosition(v1);
	Vertex p2 = transformPosition(v2);
	Vertex p3 = transformPosition(v3);

	if (p1.pos().y() > p2.pos().y())
	{
		std::swap(p1, p2);
	}
	if (p2.pos().y() > p3.pos().y())
	{
		std::swap(p2, p3);
	}
	if (p1.pos().y() > p2.pos().y())
	{
		std::swap(p1, p2);
	}

	float midFactor = (p2.pos().y() - p1.pos().y()) / (p3.pos().y() - p1.pos().y());
	Vertex mid = p1.interpolate(p3, midFactor);

	int yStart = static_cast<int>(mid.pos().y());
	int yEnd = static_cast<int>(p3.pos().y());
	for (int y = yStart; y <= yEnd; y++)
	{
		float factor = 0.0f;
		if (yStart != yEnd)
		{
			factor = static_cast<float>(y - yStart) / static_cast<float>(yEnd - yStart);
		}
		Vertex a = mid.interpolate(p3, factor);
		Vertex b = p2.interpolate(p3, factor);
		drawLine(a, b);
	}

	yStart = static_cast<int>(p1.pos().y());
	yEnd = static_cast<int>(mid.pos().y());
	for (int y = yStart; y <= yEnd; y++)
	{
		float factor = 0.0f;
		if (yStart != yEnd)
		{
			factor = static_cast<float>(y - yStart) / static_cast<float>(yEnd - yStart);
		}
		Vertex a = p1.interpolate(mid, factor);
		Vertex b = p1.interpolate(p2, factor);
		drawLine(a, b);
	}
}

void Renderer::drawMesh(const std::vector<Vertex>& vertices, const std::vector<int>& indices)
{
	if (renderState == RENDER_STATE_WIREFRAME)
	{
		for (std::vector<int>::size_type i = 0; i < indices.size(); i += 3)
		{
			drawTriangle(vertices[indices[i]].pos(), vertices[indices[i+1]].pos(), 
						 vertices[indices[i+2]].pos(), Color(1.0f, 1.0f, 0.0f));
		}
	}
	else if (renderState == RENDER_STATE_COLOR || renderState == RENDER_STATE_TEXTURE)
	{
		for (std::vector<int>::size_type i = 0; i < indices.size(); i += 3)
		{
			drawTriangle(vertices[indices[i]], vertices[indices[i+1]], vertices[indices[i+2]]);
		}
	}
}

void Renderer::drawMesh(const Mesh& mesh)
{
	texture = mesh.texture;
	for (std::size_t i = 0; i < mesh.indices.size(); i += 3)
	{
		drawTriangle(mesh.vertices[mesh.indices[i]], 
			         mesh.vertices[mesh.indices[i+1]], 
					 mesh.vertices[mesh.indices[i+2]]);
	}
}

void Renderer::loadObj(const std::string& file)
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	std::vector<Vector> posBuffer;
	std::vector<float> uBuffer;
	std::vector<float> vBuffer;

	std::vector<int> uvIndices;

	std::ifstream ifs(file);
	std::string line;

	while (std::getline(ifs, line))
	{
		if (line.size() < 2)
		{
			continue;
		}

		std::istringstream iss(line);
		std::string token;
		float x, y, z;

		if (line[0] == 'v' && line[1] == 't') // load uv
		{
			iss >> token >> x >> y;
			uBuffer.push_back(x);
			vBuffer.push_back(y);
		}
		else if (line[0] == 'v' && line[1] == 'n') // load normal
		{
			iss >> token >> x >> y >> z;
		}
		else if (line[0] == 'v') // load position
		{
			iss >> token >> x >> y >> z;
			posBuffer.push_back(Vector(x, y, z));
		}
		else if (line[0] == 'f') // load index
		{
			int posIndex[3], uvIndex[3], normalIndex[3];
			char dummy;

			if (line.find("//") != std::string::npos)
			{
				iss >> token >> posIndex[0] >> dummy >> dummy >> normalIndex[0]
				             >> posIndex[1] >> dummy >> dummy >> normalIndex[1]
							 >> posIndex[2] >> dummy >> dummy >> normalIndex[2];
			}
			else
			{
				size_t count = 0;
				size_t pos = line.find('/');
				while (pos != std::string::npos)
				{
					++count;
					pos = line.find('/', pos + 1);
				}

				if (count == 6)
				{
					iss >> token >> posIndex[0] >> dummy >> uvIndex[0] >> dummy >> normalIndex[0]
						         >> posIndex[1] >> dummy >> uvIndex[1] >> dummy >> normalIndex[1]
								 >> posIndex[2] >> dummy >> uvIndex[2] >> dummy >> normalIndex[2];
				}
				else if (count == 3)
				{
					iss >> token >> posIndex[0] >> dummy >> uvIndex[0]
					             >> posIndex[1] >> dummy >> uvIndex[1]
								 >> posIndex[2] >> dummy >> uvIndex[2];
				}

				uvIndices.push_back(uvIndex[0] - 1);
				uvIndices.push_back(uvIndex[1] - 1);
				uvIndices.push_back(uvIndex[2] - 1);
			}

			indices.push_back(posIndex[0] - 1);
			indices.push_back(posIndex[1] - 1);
			indices.push_back(posIndex[2] - 1);
		}
	}

	ifs.close();

	for (std::vector<int>::size_type i = 0; i < indices.size(); i += 3)
	{
		Vertex v0(posBuffer[indices[i]], Color(1.0f, 1.0f, 1.0f), uBuffer[uvIndices[i]], vBuffer[uvIndices[i]]);
		Vertex v1(posBuffer[indices[i+1]], Color(1.0f, 1.0f, 1.0f), uBuffer[uvIndices[i+1]], vBuffer[uvIndices[i+1]]);
		Vertex v2(posBuffer[indices[i+2]], Color(1.0f, 1.0f, 1.0f), uBuffer[uvIndices[i+2]], vBuffer[uvIndices[i+2]]);
		
		if (renderState == RENDER_STATE_WIREFRAME)		
		{
			drawTriangle(v0.pos(), v1.pos(), v2.pos(), Color(1.0f, 1.0f, 0.0f));
		}
		else if (renderState == RENDER_STATE_COLOR || renderState == RENDER_STATE_TEXTURE)
		{
			drawTriangle(v0, v1, v2);
		}
	}
}

void Renderer::saveBmp(const std::string& file) const
{
	unsigned char buf[54] = 
	{ 
		'B', 'M', INT2CHAR(54 + width * height * 32), 
		INT2CHAR(0), INT2CHAR(54), INT2CHAR(40), 
		INT2CHAR(width), INT2CHAR(height), 
		1, 0, 32, 0 
	};
	std::ofstream ofs(file, std::ios_base::out | std::ios_base::binary);
	ofs.write(reinterpret_cast<char*>(buf), sizeof(buf));
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Color color = frameBuffer[y][x];
			buf[0] = static_cast<unsigned char>(std::min(255, static_cast<int>(color.b() * 255)));
			buf[1] = static_cast<unsigned char>(std::min(255, static_cast<int>(color.g() * 255)));
			buf[2] = static_cast<unsigned char>(std::min(255, static_cast<int>(color.r() * 255)));
			buf[3] = static_cast<unsigned char>(std::min(255, static_cast<int>(1.0f * 255)));
			ofs.write(reinterpret_cast<char*>(buf), 4);
		}
	}
}

void Renderer::updateTransform()
{
	transform = world * view * projection;
}

Vector Renderer::transformPosition(const Vector& p) const
{
	Vector v = transform * p;
	float rhw = 1.0f / v.w();
	float x = (v.x() * rhw + 1.0f) * width * 0.5f;
	float y = (1.0f - v.y() * rhw) * height * 0.5f;
	float z = v.z() * rhw;
	return Vector(x, y, z);
}

Vertex Renderer::transformPosition(const Vertex& v) const
{
	return Vertex(transformPosition(v.pos()), v.color(), v.u(), v.v());
}

int Renderer::checkCVV(const Vector& v) const
{
	int check = 0;

	if (v.z() < 0.0f)
	{
		check |= 1;
	}
	if (v.z() > v.w())
	{
		check |= 2;
	}

	if (v.x() < -v.w())
	{
		check |= 4;
	}
	if (v.x() > v.w())
	{
		check |= 8;
	}

	if (v.y() < -v.w())
	{
		check |= 16;
	}
	if (v.y() > v.w())
	{
		check |= 32;
	}

	return check;
}