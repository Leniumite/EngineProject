#pragma once
class STimer
{
	float s_initTime;

	bool s_isPerformanceTimer;
	float s_frequency;

	LONGLONG s_performTime;

public:
	int _counter = 0;
	int _previousCounter = 0;
	float _timeCounterStarted = 0.0f;

public:
	STimer();

	void init_SystemTime();
	float GetAppTime();
	float GetDeltaTime() { return deltaTime; }
	void SetDeltaTime(float newDeltaTime);

	float oldtime;
	float deltaTime;
	float time;
};
