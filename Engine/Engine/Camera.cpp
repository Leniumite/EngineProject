#include "pch.h"
#include "framework.h"

CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{

}

void CameraComponent::Init()
void CameraComponent::InitComponent()
{

    _d3ddev = _engine->GetDevice();
    matView;    // the view transform matrix
//Transform test;

    camPos = D3DXVECTOR3(0.0f, 0.0f, 20.0f);
    camLookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    camUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    D3DXMatrixLookAtLH(&matView,
        &camPos,    // the camera position
        &camLookAt,    // the look-at position
        &camUp);    // the up direction
    //_d3ddev->SetTransform(D3DTS_VIEW, &matView);    // set the view transform to matView

    matProjection;     // the projection transform matrix
    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        1920.0f / 1080.0f, // aspect ratio
        1.0f,    // the near view-plane
        100.0f);    // the far view-plane

}

void CameraComponent::Update()
{
    camLookAt = D3DXVECTOR3(sinf(_rotX)*cosf(_rotY), sinf(_rotX) * sinf(_rotY),  cosf(_rotY));
    D3DXMatrixLookAtLH(&matView,
        &camPos,    // the camera position
        &camLookAt,    // the look-at position
        &camUp);

    _d3ddev->SetTransform(D3DTS_VIEW, &matView);

    D3DXMatrixPerspectiveFovLH(&matProjection,
        D3DXToRadian(45),    // the horizontal field of view
        1920.0f / 1080.0f, // aspect ratio
        1.0f,    // the near view-plane
        100.0f);
}

void CameraComponent::UpdateRot(float rotX, float rotY)
{
    _rotX,_rotY += rotX,rotY;
    if (_rotY>90)
    {
        _rotY = 90;
    }
    if (_rotY<-90)
    {
        _rotY = -90;
    }
}
