#pragma once


class CameraComponent : public Component
{
	D3DXVECTOR3 camPos, camLookAt, camUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;

private:
	float _rotX,_rotY;
	D3DXVECTOR3 currentwp;


public:
	vector<D3DXVECTOR3> _waypoints;
	bool isMenuOpen = FALSE;
	D3DXVECTOR3 dir;

	CameraComponent(GameObject* gameObject);
	virtual ~CameraComponent() {};

	inline D3DXVECTOR3 GetCamPos() { return camPos; }
	inline D3DXVECTOR3 GetCamLookAt() { return camLookAt; }

	virtual void InitComponent() override;
	virtual void Update() override;
	void UpdatePos();
	void UpdateRot(float rotx,float rotY);
	void AddWaypoint(D3DXVECTOR3 wp);
};
