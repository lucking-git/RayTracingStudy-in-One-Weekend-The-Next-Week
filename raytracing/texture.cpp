#include "texture.h"

constant_texture::constant_texture(vec3 c) :color(c) {}



vec3 constant_texture::value(double u, double v, const vec3& p)const
{
	return color;
}

checker_texture::checker_texture(shared_ptr<texture> t0, shared_ptr<texture> t1) :even(t0), odd(t1) {}
vec3 checker_texture::value(double u, double v, const vec3& p)const
{
	auto sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());
	if (sines < 0)
		return odd->value(u, v, p);
	else
	{
		return even->value(u, v, p);
	}
}

noise_texture::noise_texture(double sc) :scale(sc) {}

vec3 noise_texture::value(double u, double v, const vec3& p)const
{
	return vec3(1, 1, 1) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turb(p,7)));
}

image_texture::image_texture(unsigned char* pixels, int A, int B) :data(pixels), nx(A), ny(B) {}

image_texture::~image_texture() {
	delete data;
}


vec3 image_texture::value(double u, double v, const vec3& p)const
{
	if (data == nullptr)
		return vec3(0, 1, 1);

	auto i = static_cast<int>((u)*nx);
	auto j = static_cast<int>((1 - v) * ny - 0.001);

	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i > nx - 1) i = nx - 1;
	if (j > ny - 1) j = ny - 1;

	auto r = static_cast<int>(data[3 * i + 3 * nx * j + 0]) / 255.0;
	auto g = static_cast<int>(data[3 * i + 3 * nx * j + 1]) / 255.0;
	auto b = static_cast<int>(data[3 * i + 3 * nx * j + 2]) / 255.0;

	return vec3(r, g, b);



}