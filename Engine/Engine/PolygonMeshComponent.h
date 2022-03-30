#pragma once
class PolygonMeshComponent : public MeshComponent
{

private:
    Mesh* _mesh;


public:

    PolygonMeshComponent(GameObject* gameObject);

    virtual void InitComponent() override;
    virtual void Clean() override;
    virtual void Draw() override;
    HRESULT SetMeshModel(LPCWSTR modelPath);
    void SetMesh(Mesh*);
};

