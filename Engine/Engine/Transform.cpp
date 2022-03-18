#include "pch.h"
#include "Engine.h"

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
}

void Transform::RotateYaw(float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vUp, angle);
	qRot *= quat;
}

void Transform::RotatePitch(float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vRight, angle);
	qRot *= quat;
}

void Transform::RotateRoll(float angle)
{
	D3DXQUATERNION quat;
	D3DXQuaternionRotationAxis(&quat, &vDir, angle);
	qRot *= quat;
}

void Transform::FromMatrix(D3DXMATRIX* pMat)
{
	matrix = *pMat;
}

void Transform::UpdateRotationFromQuaternion()
{
	D3DXMatrixRotationQuaternion(&matrix, &qRot);
}

void Transform::RotateWorldX(float angle)
{
	D3DXMatrixRotationX(&mRot, angle);
}

void Transform::RotateWorldY(float angle)
{
	D3DXMatrixRotationY(&mRot, angle);
}

void Transform::RotateWorldZ(float angle)
{
	D3DXMatrixRotationZ(&mRot, angle);
}

void Transform::ChangeScale(D3DXVECTOR3 newScale)
{
	vSca = newScale;
}

void Transform::ChangePosition(D3DXVECTOR3 newxPos)
{
	vPos = newxPos;
}

void Transform::ChangePositionX(float newX)
{
	vPos.x = newX;
}

void Transform::ChangePositionY(float newY)
{
	vPos.y = newY;
}

void Transform::ChangePositionZ(float newZ)
{
	vPos.z = newZ;
}

void Transform::Translate(D3DXVECTOR3 targetPos)
{
	//D3DXMatrixTranslation(&vPos, targetPos.x, targetPos.y, targetPos.z);
}


