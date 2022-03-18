#pragma once
class CameraComponent;
class Scene
{
private:
	CameraComponent* _mainCamera;
	
	Engine* _engine;
	

public:
	

	Scene(Engine* engine);
	
	list<GameObject*> _gameObjectList;


	void Init();
	GameObject* AddGameObject();
	void RemoveGameObject(GameObject* targetGameObject);

};

