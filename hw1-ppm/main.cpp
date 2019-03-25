#include <iostream>
#include <fstream>
#include <cfloat>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"

using namespace std;

/*bool hit_sphere(const vec3& center, float radius, const ray& r){
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	return (discriminant>0);
}*/

/*float hit_sphere(const vec3& center, float radius, const ray& r){
	vec3 oc = r.origin() -center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	if(discriminant < 0){
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant) ) / (2.0*a);
	}
}*/
/*
vec3 color(const ray& r){
	float t = hit_sphere(vec3(0,0,-1), 0.5, r);
	if( t > 0.0 ){
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
		return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
	}
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*vec3(1.0, 1.0, 1.0) + t*vec3(0.5, 0.7, 1.0);
}*/

vec3 color(const ray& r, hitable *world){
	hit_record rec;
	if( world -> hit(r, 0.0, FLT_MAX, rec) ){
		return 0.5*vec3(rec.normal.x() +1.0, rec.normal.y() +1.0, rec.normal.z() +1.0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){
	int nx = 200;
	int ny = 100;
	
	fstream file;
	file.open("ray.ppm", ios::out);
	file << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	
	hitable* list[2];
	list[0] = new sphere( vec3(0.0, 0.0, -1.0), 0.5);
	list[1] = new sphere( vec3(0.0, -100.5, -1.0), 100);
	hitable *world = new hitable_list(list, 2);
	
	for(int j = ny-1; j>=0; j--){
		for(int i = 0; i<nx; i++){
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin , lower_left_corner + u*horizontal + v*vertical);
//			vec3 col = color(r);
			vec3 col = color(r, world);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			file << ir << " " << ig << " " << ib << "\n";

//			float r = float(i) / float(nx);
//			float g = float(j) / float(ny);
//			float b = 0.2;
//			int ir = int(255.99*r);
//			int ig = int(255.99*g);
//			int ib = int(255.99*b);
//			file << ir << " " << ig << " " << ib << "\n";
		}
	}
}
