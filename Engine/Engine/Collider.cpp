#include "pch.h"
#include "framework.h"

Collider::Collider(GameObject* gameObject) : Component(gameObject)
{
	_engine->_CM.AddCollider(this);
}
