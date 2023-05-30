
#ifndef RAY_H
#define RAY_H
#include "vec3.h"



class ray
{
public:
	ray();
	ray(const vec3& origin, const vec3& direction);//初始化光线  原点+t*方向
	vec3 origin() const;//返回光线原点
	vec3 direction() const;//返回光线方向

	vec3 at(double t)const; //返回光线



public:
	vec3 orig;
	vec3 dir;


};

#endif

