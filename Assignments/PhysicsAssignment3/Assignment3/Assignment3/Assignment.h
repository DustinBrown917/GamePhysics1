#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include "Vector.h";

class Assignment
{
public:
	class PhysicsBody2D* bodies[2];
	float elapsedTime;
	Vec2 gravitationalAcceleration;

	Assignment(Vec2 gravitationalAcceleration_);
	~Assignment();

	// Add two bodies to the array of bodies
	void AddTwoBodies(PhysicsBody2D* body1, PhysicsBody2D* body2);

	// Update all the bodies using wind, gravity, and the equations of motion
	void Update(float timeStep);

};

#endif

