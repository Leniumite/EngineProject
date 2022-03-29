#include "framework.h"

void Player::InitComponent()
{
	GameObject* ptsGO = _engine->GetScene()->AddGameObject();
	_ptsText = ptsGO->AddComponent<TextComponent>();
	_ptsText->_color = D3DXCOLOR(255.0f, 0.0f,0.0f, 1);
	_ptsText->SetCorners(0, 1820, 200, 1920);

	GameObject* crosshairGO = _engine->GetScene()->AddGameObject();
	_Crosshair = crosshairGO->AddComponent<Crosshair>();
	crosshairGO->_transform->ChangeScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
}

Player::Player(GameObject* gameObject) : Component(gameObject)
{
}

Player::~Player()
{
}

void Player::Update()
{
	_gameObject->_transform->Translate(D3DXVECTOR3(_speed * _engine->GetTimer()->deltaTime, 0, 0));

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

	D3DXVECTOR3 dirNormalized;
	D3DXVec3Normalize(&dirNormalized, &dir);

	ball->_transform->ChangePosition(cam->GetCamPos() + dirNormalized);

	Rigidbody* rb = ball->AddComponent<Rigidbody>();
	SphereCollider* scol = ball->AddComponent<SphereCollider>();
	PlayerBulletCollide* listener = ball->AddComponent<PlayerBulletCollide>();
	listener->_player = this;
	scol->collisionListeners.push_back(listener);

	rb->AddVelocity(dirNormalized * _shootPower);
	_timeBeforeNextShoot = _shootCooldown;
}
