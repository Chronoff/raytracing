#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"


using color = vec3;

inline double linearToGamma(double linearComponent)
{
	if(linearComponent > 0)
	{
		return std::sqrt(linearComponent);
	}

	return 0;
}

void writeColor(std::ostream& out, const color& pixelColor)
{
	auto r = pixelColor.x();
	auto g = pixelColor.y();
	auto b = pixelColor.z();

	r = linearToGamma(r);
	g = linearToGamma(g);
	b = linearToGamma(b);

	static const interval intensity(0.000, 0.999);
	int rbyte = int(intensity.clamp(r) * 256);
	int gbyte = int(intensity.clamp(g) * 256);
	int bbyte = int(intensity.clamp(b) * 256);

	out << rbyte << ' ' << gbyte << ' ' << bbyte << "\n";
}

#endif

