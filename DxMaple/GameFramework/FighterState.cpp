#include "stdafx.h"
#include "FighterState.h"
#include "ComponentsHeader.h"
#include "PlayerController.h"
#include "AttackBox.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "EntityManager.h"
#include "GameManager.h"
USING(FighterState)
Damaged Damaged::instance;
Downed Downed::instance;
Idle Idle::instance;
Walk Walk::instance;
Jump Jump::instance;
Dash Dash::instance;
BackStep BackStep::instance;


Flash Flash::instance;
Rope Rope::instance;
KneelDown KneelDown::instance;

Attack_1 Attack_1::instance;
Attack_2 Attack_2::instance;
Attack_3 Attack_3::instance;
Attack_4 Attack_4::instance;


Attack_Dash Attack_Dash::instance;
Attack_Jump Attack_Jump::instance;

HammerKick HammerKick::instance;
LowKick LowKick::instance;
Hosinyeongeok Hosinyeongeok::instance;
HoverStomp HoverStomp::instance;
Boonggwon Boonggwon::instance;
Ganggwon Ganggwon::instance;
BoneCrusher BoneCrusher::instance;
Jilpoonggak Jilpoonggak::instance;
RisingKnuckle RisingKnuckle::instance;
Bitdrive Bitdrive::instance;
Chulsango Chulsango::instance;
OneInchPunch OneInchPunch::instance;
PowerfulLowkick PowerfulLowkick::instance;
LighteningDance LighteningDance::instance;
QuickStanding QuickStanding::instance;


void Damaged::enter(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"damaged");
	
	tempTimer = 0.f;
}

void Damaged::update(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(1.5f, bind(&Damaged::stopEndTrigger, this, entity));
	//StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//
	//tempTimer += TimeManager::getInstance()->getDeltaTime();

	//if(tempTimer>2.f)
	//	stateMachine.transitionState(IDLE);

}

void Damaged::exit(Entity * entity)
{
	
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();
}

void Damaged::stopEndTrigger(Entity * entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(IDLE);
}

void Downed::enter(Entity* entity)
{
}

void Downed::update(Entity* entity)
{
}

void Downed::exit(Entity* entity)
{
}

void Downed::stopEndTrigger(Entity* entity)
{
}


void Idle::enter(Entity* entity) 
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"idle");
}

void Idle::update(Entity* entity)
{

	
}

void Idle::exit(Entity* entity)
{
}

void Walk::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"walk");
}

void Walk::update(Entity* entity)
{
	Status& status = entity->getComponent<Status>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	rigidbody.setForce(rigidbody.direction_ * (float)status.moveSpeed_);

	if (rigidbody.getCurrentSpeed() <= 0.1f)
		stateMachine.transitionState(IDLE);

	if (rigidbody.velocity_.x > 1.f)
		anim.setRight(false);
	else if (rigidbody.velocity_.x < -1.f)
		anim.setRight(true);
}

void Walk::exit(Entity* entity)
{
}

void Jump::enter(Entity* entity)
{
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	
	anim.changeMotion(L"jump_in");
	if(rigidbody.onGround_ || rigidbody.inRope_)
	rigidbody.addForce(_vec3(0.f, JUMP_FORCE, 0.f));
	

	entity->getComponent<Sound>().PlaySoundEffect(2);
	

}

void Jump::update(Entity* entity)
{
	Status& status = entity->getComponent<Status>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	//if(anim.isSpriteEnd())
		//anim.changeMotion(L"jump_loop");

	rigidbody.setForce(rigidbody.direction_ * (float)status.moveSpeed_);


	if (rigidbody.velocity_.x > 1.f)
		anim.setRight(false);
	else if (rigidbody.velocity_.x < -1.f)
		anim.setRight(true);
	
	if (rigidbody.onGround_)
		stateMachine.transitionState(IDLE);
}

void Jump::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"jump_out");
}


void Dash::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"dash");
	timer = 0.f;
}

void Dash::update(Entity* entity)
{
	Status& status = entity->getComponent<Status>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	rigidbody.setForce(rigidbody.direction_ * (float)status.moveSpeed_*3.f);

	if (rigidbody.getCurrentSpeed() <= 0.1f)
		stateMachine.transitionState(IDLE);

	if (rigidbody.velocity_.x > 1.f)
		anim.setRight(false);
	else if (rigidbody.velocity_.x < -1.f)
		anim.setRight(true);

	if (timer > 0.2f)
	{
		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/dash_1");
		effect->getComponent<CommonEffect>().setEffect(entity, false, L"dash_1");
		effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/dash_2");
		effect->getComponent<CommonEffect>().setEffect(entity, false, L"dash_2");
		effect->getComponent<AtlasAnimation>().setRight(!effect->getComponent<AtlasAnimation>().getIsRight());
		timer = 0.f;

	//	entity->getComponent<Sound>().PlaySoundEffect(0);
	}
	timer += TimeManager::getInstance()->getDeltaTime();
}

void Dash::exit(Entity* entity)
{
}


void Attack_1::enter(Entity* entity)
{
	Status& status = entity->getComponent<Status>();

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	_vec3 pos = entity->getComponent<Transform>().position_;
	anim.setAnimationSpeed(float(status.attackSpeed_));
	int ind = rand() % 3;

	if(ind==0)
	anim.changeMotion(L"attack_normal_1");
	else if(ind==1)
		anim.changeMotion(L"attack_normal_2");
	else
		anim.changeMotion(L"attack_normal_3");


	entity->getComponent<Sound>().PlaySoundEffect(11);

	//_vec3 direction;
	//if (anim.getIsRight())
	//	direction = { 1.f, 0.f, 0.f };
	//else
	//	direction = { -1.f, 0.f, 0.f };

	//rigidbody.setForce((rigidbody.direction_+direction) * ATTACK_ACCEL);

	entity->getComponent<PlayerController>().AttackStart();

	/*wstring surigumName = entity->getComponent<PlayerController>().playerSurigumName_;

	if (!anim.getIsRight())
	{
		shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(true,pos + _vec3(100.f, 0.f, 0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

	    surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false,pos+_vec3(50.f,0.f,0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false,pos , anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

	}
	else
	{
		shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(true,pos - _vec3(100.f, 0.f, 0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false,pos - _vec3(50.f, 0.f, 0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false,pos , anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);
	}


	if (entity->getComponent<BUFF>().nowShadow)
	{
		if (!anim.getIsRight())
		{
			shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos + _vec3(85.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos + _vec3(35.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos + _vec3(-15.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

		}
		else
		{
			shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos - _vec3(85.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos - _vec3(35.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos - _vec3(-15.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);
		}
	}*/






	Transform& transform = entity->getComponent<Transform>();
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/effect1");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(-5.f, -5.f, 0.f), 0.f, 1.f);
	


	//entity->getComponent<Sound>().PlaySoundEffect(4);
	//entity->getComponent<Sound>().PlaySoundEffect(1);

}

