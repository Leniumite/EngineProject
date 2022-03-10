#include "pch.h"
#include "Transform.h"
#include "framework.h"


struct TRANSFORM {
	D3DVECTOR vSca;

	D3DVECTOR vDir;
	D3DVECTOR vRight;
	D3DVECTOR vUp;
	D3DXQUATERNION qRot;
	D3DMATRIX mRot;
	D3DVECTOR vPos;

	D3DMATRIX matrix;
};