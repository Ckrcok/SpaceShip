#ifndef SCENE0_H
#define SCENE0_H
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

class Scene0 : public Scene {
private:
	// create pointer called ship
	PhysicsObject* ship;
	// create pointer of mesh called shipMesh
	Mesh* shipMesh;
	Shader* shader;
	Texture* shipTexture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 shipMatrix;
	Vec3 lightPos;
	Texture *texture;

public:
	explicit Scene0();
	virtual ~Scene0();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // SCENE0_H