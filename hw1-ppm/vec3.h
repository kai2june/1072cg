//================================================================================================= 
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#ifndef VEC3H
#define VEC3H

#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3 {

public:
	vec3() {}
	vec3(float e0, float e1, float e2) { e[0] = e0; e[1] = e1; e[2] = e2; }
	float x() const { return e[0]; }
	float y() const { return e[1]; }
	float z() const { return e[2]; }
	float r() const { return e[0]; }
	float g() const { return e[1]; }
	float b() const { return e[2]; }


	inline vec3& operator+=(const vec3 &v2);
	inline vec3& operator-=(const vec3 &v2);
	inline vec3& operator*=(const vec3 &v2);
	inline vec3& operator/=(const vec3 &v2);

	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
	inline float squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	inline void make_unit_vector();

	float e[3];

	////////////////
	inline float operator[](const int i);
};
inline vec3& vec3::operator+=(const vec3 &v2){
	e[0]+=v2.x();
	e[1]+=v2.y();
	e[2]+=v2.z();
	return *this;
}

inline vec3& vec3::operator-=(const vec3 &v2){
	e[0]-=v2.x();
	e[1]-=v2.y();
	e[2]-=v2.z();
	return *this;
}

inline vec3& vec3::operator*=(const float t){
	e[0]*=t;
	e[1]*=t;
	e[2]*=t;
	return *this;
}

inline vec3& vec3::operator/=(const float t){
	e[0]/=t;
	e[1]/=t;
	e[2]/=t;
	return *this;
}

inline std::ostream& operator<<(std::ostream &os, const vec3 &t) 
{
	os << t.x() << ' ' << t.y() <<' ' << t.z();
	return os;
}

inline void vec3::make_unit_vector() 
{
	float length = sqrt(e[0]*e[0] + e[1]*e[1]+e[2]*e[2]);
	e[0]/=length;
	e[1]/=length;
	e[2]/=length;
}

inline float dot(const vec3 &v1, const vec3 &v2) 
{
	return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) 
{
	return vec3(v1.y()*v2.z() - v1.z()*v2.y(), v1.z()*v2.x() - v1.x()*v2.z(), v1.x()*v2.y() - v1.y()*v2.x());
}

inline vec3 unit_vector(vec3 v) 
{
	float length = sqrt(v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2]);
	return vec3(v.e[0]/length , v.e[1]/length, v.e[2]/length);
}
//////////////////////
inline vec3 operator*(float t, vec3 v){
	return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator/(float t, vec3 v){
	return vec3(t/v.e[0], t/v.e[1], t/v.e[2]);
}

inline vec3 operator+(vec3 u, vec3 v){
	return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline vec3 operator-(vec3 u, vec3 v){
	return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
}

inline float vec3::operator[](const int i){
	return e[i];
}
#endif
