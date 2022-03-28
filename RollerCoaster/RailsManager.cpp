#include "framework.h"

//#define PI 3.14159265

RailsManager::RailsManager(GameObject* gameObject) : Component(gameObject)
{
}

void RailsManager::InitComponent()
{
	_mainCam = _engine->GetScene()->_mainCamera;

	CreatePath();
}

void RailsManager::Update()
{
	ManageRails();
}

void RailsManager::CreatePath()
{
	LPD3DXMESH* mesh = LoadMesh(L"Ressources\\Rails.x");

	for (int i = 1; i < 4; i++)
	{
		railGO = _engine->GetScene()->AddGameObject();
		railGO->_transform->ChangePositionY(-7.0f);
		PolygonMeshComponent* polyMesh = railGO->AddComponent<PolygonMeshComponent>();
		polyMesh->SetMeshModel(mesh, pD3DXMtrlBuffer, g_pMeshMaterials, g_pMeshTextures, g_dwNumMaterials);

		rails[i] = railGO;
		postLastRail = railGO->_transform->GetPosition();
	}

	D3DXVECTOR3 nextRailPos = D3DXVECTOR3(0, -7.0f, 0);

	for (int i = 0; i <= pathWaypoints; i++)
	{
		waypoints.push_back(nextRailPos);

		//define next position
		//nextRailPos = D3DXVECTOR3(nextRailPos.x + railWidth, -7.0f, (posZ * 10.0f));
	}
}

void RailsManager::ManageRails()
{
	for (GameObject* rail : rails)
	{
		float dist = _mainCam->GetCamPos().x - rail->_transform->GetPosition().x;
		
		//random range Z
		int posZ = rand() % 3;

		//If the camera can't see it
		if (dist > cameraTreshold)
		{
			rail->_transform->ChangePositionX(postLastRail.x + offset);

			switch (posZ)
			{
				case 0:	
					rail->_transform->ChangePositionZ(postLastRail.z - 12.5f);
					break;
				case 1:
					rail->_transform->ChangePositionZ(postLastRail.z);
					break;
				case 2:
					rail->_transform->ChangePositionZ(postLastRail.z + 12.5f);
					break;
				default:
					rail->_transform->ChangePositionZ(postLastRail.z); break;
			}
			
			postLastRail = rail->_transform->GetPosition();
		}
	}

	//If distance between rail and cam is < 0.1f
	if (_mainCam->GetCamPos().x - rails[indexRail % (sizeof(rails) / sizeof(rails[0]))]->_transform->GetPosition().x < 0.1f)
	{
		indexRail += 1;
	}
}

LPD3DXMESH* RailsManager::LoadMesh(LPCWSTR fileName)
{
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, _d3ddev, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &mesh);
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if (g_pMeshMaterials == NULL)
		return NULL;

	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	if (g_pMeshTextures == NULL)
		return NULL;

	return &mesh;
}