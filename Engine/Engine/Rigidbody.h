#pragma once
#include "Component.h"
class Rigidbody :
    public Component
{
public:
    MeshComponent* mesh;
   
    void Init();
    virtual void Update() override;
    void SetGravity(bool b);
    void AddVelocity(D3DXVECTOR3 vvect);
    void AddVelocityX(float vx );
    void AddVelocityY(float vy);
    void AddVelocityZ(float vz);
    void AddForce(D3DXVECTOR3 avect);
    void AddForceX(float ax);
    void AddForceY(float ay);
    void AddForceZ(float ax);


private:
    bool IsInit;
    bool gravityEnabled;
    D3DXVECTOR3 pos;
    D3DXVECTOR3 velocity;
    D3DXVECTOR3 acc;
    float g = 9.81f;

    Transform* transform;
    STimer* timer;
};

