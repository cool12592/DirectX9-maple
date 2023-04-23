#include "stdafx.h"
#include "Skill.h"
#include "StateMachine.h"
#include "Rigidbody.h"
#include "AtlasAnimation.h"
#include "InputManager.h"
#include "Status.h"

bool Skill::checkSkillAvailableAndExecute()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(entity->hasComponent<StateMachine>(), "Skill component needs StateMachine component",false);
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Rigidbody>(), "Skill component needs Rigidbody component", false);
	ASSERT_MESSAGE_RETURN(entity->hasComponent<AtlasAnimation>(), "Skill component needs AtlasAnimation component", false);
#endif
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	for (auto& iter = mapSkills_.begin(); iter != mapSkills_.end(); ++iter)
	{
		//��Ÿ�� ���� ��
		if (get<(int)Skill::GETTYPE::CURRENTTIME>(iter->second) < get<(int)Skill::GETTYPE::COOLTIME>(iter->second))
			continue;
		//������ ���󿡼���, ���߱�� ���߿�����
		if (!(rigidbody.onGround_ && (SKILLTYPE::GROUND == get<(int)Skill::GETTYPE::SKILLTYPE>(iter->second))) &&
			!(!rigidbody.onGround_ && (SKILLTYPE::JUMP == get<(int)Skill::GETTYPE::SKILLTYPE>(iter->second))))
			continue;

		//ĵ�� �Ұ� ����� ��ų ����߿� ĵ�� �Ұ��ϰ�
		if (!get<(int)Skill::GETTYPE::CANCELABLE>(iter->second))
		{
			bool isCurrentSkill = false;
			for (auto& secondIter = mapSkills_.begin(); secondIter != mapSkills_.end(); ++secondIter)
				if (secondIter->first == stateMachine.getCurrentStateName())
				{
					isCurrentSkill = true;
					break;
				}
			
			if (isCurrentSkill)
				continue;
		}

		//��Ŀ�ǵ� ����
		if (InputManager::getInstance()->keyDown(get<(int)Skill::GETTYPE::QUICKCOMMAND>(iter->second)))
		{
			get<(int)Skill::GETTYPE::CURRENTTIME>(iter->second) = 0.f;
			stateMachine.changeState(iter->first);

			//�Һ� ���� �ȸ������..
			if (entity->hasComponent<Status>())
			{
				Status& status = entity->getComponent<Status>();
				status.useMp(10);
			}
			return true;
		}

		//Ŀ�ǵ� �Է� üũ
		if (InputManager::getInstance()->commandCheck(anim.getIsRight(), get<(int)Skill::GETTYPE::COMMANDLIST>(iter->second)))
		{
			get<(int)Skill::GETTYPE::CURRENTTIME>(iter->second) = 0.f;
			stateMachine.changeState(iter->first);
			//�Һ� ���� �ȸ������..
			if (entity->hasComponent<Status>())
			{
				Status& status = entity->getComponent<Status>();
				status.useMp(10);
			}
			return true;
		}
		
	}
	
	return false;
}

HRESULT Skill::insertSkillInfo(wstring stateName, SKILLTYPE skillType, bool cancelable, bool isPercentDamage, float damageValue, float cooltime, int quickCommand, vector<int> commandList)
{
#ifdef _DEBUG
	auto& find_iter = mapSkills_.find(stateName);
	ASSERT_MESSAGE_RETURN(mapSkills_.end() == find_iter, "Skill info already exist", E_FAIL);
#endif
	mapSkills_.emplace(stateName, make_tuple(skillType, cancelable, isPercentDamage, damageValue, cooltime, cooltime, quickCommand, move(commandList)));
	return S_OK;
}

float Skill::getCooltime(const wstring stateName)
{
	return  get<(int)Skill::GETTYPE::COOLTIME>(mapSkills_[stateName]);
}

float Skill::getCurrentTime(const wstring stateName)
{

	return  get<(int)Skill::GETTYPE::CURRENTTIME>(mapSkills_[stateName]);
}

bool Skill::getIsPercent(const wstring stateName)
{
	return get<(int)Skill::GETTYPE::ISPERCENT>(mapSkills_[stateName]);
}

float Skill::getDamageValue(const wstring stateName)
{
	return get<(int)Skill::GETTYPE::DAMAGEVALUE>(mapSkills_[stateName]);
}

void Skill::initialize()
{
}

void Skill::update()
{
	for (auto& iter = mapSkills_.begin(); iter != mapSkills_.end(); ++iter)
	{
		//��Ÿ�� ���� ��
		if (get<(int)Skill::GETTYPE::CURRENTTIME>(iter->second) < get<(int)Skill::GETTYPE::COOLTIME>(iter->second))
			get<(int)Skill::GETTYPE::CURRENTTIME>(iter->second) += TimeManager::getInstance()->getDeltaTime();
	}
}

void Skill::lateUpdate()
{
}

void Skill::render()
{
}

void Skill::release()
{
}
