#ifndef Scene3_H
#define Scene3_H
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

class Scene3 : public Scene {
private:
	// create pointer called ship
	PhysicsObject* sphere;
	PhysicsObject* sphere2;
	float waterHeight;


	// create pointer of mesh called shipMesh
	Mesh* sphereMesh;
	Shader* shader;
	Texture* sphereTexture;
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	Matrix4 sphereMatrix;
	Vec3 lightPos;
	Texture *texture;


public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // Scene3_H