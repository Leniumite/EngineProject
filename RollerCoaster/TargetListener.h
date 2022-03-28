#pragma once

class TargetListener :
    public Listener
{
public:
    virtual void InitComponent() override;
    virtual void Update() override;
    virtual void OnRaise() override;
    TargetListener(GameObject* gameObject);
};

