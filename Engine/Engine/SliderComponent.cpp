#include "Moteur.h"
#include "pch.h"

SliderComponent::SliderComponent(GameObject* gameObject) : UIClickableComponent(gameObject)
{
    D3DXCreateSprite(_engine->GetDevice(), &_spriteBG);
    D3DXCreateSprite(_engine->GetDevice(), &_spriteFill);
    HRESULT result = D3DXCreateTextureFromFile(_engine->GetDevice(), L"Ressources\\SliderBG.png", &_textureBG);
    result = D3DXCreateTextureFromFile(_engine->GetDevice(), L"Ressources\\SliderFill.png", &_textureFill);
}

bool SliderComponent::CheckForButtonPress()
{
    POINT mousePos;
    if (GetCursorPos(&mousePos)) //Gets the mousePos on the screen
    {
        if (ScreenToClient(_engine->GetWindow(), &mousePos)) //Sets the mousePos relative to the window
        {
            RECT mouseRect = { mousePos.x, mousePos.y, 1, 1 };

            if (PtInRect(&_rectBG, mousePos))
            {
                for (Listener* listener : _listeners)
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

bool SliderComponent::RectCollision(RECT rectA, RECT rectB)
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

void SliderComponent::Draw()
{
    D3DXVECTOR3 scale = _gameObject->_transform->GetScale();
    _spriteBG->Begin(D3DXSPRITE_ALPHABLEND);
    _spriteFill->Begin(D3DXSPRITE_ALPHABLEND);
    _spriteBG->SetTransform(&_gameObject->_transform->matrix);
    _spriteFill->SetTransform(&_gameObject->_transform->matrix);

    _spriteBG->Draw(_textureBG, NULL, &_center, new D3DXVECTOR3(1920 * .5f / scale.x, 1080 * .5f / scale.y, 0.0f), D3DXCOLOR(1, 1, 1, 1));
    _spriteFill->Draw(_textureFill, NULL, &_center, new D3DXVECTOR3(1920 * .5f / scale.x, 1080 * .5f / scale.y, 0.0f), D3DXCOLOR(1, 1, 1, 1));

    _spriteBG->End();
    _spriteFill->End();
}

void SliderComponent::ChangeRect(RECT newRect)
{
}

void SliderComponent::ChangeRect(LONG top, LONG left, LONG bottom, LONG right)
{
}
