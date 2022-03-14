#pragma once
class Component
{
public:
	Component();
	void Update();
	static void Init();

public:

	int m_type;
	static int m_nextID;
	int m_id;
};
