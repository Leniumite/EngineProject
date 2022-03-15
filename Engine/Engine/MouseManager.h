#pragma once
class MouseManager
{
public: 
	POINT pt = { 0, 0 };
	LONG _mouseX=0;
	LONG _mouseY=0;
	LONG _mouseDeltaX;
	LONG _mouseDeltaY;


	void Init();

	bool _showcursor;

	void GetMousePosition();
	void CenterCursor();
	void CalculateDeltaX();
	void CalculateDeltaY();


};

