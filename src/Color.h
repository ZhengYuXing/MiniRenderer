#ifndef __COLOR_H__
#define __COLOR_H__

class Color
{
public:
	Color();
	Color(float r, float g, float b);
	Color(const Color& other);
	Color& operator=(const Color& other);
	~Color();

	Color interpolate(const Color& color, float factor) const;
	int toInt() const;

	float r() const;
	float g() const;
	float b() const;

	static Color randomColor();

private:
	float r_, g_, b_;
};

#endif