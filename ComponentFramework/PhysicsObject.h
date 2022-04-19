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
	float angle, angularVel, angularAccel, length;
	Vec3 previousAccel;
	float radius;

public:
	PhysicsObject();
	PhysicsObject(const Vec3 velocity_, const float rotationalInertia_, const float radius_);
	PhysicsObject(const Vec3 velocity_, const float rotationalInertia_, const float radius_, const float length_);
	virtual ~PhysicsObject();
	void csv(float Time, float Torque);

	//	set mess and get mass
	inline	void	setMass(const float& mass_) { mass = mass_; }
	inline	float	getMass() const { return mass; }

	//	set mess and get mass
	inline	void	setPreviousAccel(const Vec3& previousAccel_) { previousAccel = previousAccel_; }
	inline	Vec3	getPreviousAccel() const { return previousAccel; }



	// set and get length
	inline	void	setlength(const float& length_) { length = length_; }
	inline	float	getlength() const { return length; }


	// set and get rotationalInertia
	inline	void	setrotationalInertia(const float& rotationalInertia_) { rotationalInertia = rotationalInertia_; }
	inline	float	getrotationalInertia() const {return rotationalInertia;}

	// set and get position
	inline	void	setPosition(const Vec3& pos_) { pos = pos_; };
	inline	Vec3	getPosition() const { return pos; }

	//	set and get velocity
	inline	void	setVelocity(const Vec3& vel_) { vel = vel_; }
	inline	Vec3	getVelocity()const { return vel; }

	// set and get Acceleration
	inline	void	setAcceleration(const Vec3& accel_) { accel = accel_; }
	inline	Vec3	getAcceleration() const { return accel; }

	//	set and get angle
	inline	void	setAngle(const float& angle_) { angle = angle_; }
	inline	float	getAngle() const { return angle; }

	//	set and get angular velocity
	inline	void	setAngularVelocity(const float angularVel_) { angularVel = angularVel_; }
	inline	float	getAngularVelocity()const { return angularVel; }

	//	set and get angular angular acceleration
	inline	void	setAngularAcceleration(const float angularAccel_) { angularAccel = angularAccel_; }
	inline	float	getAngularAcceleration() const { return angularAccel; }


	//	set and get angular angular acceleration
	inline	void	setRadius(const float radius_) { radius = radius_; }
	inline	float	getRadius() const { return radius; }


	// F = ma
	inline	Vec3	getForce() const { return mass* accel; }

};