void Attack_1::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
	{
		anim.stopAnimation(0.1f, bind(&Attack_1::stopEndTrigger, this, entity));
		
	}
	

}

void Attack_1::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();


}

void Attack_1::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(IDLE);
}

void Attack_2::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"attack_normal_2");

	/*_vec3 direction;
	if (anim.getIsRight())
		direction = { 1.f, 0.f, 0.f };
	else
		direction = { -1.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);*/

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.activateAttackBox(L"player_attack_2", entity);

	//entity->getComponent<Sound>().PlaySoundEffect(5);

}

void Attack_2::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(CAN_ATTACK_DELAY, bind(&Attack_2::stopEndTrigger, this, entity));
}

void Attack_2::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Attack_2::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(IDLE);
}

void Attack_3::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"attack_normal_3");

	/*_vec3 direction;
	if (anim.getIsRight())
		direction = { 1.f, 0.f, 0.f };
	else
		direction = { -1.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);*/

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.activateAttackBox(L"player_attack_3", entity);

//	entity->getComponent<Sound>().PlaySoundEffect(6);

}

void Attack_3::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(CAN_ATTACK_DELAY, bind(&Attack_3::stopEndTrigger, this, entity));
}

void Attack_3::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Attack_3::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(IDLE);
}

void Attack_4::enter(Entity* entity)
{
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"attack_normal_4");

	/*_vec3 direction;
	if (anim.getIsRight())
		direction = { 1.f, 0.f, 0.f };
	else
		direction = { -1.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);*/

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.activateAttackBox(L"player_attack_4", entity);

	//entity->getComponent<Sound>().PlaySoundEffect(2);

}

void Attack_4::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd())
		stateMachine.transitionState(IDLE);
}

void Attack_4::exit(Entity* entity)
{
	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Attack_Dash::enter(Entity* entity)
{
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"attack_dash");

	_vec3 direction;
	if (anim.getIsRight())
		direction = { 1.f, 0.f, 0.f };
	else
		direction = { -1.f, 0.f, 0.f };

	rigidbody.setForce(direction * ATTACK_ACCEL);

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.activateAttackBox(L"player_attack_dash", entity);

//	entity->getComponent<Sound>().PlaySoundEffect(22);

}

void Attack_Dash::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(0.2f, bind(&Attack_Dash::stopEndTrigger, this, entity));
}

void Attack_Dash::exit(Entity* entity)
{
	entity->getComponent<AtlasAnimation>().resumeAnimation();

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Attack_Dash::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	stateMachine.transitionState(IDLE);
}

