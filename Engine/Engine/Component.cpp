#include "pch.h"
#include "framework.h"

int Component::m_nextID;



void Component::Init() {
	m_nextID = 0; 
}

Component::Component(GameObject* gameObject)
{
	m_type = 0;
	m_id = m_nextID++;
	_gameObject = gameObject;
	_engine = _gameObject->GetEngine();
	InitComponent();
}

void Component::Update()
{
}
