#include "framework.h"

TargetManager::TargetManager(GameObject* gameobject) : Component(gameobject)
{
	
}

TargetManager::~TargetManager()
{
}

void TargetManager::InitComponent()
{
	for (int i = 0; i < ammountTarget; i++)
	{
		GameObject* go = _engine->GetScene()->AddGameObject();
		CubeMeshComponent* cubeComponent2 = go->AddComponent<CubeMeshComponent>();
		TargetListener* tList2 = go->AddComponent<TargetListener>();
		tList2->tManager = this;
		cubeComponent2->SetMaterialColor(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
		go->_transform->ChangePosition(D3DXVECTOR3(20.f, 0.f, 0.f));
		BoxCollider* boxCollider = go->AddComponent<BoxCollider>();
		boxCollider->collisionListeners.push_back(tList2);

		targets.push_back(go);
	}
}

void TargetManager::Update()
{
	for (GameObject* target : targets)
	{
		D3DXVECTOR3 temp = _engine->GetScene()->_mainCamera->GetCamPos() - target->_transform->GetPosition();
		//float norm = (temp.x * temp.x) + (temp.y * temp.y) + (temp.z * temp.z);

		if (D3DXVec3Dot(&_engine->GetScene()->_mainCamera->dir, &temp) > 50.f)
			Replace(target);
	}
}

void TargetManager::Replace(GameObject* go)
{
	D3DXVECTOR3 forward = _engine->GetScene()->_mainCamera->dir;
	D3DXVECTOR3 forwardNorm;
	D3DXVec3Normalize(&forwardNorm, &forward);
	forwardNorm.x *= 110.0f;
	forwardNorm.y *= 110.0f;
	forwardNorm.z *= 110.0f;
	go->_transform->ChangePosition(_engine->GetScene()->_mainCamera->GetCamPos() + forwardNorm);


}
