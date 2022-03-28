#include "framework.h"

RailsManager::RailsManager(GameObject* gameObject) : Component(gameObject)
{
}

//RailsManager::~RailsManager()
//{
//	for (GameObject* rail : rails)
//	{
//		delete rail;
//	}
//}

void RailsManager::InitComponent()
{
	_mainCam = _engine->GetScene()->_mainCamera;

	for (int i = 0; i < 4; i++)
	{
		GameObject* railGameObject = _engine->GetScene()->AddGameObject();
		railGameObject->_transform->ChangePositionX(postLastRail.x + offset);
		railGameObject->_transform->ChangePositionY(-7.0f);
		PolygonMeshComponent* railMeshComponent = railGameObject->AddComponent<PolygonMeshComponent>();
		railMeshComponent->SetMeshModel(L"Ressources\\Rails.x");
		postLastRail = railGameObject->_transform->GetPosition();

		rails.push_back(railGameObject);
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
}
