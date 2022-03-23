#include "framework.h"

void Player::InitComponent()
{
	GameObject* ptsGO = _engine->GetScene()->AddGameObject();
	_ptsText = ptsGO->AddComponent<TextComponent>();
	_ptsText->_color = D3DXCOLOR(255.0f, 0.0f,0.0f, 1);
	_ptsText->SetCorners(0, 1820, 200, 1920);
}

Player::Player(GameObject* gameObject) : Component(gameObject)
{
}

void Player::Update()
{
	if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000f && _timeBeforeNextShoot <= 0.0f) 
	{ 
		Shoot();
	}
	_ptsText->_txt = L"Points: " + std::to_wstring(_points);
	_timeBeforeNextShoot -= _engine->GetTimer()->GetDeltaTime();
}

void Player::Shoot()
{
	GameObject* ball = _engine->GetScene()->AddGameObject();
	ball->AddComponent<SphereMeshComponent>();
	CameraComponent* cam = _engine->GetScene()->_mainCamera;
	D3DXVECTOR3 dir = cam->GetCamLookAt() - cam->GetCamPos();

	ball->_transform->ChangePosition(cam->GetCamPos() + dir);
	Rigidbody* rb = ball->AddComponent<Rigidbody>();

	rb->AddVelocity(dir * _shootPower);
	_timeBeforeNextShoot = _shootCooldown;
}
