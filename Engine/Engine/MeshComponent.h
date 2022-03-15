#pragma once
#include "Component.h"

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
    
    LPDIRECT3DDEVICE9* _d3ddev;

public:

    virtual void Init(LPDIRECT3DDEVICE9* d3ddev);
    
    virtual void Draw() = 0;

};

