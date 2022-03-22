#pragma once

class LightComponent :
    public Component
{
public:

    LightComponent(GameObject* gameObject);
    virtual ~LightComponent() override;

    void SetType(D3DLIGHTTYPE newLightType);
    void SetColor(D3DXCOLOR newColor);
    void SetDirection(D3DXVECTOR3 newDirection);

};

