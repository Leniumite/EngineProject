#include "pch.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	_transform = new Transform();
}

template<typename T>
T* GameObject::AddComponent()
{
	if (is_base_of_v<Component, T>)
	{
		T* p = new T();
		_components.push_back(p);
		return p;
	}
	else
	{
		return NULL;
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

template <typename T>
T* GameObject::GetComponent() {
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		T* temp = dynamic_cast<T*>(*it);
		if (temp)
		{
			return temp;
		}
	}
	return nullptr;
}
