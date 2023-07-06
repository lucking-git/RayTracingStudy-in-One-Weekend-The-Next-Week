#pragma once
#include "hittable.h"
//#include "vec3.h"

class sphere:public hittable
{
public:
	sphere() {}
	sphere(vec3 cen, double r, shared_ptr<material> m) :center(cen), radius(r), mat_ptr(m) {}


	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec)const;
	
	virtual bool bounding_box(double t0, double t1, aabb& output_box) const;





public:
	vec3 center;
	double radius;
	shared_ptr<material> mat_ptr;

private:
	static void get_sphere_uv(const vec3& p, double& u, double& v);


};

class moving_sphere :public hittable
{
public:
	moving_sphere() {}
	moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, shared_ptr<material> m);
	virtual bool hit(const ray& r, double tmin, double tmax, hit_record& rec) const;
	virtual bool bounding_box(double t0, double t1, aabb& output_box) const;

	vec3 center(double time) const;

public:
	vec3 center0, center1;
	double time0, time1;
	double radius;
	shared_ptr<material> mat_ptr;
 };
