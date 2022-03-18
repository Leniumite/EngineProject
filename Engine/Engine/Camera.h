#pragma once
#include "framework.h"
#include "Component.h"
class Camera : public Component
{
	D3DXVECTOR3 camPos, camLookAt, camUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;

private:
	Engine* _engine;
	LPDIRECT3DDEVICE9 _d3ddev;

public:
	

	void Init();
	virtual void Update() override;
	void AddRot(float rot);

};


