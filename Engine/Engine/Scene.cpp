#include "pch.h"
#include "Scene.h"

void Scene::Init()
{

}

GameObject* Scene::AddGameObject()
{
	GameObject* newGameObject = new GameObject();
	_gameObjectList.push_back(newGameObject);
	return newGameObject;
}

void Scene::RemoveGameObject(GameObject* targetGameObject)
{
	_gameObjectList.remove(targetGameObject);
}
