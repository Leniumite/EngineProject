#include "framework.h"

CameraController::CameraController(GameObject* go) : Component(go)
{
    _camera = go->GetComponent<CameraComponent>();
    _currentwp = D3DXVECTOR3(20.f, .0f, .0f);
    _camera->dir = _currentwp;
    _waypoints.reserve(25);
}



void CameraController::Update()
{
    D3DXVECTOR3 temp = _currentwp - _camera->GetCamPos();

    _camera->UpdateRot(_engine->_MM._mouseDeltaX, _engine->_MM._mouseDeltaY);

    D3DXVec3Normalize(&_camera->dir, &temp);
    _gameObject->_transform->ChangePosition(_camera->GetCamPos() + (speed - (_camera->dir.y - 0.5f) * 40.f)* _camera->dir* _engine->GetTimer()->deltaTime);
    if (sqrtf(temp.x * temp.x + temp.y * temp.y + temp.z * temp.z) < 5.0f)
    {
        _waypoints.erase(_waypoints.begin());
        _currentwp = _waypoints[0];

    }
}

CameraController::~CameraController()
{
    if (_camera != nullptr)
    {
        _camera = NULL;
    }
}

void CameraController::AddWaypoint(D3DXVECTOR3 wp)
{
    _waypoints.push_back(wp);
}