#include "Actor.h"


Actor::Actor(Component* parent_) :Component(parent_), modelMatrix(MATH::Matrix4()), texture(nullptr), mesh(nullptr) {}
Actor::~Actor() {}

void Actor::ListComponents() const {
	for (auto c : components) {
		std::cout << typeid(*c).name() << std::endl;
	}
}


bool Actor::OnCreate() {
	return true;
}
void Actor::OnDestroy() {
	if (mesh)
	{
		mesh->OnDestroy();
		delete mesh;
		mesh = nullptr;
	}

	if (texture)
	{
		delete texture;
		texture = nullptr;
	}


}
void Actor::Update(const float deltaTime) {}
void Actor::Render()const {}






