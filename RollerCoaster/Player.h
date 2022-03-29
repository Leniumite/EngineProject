#pragma once

class Component;
class Player :
    public Component
{
private:
    Crosshair* _Crosshair;
    list<GameObject*> balls;
    //Maybe later make a reload system
    int nbBallMax = 10;

public:
    float _shootPower = 300.0f;
    TextComponent* _ptsText = NULL;

    virtual void InitComponent() override;
    Player(GameObject* gameObject);
    virtual ~Player() override;

    virtual void Update() override;

    void Shoot();

    float _shootCooldown = 0.5f;
    float _timeBeforeNextShoot = 0.0f;

    int _points = 0;
};

