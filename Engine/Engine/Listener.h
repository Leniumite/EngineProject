#pragma once

class Component;
class Listener :
    public Component
{
public:
    Listener(GameObject* gameObject);
    virtual ~Listener() override;
    virtual void OnRaise();
};

