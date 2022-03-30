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
    if (_mesh->g_pMeshMaterials != NULL)
        delete[] _mesh->g_pMeshMaterials;

    if (_mesh->g_pMeshTextures)
    {
        for (DWORD i = 0; i < _mesh->g_dwNumMaterials; i++)
        {
            if (_mesh->g_pMeshTextures[i])
                _mesh->g_pMeshTextures[i]->Release();
        }
        delete[] _mesh->g_pMeshTextures;
    }

    if (_mesh != NULL)
    {
        _mesh->pD3DXMtrlBuffer->Release();
        _mesh = NULL;
    } 

    if (_mesh->pD3DXMtrlBuffer != NULL) _mesh->pD3DXMtrlBuffer->Release();
}

void PolygonMeshComponent::SetMesh(Mesh* mesh)
{
    _mesh = mesh;
}

void PolygonMeshComponent::Draw()
{
    // Meshes are divided into subsets, one for each material. Render them in
    // a loop

    _d3ddev->SetFVF(CUSTOMFVF);

    for (DWORD i = 0; i < _mesh->g_dwNumMaterials; i++)
    {
        // Set the material and texture for this subset
        _d3ddev->SetMaterial(&_mesh->g_pMeshMaterials[i]);
        _d3ddev->SetTexture(0, _mesh->g_pMeshTextures[i]);

        // Draw the mesh subset
        _mesh->_mesh->DrawSubset(i);
    }
}

HRESULT PolygonMeshComponent::SetMeshModel(LPCWSTR fileName)
{
    D3DXLoadMeshFromX(fileName, D3DXMESH_SYSTEMMEM, _d3ddev, NULL, &_mesh->pD3DXMtrlBuffer, NULL, &_mesh->g_dwNumMaterials, &_mesh->_mesh);
    D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)_mesh->pD3DXMtrlBuffer->GetBufferPointer();
    _mesh->g_pMeshMaterials = new D3DMATERIAL9[_mesh->g_dwNumMaterials];
    if (_mesh->g_pMeshMaterials == NULL)
        return E_OUTOFMEMORY;
    _mesh->g_pMeshTextures = new LPDIRECT3DTEXTURE9[_mesh->g_dwNumMaterials];
    if (_mesh->g_pMeshTextures == NULL)
        return E_OUTOFMEMORY;

    for (DWORD i = 0; i < _mesh->g_dwNumMaterials; i++)
    {
        // Copy the material
        _mesh->g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        _mesh->g_pMeshMaterials[i].Ambient = _mesh->g_pMeshMaterials[i].Diffuse;

        _mesh->g_pMeshTextures[i] = NULL;
        if (d3dxMaterials[i].pTextureFilename != NULL &&
            lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
        {
            //UTILISER ::GetCommandLine() pour obtenir le path de l'éxecutableYaimiaou
            string path = "Ressources\\";
            path += d3dxMaterials[i].pTextureFilename;

            // Create the texture
            if (FAILED(D3DXCreateTextureFromFileA(_d3ddev, path.c_str(), &_mesh->g_pMeshTextures[i])))
            {
                MessageBox(NULL, L"Could not find texture map", L"Meshes.exe", MB_OK);
            }
        }
    }

    
    DWORD* adj = new DWORD[_mesh->_mesh->GetNumFaces() * 3];
    _mesh->_mesh->GenerateAdjacency(0.005F, adj);
    _mesh->_mesh->OptimizeInplace(D3DXMESHOPT_VERTEXCACHE, adj, NULL, NULL, NULL);

    // Done with the material buffer
    _mesh->pD3DXMtrlBuffer->Release();

    return S_OK;
}