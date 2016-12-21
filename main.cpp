#include "src/Renderer.h"

int main(int argc, char* argv[])
{
	std::vector<Vertex> vertices = 
	{
		Vertex(Vector(-1.0f,  1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector( 1.0f,  1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 0.0f),
		Vertex(Vector( 1.0f, -1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 1.0f),
		Vertex(Vector(-1.0f, -1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 1.0f),

		Vertex(Vector( 1.0f,  1.0f, 1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector(-1.0f,  1.0f, 1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 0.0f),
		Vertex(Vector(-1.0f, -1.0f, 1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 1.0f),
		Vertex(Vector( 1.0f, -1.0f, 1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 1.0f),

		Vertex(Vector(-1.0f, 1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector( 1.0f, 1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 0.0f),
		Vertex(Vector( 1.0f, 1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 1.0f),
		Vertex(Vector(-1.0f, 1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 1.0f),

		Vertex(Vector(-1.0f, -1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector( 1.0f, -1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 0.0f),
		Vertex(Vector( 1.0f, -1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 1.0f),
		Vertex(Vector(-1.0f, -1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 1.0f),

		Vertex(Vector(-1.0f,  1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector(-1.0f,  1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 0.0f),
		Vertex(Vector(-1.0f, -1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 1.0f),
		Vertex(Vector(-1.0f, -1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 1.0f),

		Vertex(Vector(1.0f,  1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector(1.0f,  1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 0.0f),
		Vertex(Vector(1.0f, -1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 1.0f, 1.0f),
		Vertex(Vector(1.0f, -1.0f, -1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 1.0f)
	};

	std::vector<int> indices =
	{ 
		0,   1,  2,  0,  2,  3, 
		4,   5,  6,  4,  6,  7, 
		8,   9, 10,  8, 10, 11, 
		12, 13, 14, 12, 14, 15,
		16, 17, 18, 16, 18, 19,
		20, 21, 22, 20, 22, 23
	};

	Renderer renderer(800, 600);
	renderer.setCamera(Vector(0.0f, 0.0f, -3.0f), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 1.0f, 0.0f));
	renderer.setFrustum(3.1415926f * 0.5f, 800.0f / 600.0f, 1.0f, 500.0f);
	renderer.setRotation(0.0f, 1.0f, 0.0f, 1.0f);
	renderer.setRotation(1.0f, 0.0f, 0.0f, 0.5f);
	renderer.setScale(0.5f, 0.5f, 0.5f);

	// wireframe model
	renderer.setRenderState(RENDER_STATE_WIREFRAME);
	renderer.drawMesh(vertices, indices);
	renderer.saveBmp("image/image1.bmp");
	renderer.clearBuffer();

	// texture model
	Texture texture("res/cube.bmp");
	renderer.setTexture(texture);

	renderer.setRenderState(RENDER_STATE_TEXTURE);
	renderer.drawMesh(vertices, indices);
	renderer.saveBmp("image/image2.bmp");
	renderer.clearBuffer();

	// color model
	vertices = 
	{
		Vertex(Vector( 1.0f, -1.0f,  1.0f), Color(1.0f, 0.2f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector(-1.0f, -1.0f,  1.0f), Color(0.2f, 1.0f, 0.2f), 0.0f, 1.0f),
		Vertex(Vector(-1.0f,  1.0f,  1.0f), Color(0.2f, 0.2f, 1.0f), 1.0f, 1.0f),
		Vertex(Vector( 1.0f,  1.0f,  1.0f), Color(1.0f, 0.2f, 1.0f), 1.0f, 0.0f),
		Vertex(Vector( 1.0f, -1.0f, -1.0f), Color(1.0f, 1.0f, 0.2f), 0.0f, 0.0f),
		Vertex(Vector(-1.0f, -1.0f, -1.0f), Color(0.2f, 1.0f, 1.0f), 0.0f, 1.0f),
		Vertex(Vector(-1.0f,  1.0f, -1.0f), Color(1.0f, 0.3f, 0.3f), 1.0f, 1.0f),
		Vertex(Vector( 1.0f,  1.0f, -1.0f), Color(0.2f, 1.0f, 0.3f), 1.0f, 0.0f)
	};

	indices = 
	{
		0, 1, 2, 0, 2, 3, 
		4, 5, 6, 4, 6, 7,
		4, 0, 3, 4, 3, 7,
		5, 1, 2, 5, 2, 6, 
		4, 5, 1, 4, 1, 0,
		7, 6, 2, 7, 2, 3
	};

	renderer.setRenderState(RENDER_STATE_COLOR);
	renderer.drawMesh(vertices, indices);
	renderer.saveBmp("image/image3.bmp");
	renderer.clearBuffer();

	// load obj model file
	renderer.setTexture(Texture("res/sphere.bmp"));
	renderer.setRenderState(RENDER_STATE_TEXTURE);
	renderer.loadObj("res/sphere.obj");
	renderer.saveBmp("image/image4.bmp");
	renderer.clearBuffer();

	return 0;
}