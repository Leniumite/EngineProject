#include "pch.h"
#include "Engine.h"


GameObject::GameObject(Engine* engine)
{
	_engine = engine;
	_transform = new Transform(this);
}



void GameObject::UpdateComponents() {
	for_each(_components.begin(), _components.end(), [](Component component) {component.Update(); });
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
	for (auto it = _components.begin(); it != _components.end(); ++it)
	{
		T* temp = dynamic_cast<T*>(*it);
		if (temp)
		{
			return temp;
		}
	}
	return nullptr;
}

template<typename T>
T* GameObject::AddComponent()
{
	if (is_base_of_v<Component, T>)
	{
		T* p = new T(this);

		_components.push_back(p);

		//Component* pCo = (Component*)p;
		//pCo->_gameObject =this
		//dynamic_cast<Component*>(p)->_gameObject = this;

		return p;
	}
	else
	{
		return NULL;
	}
}
