#include "framework.h"

void QuitButton::InitComponent()
{
}

void QuitButton::Update()
{
}

void QuitButton::OnRaise()
{
	exit(0);
}

QuitButton::QuitButton(GameObject* gameObject) : Listener(gameObject)
{
}

void QuitButton::OnButtonClicked()
{
}
