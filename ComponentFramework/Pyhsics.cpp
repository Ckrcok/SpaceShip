#include "Pyhsics.h"
#include <iostream>

void Pyhsics::SimpleNewtonMotion(PhysicsObject& object, const float deltatime){

	//posf = posi + velli * deltatime + 0.5  * accel * deltaTime
	object.setPosition(object.getPosition() + object.getVelocity() + 0.5 * object.getAcceleration() * deltatime * deltatime);

	//velf =veli + accel * deltaTime
	object.setVelocity(object.getVelocity() + object.getAcceleration() * deltatime);
}

void Pyhsics::RigidBodyRotation(PhysicsObject& object, const float deltatime){
	//angPosf = angPosi + angVelli * deltatime + 0.5  * angAccel * deltaTime
	object.setAngle(object.getAngle() + object.getAngularVelocity() * deltatime + 0.5f * object.getAngularAcceleration() * deltatime * deltatime);
	//angVelf = angVeli + accel * deltaTime
	object.setAngularVelocity(object.getAngularVelocity() + object.getAngularAcceleration() * deltatime);
}

Vec3 Pyhsics::rotateZ(const Vec3 force, PhysicsObject& object){
	// converte degres to radians  Deg × π / 180 = Rad
	double rads = (object.getAngle() * M_PI / 180);

	//decleare ForceX, ForceY
	double ForceX, ForceY;

	// rotate  the thrust  vector  direction  using 2D transformation  matrix
	ForceX = (cos(rads) * force.x) - (sin(rads) * force.y);
	ForceY = (sin(rads) * force.x) + (cos(rads) * force.y);

	// return force X and force Y
	return Vec3(ForceX, ForceY, 0.0f);
}

