#pragma once
class Mesh
{
public:
    LPD3DXMESH _mesh = NULL;
    LPD3DXBUFFER pD3DXMtrlBuffer;
    D3DMATERIAL9* g_pMeshMaterials = NULL;
    LPDIRECT3DTEXTURE9* g_pMeshTextures = NULL;
    DWORD g_dwNumMaterials = 0L;
};

