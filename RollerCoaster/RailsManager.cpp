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

	for (int i = 0; i < 10; i++)
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
			
			float rotationX = ((rand() % 19) - 9) ;
			float rotationY = ((rand() % 19) - 9) ;
			rotX += rotationX;
			rotY += rotationY;
			if (rotX>70.f)
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
			}
			dirRail = D3DXVECTOR3( cosf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY)),
								   sinf(D3DXToRadian(rotY)),
								   sinf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY)));

			
			
			rail->_transform->ChangePosition(endPosLastRail+ +dirRail * 0.45f * offset);

			
			rail->_transform->SetRotation(D3DXToRadian(rotY), D3DXToRadian(-rotX),0.f);
			posLastRail = endPosLastRail  +dirRail * 0.5f * offset;
			endPosLastRail = posLastRail+dirRail*0.5f*offset;			
			_mainCam->AddWaypoint(posLastRail+D3DXVECTOR3(0.f,7.f,0.f));

			//posLastRail-dirRail*0.5f*offset =beginPosRail=lastendPosRail
		}
	}
}
