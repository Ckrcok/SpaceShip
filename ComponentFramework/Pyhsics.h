#pragma once
#include "Vector.h"
#include "VMath.h"
#include "PhysicsObject.h"
#include "Plane.h"


class Pyhsics
{
public:
	//  it will remain at rest or keep moving in a straight line at constant speed unless it is acted upon by a force.
	static	void	SimpleNewtonMotion(PhysicsObject &object, const float deltaTime);
	static	void	RigidBodyRotation(PhysicsObject &object, const float deltaTime);

	// Collision detection methods:
	static bool SphereSphereCollisionDetected(const PhysicsObject& PhysicsObject1, const PhysicsObject& PhysicsObject2);
	static bool SpherePlaneCollisionDetected(const PhysicsObject& PhysicsObject1, const Plane& plane);
	// Collision response methods:
	static void SphereSphereCollisionResponse(PhysicsObject& PhysicsObject1,  PhysicsObject& PhysicsObject2);
	static void SphereStaticSphereCollisionResponse(PhysicsObject& PhysicsObject1, const PhysicsObject& staticSphere);
	static void SpherePlaneCollisionResponse(PhysicsObject& PhysicsObject1, const Plane& plane);

	// rotate Z by the applied force on the object - the ship
	Vec3 rotateZ(const Vec3 force, PhysicsObject& object);


	// rate of change of angular momentum of an object
	static	void ApplyTorque(float torque, PhysicsObject& object) { object.setAngularAcceleration(torque / object.getrotationalInertia()); };

	//	apply force and will change accelration by force/ mass  // F = ma
	static	void ApplyForce(Vec3 force, PhysicsObject& object) { object.setAcceleration(force / object.getMass()); };
};

