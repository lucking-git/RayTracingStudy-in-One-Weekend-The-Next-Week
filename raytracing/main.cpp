
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include <iostream>



vec3 random_in_unit_sphere()
{
    while (true)
    {
        auto p = vec3::random(-1, 1);
        if (p.length_squared() >= 1)
            continue;
        return p;
    }
}

vec3 ray_color(const ray& r,const hittable& world,int depth)
{
	hit_record rec;
    if (depth <= 0)
        return vec3(0, 0, 0);

	if (world.hit(r,0,infinity,rec))
	{
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        return 0.5 * ray_color(ray(rec.p, target - rec.p), world,depth-1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);

}


int main()
{
    const int image_width = 200;
    const int image_height = 100;
    const int samples_per_pixel = 100;//每个像素采样100次
    const int max_depth = 50;
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);

    hittable_list world;
    world.add(make_shared<sphere>(vec3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(vec3(0, -100.5,-1), 100));
    camera cam;

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s)
            {
                auto u = (i + random_double()) / image_width;
                auto v = (j + random_double()) / image_height;
                ray r=cam.get_ray(u,v);

                color += ray_color(r, world,max_depth);
            }
            color.write_color(std::cout,samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";



	return 0;
}