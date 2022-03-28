#pragma once
#include "pch.h"
#include "framework.h"

Scene::Scene(Engine* engine)
{
	_engine = engine;
}

void Scene::Init()
{
	_cameraGO = AddGameObject();
	_mainCamera = _cameraGO->AddComponent<CameraComponent>();
	_mainCamera->Init();
}

GameObject* Scene::AddGameObject()
{
	GameObject* newGameObject = new GameObject(_engine);
	_gameObjectList.push_back(newGameObject);
	return newGameObject;
}

Scene::~Scene()
{
	for (GameObject* go : _gameObjectList)
	{
		delete go;
	}
}

void Scene::RemoveGameObject(GameObject* targetGameObject)
{
	delete targetGameObject;
	_gameObjectList.remove(targetGameObject);
}
