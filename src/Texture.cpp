#include "Texture.h"
#include <fstream>

Texture::Texture() : width(256), height(256), uMax(255.0f), vMax(255.0f)
{
	buffer.resize(width * height);
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			int x = i / 32;
			int y = j / 32;
			buffer[j * width + i] = ((x + y) & 1)? Color(1.0f, 1.0f, 1.0f) : Color(0.2f, 0.2f, 0.8f);
		}
	}
}

Texture::Texture(const std::string& file)
{
	std::ifstream ifs(file, std::ios_base::binary);
	unsigned char buf[54];
	ifs.read(reinterpret_cast<char*>(buf), sizeof(buf));

	width = *(reinterpret_cast<int*>(&buf[18]));
	height = *(reinterpret_cast<int*>(&buf[22]));
	uMax = static_cast<float>(width) - 1.0f;
	vMax = static_cast<float>(height) - 1.0f;

	int bytes = buf[28] / 8;
	int count = width * height * bytes;
	unsigned char* tmp = new unsigned char[count];
	ifs.read(reinterpret_cast<char*>(tmp), count);
	buffer.resize(width * height);
	count = 0;
	for (size_t i = 0; i < buffer.size(); i++)
	{
		buffer[i] = Color(tmp[count + 2] / 255.0f, tmp[count + 1] / 255.0f, tmp[count + 0] / 255.0f);
		count += bytes;
	}
	delete[] tmp;
	ifs.close();
}

Texture::Texture(const Texture& other) 
  : width(other.width), height(other.height), uMax(other.uMax), vMax(other.vMax), buffer(other.buffer)
{
}

Texture& Texture::operator=(const Texture& other)
{
	if (this != &other)
	{
		width = other.width;
		height = other.height;
		uMax = other.uMax;
		vMax = other.vMax;
		buffer = other.buffer;
	}
	return *this;
}

Texture::~Texture()
{
}

Color Texture::sample(float u, float v) const
{
	//u = u * uMax;
	//v = v * vMax;
	//int x = static_cast<int>(u + 0.5f);
	//int y = static_cast<int>(v + 0.5f);

	int tu = static_cast<int>(u * (width - 1));
	int tv = static_cast<int>(v * (height - 1));
	return buffer[tu + tv * width];
}