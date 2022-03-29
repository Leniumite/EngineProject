#include "pch.h"
#include "framework.h"

Transform::Transform(GameObject* gameObject) : Component(gameObject)
{
	Identity();
}

void Transform::Identity()
{
	D3DXMatrixIdentity(&matrix);
	D3DXMatrixIdentity(&mRot);
	D3DXQuaternionIdentity(&qRot);

	vDir = D3DXVECTOR3(1, 0, 0);
	vUp = D3DXVECTOR3(0, 0, 1);
	vRight = D3DXVECTOR3(0, 1, 0);
	vSca = D3DXVECTOR3(1, 1, 1);
}

void Transform::Rotate(float yaw, float pitch, float roll)
{
	D3DXQUATERNION quat;
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationAxis(&quat, &vDir, roll);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, pitch);
	quatRot *= quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, yaw);
	quatRot *= quat;
	// Ajouter la rotation delta à la rotation actuelle de l’objet
	qRot *= quatRot;

	// Convertir le quaternion en une matrice de rotation (magique)
	D3DXMATRIX matRot;
	D3DXMatrixRotationQuaternion(&matRot, &qRot);
	// Mettre à jour les axes de notre objet (3 vecteurs)
	vRight.x = matRot._11;
	vRight.y = matRot._12;
	vRight.z = matRot._13;
	vUp.x = matRot._21;
	vUp.y = matRot._22;
	vUp.z = matRot._23;
	vDir.x = matRot._31;
	vDir.y = matRot._32;
	vDir.z = matRot._33;

	UpdateMatrix();
}

void Transform::RotateYaw(float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, angle);
	qRot *= quat;
	UpdateRotationFromQuaternion();
}

void Transform::RotatePitch(float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, angle);
	qRot *= quat;
	UpdateRotationFromQuaternion();
}

void Transform::RotateRoll(float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vDir, angle);
	qRot *= quat;
	UpdateRotationFromQuaternion();
}

void Transform::SetRotation(float yaw, float pitch, float roll)
{

	D3DXMatrixIdentity(&mRot);
	D3DXQuaternionIdentity(&qRot);
	UpdateRotationFromQuaternion();
	//Rotate(yaw, pitch, roll);
	RotateYaw(yaw);
	RotatePitch(pitch);
	RotateRoll(roll);
}

void Transform::FromMatrix(D3DXMATRIX* pMat)
{
	matrix = *pMat;
}

void Transform::UpdateMatrix()
{
	D3DXMatrixScaling(&matrix, vSca.x, vSca.y, vSca.z);
	matrix *= mRot;
	matrix._41 = vPos.x;
	matrix._42 = vPos.y;
	matrix._43 = vPos.z;
}

void Transform::UpdateRotationFromQuaternion()
{
	D3DXMatrixRotationQuaternion(&mRot, &qRot);
	UpdateMatrix();
}

void Transform::RotateWorldX(float angle)
{
	D3DXMatrixRotationX(&mRot, angle);
	UpdateMatrix();
}

void Transform::RotateWorldY(float angle)
{
	D3DXMatrixRotationY(&mRot, angle);
	UpdateMatrix();
}

void Transform::RotateWorldZ(float angle)
{
	D3DXMatrixRotationZ(&mRot, angle);
	UpdateMatrix();
}

void Transform::ChangeScale(D3DXVECTOR3 newScale)
{
	vSca = newScale;
	UpdateMatrix();
}

void Transform::ChangePosition(D3DXVECTOR3 newxPos)
{
	vPos = newxPos;
	UpdateMatrix();
}

void Transform::ChangePositionX(float newX)
{
	vPos.x = newX;
	UpdateMatrix();
}

void Transform::ChangePositionY(float newY)
{
	vPos.y = newY;
	UpdateMatrix();
}

void Transform::ChangePositionZ(float newZ)
{
	vPos.z = newZ;
	UpdateMatrix();
}

D3DXVECTOR3 Transform::GetPosition() {
	return vPos;
}

//delta is quite bizarre, so let me explain that it's just component of the vector*speed*deltaTime...
void Transform::Translate(D3DXVECTOR3 delta)
{
	//D3DXMatrixTranslation(&vPos, direction.x, direction.y, direction.z);
	vPos += delta;
	matrix._41 = vPos.x;
	matrix._42 = vPos.y;
	matrix._43 = vPos.z;
}


