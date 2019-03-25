
#ifndef HITABLELISTH
#define HITABLELISTH

#include "ray.h"
#include "hitable.h"

class hitable_list : public hitable {
	public:
		hitable_list(){}
		hitable_list(hitable** l, int n){
			list = l;
			size = n;
		}
		virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
		hitable** list;
		int size;
};

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const{
	hit_record temp_rec;
	bool hit_anything = false;
	float closest_so_far = t_max;
	for(int i=0; i<size; i++){
		if( list[i] -> hit(r, t_min, closest_so_far, temp_rec) ){
			rec = temp_rec; //is there shallow copy problem?
			hit_anything = true;
			closest_so_far = temp_rec.t;
		}
	}
	return hit_anything;
}

#endif

