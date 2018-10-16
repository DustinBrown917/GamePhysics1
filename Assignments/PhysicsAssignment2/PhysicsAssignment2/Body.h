//More compatible version of #pragma once
#ifndef BODY_H
#define BODY_H


#include "Vec3.h"

//Body header

class Body {

public: //Member variables
	float mass, angle;
	Vec3 position, velocity, acceleration;

public:
	Body(); //Default Constructor
	Body(float _mass); // _mass constructor
	Body(float _mass, float _angle, Vec3 _position, Vec3 _velocity, Vec3 _acceleration); //Advanced constructor
	~Body(); //Destructor

public:
	void Update(float timeStep); //Called every frame
	void ApplyForce(Vec3 force); //Add force to the body
};

#endif // !BODY_H