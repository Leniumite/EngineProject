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


public:
    TextComponent(GameObject* GO);
    virtual ~TextComponent();

    virtual void Draw() override;

    virtual void InitComponent() override;

    virtual void Update() override;

    void InitFont(ID3DXFont* font);
    void InitText(LPCWSTR txt, D3DXCOLOR color, D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner);
    void SetCorners(D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner);
    void SetCorners(LONG top, LONG left, LONG bottom, LONG right);
    
    RECT GetRect();

};

