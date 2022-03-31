#include "framework.h"

RailsManager::RailsManager(GameObject* gameObject) : Component(gameObject)
{
	_railsMesh = new Mesh();
	_mainCam = _engine->GetScene()->_mainCamera;
}

RailsManager::~RailsManager()
{
	delete _railsMesh;
	_railsMesh = NULL;
}


void RailsManager::InitComponent()
{
	LoadRailMesh(L"Ressources\\Rails.x");
	

	for (int i = 0; i < 14; i++)
	{
		GameObject* railGameObject = _engine->GetScene()->AddGameObject();
		railGameObject->_transform->ChangePositionX(posLastRail.x + offset);
		railGameObject->_transform->ChangePositionY(-7.0f);
		PolygonMeshComponent* railMeshComponent = railGameObject->AddComponent<PolygonMeshComponent>();
		railMeshComponent->SetMesh(_railsMesh);
		posLastRail = railGameObject->_transform->GetPosition();
		_mainCam->_gameObject->GetComponent<CameraController>()->AddWaypoint(posLastRail + D3DXVECTOR3(0.f, 7.f, 0.f));
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
		

		//If the camera can't see it
		if (D3DXVec3Dot(&_mainCam->dir, &temp) >100.f)
		{			
			
			float rotationX = ((rand() % 31) - 15) ;
			float rotationY = ((rand() % 31) - 15) ;

			rotX += rotationX;
			rotY += rotationY;

			dirRail = D3DXVECTOR3( cosf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY)),
								   sinf(D3DXToRadian(rotY)),
								   sinf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY)));

			D3DXVECTOR3 dirup = D3DXVECTOR3(cosf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY+90)),
											sinf(D3DXToRadian(rotY+90)),
											sinf(D3DXToRadian(rotX)) * cosf(D3DXToRadian(rotY + 90)));
			
			rail->_transform->ChangePosition(endPosLastRail+dirRail * 0.45f * offset);

			
			rail->_transform->SetRotation(D3DXToRadian(rotY), D3DXToRadian(-rotX), D3DXToRadian(-rotZ));
			posLastRail = endPosLastRail  +dirRail * 0.5f * offset;
			endPosLastRail = posLastRail+dirRail*0.5f*offset;			
			_mainCam->_gameObject->GetComponent<CameraController>()->AddWaypoint(posLastRail+7*dirup);
		}
	}
}

HRESULT RailsManager::LoadRailMesh(LPCWSTR fileName)
{
	D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, _d3ddev, NULL, &_railsMesh->pD3DXMtrlBuffer, NULL, &_railsMesh->g_dwNumMaterials, &_railsMesh->_mesh);
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)_railsMesh->pD3DXMtrlBuffer->GetBufferPointer();
	_railsMesh->g_pMeshMaterials = new D3DMATERIAL9[_railsMesh->g_dwNumMaterials];
	if (_railsMesh->g_pMeshMaterials == NULL)
		return E_OUTOFMEMORY;
	_railsMesh->g_pMeshTextures = new LPDIRECT3DTEXTURE9[_railsMesh->g_dwNumMaterials];
	if (_railsMesh->g_pMeshTextures == NULL)
		return E_OUTOFMEMORY;

	for (DWORD i = 0; i < _railsMesh->g_dwNumMaterials; i++)
	{
		// Copy the material
		_railsMesh->g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		_railsMesh->g_pMeshMaterials[i].Ambient = _railsMesh->g_pMeshMaterials[i].Diffuse;

		_railsMesh->g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			//UTILISER ::GetCommandLine() pour obtenir le path de l'éxecutable
			string path = "Ressources\\";
			path += d3dxMaterials[i].pTextureFilename;

			// Create the texture
			if (FAILED(D3DXCreateTextureFromFileA(_d3ddev, path.c_str(), &_railsMesh->g_pMeshTextures[i])))
			{
				MessageBox(NULL, L"Could not find texture map", L"Meshes.exe", MB_OK);
			}
		}
	}


	DWORD* adj = new DWORD[_railsMesh->_mesh->GetNumFaces() * 3];
	_railsMesh->_mesh->GenerateAdjacency(0.005F, adj);
	_railsMesh->_mesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, adj, NULL, NULL, NULL);

	// Done with the material buffer
	_railsMesh->pD3DXMtrlBuffer->Release();

	return S_OK;
}
