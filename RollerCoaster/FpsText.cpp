#include "framework.h"


FpsText::FpsText(GameObject* gameObject) : Component(gameObject)
{
}


void FpsText::InitComponent()
{
	_text = _gameObject->AddComponent<TextComponent>();

	_text->SetCorners(0, 0, 100, 100);
}

void FpsText::Update()
{

	_text->_txt = L"FPS: " + std::to_wstring(_engine->GetTimer()->_previousCounter);
	
}
