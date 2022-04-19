#include "Pyhsics.h"
#include <iostream>
#include "VMath.h"

void Pyhsics::SimpleNewtonMotion(PhysicsObject& object, const float deltatime){

	//posf = posi + velli * deltatime + 0.5  * accel * deltaTime^2
	//object.setPosition(object.getPosition() + object.getVelocity() + 0.5 * object.getAcceleration() * deltatime * deltatime);
	object.setPosition(object.getPosition() + object.getVelocity() * deltatime + ( 0.5 * object.getPreviousAccel() * deltatime * deltatime));

	//velf =veli + accel * deltaTime
	//object.setVelocity(object.getVelocity() + object.getAcceleration() * deltatime);
	object.setVelocity(object.getVelocity() + 0.5 * ( object.getPreviousAccel() + object.getAcceleration()) * deltatime);

	object.setPreviousAccel(object.getAcceleration());
}

void Pyhsics::RigidBodyRotation(PhysicsObject& object, const float deltatime){
	//angPosf = angPosi + angVelli * deltatime + 0.5  * angAccel * deltaTime
	object.setAngle(object.getAngle() + object.getAngularVelocity() * deltatime + 0.5f * object.getAngularAcceleration() * deltatime * deltatime);
	//angVelf = angVeli + accel * deltaTime
	object.setAngularVelocity(object.getAngularVelocity() + object.getAngularAcceleration() * deltatime);
}



Vec3 Pyhsics::rotateZ(const Vec3 force, PhysicsObject& object){
	// converte degres to radians  Deg × π / 180 = Rad
	float rads = (object.getAngle() * M_PI / 180);

	//decleare ForceX, ForceY
	float ForceX, ForceY;

	// rotate  the thrust  vector  direction  using 2D transformation  matrix
	ForceX = (cos(rads) * force.x) - (sin(rads) * force.y);
	ForceY = (sin(rads) * force.x) + (cos(rads) * force.y);

	// return force X and force Y
	return Vec3(ForceX, ForceY, 0.0f);
}

void Pyhsics::ApplyForces(PhysicsObject& object, float& waterHeight) {
	const float g = 9.81f;
	const float dragC = 0.4f;
	const float waterDensity = 1.0f;
	float theta = 2 * acosf(object.getMass() / object.getRadius());
	float v = 0;


	if (object.getPosition().y + object.getRadius() <= waterHeight){
	// fully sumbereged
		v = M_PI * powf(object.getRadius(), 2) * object.getlength();
		printf("\n Submereged \n");
	}else if ((object.getPosition().y - object.getRadius()) <= waterHeight && object.getPosition().y >= waterHeight) {
	// half subemreged
		v = (1 / 2) * powf(object.getRadius(), 2) * (theta - sinf(theta)) * object.getlength();
		printf("\n Half Sumberged");
	}else if (object.getPosition().y <= waterHeight) {
	// above the waterHeight
		v = M_PI * powf(object.getRadius(), 2) * object.getlength() - (1.0f / 2.0f) * powf(object.getRadius(), 2) * (theta - sinf(theta) * object.getlength());
		printf("\n mostly submerged \n");
	}else if ((object.getPosition().y - object.getRadius()) > waterHeight) {
		v = 0;
		printf("\n above watrer \n");
	}




	Vec3 fGrav(0, object.getMass() * -g, 0);
	Vec3 fDrag(dragC * -object.getVelocity());
	Vec3 fBouy(0, waterDensity * g * v, 0);
	Vec3 fNet = fGrav + fDrag + fBouy;
	ApplyForce(fNet, object);

}

bool Pyhsics::SphereSphereCollisionDetected(const PhysicsObject& PhysicsObject1, const PhysicsObject& PhysicsObject2) {
	float distance2 = VMath::distance(PhysicsObject1.getPosition(), PhysicsObject2.getPosition());
	float sumRadius = PhysicsObject1.getRadius() + PhysicsObject2.getRadius();

	//printf("\n\n \t distance %f \n", distance2);
	//printf("\n\n \t sumRadius %f \n", sumRadius);

	//check if the sum radius is bigger then distance if true there is collision
	if (sumRadius >= distance2 ){

		return true;
	} else {

		return false;
	}
}

