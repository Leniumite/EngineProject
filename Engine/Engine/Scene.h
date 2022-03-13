#pragma once

#include <list>
#include "GameObject.h"

class Scene
{
public:
	
	list<GameObject>* _gameObjectList;

	GameObject* AddGameObject();
	void RemoveGameObject(const GameObject &targetGameObject);

};

