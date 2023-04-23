#include "stdafx.h"
#include "HornTailState.h"
#include "ComponentsHeader.h"
#include "GameManager.h"
#include "MonoBehaviour.h"

USING(HornTailState)

Idle Idle::instance;

Attack1 Attack1::instance;
Attack2 Attack2::instance;
Die Die::instance;
HornTailDie HornTailDie::instance;
void Idle::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeCurrentSprite(L"idle");
	anim.setUserPivot(_vec2(0.f, 0.f));
}

void Idle::update(Entity* entity)
{


}

void Idle::exit(Entity* entity)
{
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Attack1::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.changeCurrentSprite(L"breath1");

	anim.setUserPivot(_vec2(0.f, -130.f));
}

void Attack1::update(Entity* entity)
{

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if ((int)anim.getCurrentIndex() == 17)
	{
		entity->getComponent<HornTail>().
			getAttackBox()->getComponent<AttackBox>().
			activateAttackBox(L"mid_hornTail_breath", entity);
	}

	if (anim.getCurrentAnim() == L"breath1" && anim.isSpriteEnd())
		anim.changeCurrentSprite(L"breath2");


	if (anim.getCurrentAnim() == L"breath2" && anim.isSpriteEnd())
	{
		stateMachine.transitionState(IDLE);
	}

}

void Attack1::exit(Entity* entity)
{

	entity->getComponent<HornTail>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();
}




void Attack2::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.changeCurrentSprite(L"skill");

	anim.setUserPivot(_vec2(5.f, -73.f));

	vector<_vec3>firePostion = entity->getComponent<HornTail>().getFirePosition();


	shared_ptr<Entity> effect;//= GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/leftattack2effect");
	for (int i = 0; i < firePostion.size(); i++)
	{
		effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/midattack2effect");
		effect->getComponent<CommonEffect>().setEffect(false, false, firePostion[i], 0.f, 1.f);
		effect->getComponent<CommonEffect>().setAttackBox(L"mid_hornTail_skill", 24,_vec3(0.f,0.f,0.f));
		effect->getComponent<CommonEffect>().setAttackEnity(entity);

	}

	if (entity->getComponent<HornTail>().page_ == 2)
	{
		vector<_vec3>icePosition = entity->getComponent<HornTail>().getIcePosition();


		for (int i = 0; i < icePosition.size(); i++)
		{
			effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/midattack2effect");
			effect->getComponent<CommonEffect>().setEffect(false, false, icePosition[i]+_vec3(0.f, -65.f, 0.f), 0.f, 1.f);
			effect->getComponent<CommonEffect>().setAttackBox(L"mid_hornTail_skill", 24, _vec3(0.f, 0.f, 0.f));
			effect->getComponent<CommonEffect>().setAttackEnity(entity);

		}
	}
}

void Attack2::update(Entity* entity)
{

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	if (anim.isSpriteEnd())
	{
		stateMachine.transitionState(IDLE);
	}

}

void Attack2::exit(Entity* entity)
{


}



void Die::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeCurrentSprite(L"die");
}

void Die::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (anim.isSpriteEnd())
		anim.PauseAnimation();
}

void Die::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();

}


void HornTailDie::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if(entity->getComponent<HornTail>().getBody().lock()!=nullptr)
	entity->getComponent<HornTail>().getBody().lock()->setActive(false);
	if (entity->getComponent<HornTail>().getLeftHead().lock() != nullptr)
	entity->getComponent<HornTail>().getLeftHead().lock()->setActive(false);
	if (entity->getComponent<HornTail>().getRightHead().lock() != nullptr)
	entity->getComponent<HornTail>().getRightHead().lock()->setActive(false);
	anim.resumeAnimation();
	anim.changeCurrentSprite(L"die0");
	anim.setAnimationSpeed(4.f);
	entity->getComponent<Transform>().position_ = _vec3(-75.f, -230.f, 1.f);
}

void HornTailDie::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

		if (anim.isSpriteEnd())
		{
			if (anim.getCurrentAnim() == L"die6")
			{
				//anim.PauseAnimation();
				
			}
			 if (anim.getCurrentAnim() == L"die5")
				anim.changeCurrentSprite(L"die6");
			 if (anim.getCurrentAnim() == L"die4")
				anim.changeCurrentSprite(L"die5");
			 if (anim.getCurrentAnim() == L"die3")
				anim.changeCurrentSprite(L"die4");
			 if (anim.getCurrentAnim() == L"die2")
				anim.changeCurrentSprite(L"die3");
			 if (anim.getCurrentAnim() == L"die1")
				anim.changeCurrentSprite(L"die2");
			 if (anim.getCurrentAnim() == L"die0")
				anim.changeCurrentSprite(L"die1");

		}
	

}

void HornTailDie::exit(Entity* entity)
{


}