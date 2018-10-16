
#include <string> // Just for the ToString() method.
using namespace std;
//Guard statement - Prevents Vec3.h from being compiled more than once.
#ifndef VEC3_H
#define VEC3_H


//Vec3 Class Header
struct Vec3 {
 //Member variables
	float x, y, z;

 //Constructors
	//Create a Vec3 with all member properties initialized to 0.
	Vec3();
	//Create a Vec3 with all member properties initialized to val.
	Vec3(float val);
	//Create a Vec3 and initialize all member properties explicitly.
	Vec3(float x, float y, float z);
	//Destruct the Vec3
	~Vec3();

 //Operator overloads
 // I inlined the operator overloads because they would generate more overhead if they were called as normal in the cpp.
 // They are short and common enough that inlining the operators generates a justifiable improvement in efficiency.
 //TS

	//Assignment operator. Return a reference to value at this.
	inline Vec3& operator = (const Vec3& vec) {
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	//Add two different vectors.
	inline const Vec3 operator + (const Vec3& vec) const {
		return Vec3(x + vec.x, y + vec.y, z + vec.z);
	}

	//Subtract two different vectors.
	inline const Vec3 operator - (const Vec3& vec) const {
		return Vec3(x - vec.x, y - vec.y, z - vec.z);
	}

	//Multiply vector by scalar
	inline const Vec3 operator * (const float f) const {
		return Vec3(x * f, y * f, z * f);
	}

	//Divide vector by scalar
	//Beware of dividing by extremely small numbers. Will update to handle such cases as the class develops.
	inline const Vec3 operator /(const float f) const {
		return Vec3(x / f, y / f, z / f);
	}

	//Add another vector to this and return a reference to itself.
	inline Vec3& operator += (const Vec3& vec) {
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}

	//Subtract another vector from this one and return a reference to itself.
	inline Vec3& operator -= (const Vec3& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	//Multiply this vector by float f and return a reference to itself.
	inline Vec3& operator *= (float f) {
		x *= f;
		y *= f;
		z *= f;

		return *this;
	}

	//Divide this vector by float f and return a reference to itself.
	inline Vec3& operator /= (float f) {
		x /= f;
		y /= f;
		z /= f;

		return *this;
	}


//Member methods
	//Get the magnitude of this Vec3.
	float Mag() const;
	//Scale the vector so its magnitude is 1.
	void Normalize();
	//Return the Dot product of this Vec3 given another.
	float Dot(const Vec3& other) const;
	//Scale a vector between itself and another Vec3 by factor t.
	void Lerp(const Vec3& other, float t);
	//Rotate a vector around its z axis.
	void RotateZ(float angle);

	//Get the Vec3 as a string.
	string ToString();
};

#endif //!VEC3_H
