#include "camera.h"
camera::camera()
{
	lower_left_corner = vec3(-2.0, -1.0, -1.0);
	horizontal = vec3(4.0, 0.0, 0.0);
	vertical = vec3(0.0, 2.0, 0.0);
	origin = vec3(0.0, 0.0, 0.0);
}
ray camera::get_ray(double u, double v)
{
	return ray(origin, lower_left_corner + u * horizontal + v * vertical);
}
