#include "framework.h"

void QuitButton::InitComponent()
{
}

void QuitButton::Update()
{
}

void QuitButton::OnRaise()
{
	for (GameObject* go : _engine->GetScene()->_gameObjectList)
	{
		_engine->Destroy(go);
	}

	exit(0);
}

QuitButton::QuitButton(GameObject* gameObject) : Listener(gameObject)
{
}

QuitButton::~QuitButton()
{
}

void QuitButton::OnButtonClicked()
{
}
