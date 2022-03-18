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




