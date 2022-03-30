#include "pch.h"
#include "framework.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* gameObject) : MeshComponent(gameObject)
{

	_particlesArray = nullptr;
	_pointSize = 1.0f;
	_pointSizeMax = 25.0f;
	_particlesTexture = NULL;
	_particleVertexBuffer = NULL;
	_aliveParticlesCount = 0;
	_maxParticlesCount = 0;
	_particlesLifeTime = 2.0f;
	_particlesmaxAngle = 45.0f;
	_minParticleBurstAmount = 1;
	_maxParticleBurstAmount = 5000;
	_randomColorAtStart = false;
	_particleEmissionShape = ParticleEmissionShape::Cone;
	_particleStartColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_minParticleSpeedMultiplier = 1.0f;
	_maxParticleSpeedMultiplier = 1.0f;


	SetMaterialColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	_material.Ambient.r = _material.Ambient.g = _material.Ambient.b = 0.0f;
	_material.Ambient.a = 1.0f;
	_material.Diffuse.r = _material.Diffuse.g = _material.Diffuse.b = 1.0f;
	_material.Diffuse.a = 1.0f;
}

void ParticleSystemComponent::InitComponent()
{
	D3DXCreateTextureFromFile(_d3ddev, L"Ressources\\particle.png", &_particlesTexture);
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	Clean();
}


void ParticleSystemComponent::Draw()
{
	InitDraw();
	ModifyVertexBuffer();

	_d3ddev->SetMaterial(&_material);
	_d3ddev->SetTexture(0, _particlesTexture);
	_d3ddev->SetFVF(PARTICLEFVF);
	_d3ddev->SetStreamSource(0, _particleVertexBuffer, 0, sizeof(PARTICLEVERTEX));
	_d3ddev->SetTransform(D3DTS_WORLD, &_engine->_identityMatrix);
	_d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, _aliveParticlesCount);

	UninitDraw();
}

DWORD FloatIntoDWORD(float v)
{
	return *((DWORD*)&v);
}

void ParticleSystemComponent::InitDraw()
{
	_d3ddev->SetRenderState(D3DRS_LIGHTING, FALSE);
	_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	_d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_A, FloatIntoDWORD(0.0f));
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_B, FloatIntoDWORD(0.0f));
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_C, FloatIntoDWORD(1.0f));
	_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_d3ddev->SetRenderState(D3DRS_POINTSIZE, FloatIntoDWORD(_pointSize));
	_d3ddev->SetRenderState(D3DRS_POINTSIZE_MAX, FloatIntoDWORD(_pointSizeMax));
}

void ParticleSystemComponent::UninitDraw()
{
	_d3ddev->SetTexture(0, NULL);
	_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	_d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	_d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, FALSE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, FALSE);
	_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	_d3ddev->SetRenderState(D3DRS_LIGHTING, TRUE);
}

void ParticleSystemComponent::Clean()
{
	_particlesTexture->Release();
	_particleVertexBuffer->Release();
}

void ParticleSystemComponent::Update()
{
	float deltaTime = _engine->GetTimer()->deltaTime;

	int deadParticlesCount = 0;
	int remainingParticleToCreate = _maxParticlesCount - _aliveParticlesCount;

	//Update Dead particles
	for (int i = 0; i < _maxParticlesCount; i++)
	{
		Particle* currentParticle = &_particlesArray[i];

		if (currentParticle->_isAlive && currentParticle->UpdateLifeTime(deltaTime) == false)
		{
			currentParticle->_isAlive = false;
			deadParticlesCount++;
		}
	}

	remainingParticleToCreate += deadParticlesCount;


	// new
	int addParticlesCount = CreateParticleBurst(remainingParticleToCreate);

	_aliveParticlesCount -= deadParticlesCount;
	_aliveParticlesCount += addParticlesCount;

	//Updating particles positions and color
	for (int i = 0; i < _maxParticlesCount; i++)
	{
		Particle* currentParticle = &_particlesArray[i];

		if (currentParticle->_isAlive)
		{
			currentParticle->UpdatePosition(deltaTime);
			currentParticle->UpdateColor();
		}
	}

	//ModifyVertexBuffer();
}

void ParticleSystemComponent::ModifyVertexBuffer()
{
	PARTICLEVERTEX* buffer;
	HRESULT hRes = _particleVertexBuffer->Lock(0, _aliveParticlesCount * sizeof(PARTICLEVERTEX), (void**)&buffer, 0);
	//HRESULT hRes = _particleVertexBuffer->Lock(0, 0, (void**)&buffer, 0);

	if (FAILED(hRes))
		return;

	for (int i = 0; i < _aliveParticlesCount; i++)
	{
		Particle& currentParticle = _particlesArray[i];

		if (currentParticle._isAlive)
		{
			buffer->position = currentParticle._position;
			buffer->diffuse = D3DCOLOR_COLORVALUE(currentParticle._color.r, currentParticle._color.g, currentParticle._color.b, currentParticle._color.a);
			buffer++;
		}
	}
	_particleVertexBuffer->Unlock();
}


