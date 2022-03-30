#include "framework.h"

void QuitButton::InitComponent()
{
}

void QuitButton::Update()
{
}

void QuitButton::OnRaise()
{
	GetApp()->SetRunningState(false);
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
