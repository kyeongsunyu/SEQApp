#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

#include <windows.h>

extern LARGE_INTEGER sysfreq;
extern LARGE_INTEGER st;

class CRtTimer
{
private:
	inline void ResetTimer(void) { t.QuadPart = st.QuadPart; }
public:
	LARGE_INTEGER t = {};
	CRtTimer() {
		// 멀티 프로세서를 사용하는 PC 에서는 BIOS (basic input/output system) 또는
		// HAL (hardware abstraction layer) 의 Bug 로 인해서 어떤 프로세서가 사용될
		// 것인지 확실하지 않습니다.
		// 예를 들어 측정을 시작할 때는 첫 번째 프로세서가 사용되고 종료할 때는 세 번째
		// 프로세서가 사용된다면, 오차가 생기게 되어 정확한 측정 결과는 얻을 수 없습니다.
		// 이런 경우를 방지하기 위해서 SetThreadAffinityMask 함수를 사용해서 항상 첫 번째
		// 프로세서를 지정합니다.
		DWORD_PTR dOldMask = SetThreadAffinityMask(GetCurrentThread(), 0);
		SetThreadAffinityMask(GetCurrentThread(), dOldMask);


	}
	inline void TimerCondition(bool c) { if (!c) ResetTimer(); }
	inline void SetTime(void) { ResetTimer(); }

	inline LONGLONG GetTimeVar(void) { return (LONGLONG)t.QuadPart; }
	inline double GetTimeDiff(void) { return ((double)(::st.QuadPart - t.QuadPart) / (double)sysfreq.QuadPart); }
	inline double GetTimeDiffmS(void) { return ((double)(::st.QuadPart - t.QuadPart) / (double)sysfreq.QuadPart * 1000.0); }
	inline double GetTimeDiffuS(void) { return ((double)(::st.QuadPart - t.QuadPart) / (double)sysfreq.QuadPart * 1000000.0); }

	inline BOOL TimeOverS(LONGLONG l) { return ((double)(::st.QuadPart - t.QuadPart) / (double)sysfreq.QuadPart) > (l); }
	inline BOOL TimeOvermS(LONGLONG l) { return ((double)(::st.QuadPart - t.QuadPart) / (double)sysfreq.QuadPart * 1000.0) > (l); }
	inline BOOL TimeOveruS(LONGLONG l) { return ((double)(::st.QuadPart - t.QuadPart) / (double)sysfreq.QuadPart * 1000000.0) > (l); }
};

class Stopwatch
{
    LARGE_INTEGER _startTime;
    LARGE_INTEGER _frequency;

public:
    Stopwatch(bool start = false) :_startTime({ 0 })
    {
        QueryPerformanceFrequency(&_frequency);
        if (start)
        {
            Start();
        }
    }

    LONGLONG GetStartTime() { return _startTime.QuadPart; }
    bool IsStarted() { return _startTime.QuadPart; }
    bool IsStopped() { return !IsStarted(); }

    void Start()
    {
        QueryPerformanceCounter(&_startTime);
    }

    void Stop()
    {
        ZeroMemory(&_startTime, sizeof(LARGE_INTEGER));
    }

    static LONGLONG GetFrequency()
    {
        LARGE_INTEGER li;
        QueryPerformanceFrequency(&li);
        return li.QuadPart;
    }

    static LONGLONG GetTicks()
    {
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter(&endingTime);
        return endingTime.QuadPart;
    }

    LONGLONG GetElapsedTicks(bool restart = false)
    {
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter(&endingTime);
        auto qp = endingTime.QuadPart - _startTime.QuadPart;
        if (restart)
        {
            Start();
        }
        return qp;
    }

    LONGLONG GetElapsed100NanoSeconds(bool restart = false)
    {
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter(&endingTime);

        LARGE_INTEGER elapsed100NanoSeconds{};
        elapsed100NanoSeconds.QuadPart = endingTime.QuadPart - _startTime.QuadPart;
        elapsed100NanoSeconds.QuadPart *= 10000000;
        elapsed100NanoSeconds.QuadPart /= _frequency.QuadPart;
        if (restart)
        {
            Start();
        }
        return elapsed100NanoSeconds.QuadPart;
    }

    LONGLONG GetElapsedMicroseconds(bool restart = false)
    {
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter(&endingTime);

        LARGE_INTEGER elapsedMicroSeconds{};
        elapsedMicroSeconds.QuadPart = endingTime.QuadPart - _startTime.QuadPart;
        elapsedMicroSeconds.QuadPart *= 1000000;
        elapsedMicroSeconds.QuadPart /= _frequency.QuadPart;
        if (restart)
        {
            Start();
        }
        return elapsedMicroSeconds.QuadPart;
    }

    LONGLONG GetElapsedMilliseconds(bool restart = false)
    {
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter(&endingTime);

        LARGE_INTEGER elapsedMilliSeconds{};
        elapsedMilliSeconds.QuadPart = endingTime.QuadPart - _startTime.QuadPart;
        elapsedMilliSeconds.QuadPart *= 1000;
        elapsedMilliSeconds.QuadPart /= _frequency.QuadPart;
        if (restart)
        {
            Start();
        }
        return elapsedMilliSeconds.QuadPart;
    }

    LONGLONG GetElapsedSeconds(bool restart = false)
    {
        LARGE_INTEGER endingTime;
        QueryPerformanceCounter(&endingTime);

        LARGE_INTEGER elapsedSeconds{};
        elapsedSeconds.QuadPart = endingTime.QuadPart - _startTime.QuadPart;
        elapsedSeconds.QuadPart /= _frequency.QuadPart;
        if (restart)
        {
            Start();
        }
        return elapsedSeconds.QuadPart;
    }
};
#endif	