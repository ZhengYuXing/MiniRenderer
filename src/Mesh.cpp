#include "Mesh.h"
#include "Color.h"
#include <cstdlib>
#include <fstream>

static std::vector<std::string> split(const std::string& str, char delimiter)
{
	std::vector<std::string> res;
	std::string::size_type start = 0, end = 0;
	while ((end = str.find(delimiter, start)) != std::string::npos)
	{
		res.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	res.push_back(str.substr(start));
	return res;
}

Mesh::Mesh() : scale(Vector(1.0f, 1.0f, 1.0f))
{
}

Mesh::Mesh(const std::string& meshFile, const std::string& textureFile) 
  : scale(Vector(1.0f, 1.0f, 1.0f)), texture(textureFile)
{
	std::ifstream ifs(meshFile);
	std::string line;
	char delimiter = ' ';

	std::getline(ifs, line);
	std::getline(ifs, line);

	std::getline(ifs, line);
	auto svec = split(line, delimiter);
	int numOfVertices = std::atoi(svec[1].c_str());

	std::getline(ifs, line);
	svec = split(line, delimiter);
	int numOfTriangles = std::atoi(svec[1].c_str());

	for (int i = 0; i < numOfVertices; i++)
	{
		std::getline(ifs, line);
		svec = split(line, delimiter);

		float x = std::atof(svec[0].c_str());
		float y = std::atof(svec[1].c_str());
		float z = std::atof(svec[2].c_str());

		float nx = std::atof(svec[3].c_str());
		float ny = std::atof(svec[4].c_str());
		float nz = std::atof(svec[5].c_str());

		float u = std::atof(svec[6].c_str());
		float v = std::atof(svec[7].c_str());

		vertices.push_back(Vertex(Vector(x, y, z), Color::randomColor(), u, v));
	}

	for (int i = 0; i < numOfTriangles; i++)
	{
		std::getline(ifs, line);
		svec = split(line, delimiter);
		indices.push_back(std::atoi(svec[0].c_str()));
		indices.push_back(std::atoi(svec[1].c_str()));
		indices.push_back(std::atoi(svec[2].c_str()));
	}

	ifs.close();
}