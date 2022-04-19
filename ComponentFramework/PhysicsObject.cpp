#include "PhysicsObject.h"
#include "VMath.h"
#include <fstream>
using namespace MATH;
using namespace std;

PhysicsObject::PhysicsObject():pos(0.0f,0.0f,0.0f), vel(0.0f, 0.0f, 0.0f), accel(0.0f, 0.0f, 0.0f), mass(1.0f), rotationalInertia(1.0f), length(1.0f), Actor(nullptr) {
	angle = angularVel = angularAccel = 0.0f;
}


PhysicsObject::PhysicsObject(const Vec3 velocity_, const float rotationalInertia_, const float radius_) : vel(velocity_), mass(1.0f), radius(radius_), rotationalInertia(rotationalInertia_), Actor(nullptr) {

}

PhysicsObject::PhysicsObject(const Vec3 velocity_, const float rotationalInertia_, const float radius_, const float length_) : vel(velocity_), mass(1.0f), radius(radius_), rotationalInertia(rotationalInertia_), length(length_), Actor(nullptr) {

}

PhysicsObject::~PhysicsObject(){}

void PhysicsObject::csv(float Time , float Torque ) {
	fstream myFile;
	static bool writing = false;

	//print first line of what each value
	if (!writing){
		myFile.open("output.csv", ios::out);
		if (myFile.is_open()) {

			myFile << "Time" << "," << "Torque" << "," << "AngAccel" << "," << "AngVel" << "," << "Angle" << ","
				<< "Force.x" << "," << "Force.y" << "," << "Accel.x" << "," << "Accel.y" << ","
				<< "Vel.x" << "," << "Vel.y" << "," << "Pos.x" << "," << "Pos.y" << "," << endl;

			writing = true;
		}

		//print the actual value
	} else {
		myFile.open("output.csv", ios::app);
		myFile << Time << "," << Torque << "," << angularAccel << "," << angularVel << "," << angle << ","
			<< getForce().x << "," << getForce().y << "," << accel.x << "," << accel.y << ","
			<< vel.x << "," << vel.y << "," << pos.x << "," << pos.y << "," << endl;
	}

	myFile.close();
}
