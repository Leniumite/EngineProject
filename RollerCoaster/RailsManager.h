#pragma once

class RailsManager : public Component
{
private :
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

};

