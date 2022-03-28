#include "framework.h"

void TargetListener::InitComponent()
{
}

void TargetListener::Update()
{
}

void TargetListener::OnRaise()
{
	for (Component* component: _gameObject->GetAllComponents())
	{
		component->isEnable = FALSE;
	}
}

TargetListener::TargetListener(GameObject* gameObject) : Listener(gameObject)
{
}
