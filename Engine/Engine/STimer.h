#pragma once
class STimer
{
	float s_initTime;

	bool s_isPerformanceTimer;
	float s_frequency;

	
	
	


	LONGLONG s_performTime;
public:
	void init_SystemTime();
	float GetAppTime();
	float GetDeltaTime() { return deltaTime; }
	void SetDeltaTime(float newDeltaTime) { deltaTime = newDeltaTime; }

	float oldtime;
	float deltaTime;
	float time;
};
