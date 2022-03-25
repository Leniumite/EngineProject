#pragma once

class MeshComponent;
class TextComponent :
    public MeshComponent
{
public:
    wstring _txt;
    D3DXCOLOR _color;
    ID3DXFont* _font;

private:
    RECT rect;
    D3DXVECTOR2 _topLeftCorner;
    D3DXVECTOR2 _bottomRightCorner;
    LPD3DXSPRITE _sprite = NULL;
    LPDIRECT3DTEXTURE9 _texture = NULL;


public:
    TextComponent(GameObject* GO);
    virtual ~TextComponent();

    virtual void Draw() override;

    virtual void InitComponent() override;

    inline ID3DXFont* GetFont() { return _font; }
    void InitFont(ID3DXFont* font);
    void InitText(LPCWSTR txt, D3DXCOLOR color, D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner);
    void SetCorners(D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner);
    void SetCorners(LONG top, LONG left, LONG bottom, LONG right);
    
    RECT GetRect();

    void ScaleTextSize();

};
