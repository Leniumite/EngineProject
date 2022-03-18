#pragma once

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

