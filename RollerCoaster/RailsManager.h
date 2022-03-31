#pragma once

class RailsManager : public Component
{
private :
	Mesh* _railsMesh;
	list<GameObject*> rails = list<GameObject*>();
	float cameraTreshold = 110.0f;
	float offset = 25.0f;
	CameraComponent* _mainCam;
	D3DXVECTOR3 posLastRail = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 beginPosLastRail = D3DXVECTOR3(0.0f, 0.0f, -offset*0.5f);
	D3DXVECTOR3 endPosLastRail = D3DXVECTOR3(0.0f, 0.0f, offset*0.5f);
	D3DXVECTOR3 dirRail = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 OldDirRail = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;
public :
	RailsManager(GameObject* gameObject);
	~RailsManager() override;

	virtual void InitComponent() override;
	virtual void Update() override;

	void ManageRails();
	HRESULT LoadRailMesh(LPCWSTR fileName);

};

