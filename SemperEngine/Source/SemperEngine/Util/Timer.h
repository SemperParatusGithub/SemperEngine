#pragma once
#include "SemperEngine/Core/Types.h"
#include <chrono>


namespace SemperEngine
{
	namespace Util
	{
		struct Time
		{
			float time = 0.0f;	//ms
		};

		class Timer
		{
		public:
			void Start()
			{
				m_StartPoint = std::chrono::high_resolution_clock::now();
			}
			Time Restart()
			{
				Start();

				return GetTime();
			}
			Time GetTime()
			{
				auto elapsed = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartPoint).time_since_epoch().count();
				return Time { elapsed / 1000.0f };
			}

		private:
			std::chrono::time_point<std::chrono::high_resolution_clock> m_StartPoint;
		};
	}
}