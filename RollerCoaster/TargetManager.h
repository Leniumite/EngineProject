#pragma once
class TargetManager : public Component
{
private:
	list<GameObject*> targets;
	int ammountTarget = 5;

public:
	TargetManager(GameObject* gameobject);
	~TargetManager();

	virtual void InitComponent() override;
	virtual void Update() override;
	void Replace(GameObject* go);
};

