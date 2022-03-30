#pragma once

class UIClickableComponent :
    public MeshComponent
{
public:
    UIClickableComponent(GameObject* gameObject);
    virtual bool CheckForButtonPress() = 0;

private:
};

