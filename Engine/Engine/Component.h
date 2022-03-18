#pragma once

class GameObject;
class Engine;
class Component
{
public:

	Component(GameObject* gameObject);
	virtual void Update();
	static void Init();

	int m_type;
	static int m_nextID;
	int m_id;
	
	GameObject* _gameObject;

protected:
	Engine* _engine;
};
