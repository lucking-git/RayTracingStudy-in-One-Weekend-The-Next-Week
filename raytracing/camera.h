
#ifndef CAMERA_H
#define CAMERA_H
#include "rtweekend.h"


class camera
{
public:
	camera();
	
	ray get_ray(double u, double v);
	


public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

#endif