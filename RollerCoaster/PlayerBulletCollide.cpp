#include "framework.h"

void PlayerBulletCollide::InitComponent()
{
}

void PlayerBulletCollide::Update()
{
}

void PlayerBulletCollide::OnRaise()
{
	if (_player != NULL) {
		_player->_points += 10;
		for (Component* comp: _gameObject->GetAllComponents())
		{
			comp->isEnable = FALSE;
		}
	}
}

PlayerBulletCollide::PlayerBulletCollide(GameObject* gameObject) : Listener(gameObject)
{
}