#include "material.h"
#include "hittable.h"


vec3 material::emitted(double u, double v, const vec3& p)const
{
	return vec3(0, 0, 0);
}


 bool lambertian::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
{
	vec3 scatter_direction = rec.normal + random_unit_vector();
	scattered = ray(rec.p, scatter_direction,r_in.time());
	attenuation = albedo->value(rec.u, rec.v, rec.p);
	return true;
}

 bool metal ::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected+fuzz*random_in_unit_sphere(), r_in.time());
	attenuation = albedo;
	return(dot(scattered.direction(), rec.normal) > 0);
} 


 double schlick(double cosine, double ref_idx)
 {
	 auto r0 = (1 - ref_idx) / (1 + ref_idx);
	 r0 = r0 * r0;
	 return r0 + (1 - r0) * pow((1 - cosine), 5);

 }

bool dielectric :: scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const
 {
	 attenuation = vec3(1.0, 1.0, 1.0);
	 double etai_over_etat = (rec.front_face) ? (1.0 / ref_idx) : (ref_idx);

	 vec3 unit_direction = unit_vector(r_in.direction());
	 double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
	 double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	 if (etai_over_etat*sin_theta>1.0)
	 {
		 vec3 reflected = reflect(unit_direction, rec.normal);
		 scattered = ray(rec.p, reflected, r_in.time());
		 return true;
	 }
	 double reflect_prob = schlick(cos_theta, etai_over_etat);
	 if (random_double() < reflect_prob)
	 {
		 vec3 reflected = reflect(unit_direction, rec.normal);
		 scattered = ray(rec.p, reflected, r_in.time());
		 return true;
	 }

	 vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
	 scattered = ray(rec.p, refracted, r_in.time());
	 return true;



 }


diffuse_light::diffuse_light(shared_ptr<texture> a) : emit(a) {}

bool diffuse_light::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const
{
	return false;

}

vec3 diffuse_light::emitted(double u, double v, const vec3& p)const
{
	return emit->value(u, v, p);
}


isotropic::isotropic(shared_ptr<texture> a) :albedo(a) {}

bool isotropic::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)const
{
	scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
	attenuation = albedo->value(rec.u, rec.v, rec.p);
	return true;
}

