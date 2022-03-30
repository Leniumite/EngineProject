#pragma once

class RailsManager : public Component
{
private :
	Mesh* _railsMesh;
	list<GameObject*> rails;
	float cameraTreshold = 110.0f;
	float offset = 25.0f;
	CameraComponent* _mainCam;
	D3DXVECTOR3 posLastRail = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 beginPosLastRail = D3DXVECTOR3(0.0f, 0.0f, -offset*0.5f);
	D3DXVECTOR3 endPosLastRail = D3DXVECTOR3(0.0f, 0.0f, offset*0.5f);
	D3DXVECTOR3 dirRail;
	D3DXVECTOR3 OldDirRail;
	float rotX;
	float rotY;
	float rotZ;
public :
	RailsManager(GameObject* gameObject);
	//virtual ~RailsManager() override;

	virtual void InitComponent() override;
	virtual void Update() override;

	void ManageRails();
	HRESULT LoadRailMesh(LPCWSTR fileName);

};

