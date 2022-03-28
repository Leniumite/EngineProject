#include "pch.h"
#include "framework.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
	_particlesArray = nullptr;
}

void ParticleSystemComponent::InitComponent()
{
	D3DXCreateSphere(_d3ddev, 1.0f, 10, 10, &_particleMesh, NULL);
	D3DXCreateTextureFromFile(_d3ddev, L"Ressources\\particle.png", &_particlesTexture);
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	Clean();
}


void ParticleSystemComponent::Draw()
{
	
	InitDraw();

	_d3ddev->SetTexture(0, _particlesTexture);
	_d3ddev->SetStreamSource(0, _particleVertexBuffer, 0, sizeof(PARTICLEVERTEX));
	_d3ddev->SetFVF(PARTICLEFVF);
	_d3ddev->SetTransform(D3DTS_WORLD, &_engine->_identityMatrix);
	_d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, _livingParticles.size());

	UninitDraw();

}

void ParticleSystemComponent::InitDraw()
{
	_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	_d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_A, DWORD(0.0f));
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_B, DWORD(0.0f));
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_C, DWORD(1.0f));
	_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_d3ddev->SetRenderState(D3DRS_POINTSIZE, DWORD(_pointSize));
	_d3ddev->SetRenderState(D3DRS_POINTSIZE_MAX, DWORD(_pointSizeMax));
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
}

void ParticleSystemComponent::Clean()
{
	for (Particle* particle : _livingParticles)
	{
		delete particle;
	}
	_particleMesh->Release();
	_particlesTexture->Release();
	_particleVertexBuffer->Release();
}

void ParticleSystemComponent::Update()
{
	float deltaTime = _engine->GetTimer()->deltaTime;

	if (_livingParticles.empty()) return;

	for (Particle* particle : _livingParticles)
	{
		if (particle->UpdateLifeTime(deltaTime))
		{
			particle->UpdatePosition(deltaTime);
			particle->UpdateColor();
		}
		else
		{
		}
	}






	/*if (!particlesToDestroy.empty())
	{
		int particleAmountToDestroy = particlesToDestroy.size();

		for (Particle* particle : _livingParticles)
		{
			for (Particle* particleToDestroy : particlesToDestroy)
			{
				if (particle == particleToDestroy)
				{
					delete particle;
				}
			}
		}

		if (_isLooping)
		{
			for (int i = 0; i < particleAmountToDestroy; i++)
			{
				Particle* newParticle = new Particle();
				newParticle->_position = _gameObject->_transform->GetPosition();
				newParticle->_lifeTime = _particlesLifeTime;
				_livingParticles.push_back(newParticle);
			}
		}

		for (Particle* particle : particlesToDestroy)
		{
			delete particle;
		}
		
	}*/


	
}

void ParticleSystemComponent::SetIsLooping(bool newValue)
{
	_isLooping = newValue;
}

void ParticleSystemComponent::ModifyVertexBuffer()
{
	//vector<PARTICLEVERTEX> particleVertices;
	//for (Particle* particle : _livingParticles)
	//{
	//	PARTICLEVERTEX newVertex;
	//	newVertex.position = particle->_position;
	//	newVertex.diffuse = particle->_color;
	//	particleVertices.push_back(newVertex);
	//}

	

	//VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	PARTICLEVERTEX* buffer;
	_particleVertexBuffer->Lock(0, 0, (void**)&buffer, 0);
	for (Particle* particle : _livingParticles)
	{
		buffer->position = particle->_position;
		buffer->diffuse = particle->_color;
		buffer++;
	}
	_particleVertexBuffer->Unlock();
}


void ParticleSystemComponent::SetParticlesAcceleration(D3DXVECTOR3 newAcceleration)
{
	for (Particle* particle : _livingParticles)
	{
		particle->_acceleration = newAcceleration;
	}
}

void ParticleSystemComponent::SetParticlesMaxAngle(float angle)
{

}

void ParticleSystemComponent::SetMesh(LPCWSTR meshPath)
{
}

void ParticleSystemComponent::SetTexture(LPCWSTR texturePath)
{

}

void ParticleSystemComponent::SetMaxParticlesCount(int newCount)
{
	_maxParticlesCount = newCount;

	_particlesArray = new Particle[_maxParticlesCount];

	if (_particleVertexBuffer != NULL)
	{
		_particleVertexBuffer->Release();
		_particleVertexBuffer = NULL;
	}

	auto result = _d3ddev->CreateVertexBuffer(_maxParticlesCount * sizeof(PARTICLEVERTEX),
		D3DUSAGE_DYNAMIC,
		PARTICLEFVF,
		D3DPOOL_DEFAULT,
		&_particleVertexBuffer, NULL);

	if (_livingParticles.empty() == false)
	{
		for (Particle* particle : _livingParticles)
		{
			delete particle;
		}
	}
	

	_livingParticles.clear();

	for (int i = 0; i < newCount; i++)
	{
		Particle* newParticle = new Particle();
		newParticle->_position = _gameObject->_transform->GetPosition();
		newParticle->_lifeTime = _particlesLifeTime;
		_livingParticles.push_back(newParticle);
	}
	
}

void ParticleSystemComponent::SetEmissionShape(ParticleEmissionShape newEmissionShape)
{

}
