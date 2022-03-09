#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene0.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"



using namespace std;

Scene0::Scene0() :ship(nullptr), shader{ nullptr }, shipMesh{ nullptr }, shipTexture{ nullptr }  {
	Debug::Info("Created Scene0: ", __FILE__, __LINE__);
}

Scene0::~Scene0() {
	Debug::Info("Deleted Scene0: ", __FILE__, __LINE__);
}

bool Scene0::OnCreate() {
	Debug::Info("Loading assets Scene0: ", __FILE__, __LINE__);
	// define ship with mass and rotationalInertia values
	ship = new PhysicsObject(1000000, 26700000000);

	// create ship
	ship->OnCreate();

	//	set up mesh for ship
	shipMesh = new Mesh(nullptr, "meshes/spaceShip.obj");
	shipMesh->OnCreate();

	// set up shaders for ship
	shader = new Shader(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	shader->OnCreate();
	if (shader->OnCreate() == false) {
		std::cout << "Shader Failed..";
	}

	// load ship texture
	shipTexture = new Texture();
	shipTexture->LoadImage("textures/spaceshuttle.png");

	// set up the scene camera
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 25.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	// light position
	lightPos = Vec3(0.0f, 0.0f, 0.0f);
	return true;
}

void Scene0::OnDestroy() {
	Debug::Info("Deleting assets Scene0: ", __FILE__, __LINE__);

	ship->OnDestroy();
	delete ship;

	shader->OnDestroy();
	delete shader;

	shipMesh->OnDestroy();
	delete shipMesh;

	delete shipTexture;
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent) {
	switch (sdlEvent.type) {
	case SDL_KEYDOWN:
		break;

	case SDL_MOUSEMOTION:
		break;

	case SDL_MOUSEBUTTONDOWN:
		break;

	case SDL_MOUSEBUTTONUP:
		break;

	default:
		break;
	}
}

void Scene0::Update(const float deltaTime) {
	//track print time
	static float printTime = 0;
	printTime += deltaTime;

	//actual time
	static float time = 0;
	time += deltaTime;
	static float torque = 0;

	//	print csv
	if (printTime >= 1) {
		ship->csv(time, torque);
		printTime = 0;
	}

	// 5 sec before one of the engines faluty
	if (time <= 5){

		Pyhsics::ApplyForce(Vec3(5000000, 0, 0), *ship);
		Pyhsics::ApplyTorque(torque, *ship);
		printf(" \n less then 5   \n");

	}else if (time >= 5 && time <= 35) { //	fault engine accuered
		torque = 629100000;
		Pyhsics::ApplyForce(Vec3(2500000, 0, 0), *ship);
		Pyhsics::ApplyTorque(torque, *ship);
		printf("\n \t more then 5 \n");

	}else if (time >= 35) { //	the working engine  stops
		torque = 0;
		Pyhsics::ApplyForce(Vec3(0, 0, 0), *ship);
		Pyhsics::ApplyTorque(torque, *ship);

	}

	// making rotation body work
	Pyhsics::RigidBodyRotation(*ship, deltaTime);

	// define force
	Vec3 force(0.0f, 0.0f, 0.0f);

	// change values for for x and y
	force.x = ship->getForce().x * cos(ship->getAngle()) - ship->getForce().y * sin(ship->getAngle());
	force.y = ship->getForce().x * sin(ship->getAngle()) + ship->getForce().y * cos(ship->getAngle());

	// apply force on the ship with force.x and force.y
	Pyhsics::ApplyForce(force, *ship);

	//setting up the ship and it angle in the world
	ship->SetModelMatrix(	MMath::translate(Vec3(-15 ,-5 ,0) )*
							MMath::translate(ship->getPosition() * 0.0004) *
							MMath::rotate(ship->getAngle() * RADIANS_TO_DEGREES, 0.0, 0.0, 1.0) *
							MMath::rotate(90,1.0, 0.0, 0.0) *
							MMath::rotate(90, 0.0, 2.0, 0.0) *
							MMath::scale(0.4f, 0.4f, 0.4f));

	//	apply simple newton motion
	Pyhsics::SimpleNewtonMotion(*ship, deltaTime);
	cout << time << endl;

}

void Scene0::Render() const {

	//render the whole scene
	glEnable(GL_DEPTH_TEST);

	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);


	glBindTexture(GL_TEXTURE_2D, shipTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, ship->GetModelMatrix());
	shipMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram(0);
}




