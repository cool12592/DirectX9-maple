#pragma once
class Frame
{
public:

	Frame(float targetFrame)
	{
		targetTime_ = 1.f / targetFrame;
		accTime_ = 0.f;
		getAccTime_ = 0.f;
	}
	~Frame() {}
	void update(float deltaTime)
	{
		accTime_ += deltaTime;
	}
	bool isTargetTime()
	{
		if (targetTime_ <= accTime_)
		{
			getAccTime_ = accTime_;
			accTime_ = 0.f;
			return true;
		}
		return false;
	}

	float getAccTime() const{ return getAccTime_; }
private:
	float targetTime_;
	float accTime_;
	float getAccTime_;
};