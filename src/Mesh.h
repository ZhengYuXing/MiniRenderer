#ifndef __MESH_H__
#define __MESH_H__

#include "Vertex.h"
#include "Vector.h"
#include "Texture.h"
#include <vector>
#include <string>

class Mesh
{
public:
	Mesh();
	Mesh(const std::string& meshFile, const std::string& textureFile);

public:
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	Vector position, rotation, scale;
	Texture texture;
};

#endif