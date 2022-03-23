#pragma once

class FpsText :
    public Component
{
public:
    TextComponent* _text = NULL;
    virtual void InitComponent() override;
    FpsText(GameObject* gameObject);
    virtual void Update() override;
};

