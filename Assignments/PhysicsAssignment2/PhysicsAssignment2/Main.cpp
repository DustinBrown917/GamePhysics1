//#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Vec3.h"
#include "Body.h"



using namespace std;

void SetAlign(int);

void OutputLineToFile(string data, ofstream& file);

int main(int argc, const char* argv[]) {

	//Are we going to write to a file? True if yes.
	const bool PRINT_TO_FILE = false;
	//What's the name of the file we are going to write to?
	const char FILE_NAME[] = "PhysicsAssignment2.csv";
	//How long is each frame going to take? A theoretical timestep.
	const float TIME_STEP = 0.5f;
	//How wide should the output columns be when writing to the console (in kerned characters).
	const int COLWIDTH = 15;
	//The file to output to if we are outputting to a file.
	ofstream file;

	if(PRINT_TO_FILE){//If we are going to print to a file, open it up.
		file.open(FILE_NAME);
	}

	//Lets go cause some chaos.
	Body ricoRodriguez = Body(200.0f);
	Vec3 force(500.0f, 0.0f, 0.0f); //The initial force that is going to be applied to the body.
	
	//To get the time step between frames dynamically
	float timeSinceLastFrame = 0;
	//Used to find the above variable. Set at the end of each "frame"
	float timeOfLastFrame = 0;

	if (PRINT_TO_FILE) {//If we are writing to a file...
		string headers = "Time:,xForce (N),xAccel (m/s),xVel (m/s),xPos (m)";
		OutputLineToFile(headers, file);
	}
	else {//...Otherwise output to console.
		//Set up headers
		SetAlign(COLWIDTH);
		cout << "Time:";
		SetAlign(COLWIDTH);
		cout << "Force(N):";
		SetAlign(COLWIDTH);
		cout << "Accel(m/s^2):";
		SetAlign(COLWIDTH);
		cout << "Vel (m/s):";
		SetAlign(COLWIDTH);
		cout << "Position(m):" << endl;
	}

	//The "game" loop.
	for (float tick = 0.0f; tick <= 15.0f; tick += TIME_STEP) {

		timeSinceLastFrame = tick - timeOfLastFrame; //Get actual time since last frame.

		//Evaluate story conditions as per the assignment.
		//Conditions are general so as to allow altering the TIME_STEP constant
		//while adhering to the conditions of the story.
		if (tick >= 10.0f && ricoRodriguez.velocity.x <= 0) { force.x = 0.0f; }
		else if (tick >= 10.0f) { force.x = -625.0f; }
		else if (tick >= 5.5f) { force.x = 0.0f; }

		//Apply force and update the body.
		ricoRodriguez.ApplyForce(force);
		ricoRodriguez.Update(timeSinceLastFrame);

		if (PRINT_TO_FILE) { //If we are writing to a file...
			string data = to_string(tick) + "," 
				+ to_string(force.x) + "," 
				+ to_string(ricoRodriguez.acceleration.x) + "," 
				+ to_string(ricoRodriguez.velocity.x) + "," 
				+ to_string(ricoRodriguez.position.x);

			OutputLineToFile(data, file);
		}
		else {//...Otherwise output to console.
			SetAlign(COLWIDTH);
			cout << tick;
			SetAlign(COLWIDTH);
			cout << force.x;
			SetAlign(COLWIDTH);
			cout << ricoRodriguez.acceleration.x;
			SetAlign(COLWIDTH);
			cout << ricoRodriguez.velocity.x;
			SetAlign(COLWIDTH);
			cout << ricoRodriguez.position.x << endl;
		}

		timeOfLastFrame = tick;
	}

	if (PRINT_TO_FILE) { //Let the user know things didn't go bad... Not that anything here actually handles things going bad.
		cout << "File created successfully: " << FILE_NAME;
	}

	cout << endl;

	//Yield for user.
	system("pause");

	if (PRINT_TO_FILE) {//Close the file if we were writing to a file.
		file.close();
	}
}

//Helper method to clean up my cout calls
void SetAlign(int width) {
	cout << setw(width) << left;
}

//I think ths one is self explanatory.
void OutputLineToFile(string data, ofstream& file) {
	file << data;
	file << endl;
}

