#include "Moteur.h"
#include "pch.h"

ButtonComponent::ButtonComponent(GameObject* gameObject) : UIClickableComponent(gameObject)
{
    _rect.left = 0;
    _rect.top = 0;
    _rect.right = 1920;
    _rect.bottom = 1080;
    _text = gameObject->AddComponent<TextComponent>();
    _text->SetCorners(_rect.top, _rect.left, _rect.bottom, _rect.right);
    _text->_txt = L"BUTTON";
}

bool ButtonComponent::RectCollision(RECT rectA, RECT rectB)
{
    if (abs(rectA.left) > abs(rectB.right))
        return false;
    if (abs(rectA.right) < abs(rectB.left))
        return false;
    if (abs(rectA.top) > abs(rectB.bottom))
        return false;
    if (abs(rectA.bottom) < abs(rectB.top))
        return false;

    return true;
}

bool ButtonComponent::CheckForButtonPress()
{
    POINT mousePos;
    if (GetCursorPos(&mousePos)) //Gets the mousePos on the screen
    {
        if (ScreenToClient(_engine->GetWindow(), &mousePos)) //Sets the mousePos relative to the window
        {
            RECT mouseRect = { mousePos.x, mousePos.y, 1, 1 };
            
            if (PtInRect(&_rect, mousePos))
            {
                for (Listener* listener: _listeners)
                {
                    listener->OnRaise();
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

void ButtonComponent::Draw()
{
    if(_line == NULL)
        D3DXCreateLine(_engine->GetDevice(), &_line);
    
    _line->Begin();

    _line->SetWidth(5);

    D3DXVECTOR2 borderPos[] = {
        D3DXVECTOR2(_rect.left, _rect.top),
        D3DXVECTOR2(_rect.right, _rect.top),
        D3DXVECTOR2(_rect.right,_rect.bottom),
        D3DXVECTOR2(_rect.left, _rect.bottom),
        D3DXVECTOR2(_rect.left, _rect.top),
    };
    _line->Draw(borderPos, 5, D3DXCOLOR(255.0f, 255.0f, 255.0f, 255.0f));

    _line->End();
}

void ButtonComponent::ChangeRect(RECT newRect) {
    _rect = newRect;
    _text->SetCorners(_rect.top, _rect.left, _rect.bottom, _rect.right);
}

void ButtonComponent::ChangeRect(LONG top, LONG left, LONG bottom, LONG right) {
    _rect.left = left;
    _rect.top = top;
    _rect.bottom = bottom;
    _rect.right = right;
    _text->SetCorners(_rect.top, _rect.left, _rect.bottom, _rect.right);
}