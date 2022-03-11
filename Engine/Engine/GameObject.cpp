#include "pch.h"
#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
{
	transform = new Transform();
}

void GameObject::AddComponentOnObject(Component comp)
{
	components.push_back(comp);
}

void GameObject::RemoveComponentOnObject(Component comp)
{
	list<Component>::iterator findComp = find(components.begin(), components.end(), 1);
	

}

list<Component> GameObject::GetComponentsOnObject()
{
	return components;
}
