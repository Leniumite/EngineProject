#pragma once
class PolygonMeshComponent : public MeshComponent
{

private:
    LPD3DXBUFFER pD3DXMtrlBuffer;
    D3DMATERIAL9* g_pMeshMaterials = NULL;
    LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL;
    DWORD g_dwNumMaterials = 0L;

public:

    PolygonMeshComponent(GameObject* gameObject);
    virtual void InitComponent() override;
    virtual void Clean() override;
    virtual void Draw() override;
    HRESULT SetMeshModel(LPD3DXMESH* mesh, LPD3DXBUFFER pD3DXMtrlBuffer, D3DMATERIAL9* g_pMeshMaterials, LPDIRECT3DTEXTURE9* g_pMeshTextures, DWORD g_dwNumMaterials);
};

