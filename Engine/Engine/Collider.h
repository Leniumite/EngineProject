#pragma once

class Collider :
    public Component
{
public:
    Collider(GameObject* gameObject);

    MeshComponent* meshComponent;
};

