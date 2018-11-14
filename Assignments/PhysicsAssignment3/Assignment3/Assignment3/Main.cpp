#include <iostream>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <string>
#include "Assignment.h"
#include "PhysicsBody2D.h"

#define PI 3.1415926f

void OutputHeaders();
void OutputWorldData(Assignment& world, float totalTime);
void CalculateFloorPosition(Vec2& floorVec, float xPos);
void OutputLineToFile(std::string data, std::ofstream& file);
std::string WorldDataToString(Assignment& world);

int main(int argc, char* argv[]) {
	//Are we going to write to a file? True if yes.
	const bool PRINT_TO_FILE = false;
	//What's the name of the file we are going to write to?
	const char FILE_NAME[] = "PhysicsAssignment3.csv";
	//The file to output to if we are outputting to a file.
	std::ofstream file;

	if (PRINT_TO_FILE) {//If we are going to print to a file, open it up.
		file.open(FILE_NAME);
	}

	//Create the gravitational acceleration for the world.
	Vec2 gravitationalAccel = Vec2(0, -9.8f);

	//In the beginning, Dustin created the earth.
	Assignment world(gravitationalAccel);

	//Create two jetski pointers with story-dictated mass.
	PhysicsBody2D* jetSki1 = new PhysicsBody2D(200.0f);
	PhysicsBody2D* jetSki2 = new PhysicsBody2D(400.0f);

	//Ass the jetskies to the world.
	world.AddTwoBodies(jetSki1, jetSki2);

	//The timestep of the simulation.
	const float timestep = 0.1f;

	//The angle of the ramp.
	const float rampAngleDegrees = 30.0f;
	// To convert to radians, use 360 degree = 2 pi radians
	float rampAngleRadians = (rampAngleDegrees / 360.0f) * 2 * PI;

	//The initial force to apply to the jetskis.
	Vec2 forceAtStart(3000.0f, 0.0f);
	//Initialize the floor position.
	Vec2 floorPosition = Vec2();

	//Print headers to console.
	OutputHeaders();

	if (PRINT_TO_FILE) {//If printing to file is enabled, then print the headers data to the file.
		OutputLineToFile("Time,Body 0 x Pos (m), Body 0 y Pos (m),Body 1 x Pos (m), Body 1 y Pos (m)", file );
	}

	// Loop until the JetSki hits the water
	// How long is that? I'll pretend it's 10 seconds??
	for (float totalTime = 0.0f; totalTime <= 4.0f; totalTime += timestep)
	{
		//acts as a sort of motor to push the bodies along the floor.
		Vec2 forceThisFrame = Vec2();
		
		for (PhysicsBody2D* b : world.bodies) { //Loop through the PhysicsBody2D's in the world.
			//Find where the floor is.
			CalculateFloorPosition(floorPosition, b->position.x);
			if (b->position.y <= floorPosition.y) { 
				b->position.y = floorPosition.y; //Make sure the body is not below the floor.
				//Not a fan of switching gravity off, but it needs to be done here to prevent
				//vertical velocity from accumulating into the negative while approaching the ramp.
				b->gravityScale = 0.0f; 
			}
			else {
				b->gravityScale = 1.0f;
			}

			if (b->position.x >= 14.33f) { //If past the ramp, apply no more x force, but ensure gravity does its job.
				forceThisFrame = (world.gravitationalAcceleration * b->mass * b->gravityScale);
			}
			else if (b->position.x >= 10.0f) {//If on the ramp, apply force with gravity opposing it.
				forceThisFrame.x = forceThisFrame.x - b->mass * world.gravitationalAcceleration.y * sin(rampAngleRadians);
				forceThisFrame = Vec2::Rotate(forceThisFrame, rampAngleDegrees); //Rotate the force to match the ramp.

				//Rotate the body once and apply the rotation to the velocity.
				if (b->angle < 30.0f) {
					b->angle = 30.0f;
					b->velocity = Vec2::Rotate(b->velocity, b->angle);
				}
			}
			else { //Otherwise force this frame is just the starting force.
				forceThisFrame = forceAtStart;
			}
			b->ApplyForce(forceThisFrame); //Apply the calculated force this frame to the body.
		}
		//Output world data to console.
		OutputWorldData(world, totalTime);

		if (PRINT_TO_FILE) {//If printing to file is enabled, then print the world data to the file.
			OutputLineToFile(WorldDataToString(world), file);
		}

		//Update the world.
		world.Update(timestep);
	}

	//Keep console open and yield for user input.
	system("pause");

	return 0;
}

//Print the headers to console.
void OutputHeaders() {
	std::cout << std::setw(15) << std::left << "Total Time"
		<< std::setw(15) << std::left << "B0 pos.x"
		<< std::setw(15) << std::left << "B0 pos.y" 
		<< std::setw(15) << std::left << "B1 pos.x"
		<< std::setw(15) << std::left << "B1 pos.y" << std::endl;
}

//Print the world data to console.
void OutputWorldData(Assignment& world, float totalTime) {
	std::cout << std::setw(15) << std::left 
		<< totalTime << std::setw(15) << std::left
		<< world.bodies[0]->position.x << std::setw(15) << std::left
		<< world.bodies[0]->position.y << std::setw(15) << std::left
		<< world.bodies[1]->position.x << std::setw(15) << std::left
		<< world.bodies[1]->position.y << std::endl;
}

//Find the y point the the jetski should not fall below.
void CalculateFloorPosition(Vec2& floorVec, float xPos) {
	if (xPos < 10.0f || xPos > 14.33f) { // If the jetski isn't on the ramp, the floor is at 0.
		floorVec.y = 0.0f;
	}
	else { //If the jetski is on the ramp, the floor position is found based on how far along the ramp they are.
		floorVec += Vec2::Lerp(Vec2(0.0f, 0.0f), Vec2(0.0f, 2.5f), (xPos - 10.0f) / (4.33f));
	}
}

//I think ths one is self explanatory.
void OutputLineToFile(std::string data, std::ofstream& file) {
	file << data;
	file << std::endl;
}

//Converts the requisite world data to a string for outputting.
std::string WorldDataToString(Assignment& world) {
	return std::to_string(world.elapsedTime) + "," +
		std::to_string(world.bodies[0]->position.x) + "," +
		std::to_string(world.bodies[0]->position.y) + "," +
		std::to_string(world.bodies[1]->position.x) + "," +
		std::to_string(world.bodies[1]->position.y);
}