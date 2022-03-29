#include "framework.h"

#define PI 3.14159265

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

	for (int i = 0; i < 14; i++)
	{
		GameObject* railGameObject = _engine->GetScene()->AddGameObject();
		railGameObject->_transform->ChangePositionX(posLastRail.x + offset);
		railGameObject->_transform->ChangePositionY(-7.0f);
		PolygonMeshComponent* railMeshComponent = railGameObject->AddComponent<PolygonMeshComponent>();
		railMeshComponent->SetMeshModel(L"Ressources\\Rails.x");
		posLastRail = railGameObject->_transform->GetPosition();
		_mainCam->AddWaypoint(posLastRail+D3DXVECTOR3(0.f, 7.f, 0.f));
		endPosLastRail = posLastRail;
		endPosLastRail.x += offset * 0.5f;
		dirRail = D3DXVECTOR3(1.f, 0.f, 0.f);
		rails.push_back(railGameObject);
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

		D3DXVECTOR3 temp = _mainCam->GetCamPos() - rail->_transform->GetPosition();

		//float dist = sqrtf(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z);
		//float dist = _mainCam->GetCamPos().x - rail->_transform->GetPosition().x;

		//If the camera can't see it
		if (D3DXVec3Dot(&_mainCam->dir, &temp) >100.f)
		{

			float rotationX = ((rand() % 31) - 15) ;
			float rotationY = ((rand() % 31) - 15) ;
			//float rotationZ = ((rand() % 5) - 2) ;
			rotX += rotationX;
			rotY += rotationY;
			//rotZ += rotationZ;
			/*if (rotX>70.f)
			{
				rotX = 70.f;
			}
			if (rotX < -70.f)
			{
				rotX = -70.f;
			}
			if (rotY > 70.f)
			{
				rotY = 70.f;
			}
			if (rotY < -70.f)
			{
				rotY = -70.f;
			}*/
			dirRail = D3DXVECTOR3( cosf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY)),
								   sinf(D3DXToRadian(rotY)),
								   sinf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY)));

			D3DXVECTOR3 dirup = D3DXVECTOR3(cosf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY+90)),
											sinf(D3DXToRadian(rotY+90)),
											sinf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY + 90)));

			rail->_transform->ChangePosition(endPosLastRail+ +dirRail * 0.45f * offset);


			rail->_transform->SetRotation(D3DXToRadian(rotY), D3DXToRadian(-rotX), D3DXToRadian(-rotZ));
			posLastRail = endPosLastRail  +dirRail * 0.5f * offset;
			endPosLastRail = posLastRail+dirRail*0.5f*offset;
			_mainCam->AddWaypoint(posLastRail+7*dirup);

			//posLastRail-dirRail*0.5f*offset =beginPosRail=lastendPosRail
		}
	}

	if (_mainCam->GetCamPos().x - rails[indexRail % (sizeof(rails) / sizeof(rails[0]))]->_transform->GetPosition().x < 0.1f)
	{
		indexRail += 1;
	}
}
