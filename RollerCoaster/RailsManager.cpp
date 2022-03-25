#include "framework.h"

#define PI 3.14159265

RailsManager::RailsManager(GameObject* gameObject) : Component(gameObject)
{
}

void RailsManager::InitComponent()
{
	_mainCam = _engine->GetScene()->_mainCamera;

	CreatePath();

	for (int i = 0; i < 5; i++)
	{
		GameObject* railGameObject = _engine->GetScene()->AddGameObject();
		PolygonMeshComponent* railMeshComponent = railGameObject->AddComponent<PolygonMeshComponent>();
		railMeshComponent->SetMeshModel(L"Ressources\\Rails.x");
		rails[i] = railGameObject;
	}

	for (D3DXVECTOR3 pos : waypoints)
	{
		int t = rand() % 5;

		rails[t]->_transform->ChangePositionY(-7.0f);
		rails[t]->_transform->ChangePositionX(pos.x);
		rails[t]->_transform->ChangePositionZ(pos.z);
	}
}

void RailsManager::Update()
{
	ManageRails();
}

void RailsManager::CreatePath()
{
	D3DXVECTOR3 nextRail = D3DXVECTOR3(0, 0, 0);

	for (int i = 0; i <= pathWaypoints; i++)
	{
		waypoints.push_back(nextRail);

		//random range X
		float rx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / cos(30*PI/180)));
		//random range Z
		float rz = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / sin(30*PI/180)));

		//define next position
		nextRail = D3DXVECTOR3(nextRail.x + (2 * rx), 0, nextRail.z + (railWidth * rz));
	}
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
	}
}