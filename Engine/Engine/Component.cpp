#include "pch.h"
#include "Component.h"

int Component::m_nextID;

Component::Component()
{
	m_type = 0;
	m_id = m_nextID++;
}

void Component::Init() {
	m_nextID = 0; 
}

void Component::Update()
{
}
