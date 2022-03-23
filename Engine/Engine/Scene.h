#pragma once
class CameraComponent;
class Scene
{
private:
	//GameObject* _cameraGO;
	
	
	Engine* _engine;
	

public:
	
	CameraComponent* _mainCamera;
	Scene(Engine* engine);
	
	list<GameObject*> _gameObjectList;

	virtual ~Scene();

	void Init();
	GameObject* AddGameObject();
	void RemoveGameObject(GameObject* targetGameObject);

};

