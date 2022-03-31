#pragma once

class Collider :
    public Component
{
public:
    Collider(GameObject* gameObject);
    virtual ~Collider() override;

    MeshComponent* meshComponent;
    list<Listener*> collisionListeners = list<Listener*>();
};

