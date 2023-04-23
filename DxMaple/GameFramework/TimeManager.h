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

	

	//�߸�����ϰ� �־���..
	//������ ���� �����ϸ� �̰� deltatime��
	/*float getFrameDeltaTime(wstring targetFrameName); 
	float getFrameDeltaTime();*/

	//�̰� ��¥ deltatime
	float getDeltaTime();

private:
	Timer timer_;
	map<wstring, unique_ptr<Frame>> mapFrames_;
	wstring currentTargetFrame_;
};

