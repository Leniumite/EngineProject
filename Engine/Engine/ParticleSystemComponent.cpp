#include "pch.h"
#include "framework.h"

ParticleSystemComponent::ParticleSystemComponent(GameObject* gameObject) : MeshComponent(gameObject)
{

}

void ParticleSystemComponent::InitComponent()
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

/*
void ParticleSystemComponent::Draw()
{
	MeshComponent::Draw();
	_d3ddev->SetTexture(0, m_pTexture->GetTexture9());
	_d3ddev->SetStreamSource(0, m_pVertex, 0, sizeof(D3DXVERTEX_PARTICLE));
	_d3ddev->SetFVF(DXFVF_PARTICLE);
	_d3ddev->DrawPrimitive(D3DPT_POINTLIST, 0, m_atoms.GetCount());

}*/
