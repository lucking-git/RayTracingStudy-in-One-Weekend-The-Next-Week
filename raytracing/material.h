#pragma once
#include "rtweekend.h"
struct hit_record;


class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const = 0; 
};

class lambertian :public material
{
public:
	lambertian(const vec3& a) :albedo(a) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const;
	




public:
	vec3 albedo;
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