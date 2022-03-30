#pragma once

class SliderComponent :
    public UIClickableComponent
{
private:
    float valueMin = 0.0f;
    float valueMax = 100.0f;
    float actualValue = 0.0f;

    D3DXVECTOR3 _center;

    RECT _rectBG;
    RECT _rectFill;
    LPD3DXSPRITE _spriteBG;
    LPD3DXSPRITE _spriteFill;

    LPDIRECT3DTEXTURE9 _textureBG;
    LPDIRECT3DTEXTURE9 _textureFill;
        
public:
    list<Listener*> _listeners;

    SliderComponent(GameObject* gameObject);

    TextComponent* _text;

    virtual bool CheckForButtonPress() override;

    bool RectCollision(RECT rectA, RECT rectB);
    virtual void Draw() override;

    void ChangeRect(RECT newRect);
    void ChangeRect(LONG top, LONG left, LONG bottom, LONG right);
};

