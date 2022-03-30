#include "pch.h"
#include "framework.h"


GameObject::GameObject(Engine* engine)
{
	_engine = engine;
	_transform = new Transform(this);
	_components.push_back(_transform);
}

GameObject::~GameObject()
{
	for (Component* component : _components)
	{
		delete component;
	}
}

void GameObject::UpdateComponents()
{
	for (Component* component : _components)
	{
		if(component->isEnable == TRUE)
			component->Update();
	}
}




