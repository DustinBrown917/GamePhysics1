#include <string>
#include "Vector.h"


//Return the Vec2 as readable string.
std::string Vec2::ToString() const {
	return"[" + std::to_string(x) + "," + std::to_string(y) + "]";
}

//Return the Vec3 as readable string.
std::string Vec3::ToString() const{
	return "[" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "]";
}

const Vec3 Vec3::Axis::x = Vec3(1.0f, 0, 0);
const Vec3 Vec3::Axis::y = Vec3(0, 1.0f, 0);
const Vec3 Vec3::Axis::z = Vec3(0, 0, 1.0f);

