#include "pch.h"
#include "framework.h"

void TextComponent::Draw()
{
    ID3DXFont* g_font = NULL;

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

        &g_font);         //ppFont

    RECT rect;
    SetRect(&rect, 500, 500, 1000, 1000);
    D3DXCOLOR color;
    color = D3DXCOLOR(255.0f, 255.0f, 255.0f, 1);
    g_font->DrawTextW(NULL, L"Test", -1, &rect, DT_NOCLIP | DT_LEFT, color);
}