void Attack_Jump::enter(Entity* entity)
{

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	_vec3 pos = entity->getComponent<Transform>().position_;
	anim.setAnimationSpeed(6.f);
	int ind = rand() % 3;

	if (ind == 0)
		anim.changeMotion(L"attack_normal_1");
	else if (ind == 1)
		anim.changeMotion(L"attack_normal_2");
	else
		anim.changeMotion(L"attack_normal_3");

	wstring surigumName = entity->getComponent<PlayerController>().playerSurigumName_;

	if (!anim.getIsRight())
	{
		shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(true, pos + _vec3(100.f, 0.f, 0.f), anim.getIsRight(),surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false, pos + _vec3(50.f, 0.f, 0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false, pos, anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

	}
	else
	{
		shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(true, pos - _vec3(100.f, 0.f, 0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false, pos - _vec3(50.f, 0.f, 0.f), anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);

		surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
		surigum->addComponent<Bullet>(false, pos, anim.getIsRight(), surigumName);
		EntityManager::getInstance()->insertEntity(surigum);
	}

	if (entity->getComponent<BUFF>().nowShadow)
	{
		if (!anim.getIsRight())
		{
			shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos + _vec3(85.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos + _vec3(35.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos + _vec3(-15.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

		}
		else
		{
			shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos - _vec3(85.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos - _vec3(35.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);

			surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
			surigum->addComponent<Bullet>(false, pos - _vec3(-15.f, 10.f, 0.f), anim.getIsRight(), surigumName);
			EntityManager::getInstance()->insertEntity(surigum);
		}
	}



	Transform& transform = entity->getComponent<Transform>();
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/effect1");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(-5.f, -5.f, 0.f), 0.f, 1.f);

}

void Attack_Jump::update(Entity* entity)
{
	Status& status = entity->getComponent<Status>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();



	if (anim.isSpriteEnd())
		anim.changeMotion(L"attack_jump_loop");

	rigidbody.setForce(rigidbody.direction_ * (float)status.moveSpeed_);


	//if (attackBox.checkHit())
	//{
	//	stateMachine.changeState(L"jump");
	//}

	if (rigidbody.onGround_)
		stateMachine.transitionState(IDLE);
}

void Attack_Jump::exit(Entity* entity)
{

}

void HammerKick::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.setAnimationSpeed(6.f);


	anim.changeMotion(L"attack_normal_3");


	 effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/bigsurigum/starteffect");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(0.F, 0.f, 0.f), 0.f, 1.f);
	effect->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);

	
	shared_ptr<Entity> bigSurigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	bigSurigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
	if(!anim.getIsRight())
		bigSurigum->addComponent<BigSuriGum>( entity->getComponent<Transform>().position_ + _vec3(100.f, 0.f, 0.f), anim.getIsRight());
	else
		bigSurigum->addComponent<BigSuriGum>(entity->getComponent<Transform>().position_ + _vec3(-100.f, 0.f, 0.f), anim.getIsRight());

	EntityManager::getInstance()->insertEntity(bigSurigum);

	entity->getComponent<Sound>().PlaySoundEffect(15);

}

void HammerKick::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	

	


	if (anim.isSpriteEnd())
		stateMachine.changeState(L"idle");
}

void HammerKick::exit(Entity* entity)
{
	first = true;
	
}

void LowKick::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	anim.changeMotion(L"damaged");


	
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/shine1");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(0.F, 120.f, 0.f), 0.f, 1.f);


	 EnemyList = EntityManager::getInstance()->getEntityList(Entity::ENTITYTYPE::ENEMY);
	
	 entity->getComponent<Sound>().PlaySoundEffect(14);
}

void LowKick::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	for (auto &enemy : *EnemyList)
	{
		if (!enemy->hasComponent<CommonEnemy>())
			continue;

		if (!enemy->hasComponent<Transform>())
			continue;
		Transform& enemyTransform = enemy->getComponent<Transform>();
		Transform& playerTransform = entity->getComponent<Transform>();


		_vec3 distVec =(enemyTransform.position_-playerTransform.position_  );
		float distance = D3DXVec3Length(&distVec);
		
		if (distance > 800.f)
			continue;

		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/shine2");


		if (!entity->getComponent<AtlasAnimation>().getIsRight())
			distVec.x = -distVec.x;
		effect->getComponent<CommonEffect>().setEffect(entity, false,_vec3((distVec.x)+0.f, (distVec.y)+140.f,0.f), 0.f, 1.f);
		effect->getComponent<CommonEffect>().setAttackEnity(entity);
		effect->getComponent<CommonEffect>().setAttackBox(L"shine", 10, _vec3(0.f, 0.f, 0.f));

	}
	stateMachine.changeState(L"idle");

	
}

void LowKick::exit(Entity* entity)
{
	alreadyHitEnemies.clear();
}

Entity * LowKick::getCloseEnemy(Entity * player)
{

	alreadyHitEnemies.erase(remove_if(alreadyHitEnemies.begin(), alreadyHitEnemies.end(), [](weak_ptr<Entity> enemy)
	{
		if (enemy.expired())
			return true;
		else
			return false;
	}), alreadyHitEnemies.end());
	vector<shared_ptr<Entity>>* enemies = EntityManager::getInstance()->getEntityList(Entity::ENTITYTYPE::ENEMY);
	for (auto& enemy : *enemies)
	{
		auto& find_iter = alreadyHitEnemies.begin();
		for (; find_iter != alreadyHitEnemies.end(); ++find_iter)
		{
			if ((*find_iter).lock().get() == enemy.get())
				break;
		}
		if (alreadyHitEnemies.end() == find_iter)
		{
			if (!enemy->hasComponent<Transform>())
				continue;
			if (!enemy->hasComponent<CommonEffect>())
				continue;

			Transform& enemyTransform = enemy->getComponent<Transform>();
			Transform& playerTransform = player->getComponent<Transform>();

			_vec3 distVec = enemyTransform.position_ - playerTransform.position_;
			float distance = D3DXVec3Length(&distVec);

			if (distance <= 800.f)
			{
				alreadyHitEnemies.emplace_back(enemy);
				return enemy.get();
			}
		}
	}
	return nullptr;
}

void Hosinyeongeok::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	anim.changeMotion(L"damaged");



	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/aa");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(35.F, 30.f, -10.f), 0.f, 1.f);
	//effect->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;// D3DBLEND_DESTALPHA;
	shared_ptr<Entity> effect2 = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/shadowPartnel2");
	effect2->getComponent<CommonEffect>().setEffect(entity, true, _vec3(35.F, 30.f, 101.f), 0.f, 1.f);
//	effect2->getComponent<AtlasAnimation>().blendEnable_ = false; D3DBLEND_DESTALPHA;
	entity->getComponent<BUFF>().onBuff(L"shadow");

	entity->getComponent<Sound>().PlaySoundEffect(7);

}

void Hosinyeongeok::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd())
		stateMachine.changeState(L"idle");
}

void Hosinyeongeok::exit(Entity* entity)
{

}

void Hosinyeongeok::stopEndTrigger(Entity* entity)
{	
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"idle");
}

void HoverStomp::enter(Entity * entity)
{

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	anim.changeMotion(L"damaged");



	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/booster");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(0.F, 30.f, 0.f), 0.f, 1.f);
	entity->getComponent<BUFF>().onBuff(L"boast");
	entity->getComponent<Sound>().PlaySoundEffect(3);
}

void HoverStomp::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd())
		stateMachine.changeState(L"idle");
}

void HoverStomp::exit(Entity* entity)
{


}

void Boonggwon::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	anim.changeMotion(L"damaged");


	
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/haste");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(0.F, 50.f, 0.f), 0.f, 1.f);

	entity->getComponent<BUFF>().onBuff(L"haist");
	
	entity->getComponent<Sound>().PlaySoundEffect(4);

}

void Boonggwon::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd())
		stateMachine.changeState(L"idle");
}

void Boonggwon::exit(Entity* entity)
{

}

void Boonggwon::stopEndTrigger(Entity* entity)
{

}

void Ganggwon::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();


	anim.changeMotion(L"damaged");


	
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/darksite");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(0.F, 25.f, 0.f), 0.f, 1.f);
	entity->getComponent<BUFF>().onBuff(L"darksite");

	entity->getComponent<Sound>().PlaySoundEffect(6);
}

void Ganggwon::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd())
		stateMachine.changeState(L"idle");
}

void Ganggwon::exit(Entity* entity)
{

}


void BoneCrusher::enter(Entity* entity)
{
	entity->getComponent<AtlasAnimation>().changeMotion(L"bonecrusher");
	entity->getComponent<AtlasAnimation>().stopAnimation(0.6f, bind(&BoneCrusher::stopEndTriggerReady, this, entity));
	

	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/bonecrusher");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"bonecrusher");
	//entity->getComponent<Sound>().PlaySoundEffect(19);

	effectCreated = false;
}

void BoneCrusher::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (anim.isSpriteEnd() && !anim.isStopState())
	{
		entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().deactivate();
		anim.stopAnimation(0.5f, bind(&BoneCrusher::stopEndTrigger, this, entity));
	}

	if (entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().checkHit() && !effectCreated)
	{
		_vec3 collidePos = entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().getCollideEntityPosition();

		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/crushEffect");
		effect->getComponent<AtlasAnimation>().setRight(anim.getIsRight());

		if (effect->getComponent<AtlasAnimation>().getIsRight())
			effect->getComponent<CommonEffect>().setEffect(collidePos + _vec3(0.f,100.f,0.f), 0.f, 1.f);
		else
			effect->getComponent<CommonEffect>().setEffect(collidePos + _vec3(0.f, 100.f, 0.f), 0.f, 1.f);

		effectCreated = true;
	}
}

