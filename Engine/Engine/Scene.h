#pragma once
class ButtonComponent;
class CameraComponent;
class Scene
{
private:
	GameObject* _cameraGO;
	Engine* _engine;
	

public:
	
	CameraComponent* _mainCamera;
	Scene(Engine* engine);
	
	list<GameObject*> _gameObjectList;
	list<ButtonComponent*> _buttonsList;

	virtual ~Scene();

	void Init();
	GameObject* AddGameObject();
	void RemoveGameObject(GameObject* targetGameObject);

	inline GameObject* GetCameraGO() { return _cameraGO; }

};

