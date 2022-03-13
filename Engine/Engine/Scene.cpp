#include "pch.h"
#include "Scene.h"

//Scene::Scene()
//{
//
//}

GameObject* Scene::AddGameObject()
{
	GameObject* newGameObject = new GameObject();
	_gameObjectList->push_back(*newGameObject);
	return newGameObject;
}

void Scene::RemoveGameObject(const GameObject& targetGameObject)
{
	//_gameObjectList->remove(targetGameObject);
}
