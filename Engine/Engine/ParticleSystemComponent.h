#pragma once
#define PARTICLEFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

enum class ParticleEmissionShape
{
    Cone,
    Point,
    Sphere,
    Cube
};


class ParticleSystemComponent :
    public MeshComponent
{

private:

    bool _isLooping = false;
    float _pointSize = 1.0f;
    float _pointSizeMax = 10.0f;
    LPD3DXMESH _particleMesh = NULL;
    LPDIRECT3DTEXTURE9 _particlesTexture = NULL;
    LPDIRECT3DVERTEXBUFFER9 _particleVertexBuffer = NULL;
    int _aliveParticlesCount = 0;
    int _maxParticlesCount = 0;
    float _particlesLifeTime = 10.0f;
    float _particlesmaxAngle = 22.5f;
    ParticleEmissionShape _emissionShape = ParticleEmissionShape::Point;
    Particle* _particlesArray;
    vector<Particle*> _livingParticles;


    void InitDraw();
    void UninitDraw();
    void ModifyVertexBuffer();

public:

    ParticleSystemComponent(GameObject* gameObject);
    virtual ~ParticleSystemComponent();
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
    void SetEmissionShape(ParticleEmissionShape newEmissionShape);
};

