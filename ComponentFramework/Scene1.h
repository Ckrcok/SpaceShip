#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
#include "Pyhsics.h"

using namespace MATH;

/// Forward declarations
union SDL_Event;
class Actor;
class Mesh;
class Shader;
class Texture;

class Scene1 : public Scene {
private:
	// create pointer called ship
	PhysicsObject* sphere;
	PhysicsObject* sphere2;
	PhysicsObject* sphere3;


	// create pointer of mesh called shipMesh
	Mesh* sphereMesh;
	Shader* shader;
	Texture* sphereTexture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 sphereMatrix;
	Vec3 lightPos;
	Texture *texture;
	Plane* plane;

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // Scene1_H