void ParticleSystemComponent::SetParticlesStartAcceleration(D3DXVECTOR3 newAcceleration)
{
	_startAcceleration = newAcceleration;
}

void ParticleSystemComponent::SetParticlesStartVelocity(D3DXVECTOR3 newVelocity)
{
	_startVelocity = newVelocity;
}

void ParticleSystemComponent::SetParticlesMaxAngle(float angle)
{
	_particlesmaxAngle = angle;
}

void ParticleSystemComponent::SetMesh(LPCWSTR meshPath)
{
}

void ParticleSystemComponent::SetTexture(LPCWSTR texturePath)
{
	D3DXCreateTextureFromFile(_d3ddev, texturePath, &_particlesTexture);
}

void ParticleSystemComponent::SetMaxParticlesCount(int newCount)
{
	_maxParticlesCount = newCount;

	delete[] _particlesArray;

	_particlesArray = new Particle[_maxParticlesCount];

	if (_particleVertexBuffer != NULL)
	{
		_particleVertexBuffer->Release();
		_particleVertexBuffer = NULL;
	}

	auto result = _d3ddev->CreateVertexBuffer(_maxParticlesCount * sizeof(PARTICLEVERTEX),
		D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
		PARTICLEFVF,
		D3DPOOL_DEFAULT,
		&_particleVertexBuffer, NULL);
}

int ParticleSystemComponent::CreateParticleBurst(int maxAmount)
{
	float deltaTime = _engine->GetTimer()->deltaTime;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr((int)(_minParticleBurstAmount * deltaTime), (int)(_maxParticleBurstAmount * deltaTime));
	int addCount = distr(gen);

	if (addCount > maxAmount) {
		addCount = maxAmount;
	}

	int index = 0;
	for (int i = 0; i < _maxParticlesCount; i++)
	{
		Particle* currentParticle = &_particlesArray[i];

		std::mt19937 gen(rd());

		if (currentParticle->_isAlive == false)
		{
			index++;
			currentParticle->_position = _gameObject->_transform->GetPosition();
			currentParticle->_lifeTime = _particlesLifeTime;
			currentParticle->_age = 0.0f;

			D3DXVECTOR3 direction;
			D3DXVECTOR3 normalizedDirection;

			switch (_particleEmissionShape) {

				case(ParticleEmissionShape::Cone):
				{
					float angleCos = abs(sin(D3DXToRadian(_particlesmaxAngle)));

					std::uniform_real_distribution<> distr1(-angleCos, angleCos);
					std::uniform_real_distribution<> distr2(-angleCos, angleCos);
					float xVelocity = distr1(gen);
					float zVelocity = distr2(gen);

					direction = D3DXVECTOR3(xVelocity, 1.0f, zVelocity);

					D3DXVec3Normalize(&normalizedDirection, &direction);

					break;
				}

				case(ParticleEmissionShape::Point):
				{
					std::uniform_real_distribution<> distrx(-1.0f, 1.0f);
					std::uniform_real_distribution<> distry(-1.0f, 1.0f);
					std::uniform_real_distribution<> distrz(-1.0f, 1.0f);
					float xVelocity = distrx(gen);
					float yVelocity = distry(gen);
					float zVelocity = distrz(gen);

					direction = D3DXVECTOR3(xVelocity, yVelocity, zVelocity);
					D3DXVec3Normalize(&normalizedDirection, &direction);

					break;
				}



				
			}

			std::uniform_real_distribution<> distrSpeed(_minParticleSpeedMultiplier, _maxParticleSpeedMultiplier);

			float speedMultiplier = distrSpeed(gen);

			currentParticle->_velocity = normalizedDirection * speedMultiplier;

			currentParticle->_acceleration = _startAcceleration;

			if (_randomColorAtStart)
			{
				std::uniform_real_distribution<> distrr(0.0f, 1.0f);
				std::uniform_real_distribution<> distrg(0.0f, 1.0f);
				std::uniform_real_distribution<> distrb(0.0f, 1.0f);
				currentParticle->_color = D3DXCOLOR(distrr(gen), distrg(gen), distrb(gen), 1.0f);
			}
			else
			{
				currentParticle->_color = _particleStartColor;
			}

			
			currentParticle->_isAlive = true;
		}

		if (index >= addCount) break;
	}

	return addCount;
}