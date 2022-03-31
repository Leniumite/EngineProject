#pragma once

class LightComponent :
    public Component
{
    D3DLIGHT9 _light;

public:

    LightComponent(GameObject* gameObject);
    virtual ~LightComponent() override {};
    virtual void InitComponent() override;


    void SetType(D3DLIGHTTYPE newLightType);
    void SetColor(D3DXCOLOR newColor);
    void SetDirection(D3DXVECTOR3 newDirection);
    void SetRange(float newRange);
    void SetInnerAngle(float newInnerAngle);
    void SetOuterAngle(float newOuterAngle);
    void Activate(bool isActivated);

};

