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
    
    LPDIRECT3DDEVICE9 _d3ddev;
    LPDIRECT3DVERTEXBUFFER9* _vertexBuffer;
    LPDIRECT3DINDEXBUFFER9* _indexBuffer;

public:

    MeshComponent(GameObject* gameObject);
    virtual void Draw();
};

