#include "framework.h"

void Player::InitComponent()
{
}

Player::Player(GameObject* gameObject) : Component(gameObject)
{
}

void Player::Update()
{
	if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000f && timeBeforeNextShoot <= 0.0f) 
	{ 
		Shoot();
	}
	timeBeforeNextShoot -= _engine->GetTimer()->GetDeltaTime();
}

void Player::Shoot()
{
	GameObject* ball = _engine->GetScene()->AddGameObject();
	ball->AddComponent<SphereMeshComponent>();
	CameraComponent* cam = _engine->GetScene()->_mainCamera;
	D3DXVECTOR3 dir = cam->GetCamLookAt() - cam->GetCamPos();

	ball->_transform->ChangePosition(cam->GetCamPos() + dir);

	timeBeforeNextShoot = shootCooldown;
}
