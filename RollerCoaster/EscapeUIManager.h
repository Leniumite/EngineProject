#pragma once

class EscapeUIManager :
    public Component
{
public:
    EscapeUIManager(GameObject* gameobject);
    virtual void Update() override;
    virtual void InitComponent() override;
    list<ButtonComponent*> _uiButtons;
    void EnableButtons(bool);
};

