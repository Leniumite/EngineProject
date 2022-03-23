#pragma once


class CameraComponent : public Component
{
	D3DXVECTOR3 camPos, camLookAt, camUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;
	D3DXVECTOR3 nextTarget;

private:
	float _rotX,_rotY;


public:

	CameraComponent(GameObject* gameObject);
	virtual ~CameraComponent() {};

	inline D3DXVECTOR3 GetCamPos() { return camPos; }
	inline D3DXVECTOR3 GetCamLookAt() { return camLookAt; }

	virtual void InitComponent() override;
	virtual void Update() override;
	void UpdateRot(float rotx,float rotY);

};
