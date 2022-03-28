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

    if (_mesh != nullptr)
    {
        _mesh->Release();
        _mesh = NULL;
    } 

    if (pD3DXMtrlBuffer != NULL) pD3DXMtrlBuffer->Release();
}

void PolygonMeshComponent::Draw()
{
    // Meshes are divided into subsets, one for each material. Render them in
    // a loop

    _d3ddev->SetFVF(CUSTOMFVF);

    for (DWORD i = 0; i < g_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        _d3ddev->SetMaterial(&g_pMeshMaterials[i]);
        _d3ddev->SetTexture(0, g_pMeshTextures[i]);

        // Draw the mesh subset
        _mesh->DrawSubset(i);
    }
}

HRESULT PolygonMeshComponent::SetMeshModel(LPD3DXMESH* mesh, LPD3DXBUFFER _pD3DXMtrlBuffer, D3DMATERIAL9* _g_pMeshMaterials, LPDIRECT3DTEXTURE9* _g_pMeshTextures, DWORD _g_dwNumMaterials)
{
    _mesh = *mesh;
    pD3DXMtrlBuffer = _pD3DXMtrlBuffer;
    g_pMeshMaterials = _g_pMeshMaterials;
    g_pMeshTextures = _g_pMeshTextures;
    g_dwNumMaterials = _g_dwNumMaterials;

    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)_pD3DXMtrlBuffer->GetBufferPointer();

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
            //UTILISER ::GetCommandLine() pour obtenir le path de l'éxecutableYaimiaou
            string path = "Ressources\\";
            path += d3dxMaterials[i].pTextureFilename;

            // Create the texture
            if (FAILED(D3DXCreateTextureFromFileA(_d3ddev, path.c_str(), &g_pMeshTextures[i])))
            {
                MessageBox(NULL, L"Could not find texture map", L"Meshes.exe", MB_OK);
            }
        }
    }


    DWORD* adj = new DWORD[_mesh->GetNumFaces() * 3];
    _mesh->GenerateAdjacency(0.005F, adj);
    _mesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, adj, NULL, NULL, NULL);

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

    return S_OK;
}