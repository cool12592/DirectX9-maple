#pragma once
class Timer
{
public:
	Timer()
	{
		reset();
	}

	~Timer() = default;

	void reset()
	{
		QueryPerformanceFrequency(&countTime_);
		QueryPerformanceCounter(&curTime_);
		QueryPerformanceCounter(&prevTime_);
		deltaTime_ = 0.f;
	}

	void update()
	{
		QueryPerformanceCounter(&curTime_);

		//델타타임= 현재시간-과거시간
		deltaTime_ = static_cast<float>((static_cast<double>(curTime_.QuadPart) - static_cast<double>(prevTime_.QuadPart)) / static_cast<double>(countTime_.QuadPart));
		
		prevTime_ = curTime_;
	}

	float getDeltaTime() const{ return deltaTime_; }
private:
	LARGE_INTEGER countTime_;
	LARGE_INTEGER curTime_;
	LARGE_INTEGER prevTime_;
	float deltaTime_;
};