#include "Timer.hpp"
#include <memory>

Timer * Timer::instance()  //!< Returns an instance of the class
{
				static std::unique_ptr<Timer> instance(new Timer());
				return instance.get();
}

float Timer::GetDelta() {
				currTime = high_resolution_clock::now();

				duration<float> delta(currTime - prevTime);

				prevTime = high_resolution_clock::now();

				return delta.count();
}

 Timer::Timer() {
				prevTime = high_resolution_clock::now();
				currTime = prevTime;
}
