#include "framework.h"

EscapeUIManager::EscapeUIManager(GameObject* gameobject) : Component(gameobject)
{
}

void EscapeUIManager::Update()
{
	if (::GetAsyncKeyState(VK_ESCAPE) & 0x01)
	{
		_engine->GetScene()->_mainCamera->isMenuOpen = !_engine->GetScene()->_mainCamera->isMenuOpen;
        EnableButtons(_engine->GetScene()->_mainCamera->isMenuOpen);
		ShowCursor(_engine->GetScene()->_mainCamera->isMenuOpen);
	}

	if (_engine->GetScene()->_mainCamera->isMenuOpen == TRUE) {
		for (UIClickableComponent* clickable : _UIClickable)
		{
			clickable->Draw();
		}
	}

    if (::GetAsyncKeyState(VK_LBUTTON) & 0x8000f && _engine->GetScene()->_mainCamera->isMenuOpen == TRUE) {
        for (UIClickableComponent* clickable : _UIClickable)
        {
			clickable->CheckForButtonPress();
        }
    }
    else if(_engine->GetScene()->_mainCamera->isMenuOpen == FALSE) {
		EnableButtons(FALSE);
    }
}

void EscapeUIManager::InitComponent()
{
    //EnableButtons(FALSE);
}

void EscapeUIManager::EnableButtons(bool newStatus)
{
	for (UIClickableComponent* clickable :_UIClickable)
	{
		for (Component* component : clickable->_gameObject->GetAllComponents())
		{
			component->isEnable = newStatus;
		}
	}
}
