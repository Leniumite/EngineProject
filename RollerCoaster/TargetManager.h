#pragma once
class TargetManager : public Component
{
private:
	list<GameObject*> targets;
	int ammountTarget = 10;

	D3DXCOLOR GetRandomColor();

public:
	TargetManager(GameObject* gameobject);
	~TargetManager();

	virtual void InitComponent() override;
	virtual void Update() override;
	void Replace(GameObject* go);
};

