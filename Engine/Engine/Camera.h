#pragma once
#include "framework.h"
#include "Component.h"
#include <math.h>
class Camera : public Component
{
	D3DXVECTOR3 camPos, camLookAt, camUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;

private:
	Engine* _engine;
	LPDIRECT3DDEVICE9 _d3ddev;
	float _rotX,_rotY;


public:
	

	void Init();
	virtual void Update() override;
	void UpdateRot(float rotx,float rotY);

};


