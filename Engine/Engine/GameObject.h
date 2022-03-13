#pragma once
#include <iostream>
#include <iterator>
#include <list>
#include "Component.h"

using namespace std;

class GameObject
{
private:
	list<Component> _components;

public:
	Transform* _transform;

	GameObject();

	template<typename T>
	T* AddComponent();

	list<Component>& GetAllComponents() { return _components; }

	template<typename T>
	T* GetComponent();
};

