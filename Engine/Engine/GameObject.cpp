#include "pch.h"
#include "framework.h"


GameObject::GameObject(Engine* engine)
{
	_engine = engine;
	_transform = new Transform(this);
}



void GameObject::UpdateComponents()
{
	for (Component* component : _components)
	{
		component->Update();
	}
}

/*
template<typename T>
bool GameObject::RemoveComponentOnObject()
{
	list<Component>::iterator it;

	for (auto const& component : components) {
		if (is_same(typeid(component), T).value == true) {
			components.remove(component);
			delete component;
			//~Component(component);
			return true;
		}
	}
	return false;

}*/




