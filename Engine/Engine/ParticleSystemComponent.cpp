#include "pch.h"
#include "framework.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* gameObject) : MeshComponent(gameObject)
{

}

void ParticleSystemComponent::InitComponent()
{
	D3DXCreateSphere(_d3ddev, .5f, 10, 10, &_particleMesh, NULL);
	D3DXCreateTextureFromFile(_d3ddev, L"Ressources\\particle.png", &_particlesTexture);
}


void ParticleSystemComponent::Draw()
{
	
	InitDraw();

	_d3ddev->SetTexture(0, _particlesTexture);
	_d3ddev->SetStreamSource(0, _particleVertexBuffer, 0, sizeof(PARTICLEVERTEX));
	_d3ddev->SetFVF(PARTICLEFVF);
	_d3ddev->SetTransform(D3DTS_WORLD, &_gameObject->_transform->matrix);
	_d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, _particlesList.size());

	UninitDraw();

}

void ParticleSystemComponent::InitDraw()
{
	_d3ddev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	_d3ddev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSPRITEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALEENABLE, TRUE);
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_A, DWORD(0.0f));
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_B, DWORD(0.0f));
	_d3ddev->SetRenderState(D3DRS_POINTSCALE_C, DWORD(1.0f));
	_d3ddev->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	_d3ddev->SetRenderState(D3DRS_POINTSIZE, DWORD(_pointSize));
	_d3ddev->SetRenderState(D3DRS_POINTSIZE_MAX, DWORD(_pointSizeMax));

	_d3ddev->CreateVertexBuffer(_maxParticlesCount * sizeof(PARTICLEVERTEX),
		D3DUSAGE_DYNAMIC,
		PARTICLEFVF,
		D3DPOOL_MANAGED,
		&_particleVertexBuffer, NULL);

	VOID* pVoid;    // a void pointer

	// lock v_buffer and load the vertices into it
	_particleVertexBuffer->Lock(0, 0, (void**)&pVoid, 0);

	vector<PARTICLEVERTEX> particleVertices;
	for (Particle* particle : _particlesList)
	{
		PARTICLEVERTEX newVertex;
		newVertex.position = particle->_position;
		newVertex.diffuse = particle->_color;
		particleVertices.push_back(newVertex);
	}

	memcpy(pVoid, &particleVertices, sizeof(particleVertices));
	_particleVertexBuffer->Unlock();
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
	_particleMesh->Release();
	_particlesTexture->Release();
	_particleVertexBuffer->Release();
}

void ParticleSystemComponent::Update()
{
	float deltaTime = _engine->GetTimer()->deltaTime;

	if (_particlesList.empty()) return;
	for (Particle* particle : _particlesList)
	{
		if (particle->UpdateLifeTime(deltaTime))
		{
			particle->UpdatePosition(deltaTime);
			particle->UpdateColor();
		}
		else
		{
			_particlesList.remove(particle);
		}
	}
}

void ParticleSystemComponent::SetParticlesAcceleration(D3DXVECTOR3 newAcceleration)
{
	for (Particle* particle : _particlesList)
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

	if(_particleVertexBuffer != NULL) _particleVertexBuffer->Release();

	if (_particlesList.empty() == false)
	{
		for (Particle* particle : _particlesList)
		{
			delete particle;
		}
	}
	

	_particlesList.clear();

	for (int i = 0; i < newCount; i++)
	{
		Particle* newParticle = new Particle();
		newParticle->_position = _gameObject->_transform->GetPosition();
		newParticle->_lifeTime = 5.0f;
		_particlesList.push_back(newParticle);
	}
	
}
