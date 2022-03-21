#include "pch.h"
#include "framework.h"


PolygonMeshComponent::PolygonMeshComponent(GameObject* gameObject) : MeshComponent(gameObject)
{
}

void PolygonMeshComponent::InitComponent()
{

}

void PolygonMeshComponent::Clean()
{
    if (g_pMeshMaterials != NULL)
        delete[] g_pMeshMaterials;

    if (g_pMeshTextures)
    {
        for (DWORD i = 0; i < g_dwNumMaterials; i++)
        {
            if (g_pMeshTextures[i])
                g_pMeshTextures[i]->Release();
        }
        delete[] g_pMeshTextures;
    }

    if (g_pMesh != NULL) g_pMesh->Release();

    if (pD3DXMtrlBuffer != NULL) pD3DXMtrlBuffer->Release();
}

void PolygonMeshComponent::Draw()
{
    MeshComponent::Draw();
    // Meshes are divided into subsets, one for each material. Render them in
    // a loop
    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        _d3ddev->SetMaterial(&g_pMeshMaterials[i]);
        _d3ddev->SetTexture(0, g_pMeshTextures[i]);

        // Draw the mesh subset
        g_pMesh->DrawSubset(i);
    }
}

HRESULT PolygonMeshComponent::SetMeshModel(LPCWSTR modelPath)
{
    D3DXLoadMeshFromX(modelPath, D3DXMESH_SYSTEMMEM, _d3ddev, NULL, &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials, &g_pMesh);
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    if (g_pMeshMaterials == NULL)
        return E_OUTOFMEMORY;
    g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
    if (g_pMeshTextures == NULL)
        return E_OUTOFMEMORY;

    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Copy the material
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

        g_pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            // Create the texture
            D3DXCreateTextureFromFileA(_d3ddev, d3dxMaterials[i].pTextureFilename, &g_pMeshTextures[i]);
        }
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}


void PolygonMeshComponent::Update()
{
    _gameObject->_transform->RotatePitch(5.0f * _engine->GetTimer()->deltaTime);
}