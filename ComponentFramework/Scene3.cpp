#include <glew.h>
#include <iostream>
#include <SDL.h>
#include "Debug.h"
#include "Scene3.h"
#include "MMath.h"
#include "Debug.h"
#include "Actor.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <SDL_image.h>




using namespace std;

Scene3::Scene3() :sphere(nullptr), shader{ nullptr }, sphereMesh{ nullptr }, sphereTexture{ nullptr }  {
	Debug::Info("Created Scene3: ", __FILE__, __LINE__);
}

Scene3::~Scene3() {
	Debug::Info("Deleted Scene3: ", __FILE__, __LINE__);
}

bool Scene3::OnCreate() {
	Debug::Info("Loading assets Scene3: ", __FILE__, __LINE__);
	// create sphere
	sphere = new PhysicsObject(Vec3(0,0,0), 0 , 1.12, 0.5);
	sphere2 = new PhysicsObject(Vec3(1, 0, 0), 0, 1.12);

	waterHeight = 0.0f;

	// create sphere
	sphere->OnCreate();
	sphere2->OnCreate();

	// set sphere position
	sphere->setPosition(Vec3(0, 2, 0));
	sphere2->setPosition(Vec3(-1, 20, 0));



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



	// set up the scene camera
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 500.f);
	viewMatrix = MMath::lookAt(Vec3(1.0f, 20.0f, 40.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));

	// light position
	lightPos = Vec3(0.0f, 0.0f, 0.0f);
	return true;
}

void Scene3::OnDestroy() {
	Debug::Info("Deleting assets Scene3: ", __FILE__, __LINE__);

	sphere->OnDestroy();
	delete sphere;

	sphere2->OnDestroy();
	delete sphere2;


	shader->OnDestroy();
	delete shader;

	sphereMesh->OnDestroy();
	delete sphereMesh;

	delete sphereTexture;
}

void Scene3::HandleEvents(const SDL_Event& sdlEvent) {
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

void Scene3::Update(const float deltaTime) {
	Pyhsics::ApplyForces(*sphere, waterHeight);
	Pyhsics::SimpleNewtonMotion(*sphere, deltaTime);
	sphere->SetModelMatrix(MMath::translate(sphere->getPosition()));
}

void Scene3::Render() const {
	//render the whole scene
	glEnable(GL_DEPTH_TEST);

	/// Clear the screen
	glClearColor(5.0f, 5.0f, 3.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// light
	glUseProgram(shader->GetProgram());
	glUniformMatrix4fv(shader->GetUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(shader->GetUniformID("viewMatrix"), 1, GL_FALSE, viewMatrix);
	glUniform3fv(shader->GetUniformID("lightPos"), 1, lightPos);

	//shpere 1
	glBindTexture(GL_TEXTURE_2D, sphereTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere->GetModelMatrix());
	sphereMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);


	//shpere 2
	glBindTexture(GL_TEXTURE_2D, sphereTexture->getTextureID());
	glUniformMatrix4fv(shader->GetUniformID("modelMatrix"), 1, GL_FALSE, sphere2->GetModelMatrix());
	sphereMesh->Render(GL_TRIANGLES);
	glBindTexture(GL_TEXTURE_2D, 0);





	glUseProgram(0);
}




