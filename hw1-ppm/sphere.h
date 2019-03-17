
#ifndef SPHEREH
#define SPHEREH

#include "vec3.h"
#include "ray.h"

class sphere{
	public:
		vec3 center;
		float radius;
};

inline float hit_sphere(const vec3 &center, float radius, const ray& r){
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(r.direction(), oc);
	float c = dot(oc,oc) - radius*radius;
	float discriminant = b*b - 4.0*a*c;
	return (-b-sqrt(discriminant))/(2.0*a);
}

vec3 color(const ray& r){
	float t = hit_sphere(vec3(0,0,-1), 0.5, r);
	if(t < 0.0){
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
		vec3 L = unit_vector(r.point_at_parameter(t));
		float cos = dot(N, L);
		vec3 I = vec3(1,1,1);
		return cos / I;
		//return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)* vec3(1,1,1) + t*vec3(0.5, 0.7, 1.0);
}

/*
inline float hit_sphere(const vec3 &center, float radius, const ray& r){
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(r.direction(), oc);
	float c = dot(oc,oc) - radius*radius;
	float discriminant = b*b - 4.0*a*c;
	return (-b-sqrt(discriminant))/(2.0*a);
}

vec3 color(const ray& r){
	float t = hit_sphere(vec3(0,0,-1), 0.5, r);
	if(t < 0.0){
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
		return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)* vec3(1,1,1) + t*vec3(0.5, 0.7, 1.0);
}
*/

/*
bool hit_sphere(const vec3 &center, float radius, const ray& r){
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0*dot(r.direction(), oc);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4.0*a*c;
	return discriminant>0.0;
}
*/
/*
vec3 color(const ray& r){
	if(hit_sphere(vec3(0,0,-1), 0.5, r))
		return vec3(1,0,0);

	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() +1.0);
	return (1.0-t)*vec3(1,1,1) + t*vec3(0.5, 0.7, 1.0);
}
*/


#endif


