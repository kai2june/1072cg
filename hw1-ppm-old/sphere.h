
#ifndef SPHEREH
#define SPHEREH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

class sphere : public hitable{
	public:
		sphere(){}
		sphere(vec3 cen, float r) : center(cen), radius(r){};
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
		vec3 center;
		float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2*dot(r.direction(), oc);
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	if(discriminant > 0.0){
		float t = (-b - sqrt(discriminant))/(2.0*a);
		if( t < t_max && t > t_min ){
			rec.t = t;
			rec.p = r.point_at_parameter(t);
			rec.normal = unit_vector( rec.p - center );
			return true;
		}
		t = (-b + sqrt(discriminant))/(2.0*a);
		if( t < t_max && t > t_min ){
			rec.t = t;
			rec.p = r.point_at_parameter(t);
			rec.normal = unit_vector( rec.p - center );
			return true;
		}
	}
	return false;
}

#endif

