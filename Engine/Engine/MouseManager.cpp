#include "pch.h"
#include "framework.h"


void MouseManager::GetMousePosition()
{
	
	::GetCursorPos(&pt);
	_mouseX = pt.x;
	_mouseY = pt.y;
}

void MouseManager::CenterCursor()
{
	SetCursorPos(1920 * 0.5f, 1080 * 0.5f);
}

void MouseManager::CalculateDelta()
{
	
	::GetCursorPos(&pt);
	_mouseDeltaX=(float) (pt.x - _mouseX)*0.001;
	_mouseDeltaY =(float) (pt.y - _mouseY)*0.001 ;
}



