#include "framework.h"

void TargetListener::InitComponent()
{
}

void TargetListener::Update()
{
}

void TargetListener::OnRaise()
{
	tManager->Replace(_gameObject);
}

TargetListener::TargetListener(GameObject* gameObject) : Listener(gameObject)
{
}
