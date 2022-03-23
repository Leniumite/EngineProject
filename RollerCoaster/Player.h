#pragma once

class Component;
class Player :
    public Component
{
public:
    virtual void InitComponent() override;
    Player(GameObject* gameObject);

    virtual void Update() override;
};

