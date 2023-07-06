#pragma once
#include "rtweekend.h"
#include "texture.h"
struct hit_record;


class material
{
public:
	virtual vec3 emitted(double u, double v, const vec3& p)const;

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const = 0; 
};

class lambertian :public material
{
public:
	lambertian(shared_ptr<texture> a) :albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
	




public:
	shared_ptr<texture> albedo;
};


class metal :public material
{
public:
	metal(const vec3& a,double f) :albedo(a) ,fuzz(f<1?f:1){}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const;
	



public:
	vec3 albedo;
	double fuzz;
};

class dielectric :public material
{
public:
	dielectric(double ri) :ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const;



public:
	double ref_idx;
};


class diffuse_light :public material
{
public:
	diffuse_light(shared_ptr<texture> a);
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const;

	virtual vec3 emitted(double u, double v, const vec3& p)const;

public:
	shared_ptr<texture> emit;

};


class isotropic :public material
{
public:
	isotropic(shared_ptr<texture> a);

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const;



public:
	shared_ptr<texture> albedo;
};