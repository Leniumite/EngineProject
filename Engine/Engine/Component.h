#pragma once

class GameObject;
class Engine;
class Component
{
public:

	Component(GameObject* gameObject);
	virtual ~Component();

	virtual void Update();
	virtual void InitComponent() {};
	static void Init();

	int m_type;
	static int m_nextID;
	int m_id;

	GameObject* _gameObject;

	bool isEnable = TRUE;

protected:

	LPDIRECT3DDEVICE9 _d3ddev;
	Engine* _engine;
};
