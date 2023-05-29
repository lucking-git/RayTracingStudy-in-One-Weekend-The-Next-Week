#pragma once
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>
#include <cstdlib>

using std::shared_ptr;
using std::make_shared;



const double  infinity = std::numeric_limits<double>::infinity();
const double pi= 3.1415926535897932385;

inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

inline double ffmin(double a, double b){return a <= b ? a : b;}

inline double ffmax(double a, double b) { return a >= b ? a : b; }

inline double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}
inline double random_double(double min, double max)
{
	return min + (max - min) * random_double();


}

inline double clamp(double x, double min, double max)
{
	if (x < min)return min;
	if (x > max)return max;
	return x;
}


#include "ray.h"

