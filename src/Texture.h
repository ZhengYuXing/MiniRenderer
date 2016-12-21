#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "Color.h"
#include <vector>
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& file);
	Texture(const Texture& other);
	Texture& operator=(const Texture& other);
	~Texture();

	Color sample(float u, float v) const;

private:
	std::vector<Color> buffer;
	int width, height;
	float uMax, vMax;
};

#endif