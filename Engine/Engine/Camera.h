#pragma once
#include "framework.h"

class Camera
{
	D3DXVECTOR3 camPos, camLookAt, camUp;
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;



public:
	void Init();
};