void BoneCrusher::exit(Entity* entity)
{
}

void BoneCrusher::stopEndTrigger(Entity* entity)
{
	entity->getComponent<StateMachine>().changeState(L"idle");
}

void BoneCrusher::stopEndTriggerReady(Entity* entity)
{
	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		activateAttackBox(L"player_bonecrusher", entity, L"bonecrusher");
}

void Jilpoonggak::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	entity->getComponent<AtlasAnimation>().changeMotion(L"jilpoonggak");
	entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(DEFAULT_USER_PIVOT_X, DEFAULT_USER_PIVOT_Y + 50.f));
	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		activateAttackBox(L"player_jilpoonggak", entity, L"jilpoonggak");
	
	if (entity->getComponent<AtlasAnimation>().getIsRight())
		direction = { 1.f,0.f,0.f };
	else
		direction = { -1.f,0.f,0.f };

	rotateCount = 0;

	if (effect.expired())
	{
		effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/jilpoonggak");
		effect.lock()->getComponent<AtlasAnimation>().setUserPivot(_vec2(70.f, 120.f));
		effect.lock()->getComponent<CommonEffect>().setEffect(entity, true, L"jilpoonggak");
		effect.lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);
	}
	
}

void Jilpoonggak::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	if (rotateCount > JILPOONGGAK_ROTATE_COUNT)
		stateMachine.changeState(L"idle");

	rigidbody.setForce(direction * ATTACK_ACCEL);

	if (anim.isSpriteEnd())
	{
		entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().
			deactivate();

		anim.setRight(!anim.getIsRight());
		anim.changeMotion(L"jilpoonggak");

		entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().
			activateAttackBox(L"player_jilpoonggak", entity, L"jilpoonggak");

		++rotateCount;
	}
}

void Jilpoonggak::exit(Entity* entity)
{
	entity->getComponent<Status>().turnOffSuperarmor();

	entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(DEFAULT_USER_PIVOT_X, DEFAULT_USER_PIVOT_Y));

	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();

	if (!effect.expired())
		effect.lock()->getComponent<CommonEffect>().deactivate();
}

void RisingKnuckle::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	//entity->getComponent<Rigidbody>().setForce(_vec3(0.f, RISINGKNUCKLE_ACCEL, 0.f));
	entity->getComponent<AtlasAnimation>().changeMotion(L"risingknuckle_ready");
	
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/risingknuckle_1");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"risingknuckle_1");
	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/risingknuckle_2");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"risingknuckle_2");
	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/risingknuckle_3");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"risingknuckle_3");
	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/risingknuckle_4");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"risingknuckle_4");

	//entity->getComponent<Sound>().PlaySoundEffect(20);

	topReached = false;
	onGround = false;
	timer = 0.f;
}

void RisingKnuckle::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	if (wcscmp(anim.getCurrentMotionName().c_str(), L"risingknuckle_ready") == 0)
	{
		if (anim.isSpriteEnd())
		{
			anim.changeMotion(L"risingknuckle_up");
			rigidbody.setForce(_vec3(0.f, RISINGKNUCKLE_UP_ACCEL, 0.f));
		}
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"risingknuckle_up") == 0)
	{
		entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().
			activateAttackBox(L"player_risingknuckle_up", entity, L"risingknuckle");

		if (!topReached)
		{
			if (rigidbody.velocity_.y < 0.f)
			{
				entity->getComponent<PlayerController>().
					getAttackBox()->getComponent<AttackBox>().
					deactivate();
				anim.changeMotion(L"risingknuckle_down");
				topReached = true;
			}
		}
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"risingknuckle_down") == 0)
	{
		rigidbody.setForce(_vec3(0.f, RISINGKNUCKLE_DOWN_ACCEL, 0.f));
		if (anim.isSpriteEnd())
		{
			anim.stopAnimation(INFINITE_STOP, bind(&RisingKnuckle::stopEndTrigger, this, entity));

			entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().
				activateAttackBox(L"player_risingknuckle_down", entity, L"risingknuckle");
		}

		if (rigidbody.onGround_)
		{
			if (!onGround)
			{
				shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/risingknuckle_5");
				effect->getComponent<CommonEffect>().setEffect(entity, false, L"risingknuckle_5");
				effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/risingknuckle_6");
				effect->getComponent<CommonEffect>().setEffect(entity, false, L"risingknuckle_6");
				onGround = true;
			}

			if(timer>0.5f)
				entity->getComponent<StateMachine>().changeState(L"idle");
			timer += TimeManager::getInstance()->getDeltaTime();
		}

	}
	
	

}

void RisingKnuckle::exit(Entity* entity)
{
	entity->getComponent<Status>().turnOffSuperarmor();

	entity->getComponent<AtlasAnimation>().resumeAnimation();
	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();
}

void RisingKnuckle::stopEndTrigger(Entity* entity)
{
	//entity->getComponent<StateMachine>().changeState(L"idle");

}

void LighteningDance::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	hitCount = 0;
	timer = LIGHTENINGDANCE_DELAY;
	effectCreated = false;
	angle = 0.f;

	//entity->getComponent<Sound>().PlaySoundEffect(17);

}

