#pragma once
#include <iostream>
#include <math.h>
#include "Vector.h"
#include "VMath.h"
#include "Actor.h"
using namespace MATH;

class PhysicsObject : public Actor
{
private:
	Vec3 pos, vel, accel;
	float mass, rotationalInertia;
	float angle, angularVel, angularAccel;

public:
	PhysicsObject();
	PhysicsObject(float mass_, float rotationalInertial);
	virtual ~PhysicsObject();

	void csv(float Time, float Torque);

	//	set mess and get mass
	inline	void	setMass(const float& mass_) { mass = mass_; }
	inline	float	getMass() { return mass; }

	// set and get rotationalInertia
	inline	void	setrotationalInertia(const float& rotationalInertia_) { rotationalInertia = rotationalInertia_; }
	inline	float	getrotationalInertia() {return rotationalInertia;}

	// set and get position
	inline	void	setPosition(const Vec3& pos_) { pos = pos_; };
	inline	Vec3	getPosition() { return pos; }

	//	set and get velocity
	inline	void	setVelocity(const Vec3& vel_) { vel = vel_; }
	inline	Vec3	getVelocity() { return vel; }

	// set and get Acceleration
	inline	void	setAcceleration(const Vec3& accel_) { accel = accel_; }
	inline	Vec3	getAcceleration() { return accel; }

	//	set and get angle
	inline	void	setAngle(const float& angle_) { angle = angle_; }
	inline	float	getAngle() { return angle; }

	//	set and get angular velocity
	inline	void	setAngularVelocity(const float angularVel_) { angularVel = angularVel_; }
	inline	float	getAngularVelocity() { return angularVel; }

	//	set and get angular angular acceleration
	inline	void	setAngularAcceleration(const float angularAccel_) { angularAccel = angularAccel_; }
	inline	float	getAngularAcceleration() { return angularAccel; }

	// F = ma
	inline	Vec3	getForce() { return mass* accel; }

};

