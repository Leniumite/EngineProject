#include "pch.h"
#include "MouseManager.h"





void MouseManager::GetMousePosition()
{
	
	::GetCursorPos(&pt);
	(_mouseX, _mouseY) = pt.x, pt.y;
}

void MouseManager::CenterCursor()
{
	SetCursorPos(1920 * 0.5f, 1080 * 0.5f);
}

void MouseManager::CalculateDeltaX()
{
	
	::GetCursorPos(&pt);
	_mouseDeltaX= (pt.x - _mouseX)*0.001f;
}

void MouseManager::CalculateDeltaY()
{
	
	GetCursorPos(&pt);
	_mouseDeltaY = pt.y - _mouseY;
}
