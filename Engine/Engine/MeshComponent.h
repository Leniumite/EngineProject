#pragma once

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL)

struct CUSTOMVERTEX
{
    float x, y, z;
    D3DVECTOR NORMAL;
};

class MeshComponent:
    public Component
{

protected:
    LPD3DXMESH _mesh = NULL;
    D3DMATERIAL9 _material;

public:

    virtual void InitComponent() override {};
    virtual ~MeshComponent() override;
    MeshComponent(GameObject* gameObject);
    virtual void Clean();
    virtual void Draw() {};
    inline LPD3DXMESH GetMesh() { return _mesh; }
    inline D3DMATERIAL9 GetMaterial() { return _material; }
    void SetMaterialColor(D3DXCOLOR newColor);
};

