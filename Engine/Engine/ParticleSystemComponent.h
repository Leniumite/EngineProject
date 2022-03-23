#pragma once

class ParticleSystemComponent :
    public MeshComponent
{

private:

    float _pointSize = 1.0f;
    float _pointSizeMax = 1.0f;

public:

    ParticleSystemComponent(GameObject* gameObject);
    virtual void InitComponent() override;
    virtual void Clean() override;
    virtual void Draw() override;
};

