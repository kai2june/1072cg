
#ifndef SPHEREH
#define SPHEREH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "material.h"
#include "metal.h"
#include "lambertian.h"

class material;

class sphere : public hitable{
	public:
		sphere(){}
		sphere(vec3 cen, float r, material* m_ptr) : center(cen), radius(r), mat_ptr(m_ptr){}
//		sphere(vec3 cen, float r, lambertian* l_ptr) : center(cen), radius(r), lam_ptr(l_ptr){}
//		sphere(vec3 cen, float r, metal* m_ptr) : center(cen), radius(r), metal_ptr(m_ptr){}
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
		vec3 center;
		float radius;
		material* mat_ptr;
		//lambertian* lam_ptr;
		//metal* metal_ptr;
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
			rec.mat_ptr = mat_ptr;
			return true;
		}
		t = (-b + sqrt(discriminant))/(2.0*a);
		if( t < t_max && t > t_min ){
			rec.t = t;
			rec.p = r.point_at_parameter(t);
			rec.normal = unit_vector( rec.p - center );
			rec.mat_ptr = mat_ptr;
			return true;
		}
	}
	return false;
}

#endif

