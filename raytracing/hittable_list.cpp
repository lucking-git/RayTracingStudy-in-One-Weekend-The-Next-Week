#include "hittable_list.h"







bool hittable_list::hit(const ray& r, double tmin, double tmax, hit_record& rec)const
{
	hit_record temp_rec;
	bool hit_anything = false;
	auto closet_so_far = tmax;

	for (const auto& object : objects)
	{
		if (object->hit(r, tmin, closet_so_far, temp_rec))
		{
			hit_anything = true;
			closet_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;


}
bool hittable_list::bounding_box(double t0, double t1, aabb& output_box)const
{
	if (objects.empty())
	{
		return false;
	
	}
	aabb temp_box;
	bool first_box = true;
	for (const auto &object:objects )
	{
		if (!object->bounding_box(t0,t1,temp_box))
		{
			return false;
		}
		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}
	return true;

}