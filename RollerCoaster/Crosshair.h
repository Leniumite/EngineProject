#pragma once

class Crosshair :
    public MeshComponent
{
private:
    LPD3DXSPRITE _sprite;
    LPDIRECT3DTEXTURE9 _texture;
    D3DXVECTOR3 _center;
public :
    Crosshair(GameObject* gameobject);
    virtual ~Crosshair() override;
    virtual void Draw() override;
};

