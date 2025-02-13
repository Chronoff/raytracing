#ifndef RTWEEKEND_H
#define RTWEEKEND_H 

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.14159265358;

inline double degreesToRadians(double degrees)
{
	return degrees * pi / 180.0;
}

inline double randomDouble()
{
	return std::rand() / (RAND_MAX + 1.0);
}

inline double randomDouble(double min, double max)
{
	return min + (max-min)*randomDouble();
}
#include "color.h"
#include "interval.h"
#include "vec3.h"
#include "ray.h"

#endif
