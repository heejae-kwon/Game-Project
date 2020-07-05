#pragma once
#include <chrono>
			using namespace std::chrono;

				class Timer
				{
				public:
								static Timer* instance();
        
								float GetDelta(); /*Return dt*/

				private:
								time_point<high_resolution_clock> prevTime;
								time_point<high_resolution_clock> currTime;

								Timer();

				};
