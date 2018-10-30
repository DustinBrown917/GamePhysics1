#ifndef VECTOR_H
#define VECTOR_H

//Tiny float to guard against divisions of near zero and zero.
#ifndef TINY_FLOAT
#define TINY_FLOAT 1.0e-7f
#endif

#ifndef DEGREE_TO_RADIAN
#define DEGREE_TO_RADIAN 0.01745329251f
#endif

#include<string>
#include<math.h>


#pragma region Vec2
struct Vec2 {
	float x, y;

	inline Vec2() : Vec2(0.0f){ }

	inline Vec2(float val) : Vec2(val,val) { }

	inline Vec2(float x_, float y_) {
		x = x_;
		y = y_;
	}

	inline ~Vec2(){}

	/*********************************************************************************************************/
	/*********************************************** OPERATORS ***********************************************/
	/*********************************************************************************************************/

	inline Vec2& operator = (const Vec2& v) {
		x = v.x;
		y = v.y;

		return *this;
	}

	inline const Vec2 operator + (const Vec2& v) const {
		return Vec2(x + v.x, y + v.y);
	}

	inline Vec2& operator += (const Vec2& v) {
		x += v.x;
		y += v.y;

		return *this;
	}

	inline const Vec2 operator - (const Vec2& v) const {
		return Vec2(x + v.x, y + v.y);
	}

	inline Vec2& operator -= (const Vec2& v) {
		x += v.x;
		y += v.y;

		return *this;
	}

	inline const Vec2 operator * (float f) const {
		return Vec2(x * f, y * f);
	}

	inline Vec2& operator *= (float f) {
		x *= f;
		y *= f;

		return *this;
	}

	inline const Vec2 operator / (float f) const {
#ifdef _DEBUG //This pattern will appear with division in order to guard against dividing by zero or tiny numbers.
		if (std::fabs(f) < TINY_FLOAT) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
#endif

		float r = 1.0f / f; //Division is a sequential operation (not simultaneous).
		return *this * r; //Multiplication is a simultaneous operation.
		//The above pattern marginally improves performance with large numbers with negligable performance impact with small number.
	}

	inline Vec2& operator /= (float f)  {
#ifdef _DEBUG
		if (std::fabs(f) < TINY_FLOAT) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
#endif

		float r = 1.0f / f;
		*this *= r;
		return *this;
	}

	/*********************************************************************************************************/
	/********************************************* MEMBER METHODS ********************************************/
	/*********************************************************************************************************/

	std::string ToString() const;

	inline static Vec2 Rotate(Vec2 vec, float theta) {
		theta *= DEGREE_TO_RADIAN; //degree to radian conversion factor.
		float tempx = (vec.x * cos(theta)) - (vec.y * sin(theta));
		vec.y = (vec.x * sin(theta)) + (vec.y * cos(theta));
		vec.x = tempx;

		return vec;
	}

	inline float Mag() const {
		return sqrt((x * x) + (y * y));
	}

	inline static Vec2 GetNormal(const Vec2& vec) {
		return (vec / vec.Mag());
	}

	inline void Normalize() {
		*this /= this->Mag();
	}

	inline static float Dot(const Vec2& v1, const Vec2& v2) {
		return (v1.x * v2.x) + (v1.y * v2.y);
	}

	inline static Vec2 Lerp(const Vec2& v1, const Vec2& v2, float t) {
		return ((v2 - v1) * t) + v1;
	}
	
};
#pragma endregion

#pragma region Vec3
//Vec3 Class Header
struct Vec3 {

	struct Axis {
		static const Vec3 x;
		static const Vec3 y;
		static const Vec3 z;
	};

	//Member variables
	float x, y, z;

	//Constructors
	//Create a Vec3 with all member properties initialized to 0.
	inline Vec3() {
		x = y = z = 0;
	}
	//Create a Vec3 with all member properties initialized to val.
	inline Vec3(float val) {
		x = y = z = val;
	}
	//Create a Vec3 and initialize all member properties explicitly.
	inline Vec3(float x_, float y_, float z_) {
		x = x_; y = y_; z = z_;
	}
	//Destruct the Vec3
	inline ~Vec3() {}

	/*********************************************************************************************************/
	/*********************************************** OPERATORS ***********************************************/
	/*********************************************************************************************************/

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

	//To allow scaler before vector
	inline friend Vec3 operator * (const float s, const Vec3& v) {
		return v * s;
	}

	//Divide vector by scalar
	//Beware of dividing by extremely small numbers. Will update to handle such cases as the class develops.
	inline const Vec3 operator / (const float f) const {
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

	/*********************************************************************************************************/
	/********************************************* MEMBER METHODS ********************************************/
	/*********************************************************************************************************/


	//Member methods
	//Get the magnitude of this Vec3.
	inline float Mag() const {
		return sqrt((x * x) + (y * y) + (z * z));
	}
	//Scale the vector so its magnitude is 1.
	inline void Normalize() {
		*this /= this->Mag();
	}
	//Get the normalized form of the vector
	inline const Vec3 GetNormal() const {
		return (*this / this->Mag());
	}

	std::string ToString() const; //Averaged 26.5 microseconds inlined, 25.8 declared.

	//Return the dot product of two Vec3s.
	inline static float Dot(const Vec3& v1, const Vec3& v2) {
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	//Return the cross product of two Vec3s.
	inline static const Vec3 Cross(const Vec3& v1, const Vec3 v2) {
		return Vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	//Lerps between v1 and v2 by factor t
	inline static Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t) {
		return ((v2 - v1) * t) + v1;
	}
};
#pragma endregion

#endif
