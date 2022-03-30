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
		go->_transform->ChangeScale(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		CubeMeshComponent* cubeComponent = go->AddComponent<CubeMeshComponent>();
		TargetListener* tList2 = go->AddComponent<TargetListener>();
		tList2->tManager = this;
		cubeComponent->SetMaterialColor(GetRandomColor());
		go->_transform->ChangePosition(D3DXVECTOR3(250.f, 2.f*i-8.f,5.f*i-20.f ));
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
	forwardNorm.x *= 110.0f ;
	forwardNorm.y *= 110.0f;
	forwardNorm.z *= 110.0f;

	MeshComponent* mesh = go->GetComponent<MeshComponent>();
	mesh->SetMaterialColor(GetRandomColor());

	D3DXVECTOR3 randVec = D3DXVECTOR3((rand() % 21) - 10.f, (rand() % 21) - 10.f, (rand() % 21) - 10.f);
	go->_transform->ChangePosition(_engine->GetScene()->_mainCamera->GetCamPos() + forwardNorm +randVec);

}


D3DXCOLOR TargetManager::GetRandomColor()
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<> distrr(0.0f, 1.0f);
	std::uniform_real_distribution<> distrg(0.0f, 1.0f);
	std::uniform_real_distribution<> distrb(0.0f, 1.0f);
	return D3DXCOLOR(distrr(gen), distrg(gen), distrb(gen), 1.0f);
}