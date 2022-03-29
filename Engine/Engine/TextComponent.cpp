#include "pch.h"
#include "framework.h"

TextComponent::TextComponent(GameObject* GO) : MeshComponent(GO)
{
    _d3ddev = _engine->GetDevice();

    D3DXCreateFont(_d3ddev,     //D3D Device

        22,               //Font height

        0,                //Font width

        FW_NORMAL,        //Font Weight

        1,                //MipLevels

        false,            //Italic

        DEFAULT_CHARSET,  //CharSet

        OUT_DEFAULT_PRECIS, //OutputPrecision

        ANTIALIASED_QUALITY, //Quality

        DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily

        L"Arial",          //pFacename,

        &_font);

    SetRect(&rect, 0, 0, 1920, 1080);
    _color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1);
    _txt = L"Test";
    ScaleTextSize();
    
}


TextComponent::~TextComponent()
{

}

void TextComponent::Draw()
{
    MeshComponent::Draw();
    if (_sprite == NULL) {
        D3DXCreateSprite(_engine->GetDevice(), &_sprite);
    }
    if (_texture == NULL) {
        D3DXCreateTextureFromFile(_engine->GetDevice(), L"Ressources\\box.png", &_texture);
    }
    /*_sprite->Begin(D3DXSPRITE_ALPHABLEND);
    //abs(rect.bottom - rect.top) / 2, abs(rect.right - rect.left) / 2
    D3DSURFACE_DESC surfaceDesc;
    int level = 0; //The level to get the width/height of (probably 0 if unsure)
    _texture->GetLevelDesc(level, &surfaceDesc);


    _gameObject->_transform->ChangeScale(D3DXVECTOR3(.5f, .5f, .5f));
    _sprite->SetTransform(&_gameObject->_transform->matrix);

    D3DXVECTOR3 pivot = D3DXVECTOR3(surfaceDesc.Width * .5,surfaceDesc.Height * .5, 0.0f);
    D3DXVECTOR2 center = D3DXVECTOR2((rect.right + rect.left) * .5, (rect.bottom + rect.top) * .5);
    D3DXVECTOR3 pos = D3DXVECTOR3(center.x, center.y, 0.0f);
    
    _sprite->Draw(_texture, NULL, &pivot, &pos, D3DCOLOR_XRGB(255, 255, 255));*/


    _sprite->Begin(D3DXSPRITE_ALPHABLEND);
    _font->DrawTextW(NULL, _txt.c_str(), -1, &rect, DT_NOCLIP | DT_LEFT, _color);
    _sprite->End();
    
}

void TextComponent::InitComponent()
{
}

void TextComponent::InitFont(ID3DXFont* font)
{
    _font = font;
    ScaleTextSize();
}

void TextComponent::InitText(LPCWSTR txt, D3DXCOLOR color, D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner) //peut-être Memory Leak ici
{
    _txt = txt;
    _color = color;
    SetCorners(topLeftCorner, bottomRightCorner);
    ScaleTextSize();
}

void TextComponent::SetCorners(D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner)
{
    SetRect(&rect, topLeftCorner.x, topLeftCorner.y, bottomRightCorner.x, bottomRightCorner.y);
    ScaleTextSize();
}

void TextComponent::SetCorners(LONG top, LONG left, LONG bottom, LONG right)
{
    SetRect(&rect, left, top, right, bottom);
    ScaleTextSize();
}

RECT TextComponent::GetRect()
{
    return rect;
}

void TextComponent::ScaleTextSize() {

    /*D3DXCreateFont(_d3ddev,     //D3D Device

        22,               //Font height

        0,                //Font width

        50,        //Font Weight

        1,                //MipLevels

        false,            //Italic

        DEFAULT_CHARSET,  //CharSet

        OUT_DEFAULT_PRECIS, //OutputPrecision

        ANTIALIASED_QUALITY, //Quality

        DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily

        L"Arial",          //pFacename,

        &_font);*/
}
