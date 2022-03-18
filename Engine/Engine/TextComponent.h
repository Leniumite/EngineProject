#pragma once


class MeshComponent;
class TextComponent :
    public MeshComponent
{
public:
    LPCWSTR _txt;
    D3DXCOLOR _color;
    D3DXVECTOR2 _topLeftCorner;
    D3DXVECTOR2 _bottomRightCorner;

    ID3DXFont* _font;

private:
    RECT rect;

public:
    TextComponent(GameObject* GO);
    virtual ~TextComponent();

    virtual void Draw() override;

    virtual void InitComponent() override;

    void InitFont(ID3DXFont* font);
    void InitText(LPCWSTR txt, D3DXCOLOR color, D3DXVECTOR2 topLeftCorner, D3DXVECTOR2 bottomRightCorner);
};

