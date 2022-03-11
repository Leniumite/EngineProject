#pragma once
#include "Component.h"

class Transform : public Component
{
	public:
		D3DXMATRIX matrix;

	protected:
		D3DXVECTOR3 vSca;

		D3DXVECTOR3 vDir;
		D3DXVECTOR3 vRight;
		D3DXVECTOR3 vUp;


		D3DXQUATERNION qRot;
		D3DXMATRIX mRot;

		D3DVECTOR vPos;

public:
	void TRANSFORM();
	void Identity();
	void Rotate(float yaw, float pitch, float roll);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateRoll(float angle);
	void FromMatrix(D3DXMATRIX* pMat);
	/*
	void UpdateMatrix();
	void UpdateRotationFromVectors();
	void UpdateRotationFromQuaternion();
	void UpdateRotationFromMatrix();
	*/

	//void RotateWorld(D3DXMATRIX* pMatrix);
	void RotateWorldX(float angle);
	void RotateWorldY(float angle);
	void RotateWorldZ(float angle);
};
