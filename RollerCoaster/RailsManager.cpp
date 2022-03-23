#include "framework.h"

RailsManager::RailsManager(GameObject* gameObject) : Component(gameObject)
{
}

void RailsManager::InitComponent()
{
	_mainCam = _engine->GetScene()->_mainCamera;

	for (int i = 0; i < 5; i++)
	{
		GameObject* railGameObject = _engine->GetScene()->AddGameObject();
		railGameObject->_transform->ChangePositionX(postLastRail.x + offset);
		railGameObject->_transform->ChangePositionY(-7.0f);
		PolygonMeshComponent* railMeshComponent = railGameObject->AddComponent<PolygonMeshComponent>();
		railMeshComponent->SetMeshModel(L"Ressources\\Rails.x");
		postLastRail = railGameObject->_transform->GetPosition();

		rails[i] = railGameObject;
	}
}

void RailsManager::Update()
{
	ManageRails();
}

void RailsManager::ManageRails()
{
	for (GameObject* rail : rails)
	{
		float dist = _mainCam->GetCamPos().x - rail->_transform->GetPosition().x;
		
		//If the camera can't see it
		if (dist > cameraTreshold)
		{
			rail->_transform->ChangePositionX(postLastRail.x + offset);
			postLastRail = rail->_transform->GetPosition();
		}
	}

	if (_mainCam->GetCamPos().x - rails[indexRail % (sizeof(rails) / sizeof(rails[0]))]->_transform->GetPosition().x < 0.1f)
	{
		indexRail += 1;
		//_mainCam->DirToNextRailX(rails[indexRail % (sizeof(rails)/sizeof(rails[0]))] );
	}
}
