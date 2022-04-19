#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene1.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <SDL_image.h>




using namespace std;

Scene1::Scene1() :sphere(nullptr), shader{ nullptr }, sphereMesh{ nullptr }, sphereTexture{ nullptr }  {
	Debug::Info("Created Scene1: ", __FILE__, __LINE__);
}

Scene1::~Scene1() {
	Debug::Info("Deleted Scene1: ", __FILE__, __LINE__);
}

bool Scene1::OnCreate() {
	Debug::Info("Loading assets Scene1: ", __FILE__, __LINE__);
	// create sphere
	sphere = new PhysicsObject(Vec3(0.2,0,0), 0 , 1.12);
	sphere2 = new PhysicsObject(Vec3(1, 0, 0), 0, 1.12);
	sphere3 = new PhysicsObject(Vec3(0.1, 0, 0), 0, 1.12);

	// create sphere
	sphere->OnCreate();
	sphere2->OnCreate();
	sphere3->OnCreate();

	// set sphere position
	sphere->setPosition(Vec3(-50, -1, 0));
	sphere2->setPosition(Vec3(-1, 20, 0));
	sphere3->setPosition(Vec3(-70, 0, 0));



	//	set up mesh for sphere
	sphereMesh = new Mesh(nullptr, "meshes/Sphere.obj");
	sphereMesh->OnCreate();

	// set up shaders for sphere
	shader = new Shader(nullptr, "shaders/textureVert.glsl", "shaders/textureFrag.glsl");
	shader->OnCreate();
	if (shader->OnCreate() == false) {
		std::cout << "Shader Failed..";
	}

	// load sphere texture
	sphereTexture = new Texture();
	sphereTexture->LoadImage("textures/moon.jpg");

	//create plane
	plane = new Plane( -1 , 1 ,0,0);



	// set up the scene camera
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 500.f);
	viewMatrix = MMath::lookAt(Vec3(1.0f, 20.0f, 40.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	// light position
	lightPos = Vec3(0.0f, 0.0f, 0.0f);
	return true;
}

void Scene1::OnDestroy() {
	Debug::Info("Deleting assets Scene1: ", __FILE__, __LINE__);

	sphere->OnDestroy();
	delete sphere;

	sphere2->OnDestroy();
	delete sphere2;


	sphere3->OnDestroy();
	delete sphere3;

	shader->OnDestroy();
	delete shader;

	sphereMesh->OnDestroy();
	delete sphereMesh;

	delete sphereTexture;
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent) {
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

void Scene1::Update(const float deltaTime) {
	//place it and resize the sphere
	sphere->SetModelMatrix(MMath::translate(sphere->getPosition()) * MMath::scale(1.12, 1.12, 1.12) );
	sphere2->SetModelMatrix(MMath::translate(sphere2->getPosition()) * MMath::scale(1.12, 1.12, 1.12));
	sphere3->SetModelMatrix(MMath::translate(sphere3->getPosition()) * MMath::scale(1.12, 1.12, 1.12));
	//check and response for sphere to plane coliision
	Pyhsics::SpherePlaneCollisionResponse(*sphere, *plane);
	//check and response for sphere to static sphere coliision
	Pyhsics::SphereStaticSphereCollisionResponse(*sphere, *sphere2);
	//check and response for sphere to  sphere coliision
	Pyhsics::SphereSphereCollisionResponse(*sphere, *sphere3);
	//Apply Simple newton motion
	Pyhsics::SimpleNewtonMotion( *sphere , deltaTime);
	Pyhsics::SimpleNewtonMotion(*sphere3, deltaTime);

}

void Scene1::Render() const {
	//render the whole scene
	glEnable(GL_DEPTH_TEST);

	/// Clear the screen
	glClearColor(5.0f, 5.0f, 3.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);


	glBindTexture(GL_TEXTURE_2D, sphereTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	sphereMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);



	glBindTexture(GL_TEXTURE_2D, sphereTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere2->GetModelMatrix());
	sphereMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, sphereTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere3->GetModelMatrix());
	sphereMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);



	glUseProgram(0);
}




