#pragma once

#include <list>
#include <iostream>
#include <iterator>
#include "Engine.h"

class Scene
{
private:

	Engine* _engine;


public:

	Scene(Engine* engine);
	
	list<GameObject*> _gameObjectList;


	void Init();
	GameObject* AddGameObject();
	void RemoveGameObject(GameObject* targetGameObject);

};

