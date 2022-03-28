#pragma once

class PlayerBulletCollide :
    public Listener
{
public:
    virtual void InitComponent() override;
    virtual void Update() override;
    virtual void OnRaise() override;
    PlayerBulletCollide(GameObject* gameObject);

    Player* _player;
};