void LighteningDance::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Transform& transform = entity->getComponent<Transform>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (timer < LIGHTENINGDANCE_DELAY)
	{

		if (timer >= LIGHTENINGDANCE_DELAY / 2.f)
		{

			entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().
				deactivate();
		}
		else
		{
			if (entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().checkHit() && !effectCreated)
			{
				_vec3 hitPos = entity->getComponent<PlayerController>().
					getAttackBox()->getComponent<AttackBox>().getCollideEntityPosition();

				shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_hit");
				effect->getComponent<AtlasAnimation>().setUserPivot(_vec2(120.f, 180.f));
				effect->getComponent<CommonEffect>().setEffect(hitPos, 0.f, 1.f);
				effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_hit2");
				effect->getComponent<AtlasAnimation>().setUserPivot(_vec2(0.f, 40.f));
				effect->getComponent<CommonEffect>().setEffect(hitPos, 0.f, 1.f);
				effectCreated = true;
			}
		}
		
		timer += TimeManager::getInstance()->getDeltaTime();
	}
	else
	{
		if (hitCount >= LIGHTENINGDANCE_MAX_HITCOUNT)
		{
			stateMachine.changeState(L"idle");
		}

		Entity* enemy = getCloseEnemy(entity);
		if (nullptr != enemy && enemy->hasComponent<AtlasAnimation>() && enemy->hasComponent<Transform>())
		{

			AtlasAnimation& enemyAnim = enemy->getComponent<AtlasAnimation>();
			Transform& enemyTransform = enemy->getComponent<Transform>();


			_vec3 direction = enemyTransform.position_ - transform.position_;
			_vec3 middlePosition = (enemyTransform.position_ + transform.position_) / 2.f;
			angle = ws::Math::calculateAngle2D(_vec3(1.f, 0.f, 0.f), direction);
			float length = D3DXVec3Length(&direction);

			shared_ptr<Entity> effect;
			if (length < 70.f)
				effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_70");
			else if (length < 150.f)
				effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_150");
			else if (length < 230.f)
				effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_230");
			else
				effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_310");

			effect->getComponent<CommonEffect>().setEffect(middlePosition+_vec3(0.f,40.f,0.f), angle, 1.f);


			if (enemyAnim.getIsRight())
				transform.position_ = enemyTransform.position_ + _vec3(50.f, 0.f, 0.f);
			else
				transform.position_ = enemyTransform.position_ - _vec3(50.f, 0.f, 0.f);

			anim.setRight(!enemyAnim.getIsRight());
			if(rand()%2==0)
				anim.changeMotion(L"lighteningdance_1");
			else
				anim.changeMotion(L"lighteningdance_2");

			entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().
				activateAttackBox(L"player_lighteningdance",entity,L"lighteningdance");

			effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/lighteningdance_kick");
			effect->getComponent<CommonEffect>().setEffect(entity, false, L"lighteningdance_kick");

		}
		else
		{
			stateMachine.changeState(L"idle");
		}

		

		++hitCount;
		timer = 0.f;
		effectCreated = false;
	}

	

}

void LighteningDance::exit(Entity* entity)
{
	//entity->getComponent<AtlasAnimation>().resumeAnimation();
	entity->getComponent<Status>().turnOffSuperarmor();

	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();
}

Entity* LighteningDance::getCloseEnemy(Entity* player)
{
	alreadyHitEnemies.erase(remove_if(alreadyHitEnemies.begin(), alreadyHitEnemies.end(), [](weak_ptr<Entity> enemy)
		{
			if (enemy.expired())
				return true;
			else
				return false;
		}), alreadyHitEnemies.end());
	vector<shared_ptr<Entity>>* enemies = EntityManager::getInstance()->getEntityList(Entity::ENTITYTYPE::ENEMY);
	for (auto& enemy : *enemies)
	{
		auto& find_iter = alreadyHitEnemies.begin();
		for (; find_iter !=alreadyHitEnemies.end();++find_iter)
		{
			if ((*find_iter).lock().get() == enemy.get())
				break;
		}
		if (alreadyHitEnemies.end() == find_iter)
		{
			if (!enemy->hasComponent<Transform>())
				continue;

			Transform& enemyTransform = enemy->getComponent<Transform>();
			Transform& playerTransform = player->getComponent<Transform>();

			_vec3 distVec = enemyTransform.position_ - playerTransform.position_;
			float distance = D3DXVec3Length(&distVec);

			if (distance <= PLAYER_SEARCH_DISTNACE)
			{
				alreadyHitEnemies.emplace_back(enemy);
				return enemy.get();
			}
		}
	}

	//이미 주변의 몬스터 다 공격함
	alreadyHitEnemies.clear();

	//한번 더 순회
	for (auto& enemy : *enemies)
	{
		auto& find_iter = alreadyHitEnemies.begin();
		for (; find_iter != alreadyHitEnemies.end(); ++find_iter)
		{
			if ((*find_iter).lock().get() == enemy.get())
				break;
		}
		if (alreadyHitEnemies.end() == find_iter)
		{
			if (!enemy->hasComponent<Transform>())
				continue;

			Transform& enemyTransform = enemy->getComponent<Transform>();
			Transform& playerTransform = player->getComponent<Transform>();

			_vec3 distVec = enemyTransform.position_ - playerTransform.position_;
			float distance = D3DXVec3Length(&distVec);

			if (distance <= PLAYER_SEARCH_DISTNACE)
			{
				alreadyHitEnemies.emplace_back(enemy);
				return enemy.get();
			}
		}
	}

	return nullptr;
}

void Bitdrive::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	entity->getComponent<AtlasAnimation>().changeMotion(L"bitdrive_in");
	timer = 0.f;

	//entity->getComponent<Sound>().PlaySoundEffect(7);
}

void Bitdrive::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	_vec3 direction;

	if (wcscmp(anim.getCurrentMotionName().c_str(), L"bitdrive_in")==0)
	{
		if (anim.isSpriteEnd() && !anim.isStopState())
			anim.stopAnimation(0.1f, bind(&Bitdrive::stopEndTrigger, this, entity));
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"bitdrive_loop") == 0)
	{
		if (timer < BITDRIVE_TIMER)
		{
			if (anim.getIsRight())
				direction = { 1.f,0.f,0.f };
			else
				direction = { -1.f,0.f,0.f };
			rigidbody.setForce(direction * BITDRIVE_ACCEL);

			if ((int)(timer * 10.f) % 2 == 0) 
			{
				entity->getComponent<PlayerController>().
					getAttackBox()->getComponent<AttackBox>().
					activateAttackBox(L"player_bitdrive", entity, L"bitdrive");

				effectDust = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/bitdrive_dust2");
				effectDust.lock()->getComponent<CommonEffect>().setEffect(entity, false, L"bitdrive_dust2");
			}
			else
				entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().
				deactivate();


			timer += TimeManager::getInstance()->getDeltaTime();
		}
		else
		{
			anim.changeMotion(L"bitdrive_out");
			if (!effect.expired())
				effect.lock()->getComponent<CommonEffect>().deactivate();
		}
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"bitdrive_out") == 0)
	{
		if (anim.isSpriteEnd() && !anim.isStopState())
		{
			anim.stopAnimation(0.1f, bind(&Bitdrive::stopEndTrigger, this, entity));
		//	entity->getComponent<Sound>().PlaySoundEffect(9);

		}
	}
	
	



}

void Bitdrive::exit(Entity* entity)
{
	entity->getComponent<Status>().turnOffSuperarmor();

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();
	if (!effect.expired())
		effect.lock()->getComponent<CommonEffect>().deactivate();
}

