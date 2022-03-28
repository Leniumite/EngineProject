#pragma once

class ButtonComponent :
    public MeshComponent
{
private:
    LPD3DXLINE _line;
public:
    list<Listener*> _listeners;

    TextComponent* _text;
    ButtonComponent(GameObject* gameObject);

    RECT _rect;

    bool RectCollision(RECT rectA, RECT rectB);
    bool CheckForButtonPress();
    virtual void Draw() override;
    void ChangeRect(RECT newRect);
    void ChangeRect(LONG top, LONG left, LONG bottom, LONG right);
};

