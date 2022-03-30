#pragma once

class CameraController :
    public Component
{
private:
    CameraComponent* _camera;
    D3DXVECTOR3 _currentwp;
public:
    vector<D3DXVECTOR3> _waypoints;
    CameraController(GameObject*);
    virtual void Update() override;
    void AddWaypoint(D3DXVECTOR3 wp);
};

