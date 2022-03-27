#pragma once
#define PARTICLEFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

class ParticleSystemComponent :
    public MeshComponent
{

private:

    bool _isLooping;
    float _pointSize = 1.0f;
    float _pointSizeMax = 10.0f;
    LPD3DXMESH _particleMesh = NULL;
    LPDIRECT3DTEXTURE9 _particlesTexture = NULL;
    LPDIRECT3DVERTEXBUFFER9 _particleVertexBuffer = NULL;
    int _maxParticlesCount = 0;
    float _particlesLifeTime = 5.0f;
    float _particlesmaxAngle = 22.5f;
    list<Particle*> _particlesList = list<Particle*>();


    void InitDraw();
    void UninitDraw();

public:

    ParticleSystemComponent(GameObject* gameObject);
    virtual void InitComponent() override;
    virtual void Clean() override;
    virtual void Draw() override;
    virtual void Update() override;

    void SetParticlesAcceleration(D3DXVECTOR3 newAcceleration);
    void SetParticlesMaxAngle(float angle);
    void SetMesh(LPCWSTR meshPath);
    void SetTexture(LPCWSTR texturePath);
    void SetMaxParticlesCount(int newCount);
    void SetIsLooping(bool newValue);
};

