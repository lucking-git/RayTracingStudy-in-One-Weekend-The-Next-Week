#include "sphere.h"




bool sphere::hit(const ray& r, double tmin, double tmax, hit_record& rec)const
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
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			get_sphere_uv(outward_normal, rec.u, rec.v);//tmd教程里没写这里要加上这个函数获取uv坐标！！
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = (-half_b + root) / a;//对两个根都判断
		if (temp<tmax && temp>tmin)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.set_face_normal(r, outward_normal);
			get_sphere_uv(outward_normal, rec.u, rec.v);
			rec.mat_ptr = mat_ptr;
			return true;

		}


	}
	return false;

}
void sphere::get_sphere_uv(const vec3& p, double& u, double& v)
{
	auto phi = atan2(p.z(), p.x());
	auto theta = asin(p.y());
	u = 1 - (phi + pi) / (2 * pi);
	v = (theta + pi / 2) / pi;

}
bool sphere::bounding_box(double t0, double t1, aabb& output_box)const
{
	output_box = aabb(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
	return true;
}

moving_sphere::moving_sphere(vec3 cen0, vec3 cen1, double t0, double t1, double r, shared_ptr<material> m): center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m){}

vec3 moving_sphere::center(double time)const
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, double tmin, double tmax, hit_record& rec)const
{
	vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;

	auto discriminant = half_b * half_b - a * c;

	if (discriminant > 0)
	{
		auto root = sqrt(discriminant);
		auto temp = (-half_b - root) / a;
		if (temp<tmax&&temp>tmin)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center(r.time())) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}
		temp = -(half_b + root) / a;
		if (temp<tmax&&temp>tmin)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center(r.time())) / radius;
			rec.set_face_normal(r, outward_normal);
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;




}

bool moving_sphere::bounding_box(double t0, double t1, aabb& output_box)const
{
	aabb box0(center(t0) - vec3(radius, radius, radius), center(t0) + vec3(radius, radius, radius));
	aabb box1(center(t1) - vec3(radius, radius, radius), center(t1) + vec3(radius, radius, radius));
	output_box = surrounding_box(box0, box1);
	return true;
}	





