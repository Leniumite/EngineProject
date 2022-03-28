#pragma once

class QuitButton :
    public Listener
{
public:

    virtual void InitComponent() override;
    virtual void Update() override;
    virtual void OnRaise() override;
    QuitButton(GameObject* gameObject);
    virtual ~QuitButton() override;
    void OnButtonClicked();

};

