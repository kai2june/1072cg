#include <iostream>
#include <fstream>
#include <cfloat>
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "hitable_list.h"
#include "hitable.h"
#include "camera.h"
#include "material.h"
#include "metal.h"
#include "lambertian.h"

using namespace std;

/*bool hit_sphere(const vec3& center, float radius, const ray& r){
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float discriminant = b*b - 4*a*c;
	return (discriminant>0);
}*/
/*
float hit_sphere(const vec3& center, float radius, const ray& r){
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


vec3 color(const ray& r, hitable *world, int depth){
	hit_record rec;
	if( world -> hit(r, 0.001, FLT_MAX, rec) ){
		ray scattered;
		vec3 attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(r,rec,attenuation, scattered))
			return attenuation*color(scattered, world, depth+1);
		else
			return vec3(0,0,0);
//		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
//		return 0.5*color(ray(rec.p, target-rec.p), world);

//		vec3 N = rec.normal;
//		vec3 L = unit_vector( r.origin() - r.point_at_parameter(rec.t));
//		float cos = dot(N, L);
//		vec3 I = vec3(1,1,1);
//		return cos / I;

//		return 0.5*vec3(rec.normal.x() +1.0, rec.normal.y() +1.0, rec.normal.z() +1.0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5*(unit_direction.y() + 1.0);
	return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5, 0.7, 1.0);
}

int main(){
	int nx = 200;
	int ny = 100;
	int ns = 100;
	
	fstream file;
	file.open("ray.ppm", ios::out);
	file << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	
	hitable* list[4];
	list[0]=new sphere(vec3(0,0,-1),0.5, new lambertian(vec3(0.8,0.3,0.3)));
	list[1]=new sphere(vec3(0,-100.5,-1),100,new lambertian(vec3(0.8,0.8,0.0)));
	list[2]=new sphere(vec3(1,0,-1),0.5, new metal(vec3(0.8,0.6,0.2), 0.7));
	list[3]=new sphere(vec3(-1,0,-1),0.5, new metal(vec3(0.8,0.8,0.8), 0.8) );

	hitable *world = new hitable_list(list, 4);
	camera cam;

	for(int j = ny-1; j>=0; j--){
		for(int i = 0; i<nx; i++){
			vec3 col(0.0, 0.0, 0.0);
			for(int s = 0; s < ns; s++){
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);	
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			file << ir << " " << ig << " " << ib << "\n";
		}
	}
}
