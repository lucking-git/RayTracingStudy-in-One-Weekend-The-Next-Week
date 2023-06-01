
#ifndef CAMERA_H
#define CAMERA_H
#include "rtweekend.h"


class camera
{
public:
	camera();
	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspect, double aperture, double focus_dist);
	
	
	ray get_ray(double u, double v);
	


public:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
};

#endif