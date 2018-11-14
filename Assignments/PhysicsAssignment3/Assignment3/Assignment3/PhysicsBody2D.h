#ifndef PHYSICSBODY2D_H
#define PHYSICSBODY2D_H

#include "Vector.h"

class PhysicsBody2D
{
public: //Member variables
	bool gravityScale;
	float mass, angle;
	Vec2 position, velocity, acceleration;

public:
	PhysicsBody2D();
	PhysicsBody2D(float _mass); // _mass constructor
	PhysicsBody2D(float _mass, float _angle, Vec2 _position, Vec2 _velocity, Vec2 _acceleration); //Advanced constructor
	~PhysicsBody2D();

public:
	void Update(float timeStep); //Called every frame
	void ApplyForce(Vec2 force); //Add force to the body
};


#endif // !PHYSICSBODY2D_H

