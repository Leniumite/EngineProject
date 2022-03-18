#pragma once
#include "Component.h"

using namespace std;

class GameObject
{
private:
	list<Component> _components;
	Engine* _engine;

public:


	Transform* _transform;

	GameObject(Engine* engine);

	inline Engine* GetEngine() { return _engine; }

	void UpdateComponents();

	template<typename T>
	T* AddComponent();

	inline list<Component>& GetAllComponents() { return _components; }

	template<typename T>
	T* GetComponent();
};