void Bitdrive::stopEndTrigger(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	anim.resumeAnimation();
	
	if (wcscmp(anim.getCurrentMotionName().c_str(), L"bitdrive_in") == 0)
	{
		anim.changeMotion(L"bitdrive_loop");
		effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/bitdrive");
		effect.lock()->getComponent<CommonEffect>().setEffect(entity, true, L"bitdrive");
		effect.lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"bitdrive_out") == 0)
	{
		stateMachine.changeState(L"idle");
		effectDust = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/bitdrive_dust1");
		effectDust.lock()->getComponent<CommonEffect>().setEffect(entity, false, L"bitdrive_dust1");
	}
}

void PowerfulLowkick::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);
	entity->getComponent<AtlasAnimation>().changeMotion(L"powerfullowkick_ready");
	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		activateAttackBox(L"player_powerfullowkick", entity, L"powerfullowkick");

	attackBoxPosition = entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<Transform>().position_;

	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_readyHit1");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_readyHit1");
	effect->getComponent<CommonEffect>().setOnVanish(1.f);

	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_readyHit2");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_readyHit2_left");
	effect->getComponent<CommonEffect>().setOnVanish(1.f);

	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_readyHit2");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_readyHit2_right");
	effect->getComponent<AtlasAnimation>().setRight(false);
	effect->getComponent<CommonEffect>().setOnVanish(1.f);


	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_cutin");
	effect->getComponent<CommonEffect>().setCameraLockEffect(L"powerfullowkick_cutin");

	//entity->getComponent<Sound>().PlaySoundEffect(28);

	timer = 0;
	initRight = entity->getComponent<AtlasAnimation>().getIsRight();
}

void PowerfulLowkick::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (wcscmp(anim.getCurrentMotionName().c_str(), L"powerfullowkick_ready") == 0)
	{
		if (entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().checkHit())
		{
			//맞은 녀석 멈추게 해야함
			vector<weak_ptr<Entity>>* hitEnemies = entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().getCollideEntities();

			for (auto& entity : *hitEnemies)
			{
				if (entity.expired())
					continue;
				if (entity.lock()->hasComponent<StateMachine>()&&entity.lock()->getType()==Entity::ENTITYTYPE::ENEMY)
					vecHitEnemies.emplace_back(entity);
			}


		}

		if (anim.isSpriteEnd()&&!anim.isStopState())
		{
			anim.stopAnimation(1.f, bind(&PowerfulLowkick::stopEndTriggerSecond, this, entity));
		}
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"powerfullowkick_spin") == 0)
	{
		if (timer < 0.1f)
			anim.setRight(!initRight);
		else if (timer < 0.2f)
			anim.setRight(initRight);
		else
		{
			chargeEffect[0] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_charge1");
			chargeEffect[0].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_charge1");
			chargeEffect[0].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

			chargeEffect[1] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_charge2");
			chargeEffect[1].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_charge2");
			chargeEffect[1].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

			chargeEffect[2] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_charge3");
			chargeEffect[2].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_charge3");
			chargeEffect[2].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

			chargeEffect[3] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_wind1");
			chargeEffect[3].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_wind1_right");
			chargeEffect[3].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

			chargeEffect[4] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_wind2");
			chargeEffect[4].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_wind2_right");
			chargeEffect[4].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

			chargeEffect[5] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_wind3");
			chargeEffect[5].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_wind3_right");
			chargeEffect[5].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);

			chargeEffect[6] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_wind1");
			chargeEffect[6].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_wind1_left");
			chargeEffect[6].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);
			chargeEffect[6].lock()->getComponent<AtlasAnimation>().setRight(!anim.getIsRight());

			chargeEffect[7] = GameManager::getInstance()->makeEffect( L"../AtlasFiles/Effect/fighter/powerfullowkick_wind2");
			chargeEffect[7].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_wind2_left");
			chargeEffect[7].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);
			chargeEffect[7].lock()->getComponent<AtlasAnimation>().setRight(!anim.getIsRight());
			
			chargeEffect[8] = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_wind3");
			chargeEffect[8].lock()->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_wind3_left");
			chargeEffect[8].lock()->getComponent<CommonEffect>().setDuration(INFINITE_STOP);
			chargeEffect[8].lock()->getComponent<AtlasAnimation>().setRight(!anim.getIsRight());

			//entity->getComponent<Sound>().PlaySoundEffect(27);


			anim.changeMotion(L"powerfullowkick_charge");
			timer = 0.f;
		}
		timer += TimeManager::getInstance()->getDeltaTime();


		lockDamageState();
		
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"powerfullowkick_charge") == 0)
	{


		if (InputManager::getInstance()->keyDown(DIK_Z))
		{
			anim.changeMotion(L"powerfullowkick");

			for (int i = 0; i < sizeof(chargeEffect) / sizeof(weak_ptr<Entity>); ++i)
			{
				if(!chargeEffect[i].expired())
					chargeEffect[i].lock()->getComponent<CommonEffect>().deactivate();
			}

			//각종 이펙트
			shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_startAttack");
			effect->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_startAttack");

		//	entity->getComponent<Sound>().PlaySoundEffect(25);
		//	entity->getComponent<Sound>().PlaySoundEffect(26);


		}

		if (timer < MAX_CHARGE_TIMER)
		{
			timer += TimeManager::getInstance()->getDeltaTime();
		}

		for (auto entity : vecHitEnemies)
		{
			if (entity.expired() || !entity.lock()->hasComponent<StateMachine>())
				continue;

			entity.lock()->getComponent<StateMachine>().changeState(L"damaged");
		}
	}
	else if (wcscmp(anim.getCurrentMotionName().c_str(), L"powerfullowkick") == 0)
	{
			
		if(!anim.isSpriteEnd())
			entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().
			activateAttackBox(L"player_powerfullowkick", entity, L"powerfullowkick");

		if (anim.isSpriteEnd() && !anim.isStopState())
		{
			if (entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().checkHit())
			{
				_vec3 hitPos = entity->getComponent<PlayerController>().
					getAttackBox()->getComponent<AttackBox>().getCollideEntityPosition();

				shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_hit");
				effect->getComponent<CommonEffect>().setEffect(hitPos+_vec3(0.f,50.f,0.f), 0.f, 1.f);

				universeEffect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_universe");
				universeEffect.lock()->getComponent<CommonEffect>().setCameraLockEffect(L"powerfullowkick_universe");
				universeEffect.lock()->getComponent<CommonEffect>().setOnVanish(0.f);

				zoomIn(entity);

			//	entity->getComponent<Sound>().PlaySoundEffect(24);

			}

			anim.stopAnimation(1.5f, bind(&PowerfulLowkick::stopEndTrigger, this, entity));
		}
	}
}

