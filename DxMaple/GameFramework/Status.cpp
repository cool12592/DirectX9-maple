#include "stdafx.h"
#include "Status.h"
#include "TimeManager.h"
#include "GameManager.h"
Status::Status():maxHp_(0),hp_(0),maxMp_(0),mp_(0),physicalAttack_(0),physicalDefense_(0),classType_(CLASSTYPE::FIGHTER),attackSpeed_(DEFAULT_ANIMATION_SPEED),castingSpeed_(DEFAULT_ANIMATION_SPEED),moveSpeed_(DEFAULT_MOVE_SPEED),isSuperArmor_(false),superArmorTimer_(0.f),superArmorDuration_(DEFAULT_SUPERARMOR_DURATION),invincible_(false)
{
}

Status::~Status()
{
}

void Status::damaged(double physicalDamage, double magicalDamage, Entity* attackboxEntity)
{
	if (invincible_)
		return;

	hp_ -= (physicalDamage - physicalDefense_);
	hp_ -= (magicalDamage - magicalDefense_);

	if (hp_ < 0)
		hp_ = 0;

	damagedFunction_(attackboxEntity);
	
	
}

void Status::downed(double physicalDamage, double magicalDamage, Entity* attackboxEntity)
{
	if (invincible_)
		return;

	hp_ -= (physicalDamage - physicalDefense_);
	hp_ -= (magicalDamage - magicalDefense_);

	if (hp_ < 0)
		hp_ = 0;

	downedFunction_(attackboxEntity);
}

void Status::stunned(double physicalDamage, double magicalDamage, Entity* attackboxEntity)
{
	if (invincible_)
		return;
	hp_ -= (physicalDamage - physicalDefense_);
	hp_ -= (magicalDamage - magicalDefense_);

	if (hp_ < 0)
		hp_ = 0;

	stunnedFunction_(attackboxEntity);
}

void Status::setStatus(CLASSTYPE classType, double maxHp, double maxMp, double physicalAttack, double physicalDefense, double magicalAttack, double magicalDefense, double moveSpeed, double attackSpeed, double castingSpeed)
{
	classType_ = classType;
	maxHp_ = maxHp;
	hp_ = maxHp;
	maxMp_ = maxMp;
	mp_ = maxMp;
	physicalAttack_ = physicalAttack;
	physicalDefense_ = physicalDefense;
	magicalAttack_ = magicalAttack;
	magicalDefense_ = magicalDefense;
	moveSpeed_ = moveSpeed;
	attackSpeed_ = attackSpeed;
	castingSpeed_ = castingSpeed;
}

void Status::useMp(double spendMp)
{
	mp_ = clamp(mp_ - spendMp, 0.0, maxMp_);
}

void Status::Recover(double hp, double mp)
{
	hp_ = clamp(hp_ + hp, 0.0, maxHp_);
	mp_ = clamp(mp_ + mp, 0.0, maxMp_);
}

void Status::turnOnSuperarmor(float duration)
{
	isSuperArmor_ = true;
	superArmorTimer_ = 0.f;
	superArmorDuration_ = duration;
}

void Status::turnOffSuperarmor()
{
	isSuperArmor_ = false;
}

void Status::turnOnAttackUp(float duration)
{
	isAttackUp_ = true;
	attackUpTimer_ = 0.f;
	attackUpDuration_ = duration;
}

void Status::turnOffAttackUp()
{
	isAttackUp_ = false;

}

void Status::DamageFont(float damage,int multiHit, bool isCritical, int kind)
{
	zCount -= 0.001f;
	fontQue.emplace(make_pair(damage, multiHit));
	CriQue.emplace(isCritical);
	isTimer_ = true;
	KindQue.emplace(kind);
	
}



void Status::initialize()
{
}

void Status::update()
{
	if (isSuperArmor_)
	{
		if (superArmorTimer_ > superArmorDuration_)
		{
			isSuperArmor_ = false;
		}
		superArmorTimer_ += TimeManager::getInstance()->getDeltaTime();
	}

	if (isAttackUp_)
	{
		if (attackUpTimer_ > attackUpDuration_)
		{
			isAttackUp_ = false;
		}
		attackUpTimer_ += TimeManager::getInstance()->getDeltaTime();
	}



	if (isTimer_)
	{
		damageFontTime_ += TimeManager::getInstance()->getDeltaTime();
		if (damageFontTime_ >= 0.1f)
		{


			//우선 피격사운드및 이펙트
			//기본
			if (KindQue.front() == 0)
			{
				
				GameManager::getInstance()->getPlayer()->getComponent<Sound>().PlaySoundEffect(10);
				hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/knockSmall");

			}
			//shine
			if (KindQue.front() == 1)
			{
				GameManager::getInstance()->getPlayer()->getComponent<Sound>().PlaySoundEffect(12);
				hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/hit/shine3");

			}
			if (KindQue.front() == 2)
			//왕표창
			{
				GameManager::getInstance()->getPlayer()->getComponent<Sound>().PlaySoundEffect(13);
				hitEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/maplechar/bigsurigum/hiteffect");

			}
			
		

			KindQue.pop();
			

			hitEffect->getComponent<CommonEffect>().setEffect(entity->getComponent<Transform>().position_ + _vec3(0.f, 0.f, -1.f), 0.f, 1.f);



			//큐를 팝함
		
			if (CriQue.front())
			{
				GameManager::getInstance()->makeDamageFont(DNFUI::Cnum0,fontQue.front().first, entity->getComponent<Transform>().position_ + _vec3(0, 100.f + 30.f * fontQue.front().second, zCount));
				fontQue.pop();
				CriQue.pop();
			

			}
			else
			{
				GameManager::getInstance()->makeDamageFont(DNFUI::Hnum0,fontQue.front().first, entity->getComponent<Transform>().position_ + _vec3(0, 100.f + 30.f * fontQue.front().second, zCount));
				fontQue.pop();
				CriQue.pop();
			}

			damageFontTime_ = 0.f;
			if (fontQue.empty())
				isTimer_ = false;
		}
	}



}

void Status::lateUpdate()
{
}

void Status::render()
{
}

void Status::release()
{
}
