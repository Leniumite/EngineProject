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
    if (_font != NULL)
    {
        _font = NULL;
    }

    _sprite->Release();
    _sprite = NULL;
    _texture->Release();
    _texture = NULL;
    
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
