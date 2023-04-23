#pragma once
//#include <functional>
//#include <string>
//#include <cstdarg>
//#include <map>
#include "InputManager.h"
#include "TimeManager.h"

using namespace std;

enum Transition { IDLE=0, WALK, DASH, JUMP, ATTACK,SKILL, MOVE, Hitted , HITTEDTOMOVE, NENGUARD,SKILL4,GROGGY, NENGROGGY ,STAND, FLASH,ROPE, KNEELDOWN};

//using Action = function<void()>;
class Entity;
class IState
{
public:
	IState(){}
	virtual ~IState(){}
//public:
//	HRESULT insertAction() { return S_OK; }
//	template<typename PairNameAction,typename... PairNameActions>
//	HRESULT insertAction(PairNameAction pairAction,PairNameActions... pairActions)
//	{
//		auto& find_iter = mapActions_.find(pairAction.first);
//		ASSERT_MESSAGE_RETURN(mapActions_.end() == find_iter, "action name already exist", E_FAIL);
//
//		mapActions_.emplace(pairAction.first, pairAction.second);
//
//		if (FAILED(insertAction(pairActions...)))
//			return E_FAIL;
//		return S_OK;
//	}
//protected:
//	void execute(wstring actionName)
//	{
//		auto& find_iter = mapActions_.find(actionName);
//		ASSERT_MESSAGE(mapActions_.end() != find_iter, "action does not exist");
//
//		mapActions_[actionName]();
//	}

public:
	virtual void enter(Entity* entity) = 0;
	virtual void update(Entity* entity) = 0;
	virtual void exit(Entity* entity) = 0;

//
//protected:
//	unordered_map<wstring, Action> mapActions_;
};