#include "framework.h"

void TargetListener::InitComponent()
{
}

void TargetListener::Update()
{
	float rotateValue = 4.0f * _engine->GetTimer()->deltaTime;
	_gameObject->_transform->RotateYaw(rotateValue);
	_gameObject->_transform->RotatePitch(rotateValue);
	_gameObject->_transform->RotateRoll(rotateValue);
}

void TargetListener::OnRaise()
{
	MeshComponent* mesh = _gameObject->GetComponent<MeshComponent>();
	D3DXCOLOR explosionColor;
	
	if (mesh != NULL)
	{
		explosionColor = mesh->GetMaterial().Diffuse;
	}
	
	mesh = nullptr;

	GameObject* particleGO = _engine->GetScene()->AddGameObject();
	particleGO->_transform->ChangePosition(_gameObject->_transform->GetPosition());
	ParticleSystemComponent* particleSystem = particleGO->AddComponent<ParticleSystemComponent>();
	particleSystem->SetParticlesEmissionShape(ParticleEmissionShape::Point);
	particleSystem->SetParticlesStartColor(explosionColor);
	particleSystem->SetParticlesStartAcceleration(D3DXVECTOR3(0.0f, -9.81f, 0.0f));
	particleSystem->SetParticlesMinSpeedMultiplier(5.0f);
	particleSystem->SetParticlesMaxSpeedMultiplier(10.0f);
	particleSystem->SetMaxParticlesCount(1000);
	particleSystem->SetParticlesMaxBurstAmount(10000);
	particleSystem->SetParticlesLifeTime(2.0f);
	//_engine->Destroy(particleGO, 2.0f);

	tManager->Replace(_gameObject);
}

TargetListener::TargetListener(GameObject* gameObject) : Listener(gameObject)
{
}
