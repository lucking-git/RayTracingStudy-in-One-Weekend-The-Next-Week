#pragma once

#include "rtweekend.h"
#include "perlin.h"

class texture
{
public:
	virtual vec3 value(double u, double v, const vec3& p)const = 0;


};

class constant_texture :public texture
{
public:
	constant_texture() {};
	constant_texture(vec3 c);
	virtual vec3 value(double u, double v, const vec3& p)const;


public:
	vec3 color;
};

class checker_texture :public texture
{
public:
	checker_texture() {};
	checker_texture(shared_ptr<texture> t0, shared_ptr<texture> t1);

	virtual vec3 value(double u, double v, const vec3& p)const;

public:
	shared_ptr<texture> odd;
	shared_ptr<texture> even;

};

class noise_texture :public texture
{
public:
	noise_texture() {}
	noise_texture(double sc);
	virtual vec3 value(double u, double v, const vec3& p)const;

public:
	perlin noise;
	double scale;
};


class image_texture :public texture
{
public:
	image_texture() {}
	image_texture(unsigned char* pixels, int A, int B);
	~image_texture();

	virtual vec3 value(double u, double v, const vec3& p)const;

public:
	unsigned char* data;
	int nx, ny;
};

