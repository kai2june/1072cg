
#ifndef MATERIALH
#define MATERIALH

#include "ray.h"
#include "vec3.h"
#include "hitable.h"

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
	if(discriminant > 0){
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	}
	else
		return false;
}

vec3 reflect(const vec3& v, const vec3& n){
	return v - 2.0*dot(v, n)*n;
}

vec3 random_in_unit_sphere(){
	vec3 p;
	do{
		p = 2.0*vec3(drand48(), drand48(), drand48()) - vec3(1.0,1.0,1.0);
	}while( p.squared_length() >= 1.0);
	return p;	
}

class material{
	public:
		virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};




#endif
