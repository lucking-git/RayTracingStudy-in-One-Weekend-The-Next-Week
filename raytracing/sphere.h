#pragma once
#include "hittable.h"
#include "vec3.h"

class sphere:public hittable
{
public:
	sphere() {}
	sphere(vec3 cen, double r) :center(cen), radius(r) {}


	virtual bool hit(const ray& r, double tmin, double tmax, hit_recorrd& rec)const {}






public:
	vec3 center;
	double radius;



};
 bool sphere::hit(const ray& r, double tmin, double tmax, hit_recorrd& rec)const
{
	 vec3 oc = r.origin() - center;
	 auto a = r.direction().length_squared();
	 auto half_b = dot(oc, r.direction());
	 auto c = oc.length_squared() - radius * radius;
	 auto discriminant = half_b * half_b - a * c;

	 if (discriminant > 0)
	 {
		 auto root = sqrt(discriminant);
		 auto temp = (-half_b - root) / a;//交点  用t的大小表示
		 if (temp<tmax && temp>tmin)
		 {
			 rec.t = temp;
			 rec.p = r.at(rec.t);
			 vec3 outward_normal = (rec. p - center) / radius;
			 rec.set_face_normal(r, outward_normal);
			 return true;
		 }
		 temp = (-half_b + root) / a;//对两个根都判断
		 if (temp<tmax && temp>tmin)
		 {
			 rec.t = temp;
			 rec.p = r.at(rec.t);
			 vec3 outward_normal = (rec. p - center) / radius;
			 rec.set_face_normal(r, outward_normal);
			 return true;

		 }
		 

	 }
	 return false;

}
