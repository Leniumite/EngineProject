#pragma once
class STimer
{
	float s_initTime;

	bool s_isPerformanceTimer;
	float s_frequency;

	float deltaTime;
	float time;
	float oldtime;


	LONGLONG s_performTime;
public:
	void init_SystemTime();
	float GetAppTime();
	float GetDeltaTime() { return deltaTime; }

	void Refresh(); //Call the functions below
	bool UpdateTime(); //Update timer values
	void Update(); //update physics & gameplay
	void Render(); //Render

};
