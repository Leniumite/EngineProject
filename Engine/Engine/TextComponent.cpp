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
}


TextComponent::~TextComponent()
{

}

void TextComponent::Draw()
{
    _font->DrawTextW(NULL, _txt.c_str(), -1, &rect, DT_NOCLIP | DT_LEFT, _color);
}

void TextComponent::InitComponent()
{
}

void TextComponent::InitFont(ID3DXFont* font)
{
    _font = font;
}

void TextComponent::InitText(LPCWSTR txt, D3DXCOLOR color, D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner)
{
    _txt = txt;
    _color = color;
    SetCorners(topLeftCorner, bottomRightCorner);
}

void TextComponent::SetCorners(D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner)
{
    SetRect(&rect, topLeftCorner.x, topLeftCorner.y, bottomRightCorner.x, bottomRightCorner.y);
}

void TextComponent::SetCorners(LONG top, LONG left, LONG bottom, LONG right)
{
    SetRect(&rect, left, top, right, bottom);
}

RECT TextComponent::GetRect()
{
    return rect;
}
