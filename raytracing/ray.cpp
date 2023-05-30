#include "ray.h"
//#include "vec3.h"

ray::ray() {}
ray::ray(const vec3& origin, const vec3& direction)
	:orig(origin), dir(direction) {}//初始化光线  原点+t*方向
vec3 ray::origin() const { return orig; }//返回光线原点
vec3 ray::direction() const { return dir; }//返回光线方向

vec3 ray::at(double t)const  //返回光线
{
	return orig + t * dir;
}