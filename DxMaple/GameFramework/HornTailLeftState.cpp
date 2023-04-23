#include "stdafx.h"
#include "HornTailLeftState.h"
#include "ComponentsHeader.h"
#include "GameManager.h"
#include "MonoBehaviour.h"
USING(HornTailLeftState)

Idle Idle::instance;

Attack1 Attack1::instance;
Attack2 Attack2::instance;
Die Die::instance;
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
	anim.setUserPivot(_vec2(0.f + 160.f - 37.f, 144.f / 2.f + 209.f / 2.f - 30.f - 315.f-2.f));
}

void Attack1::update(Entity* entity)
{

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();



	if((int)anim.getCurrentIndex() == 13)
	{
		entity->getComponent<HornTailLeft>().
			getAttackBox()->getComponent<AttackBox>().
			activateAttackBox(L"left_hornTail_breath", entity);
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

	entity->getComponent<HornTailLeft>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();
}




void Attack2::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.changeCurrentSprite(L"skill");

	anim.setUserPivot(_vec2(48.f, -73.f));

	vector<_vec3>icePosition= entity->getComponent<HornTailLeft>().getIcePosition();
	

	shared_ptr<Entity> effect;//= GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/leftattack2effect");
	for (int i = 0; i < icePosition.size(); i++)
	{
		effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/leftattack2effect");
		effect->getComponent<CommonEffect>().setAttackEnity(entity);
		effect->getComponent<CommonEffect>().setEffect(false, false, icePosition[i], 0.f, 1.f);
		effect->getComponent<CommonEffect>().setAttackBox(L"left_hornTail_skill", 25,_vec3(0.f,-80.f,0.f));


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


}