#pragma once
#include "pch.h"
#include "STimer.h"
#include "Engine.h"



void STimer::init_SystemTime()
{
    s_initTime = timeGetTime() / 1000.0f;
    s_isPerformanceTimer = false;
    s_frequency = 0.0f;

    LARGE_INTEGER frequency;
    memset(&frequency, 0, sizeof(LARGE_INTEGER));

    if (QueryPerformanceFrequency(&frequency) && frequency.QuadPart) {
        s_isPerformanceTimer = true;
        s_frequency = (float)frequency.QuadPart;

        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        s_performTime = counter.QuadPart;
    }
}

float STimer::GetAppTime()
{
    if (s_isPerformanceTimer) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);

        return (float)(counter.QuadPart - s_performTime) / s_frequency;
    }

    return timeGetTime() / 1000.0f - s_initTime;
}
