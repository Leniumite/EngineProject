#include "pch.h"
#include "framework.h"

CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{

}

void CameraComponent::InitComponent()
{
    SetCursor(NULL);
    _engine->GetDevice()->ShowCursor(FALSE);
   
    matView;    // the view transform matrix
//Transform test;
    camPos = _gameObject->_transform->GetPosition();
    camLookAt = camPos +D3DXVECTOR3(0.0f, 0.0f, 20.0f);
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
    //_rotY = -90;
}

void CameraComponent::Update()
{
    _gameObject->_transform->ChangePositionX(camPos.x + 1.1f * _engine->GetTimer()->deltaTime);
    float rayon =19.f;
    
    UpdateRot(_engine->_MM._mouseDeltaX,_engine->_MM._mouseDeltaY);
    camPos = _gameObject->_transform->GetPosition();
    camLookAt =camPos+ D3DXVECTOR3(rayon*cosf(_rotX)*cosf(_rotY),rayon*sinf(_rotY), rayon*sinf(_rotX) * cosf(_rotY));
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

    _d3ddev->SetTransform(D3DTS_PROJECTION, &matProjection);
}

void CameraComponent::UpdateRot(float rotX, float rotY)
{
    _rotX -= rotX;
    _rotY-= rotY;
    if (_rotY>D3DXToRadian( 90))
    {
        _rotY = D3DXToRadian(90);
    }
    if (_rotY< D3DXToRadian(-90))
    {
        _rotY = D3DXToRadian(-90);
    }


    //_rotY += D3DXToRadian(5.f*_engine->GetTimer()->deltaTime);
    //_rotX += D3DXToRadian(10.5f*_engine->GetTimer()->deltaTime);
}
