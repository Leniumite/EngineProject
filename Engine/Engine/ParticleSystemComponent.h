#pragma once
#define PARTICLEFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)

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



    void SetParticlesStartAcceleration(D3DXVECTOR3 newAcceleration);
    void SetParticlesStartVelocity(D3DXVECTOR3 newAcceleration);
    inline void SetParticlesSize(float newSize) { _pointSizeMax = newSize; }
    void SetParticlesMaxAngle(float angle);
    void SetMesh(LPCWSTR meshPath);
    void SetTexture(LPCWSTR texturePath);
    void SetMaxParticlesCount(int newCount);
};
