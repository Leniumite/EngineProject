#pragma once

class Component;
class Listener :
    public Component
{
public:
    Listener(GameObject* gameObject);
    virtual void OnRaise();
};

