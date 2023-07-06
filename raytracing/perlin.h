#pragma once
#include "rtweekend.h"



class perlin
{
public:
	perlin();
	~perlin();

	double noise(const vec3& p)const;
	double turb(const vec3& p, int depth ) const;

private:
	static const int point_count = 256;
	vec3* ranvec;
	int* perm_x;
	int* perm_y;
	int* perm_z;

	static int* perlin_generate_perm();

	static void permute(int* p, int n);



};

