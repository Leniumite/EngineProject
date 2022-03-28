#include "pch.h"
#include "framework.h"

Listener::Listener(GameObject* gameObject) : Component(gameObject)
{
}

Listener::~Listener()
{
}

void Listener::OnRaise()
{
}
