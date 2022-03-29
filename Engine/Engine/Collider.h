#pragma once

class Collider :
    public Component
{
public:
    Collider(GameObject* gameObject);
    ~Collider();

    MeshComponent* meshComponent;
    list<Listener*> collisionListeners = list<Listener*>();
};

