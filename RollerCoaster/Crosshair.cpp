#include "framework.h"

Crosshair::Crosshair(GameObject* gameobject) : MeshComponent(gameobject)
{
    D3DXCreateSprite(_engine->GetDevice(), &_sprite);
    //create a texture surface from a file
    HRESULT result = D3DXCreateTextureFromFile(_engine->GetDevice(), L"Ressources\\crosshair.png", &_texture);
    D3DSURFACE_DESC surfaceDesc;
    _texture->GetLevelDesc(0, &surfaceDesc);
    _center = D3DXVECTOR3(surfaceDesc.Height * 0.5, surfaceDesc.Width * 0.5, 0.0f);
}

Crosshair::~Crosshair()
{
}

void Crosshair::Draw()
{
    D3DXVECTOR3 scale = _gameObject->_transform->GetScale();
    _sprite->Begin(D3DXSPRITE_ALPHABLEND);
    _sprite->SetTransform(&_gameObject->_transform->matrix);
    _sprite->Draw(_texture, NULL, &_center, new D3DXVECTOR3(1920 * .5f / scale.x, 1080 * .5f / scale.y, 0.0f), D3DXCOLOR(1, 1, 1, 1));
    _sprite->End();
}
