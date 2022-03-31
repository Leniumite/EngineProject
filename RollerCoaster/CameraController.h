#pragma once

class CameraController :
    public Component
{
private:
    CameraComponent* _camera;
    D3DXVECTOR3 _currentwp;
    float speed = 30.0f;
public:
    vector<D3DXVECTOR3> _waypoints = vector<D3DXVECTOR3>();
    CameraController(GameObject*);
    virtual void Update() override;
    virtual ~CameraController() override;
    void AddWaypoint(D3DXVECTOR3 wp);
};