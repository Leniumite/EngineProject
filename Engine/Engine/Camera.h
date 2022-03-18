#pragma once


class CameraComponent : public Component
{
	D3DXVECTOR3 camPos, camLookAt, camUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;

private:
	Engine* _engine;
	LPDIRECT3DDEVICE9 _d3ddev;
	float _rotX,_rotY;


public:

	CameraComponent(GameObject* gameObject);
	virtual ~CameraComponent() {};

	virtual void InitComponent() override;
	virtual void Update() override;
	void UpdateRot(float rotx,float rotY);

};
