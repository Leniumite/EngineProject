#pragma once

#include <list>
#include "GameObject.h"

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

