#pragma once

class Component;
class Player :
    public Component
{
private :
    D3DXVECTOR3 nextTarget;
    float _speed = 2.0f;

public:
    float _shootPower = 3.0f;
    TextComponent* _ptsText = NULL;

    virtual void InitComponent() override;
    Player(GameObject* gameObject);

    virtual void Update() override;

    void Shoot();

    float _shootCooldown = 4.0f;
    float _timeBeforeNextShoot = 0.0f;

    int _points = 0;
};

