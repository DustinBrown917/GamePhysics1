
#include <math.h>
#include <stdio.h>
#include <string>
#include "Vec3.h"


//Vec3 Class Definitions

//Create a Vec3 with all member variables initialized to zero.
Vec3::Vec3() {
	x = y = z = 0.0f;
}

//Sets all member properties to val.
Vec3::Vec3(float val) {
	x = y = z = val;
}

//Specifically set all member variables.
Vec3::Vec3(float x_, float y_, float z_) {
	x = x_;
	y = y_;
	z = z_;
}

//Deconstructor
Vec3::~Vec3() {

}

//Get the magnitude of this scalar.
float Vec3::Mag() const{
	return sqrtf((x*x) + (y*y) + (z*z));
}
//Scale the vector so its magnitude is 1.
void Vec3::Normalize() {
	*this /= this->Mag();
}
//Return the Dot product of this Vec3 given another.
float Vec3::Dot(const Vec3& other) const {
	return (x * other.x) + (y * other.y) + (z*other.z);
}
//Scale a vector between itself and another Vec3 by factor t.
void Vec3::Lerp(const Vec3& other, float t) {
	*this = ((other - *this) * t) + *this;
}
//Rotate a vector around its z axis.
void Vec3::RotateZ(float angle) {
	angle *= 0.01745329251f; //degree to radian conversion factor.
	float tempx = (x * cos(angle)) - (y * sin(angle));
	float tempy = (x * sin(angle)) + (y * cos(angle));
	x = tempx;
	y = tempy;
}

//Return the Vec3 as readable string.
string Vec3::ToString() {
	std::string vecString = "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
	return vecString;
}

