#include "framework.h"

void PlayerBulletCollide::InitComponent()
{
}

void PlayerBulletCollide::Update()
{
	D3DXVECTOR3 dist = _engine->GetScene()->_mainCamera->GetCamPos() - _gameObject->_transform->GetPosition();

	float norm = (dist.x * dist.x) + (dist.y * dist.y) + (dist.z * dist.z);

	if (norm > 10000.0f)
		_engine->Destroy(_gameObject);
}

void PlayerBulletCollide::OnRaise()
{
	if (_player != NULL) {
		_player->_points += 10;
		for (Component* comp: _gameObject->GetAllComponents())
		{
			comp->isEnable = FALSE;
		}
		_engine->Destroy(_gameObject);
	}
}

PlayerBulletCollide::PlayerBulletCollide(GameObject* gameObject) : Listener(gameObject)
{
}