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
    IDirect3DVertexBuffer9* _vertexBuffer = NULL;
    IDirect3DIndexBuffer9* _indexBuffer = NULL;

public:

    virtual void InitComponent() override {};
    MeshComponent(GameObject* gameObject);
    void Clean();
    virtual void Draw();
};