bool Pyhsics::SpherePlaneCollisionDetected(const PhysicsObject& PhysicsObject1, const Plane& plane)
{
	//distance = (plane normal) dot(PhysicsObject position) + d – PhysicsObject.radius
	float distance = VMath::dot(plane.xyz(), PhysicsObject1.getPosition()) + plane.d - PhysicsObject1.getRadius();
	/*printf("\n distance \t %f \n" , distance );*/

	// check if the distance between the sphere and plane smaller or equle to zero if true collision detected
	if (distance <= 0)
	{
		return true;
	}else {
		return false;
	}
}

void Pyhsics::SphereSphereCollisionResponse(PhysicsObject& PhysicsObject1,  PhysicsObject& PhysicsObject2)
{
	//check if SphereSphereCollisionResponse, if true then Response to Sphere to Sphere collision
	if (SphereSphereCollisionDetected(PhysicsObject1 , PhysicsObject2))
	{
		printf("\n  SphereSphereCollisionDetected \n  \t");
		float e = 1.0f;
		// set e
		e > 1 ? e = 1 : e < 0 ? e = 0 : e;
		Vec3 N = VMath::normalize(PhysicsObject1.getPosition() - PhysicsObject2.getPosition());
		float p1 = (VMath::dot(-PhysicsObject1.getVelocity(), N));
		float p2 = (VMath::dot(-PhysicsObject2.getVelocity(), N));
		float VF1 = ((PhysicsObject1.getMass() * p1) + (PhysicsObject2.getMass() * p2) + ((PhysicsObject2.getMass() * e) * (p2 - p1))) / (PhysicsObject2.getMass() + PhysicsObject1.getMass());
		float VF2 = ((PhysicsObject1.getMass() * p1) + (PhysicsObject2.getMass() * p2) + ((PhysicsObject1.getMass() * e) * (p1 - p2))) / (PhysicsObject2.getMass() + PhysicsObject1.getMass());


		PhysicsObject1.setVelocity((VF2 - p2) * N);
		PhysicsObject2.setVelocity((VF1 - p1) * N);
	}

}

void Pyhsics::SphereStaticSphereCollisionResponse(PhysicsObject& PhysicsObject1, const PhysicsObject& staticSphere)
{
	//check if SphereStaticSphereCollisionDetected, if true then Response to sphere to static sphere collision

	if (SphereSphereCollisionDetected(PhysicsObject1, staticSphere)) {
		printf("\n  SphereStaticSphereCollisionResponse \n \t");
		Vec3 b = VMath::normalize(PhysicsObject1.getPosition() - staticSphere.getPosition());
		Vec3 p = VMath::dot(-PhysicsObject1.getVelocity(), b) * b;
		Vec3 f = PhysicsObject1.getVelocity() + 2 * p;
		PhysicsObject1.setVelocity(f);
		//print final vector
		//f.print();
	}

}

void Pyhsics::SpherePlaneCollisionResponse(PhysicsObject& PhysicsObject1, const Plane& plane)
{
	//check if SpherePlaneCollisionDetected, if true then Response to sphere to plane collision

	if (SpherePlaneCollisionDetected(PhysicsObject1, plane)){
		printf("\n SphereSphereCollisionDetected\n \t");
		Vec3 b = VMath::normalize(Vec3(plane.x, plane.y, plane.z));
		Vec3 p = VMath::dot(-PhysicsObject1.getVelocity(), b)* b;
		Vec3 f = PhysicsObject1.getVelocity() + 2 * p;
		PhysicsObject1.setVelocity(f);
		//print final vector
		//f.print();
	}
}