void PowerfulLowkick::exit(Entity* entity)
{
	for (int i = 0; i < sizeof(chargeEffect) / sizeof(weak_ptr<Entity>); ++i)
	{
		if (!chargeEffect[i].expired())
			chargeEffect[i].lock()->getComponent<CommonEffect>().deactivate();
	}
	if (!universeEffect.expired())
		universeEffect.lock()->getComponent<CommonEffect>().setOnVanish(1.f);

	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();
	entity->getComponent<AtlasAnimation>().resumeAnimation();
	entity->getComponent<Status>().turnOffSuperarmor();
}

void PowerfulLowkick::stopEndTrigger(Entity* entity)
{
	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		deactivate();

	entity->getComponent<StateMachine>().changeState(L"idle");
}

void PowerfulLowkick::stopEndTriggerSecond(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().checkHit())
	{
		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/powerfullowkick_ready");
		effect->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_ready");


		anim.changeMotion(L"powerfullowkick_spin");
		entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().deactivate();
	}
	else
		stateMachine.changeState(L"idle");

	lockHitEnemies(entity);

	////테스트용
	//shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"fighter", L"powerfullowkick_ready");
	//effect->getComponent<CommonEffect>().setEffect(entity, false, L"powerfullowkick_ready");

	//anim.changeMotion(L"powerfullowkick_spin");
	//entity->getComponent<PlayerController>().
	//	getAttackBox()->getComponent<AttackBox>().deactivate();

}

void PowerfulLowkick::lockDamageState()
{
	for (auto entity : vecHitEnemies)
	{
		if (entity.expired() || !entity.lock()->hasComponent<StateMachine>())
			continue;

		entity.lock()->getComponent<StateMachine>().changeState(L"damaged");
	}
}

void PowerfulLowkick::lockHitEnemies(Entity* entity)
{

	srand((unsigned int)time(NULL));
	

	for (auto& enemy : vecHitEnemies)
	{
		if (enemy.expired())
			continue;

		float xRand = float(rand() % 5 - 2);
		float zRand = float(rand() % 5 - 2);
		Transform& enemyTransform = enemy.lock()->getComponent<Transform>();
		enemyTransform.position_ = { attackBoxPosition.x + xRand * 10.f,0.f,attackBoxPosition.z + zRand * 10.f };

	}
}

void PowerfulLowkick::zoomIn(Entity* entity)
{
	vector<weak_ptr<Entity>>* hitEnemies = entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().getCollideEntities();

	_vec3 targetPosition = entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<Transform>().position_;
	
	entity->getComponent<Camera>().setOnZoomIn(targetPosition, 1.4f, 2.f, 1.0f);
}

void Chulsango::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"attack_dash");

	_vec3 direction;
	if (anim.getIsRight())
		direction = { 1.f, 0.f, 0.f };
	else
		direction = { -1.f, 0.f, 0.f };

	rigidbody.setForce(direction * ATTACK_ACCEL);

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.activateAttackBox(L"player_chulsango", entity,L"chulsango");

	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/chulsango_1");
	effect->getComponent<CommonEffect>().setEffect(entity, true, L"chulsango_1");
	effect = GameManager::getInstance()->makeEffect( L"../AtlasFiles/Effect/fighter/chulsango_2");
	effect->getComponent<CommonEffect>().setEffect(entity, true, L"chulsango_2");

	//entity->getComponent<Sound>().PlaySoundEffect(23);


}

void Chulsango::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(0.2f, bind(&Chulsango::stopEndTrigger, this, entity));
}

void Chulsango::exit(Entity* entity)
{
	entity->getComponent<Status>().turnOffSuperarmor();

	entity->getComponent<AtlasAnimation>().resumeAnimation();

	PlayerController& player = entity->getComponent<PlayerController>();
	auto attackBoxEntity = player.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Chulsango::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	stateMachine.changeState(L"idle");
}

void OneInchPunch::enter(Entity* entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.changeMotion(L"oneinchpunch");

	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().
		activateAttackBox(L"player_oneinchpunch", entity, L"oneinchpunch");
	attackBoxPosition = entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<Transform>().position_;
	timer = 0.f;
	lockEnemy = false;
	//시작 이펙트 생성
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/oneinchpunch_ready1");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_ready1");

	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/oneinchpunch_ready2");
	effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_ready2");
}

void OneInchPunch::update(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (timer < ONEINCHPUNCH_DELAY/2.f)
	{
		if (entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().checkHit())
		{
			if (!lockEnemy)
			{
				vector<weak_ptr<Entity>>* hitEnemies = entity->getComponent<PlayerController>().
					getAttackBox()->getComponent<AttackBox>().getCollideEntities();
				for (auto& entity : *hitEnemies)
				{
					if (entity.expired())
						continue;
					if (entity.lock()->hasComponent<StateMachine>() && entity.lock()->getType() == Entity::ENTITYTYPE::ENEMY)
						vecHitEnemies.emplace_back(entity);
				}
				lockHitEnemies(entity);
				lockEnemy = true;
			}


			entity->getComponent<PlayerController>().
				getAttackBox()->getComponent<AttackBox>().deactivate();

			//히트 이펙트 생성
			shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/oneinchpunch_hit1");
			effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_hit1");

			effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/oneinchpunch_hit2");
			effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_hit2");

			effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/fighter/oneinchpunch_hit3");
			effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_hit3");

			

			
			
		}
		lockDamageState();

	}
	else if(timer<ONEINCHPUNCH_DELAY)
	{
		entity->getComponent<PlayerController>().
			getAttackBox()->getComponent<AttackBox>().activateAttackBox(L"player_oneinchpunch",entity,L"oneinchpunch");
	}
	else
	{
		stateMachine.changeState(L"idle");
	}
	timer += TimeManager::getInstance()->getDeltaTime();
	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(INFINITE_STOP, bind(&OneInchPunch::stopEndTrigger, this, entity));
}

