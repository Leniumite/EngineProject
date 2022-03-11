#pragma once
class Component
{
public:
	Component();
	virtual ~Component();

public:
	static int m_type;
	static int m_nextID;
	int m_id;
};
