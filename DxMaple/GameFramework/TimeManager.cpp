#include "stdafx.h"
#include "TimeManager.h"

IMPLEMENT_SINGLETON(TimeManager)
TimeManager::TimeManager()
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::insertTargetFrame(wstring targetframeName, float targetFrame)
{
	auto& find_iter = mapFrames_.find(targetframeName);
	ASSERT_MESSAGE_RETURN(mapFrames_.end() == find_iter, "Frame name already exist", E_FAIL);

	unique_ptr<Frame> frame = make_unique<Frame>(targetFrame);
	mapFrames_.emplace(targetframeName, move(frame));
	return S_OK;
}

void TimeManager::update()
{
	timer_.update();
	for (auto& frame : mapFrames_)
	{
		frame.second.get()->update(timer_.getDeltaTime());
	}
}

bool TimeManager::isTargetFrame(wstring targetFrameName)
{
#ifdef _DEBUG
	auto& find_iter = mapFrames_.find(targetFrameName);
	ASSERT_MESSAGE_RETURN(mapFrames_.end() != find_iter, "target frame does not exist", false);
#endif
	if (mapFrames_[targetFrameName].get()->isTargetTime())
		return true;
	return false;
}

bool TimeManager::isTargetFrame()
{
#ifdef _DEBUG
	auto& find_iter = mapFrames_.find(currentTargetFrame_);
	ASSERT_MESSAGE_RETURN(mapFrames_.end() != find_iter, "target frame does not exist", false);
#endif
	if (mapFrames_[currentTargetFrame_].get()->isTargetTime())
		return true;
	return false;
}

//float TimeManager::getFrameDeltaTime(wstring targetFrameName)
//{
//#ifdef _DEBUG
//	auto& find_iter = mapFrames_.find(targetFrameName);
//	ASSERT_MESSAGE_RETURN(mapFrames_.end() != find_iter, "target frame does not exist", false);
//#endif
//	return (*find_iter).second->getAccTime();
//}
//
//float TimeManager::getFrameDeltaTime()
//{
//#ifdef _DEBUG
//	auto& find_iter = mapFrames_.find(currentTargetFrame_);
//	ASSERT_MESSAGE_RETURN(mapFrames_.end() != find_iter, "target frame does not exist", false);
//#endif
//	return (*find_iter).second->getAccTime();
//}

float TimeManager::getDeltaTime()
{
	return timer_.getDeltaTime();
}
