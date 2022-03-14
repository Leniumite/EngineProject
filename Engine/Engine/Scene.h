#pragma once

#include <list>
#include "GameObject.h"

class Scene
{
public:
	
	list<GameObject*> _gameObjectList;


	void Init();
	GameObject* AddGameObject();
	void RemoveGameObject(GameObject* targetGameObject);

};

