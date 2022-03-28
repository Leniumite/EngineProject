#pragma once

class RailsManager : public Component
{
private :
	GameObject* railGO;
	LPD3DXMESH mesh;

	LPD3DXBUFFER pD3DXMtrlBuffer;
	D3DMATERIAL9* g_pMeshMaterials = NULL;
	LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL;
	DWORD g_dwNumMaterials = 0L;

	GameObject* rails[5];
	float cameraTreshold = 25.0f;
	float offset = 25.0f;
	CameraComponent* _mainCam;
	unsigned int indexRail = 0;
	D3DXVECTOR3 postLastRail = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	list<D3DXVECTOR3> waypoints;

	int pathWaypoints = 10;
	float railWidth = 25.0f;

public :
	RailsManager(GameObject* gameObject);

	virtual void InitComponent() override;
	virtual void Update() override;

	void CreatePath();
	void ManageRails();

	LPD3DXMESH* LoadMesh(LPCWSTR modelPath);

};

