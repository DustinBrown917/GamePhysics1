#include <stdio.h>
#include "PhysicsBody2D.h"
#include "Vector.h"


//Default constructor.
PhysicsBody2D::PhysicsBody2D() : PhysicsBody2D( 1.0f ) {}

//Simple _mass constructor
PhysicsBody2D::PhysicsBody2D(float mass_) : PhysicsBody2D(mass_, 0, Vec2(), Vec2(), Vec2()) { }

//Advanced constructor to set all variables of the Body.
PhysicsBody2D::PhysicsBody2D(float _mass, float _angle, Vec2 _position, Vec2 _velocity, Vec2 _acceleration) {
	mass = _mass;
	angle = _angle;
	position = _position;
	velocity = _velocity;
	acceleration = _acceleration;
	gravityScale = 1.0f;
}

//Destructor
PhysicsBody2D::~PhysicsBody2D() {/*Stub*/}

//Update the status of the body by the timeStep interval.
void PhysicsBody2D::Update(float timeStep) {

	//Get the new position of the body via:
	//p = p + (v * timeStep) + (a * 0.5 * (timeStep * timeStep));

	position += (velocity * timeStep) + (acceleration * 0.5f * (timeStep * timeStep));

	//Get the new velocity of the body via:
	//v = v + (a * timeStep);

	velocity += (acceleration * timeStep);
}

//Apply a force to the body.
void PhysicsBody2D::ApplyForce(Vec2 force) {

	//Find acceleration of the body given the force applied.
	//Thanks, Newton!
	//f = m*a
	
	acceleration = force / mass;
}
