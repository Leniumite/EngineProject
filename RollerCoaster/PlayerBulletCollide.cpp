#include "framework.h"

void PlayerBulletCollide::InitComponent()
{
}

void PlayerBulletCollide::Update()
{
	D3DXVECTOR3 temp = _engine->GetScene()->_mainCamera->GetCamPos() - _gameObject->_transform->GetPosition();
	//float norm = (temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z);
	
	if (sqrtf(temp.x* temp.x + temp.y * temp.y + temp.z * temp.z) > 100.f)
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