void OneInchPunch::exit(Entity* entity)
{
	entity->getComponent<Status>().turnOffSuperarmor();

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();

	entity->getComponent<PlayerController>().
		getAttackBox()->getComponent<AttackBox>().deactivate();

	////테스트용
	//shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"fighter", L"oneinchpunch_hit1");
	//effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_hit1");

	//effect = GameManager::getInstance()->makeEffect(L"fighter", L"oneinchpunch_hit2");
	//effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_hit2");

	//effect = GameManager::getInstance()->makeEffect(L"fighter", L"oneinchpunch_hit3");
	//effect->getComponent<CommonEffect>().setEffect(entity, false, L"oneinchpunch_hit3");
}

void OneInchPunch::stopEndTrigger(Entity* entity)
{
}

void OneInchPunch::lockDamageState()
{
	for (auto entity : vecHitEnemies)
	{
		if (entity.expired() || !entity.lock()->hasComponent<StateMachine>())
			continue;

		entity.lock()->getComponent<StateMachine>().changeState(L"damaged");
	}
}

void OneInchPunch::lockHitEnemies(Entity* entity)
{
	srand((unsigned int)time(NULL));


	for (auto& enemy : vecHitEnemies)
	{
		if (enemy.expired())
			continue;

		float xRand = float(rand() % 5 - 2);
		float zRand = float(rand() % 5 - 2);
		Transform& enemyTransform = enemy.lock()->getComponent<Transform>();
		enemyTransform.position_ = { attackBoxPosition.x + xRand * 10.f,0.f,attackBoxPosition.z + zRand * 10.f };

		Rigidbody& rigidbody = enemy.lock()->getComponent<Rigidbody>();
		ZeroMemory(&rigidbody.accelation_, sizeof(_vec3));
		ZeroMemory(&rigidbody.velocity_, sizeof(_vec3));


	}
}

void BackStep::enter(Entity* entity)
{
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.getIsRight())
		rigidbody.setForce(_vec3(-2.f, 1.f, 0.f) * BACKSTEP_FORCE);
	else
		rigidbody.setForce(_vec3(2.f, 1.f, 0.f) * BACKSTEP_FORCE);

	anim.changeMotion(L"backstep_in");

}

void BackStep::update(Entity* entity)
{
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd())
		anim.changeMotion(L"backstep_loop");

	if (rigidbody.onGround_)
		entity->getComponent<StateMachine>().changeState(L"idle");



}

void BackStep::exit(Entity* entity)
{
}

void QuickStanding::enter(Entity * entity)
{
	entity->getComponent<Status>().turnOnSuperarmor((float)INFINITE);

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"standup");

}

void QuickStanding::update(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(0.5f, bind(&QuickStanding::stopEndTringger, this, entity));
}

void QuickStanding::exit(Entity * entity)
{
	entity->getComponent<Status>().turnOffSuperarmor();

}

void QuickStanding::stopEndTringger(Entity * entity)
{
	entity->getComponent<StateMachine>().changeState(L"idle");
}


void Flash::enter(Entity * entity)
{
	

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"jump_loop");

	Transform& transform = entity->getComponent<Transform>();
	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleChar/flash");
	effect->getComponent<CommonEffect>().setEffect(entity, false, _vec3(5.f, -5.f, 0.f), 0.f, 1.f);
	effect->getComponent<AtlasAnimation>().setRight(anim.getIsRight());
	effect->getComponent<AtlasAnimation>().setAnimationSpeed(10.F);
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();


	Status& status = entity->getComponent<Status>();
	status.useMp(10);

	//if(!anim.getIsRight())
	//	rigidbody.addForce(_vec3(1000.f, 0, 0.f));
	//else
	//	rigidbody.addForce(_vec3(-1000.f, 0, 0.f));

	entity->getComponent<Sound>().PlaySoundEffect(5);
}

void Flash::update(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	StateMachine& stateMachine = entity->getComponent<StateMachine>();


	_vec3 direction;
	if (anim.getIsRight())
		direction = { -2.f, 0.f, 0.f };
	else
		direction = { +2.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);

	if (rigidbody.onGround_ || !rigidbody.getUseGravity())
		entity->getComponent<StateMachine>().changeState(L"idle");
	

}

void Flash::exit(Entity * entity)
{

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();
}

void Flash::stopEndTrigger(Entity * entity)
{

	entity->getComponent<StateMachine>().changeState(L"idle");
}



void Rope::enter(Entity * entity)
{


	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.setAnimationSpeed(5.F);
	anim.changeMotion(L"rope");
	anim.PauseAnimation();
	
	
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	rigidbody.setUseGravity(false);

	


}

void Rope::update(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Transform & transform = entity->getComponent<Transform>();

	if (InputManager::getInstance()->keyPressing(DIK_UP))
	{
		transform.position_ += _vec3(0.f, 100.f, 0.f) *TimeManager::getInstance()->getDeltaTime();
		anim.resumeAnimation();
	}

	else if (InputManager::getInstance()->keyPressing(DIK_DOWN))
	{
		transform.position_ += _vec3(0.f, -100.f, 0.f) *TimeManager::getInstance()->getDeltaTime();
		anim.resumeAnimation();
	}
	else
	{
		if(anim.getCurrentIndex()!=25)
		anim.setCurrentIndex(25);
		anim.PauseAnimation();
	}

	if (!rigidbody.inRope_)
	{
		if (rigidbody.topRope_)
			stateMachine.transitionState(IDLE);
		else
		{
			//stateMachine.transitionState(IDLE);
			stateMachine.transitionState(JUMP);
			//if(rigidbody.onGround_)
				//stateMachine.transitionState(IDLE);
		}
	}


}

void Rope::exit(Entity * entity)
{
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	rigidbody.setUseGravity(true);
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();
}



void KneelDown::enter(Entity * entity)
{


	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.changeMotion(L"kneeldown");

	anim.setUserPivot(_vec2(0.f, -15.f));






}

void KneelDown::update(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Transform & transform = entity->getComponent<Transform>();

	if (InputManager::getInstance()->keyPressing(DIK_DOWN))
	{

	}

	else if (InputManager::getInstance()->keyPressing(DIK_C))
	{
	
		stateMachine.transitionState(JUMP);
	}
	else
	{
		
		stateMachine.transitionState(IDLE);
	}
	


}

void KneelDown::exit(Entity * entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.setUserPivot(_vec2(0.f, 5.f));
}
