#pragma once
#include "pch.h"
#include "framework.h"

Scene::Scene(Engine* engine)
{
	_engine = engine;
}

void Scene::Init()
{

}

GameObject* Scene::AddGameObject()
{
	GameObject* newGameObject = new GameObject(_engine);
	_gameObjectList.push_back(newGameObject);
	return newGameObject;
}

void Scene::RemoveGameObject(GameObject* targetGameObject)
{
	_gameObjectList.remove(targetGameObject);
}
