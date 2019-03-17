#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"

using namespace std;


int main()
{
	int width = 200;
	int height = 100;

	fstream file;
	file.open("ray.ppm", ios::out);

	/*file << "P3\n" << width << " " << height << "\n255\n";
	for (int j = height - 1; j >= 0; j--) {
		for (int i = 0; i < width; i++) {
			float r = float(i) / float(width);
			float g = float(j) / float(height);
			float b = 0.2;

			file << int(r * 255) << " " << int(g * 255) << " " << int(b * 255) << "\n";
		}
	}*/

	vec3 lower_left_corner(-2,-1,-1);
	vec3 origin(0,0,0);
	vec3 horizontal(4,0,0);
	vec3 vertical(0,2,0);
	file<< "P3\n" << width << " " << height <<"\n255\n";
	for(int j=height-1; j>=0; j--){
		for(int i=0; i<width; i++){
			float u=float(i)/float(width);
			float v=float(j)/float(height);
			ray r(origin, lower_left_corner+u*horizontal+v*vertical);
			vec3 myColor = color(r);

			file<< int(myColor[0]*255) <<" "<<int(myColor[1]*255)<<" "<<int(myColor[2]*255)<< "\n";
		}
	}

	return 0;
}
