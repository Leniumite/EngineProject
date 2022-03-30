#pragma once
#define PARTICLEFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

enum class ParticleEmissionShape
{
    Point,
    Cone
};


class ParticleSystemComponent :
    public MeshComponent
{

private:

    float _pointSize;
    float _pointSizeMax;
    LPDIRECT3DTEXTURE9 _particlesTexture;
    LPDIRECT3DVERTEXBUFFER9 _particleVertexBuffer;
    int _aliveParticlesCount;
    int _maxParticlesCount;
    float _particlesmaxAngle;
    float _particlesLifeTime;
    int _minParticleBurstAmount;
    int _maxParticleBurstAmount;
    bool _randomColorAtStart;
    float _minParticleSpeedMultiplier;
    float _maxParticleSpeedMultiplier;
    ParticleEmissionShape _particleEmissionShape;
    D3DXCOLOR _particleStartColor;

    D3DXVECTOR3 _startAcceleration;
    D3DXVECTOR3 _startVelocity;

    Particle* _particlesArray;

    void InitDraw();
    void UninitDraw();
    void ModifyVertexBuffer();
    int CreateParticleBurst(int maxAmount);

public:

    ParticleSystemComponent(GameObject* gameObject);
    virtual ~ParticleSystemComponent();
    virtual void InitComponent() override;
    virtual void Clean() override;
    virtual void Draw() override;
    virtual void Update() override;

    inline void SetParticlesMinSpeedMultiplier(float newMinSpeed) { _minParticleSpeedMultiplier = newMinSpeed; }
    inline void SetParticlesMaxSpeedMultiplier(float newMaxSpeed) { _maxParticleSpeedMultiplier = newMaxSpeed; }
    inline void SetParticlesStartColor(D3DXCOLOR newColor) { _particleStartColor = newColor; }
    void SetRandomColorAtStart(bool newValue) { _randomColorAtStart = newValue; }
    inline void SetParticlesEmissionShape(ParticleEmissionShape newEmissionShape) { _particleEmissionShape = newEmissionShape; }
    void SetParticlesStartAcceleration(D3DXVECTOR3 newAcceleration);
    void SetParticlesStartVelocity(D3DXVECTOR3 newAcceleration);
    inline void SetParticlesSize(float newSize) { _pointSizeMax = newSize; }
    void SetParticlesMaxAngle(float angle);
    void SetMesh(LPCWSTR meshPath);
    void SetTexture(LPCWSTR texturePath);
    void SetMaxParticlesCount(int newCount);
};
