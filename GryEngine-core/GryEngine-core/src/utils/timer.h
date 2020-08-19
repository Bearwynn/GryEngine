#pragma once

#include <Windows.h>

namespace GryEngine {

	// -- performance timing class using chrono --
	class Timer
	{
	private:
		LARGE_INTEGER m_Start;
		double m_Frequency;
	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_Frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&m_Start);
		}

		void Reset()
		{
			QueryPerformanceCounter(&m_Start);
		}

		float GetElapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			return (float)(cycles * m_Frequency);
		}

		void PrintElapsedMilliseconds()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			printf("%fms\n", (float)(cycles * m_Frequency) * 1000);
		}

		void PrintElapsedMicroseconds()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			printf("%fµs\n", (float)(cycles * m_Frequency));
		}

		void PrintElapsedNanoseconds()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_Start.QuadPart;
			printf("%fns\n", (float)(cycles * m_Frequency) / 1000);
		}
	};
}