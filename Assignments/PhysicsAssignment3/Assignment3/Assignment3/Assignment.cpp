#include "Assignment.h"
#include "PhysicsBody2D.h"


Assignment::Assignment(Vec2 gravitationalAcceleration_)
{
	gravitationalAcceleration = gravitationalAcceleration_;
	elapsedTime = 0;

	for (PhysicsBody2D* b : bodies) {
		b = new PhysicsBody2D();
	}
}


Assignment::~Assignment()
{
}

void Assignment::AddTwoBodies(PhysicsBody2D * body1, PhysicsBody2D * body2)
{
	bodies[0] = body1;
	bodies[1] = body2;
}

void Assignment::Update(float timeStep)
{
	elapsedTime += timeStep;
	for (PhysicsBody2D* b : bodies) {
		b->Update(timeStep);
	}
}
