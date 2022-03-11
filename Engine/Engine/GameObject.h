#pragma once
#include <iostream>
#include <iterator>
#include <list>
#include "Component.h"

using namespace std;

class GameObject
{
private:
	list<Component> components;

public:
	Transform* transform;

	GameObject();
	void AddComponentOnObject(Component comp);
	void RemoveComponentOnObject(Component comp);
	list<Component> GetComponentsOnObject();

};

