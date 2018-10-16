#include <stdio.h>
#include "Vec3.h"
#include "Body.h"

//Default constructor.
Body::Body() {
	mass = 1;
	angle = 0;
	position = velocity = acceleration = Vec3();
}

//Simple _mass constructor
Body::Body(float _mass) {
	mass = _mass;
	angle = 0;
	position = velocity = acceleration = Vec3();
}

//Advanced constructor to set all variables of the Body.
Body::Body(float _mass, float _angle, Vec3 _position, Vec3 _velocity, Vec3 _acceleration) {
	mass = _mass;
	angle = _angle;
	position = _position;
	velocity = _velocity;
	acceleration = _acceleration;
}

//Destructor
Body::~Body() {/*Stub*/}

//Update the status of the body by the timeStep interval.
void Body::Update(float timeStep) {

	//Get the new position of the body via:
	//p = p + (v * timeStep) + (a * 0.5 * (timeStep * timeStep));

	position += (velocity * timeStep) + (acceleration * 0.5f * (timeStep * timeStep));

	//Get the new velocity of the body via:
	//v = v + (a * timeStep);

	velocity += (acceleration * timeStep);

}

//Apply a force to the body.
void Body::ApplyForce(Vec3 force) {
	
	//Find acceleration of the body given the force applied.
	//Thanks, Newton!
	//f = m*a
	acceleration = force / mass;
}