#pragma once
class MeshComponent;
class TextComponent :
    public MeshComponent
{

public:
    virtual void Draw() override;
};

