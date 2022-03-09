#pragma once
#include "Vector.h"
#include "VMath.h"
#include "PhysicsObject.h"


class Pyhsics
{
public:
	//  it will remain at rest or keep moving in a straight line at constant speed unless it is acted upon by a force.
	static	void	SimpleNewtonMotion(PhysicsObject &object, const float deltaTime);
	static	void	RigidBodyRotation(PhysicsObject &object, const float deltaTime);

	//static	bool	PlaneSphereCollision(const PhysicsObject &object, const &Plane p);
	//static	void	PlaneSphereCollisionResponse(PhysicsObject &object, const Plane& p);
	//static	bool	SphereSphereCollision(const PhysicsObject& object1, const PhysicsObject &object2);
	//static	void	SphereSphereCollisionResponse(PhysicsObject& object1, const PhysicsObject& object2);

	// rotate Z by the applied force on the object - the ship
	Vec3 rotateZ(const Vec3 force, PhysicsObject& object);


	// rate of change of angular momentum of an object
	static	void ApplyTorque(float torque, PhysicsObject& object) { object.setAngularAcceleration(torque / object.getrotationalInertia()); };

	//	apply force and will change accelration by force/ mass  // F = ma
	static	void ApplyForce(Vec3 force, PhysicsObject& object) { object.setAcceleration(force / object.getMass()); };
};

