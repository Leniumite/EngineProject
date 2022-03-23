#pragma once

class Component;
class Player :
    public Component
{
public:

    TextComponent* _ptsText = NULL;

    virtual void InitComponent() override;
    Player(GameObject* gameObject);

    virtual void Update() override;

    void Shoot();

    float _shootCooldown = 4.0f;
    float _timeBeforeNextShoot = 0.0f;

    int _points = 0;
};

