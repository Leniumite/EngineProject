#pragma once

class Engine;
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

		D3DXVECTOR3 vPos;

public:
	Transform(GameObject* gameObject);
	void Identity();
	void Rotate(float yaw, float pitch, float roll);
	void RotateYaw(float angle);
	void RotatePitch(float angle);
	void RotateRoll(float angle);
	void FromMatrix(D3DXMATRIX* pMat);
	/*
	void UpdateMatrix();
	void UpdateRotationFromVectors();
	*/
	void UpdateRotationFromQuaternion();
	//void UpdateRotationFromMatrix();

	//void RotateWorld(D3DXMATRIX* pMatrix);
	void RotateWorldX(float angle);
	void RotateWorldY(float angle);
	void RotateWorldZ(float angle);
	void ChangeScale(D3DXVECTOR3 newScale);
	void ChangePosition(D3DXVECTOR3 newxPos);
	void ChangePositionX(float newX);
	void ChangePositionY(float newY);
	void ChangePositionZ(float newZ);
	void Translate(D3DXVECTOR3 targetPos);
};
