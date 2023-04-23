#include "stdafx.h"
#include "HornTailRightState.h"
#include "ComponentsHeader.h"
#include "GameManager.h"
#include "MonoBehaviour.h"
USING(HornTailRightState)

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
	anim.setUserPivot(_vec2(-170.f, -202.f));
}

void Attack1::update(Entity* entity)
{

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	if ((int)anim.getCurrentIndex() == 13)
	{
		entity->getComponent<HornTailRight>().
			getAttackBox()->getComponent<AttackBox>().
			activateAttackBox(L"right_hornTail_breath", entity);
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

	entity->getComponent<HornTailRight>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();
}


void Attack2::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.setUserPivot(_vec2(-45, -70.f));
	anim.changeCurrentSprite(L"skill");


	
	//anim.setUserPivot(_vec2(5.f, -73.f));
	int random = rand() % 2;
	if (random == 0)
	{
		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/rightattack2effect");
		for (int i = 0; i < 10; i++)
		{
			effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/rightattack2effect");
			effect->getComponent<CommonEffect>().setEffect(entity, false, _vec3(-900.f + i * 150.f, 0.f, 0.f), 0.f, 1.f);
			effect->getComponent<CommonEffect>().setAttackBox(L"right_hornTail_skill", 26, _vec3(0.f, -200.f, 0.f));

			
		}
	}
	else
	{
		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/rightattack2effect");
		for (int i = 0; i < 10; i++)
		{
			effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/rightattack2effect");
			effect->getComponent<CommonEffect>().setEffect(entity, false, _vec3(-900.f+75.f + i * 150.f, 0.f, 0.f), 0.f, 1.f);
			effect->getComponent<CommonEffect>().setAttackBox(L"right_hornTail_skill", 26, _vec3(0.f,-200.f,0.f));


			
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


}