#pragma once
#include "pch.h"
#include "framework.h"
#include "Camera.h"

Scene::Scene(Engine* engine)
{
	_engine = engine;
	Init();
}

void Scene::Init()
{
	GameObject* CameraGO = AddGameObject();
	_mainCamera = CameraGO->AddComponent<CameraComponent>();
	_mainCamera->Init();
	
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
