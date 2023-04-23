#pragma once
#include "Timer.h"
#include "Frame.h"
class TimeManager
{
	DECLARE_SINGLETON(TimeManager)
public:
	explicit TimeManager();
	~TimeManager();
public:
	HRESULT insertTargetFrame(wstring targetframeName,float targetFrame);
	
	
	void update();

	bool isTargetFrame(wstring targetFrameName);
	bool isTargetFrame();
	
	void setTargetFrame(wstring targetFrameName) { currentTargetFrame_ = targetFrameName; }

	

	//잘못사용하고 있었음..
	//프레임 고정 적용하면 이게 deltatime임
	/*float getFrameDeltaTime(wstring targetFrameName); 
	float getFrameDeltaTime();*/

	//이게 진짜 deltatime
	float getDeltaTime();

private:
	Timer timer_;
	map<wstring, unique_ptr<Frame>> mapFrames_;
	wstring currentTargetFrame_;
};

