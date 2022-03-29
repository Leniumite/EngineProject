#include "pch.h"
#include "framework.h"

CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{

}

void CameraComponent::InitComponent()
{
#ifndef _DEBUG
    SetCursor(NULL);
    _engine->GetDevice()->ShowCursor(FALSE);
#endif
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
    currentwp = D3DXVECTOR3(20.f, .0f, .0f);
    dir = currentwp;
    
}

void CameraComponent::Update()
{
    
    //_gameObject->_transform->ChangePositionX(camPos.x + 5.0f * _engine->GetTimer()->deltaTime);
    UpdatePos();
    float rayon = 19.f;

    UpdateRot(_engine->_MM._mouseDeltaX, _engine->_MM._mouseDeltaY);
    camPos = _gameObject->_transform->GetPosition();
    camLookAt = camPos + D3DXVECTOR3(rayon * cosf(_rotX) * cosf(_rotY), rayon * sinf(_rotY), rayon * sinf(_rotX) * cosf(_rotY));
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

void CameraComponent::UpdatePos()
{
    
    D3DXVECTOR3 temp = currentwp - camPos;

    D3DXVec3Normalize(&dir ,&temp);
    _gameObject->_transform->ChangePosition(camPos + 5.0f *dir*10.f* _engine->GetTimer()->deltaTime);
    if (sqrtf( temp.x* temp.x+ temp.y * temp.y + temp.z * temp.z)<5.0f  )
    { 
        _waypoints.erase(_waypoints.begin());
        currentwp = _waypoints[0];
        
    }
}

void CameraComponent::UpdateRot(float rotX, float rotY)
{
    _rotX -= rotX;
    _rotY -= rotY;
    if (_rotY > D3DXToRadian(85))
    {
        _rotY = D3DXToRadian(85);
    }
    if (_rotY < D3DXToRadian(-85))
    {
        _rotY = D3DXToRadian(-85);
    }

    //_rotY += D3DXToRadian(5.f*_engine->GetTimer()->deltaTime);
    //_rotX += D3DXToRadian(10.5f*_engine->GetTimer()->deltaTime);
}

void CameraComponent::AddWaypoint(D3DXVECTOR3 wp)
{
    _waypoints.push_back(wp);
}
