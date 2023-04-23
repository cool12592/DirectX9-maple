#include "stdafx.h"
#include "CrimsonState.h"
#include "ComponentsHeader.h"
#include "GameManager.h"
#include "MonoBehaviour.h"
USING(CrimsonState)

Idle Idle::instance;
Move Move::instance;

Attack Attack::instance;
Attack2 Attack2::instance;
BeHitted BeHitted::instance;
BeHitted0 BeHitted0::instance;
Die Die::instance;

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

void Move::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"move");

}

void Move::update(Entity* entity)
{


	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Transform& transform = entity->getComponent<Transform>();
	_vec3 pos = entity->getComponent<Transform>().position_;
	auto p = GameManager::getInstance()->getPlayer();
	_vec3 p_pos = p->getComponent<Transform>().position_;
	float Xdistance = fabs(p_pos.x - pos.x);
	float Ydistance = fabs(p_pos.y - pos.y);
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	


	
	
	if (Xdistance > 200.f)
	{

		if (p_pos.x > pos.x)
		{
			rigidbody.direction_ = { 0.3f, 0.f, 0.f };
			//transform.position_.x += 50.f * (TimeManager::getInstance()->getDeltaTime());
			anim.setRight(false);
		}
		else
		{
			rigidbody.direction_ = { -0.3f, 0.f, 0.f };
			//transform.position_.x -=  50.f * (TimeManager::getInstance()->getDeltaTime());
			anim.setRight(true);
		}
	}

	if(Ydistance > 20.f)
	{

		if (p_pos.y > pos.y)
			rigidbody.direction_ = { 0.f, 0.75f, 0.f };
		//transform.position_.y += 50.f * (TimeManager::getInstance()->getDeltaTime());
		else
			rigidbody.direction_ = { 0.f, -0.75f, 0.f };
		//transform.position_.y -=50.f * (TimeManager::getInstance()->getDeltaTime());

	}

	rigidbody.setForce(rigidbody.direction_ * 100.f);
}

void Move::exit(Entity* entity)
{
}





void Attack::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"attack");



	//rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);*/



	
}

void Attack::update(Entity* entity)
{


	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if ((int)anim.getCurrentIndex() == 13 )
	{
		
		if (anim.getIsRight())
		{
			myBullet = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			 myBullet->setTypeAndName(Entity::ENTITYTYPE::ENEMYEFFECT, L"bullet");
			myBullet->addComponent<BossEffect>(3, entity->getComponent<Transform>().position_, 1);
			EntityManager::getInstance()->insertEntity(myBullet);
		}
		else
		{
			myBullet = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			myBullet->setTypeAndName(Entity::ENTITYTYPE::ENEMYEFFECT, L"bullet");
			myBullet->addComponent<BossEffect>(3, entity->getComponent<Transform>().position_, 2);
			EntityManager::getInstance()->insertEntity(myBullet);
		}
		anim.setCurrentIndex(14);
		

	}

	if (anim.isSpriteEnd() && !anim.isStopState())
		stateMachine.transitionState(MOVE);

}

void Attack::exit(Entity* entity)
{

	myBullet = nullptr;
	Crimson& gs = entity->getComponent<Crimson>();
	auto attackBoxEntity = gs.getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Attack::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(MOVE);
}

void Attack2::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"attack2");


	shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleEnemy/crimsonskilleffect");
	effect->getComponent<CommonEffect>().setEffect(entity, true, _vec3(0.f, 0.f, 0.f), 0.f, 1.f);
	






}

void Attack2::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if ((int)anim.getCurrentIndex() == 20)
	{

		auto p = GameManager::getInstance()->getPlayer();
		_vec3 p_pos = p->getComponent<Transform>().position_;

		//АјАн
		
		shared_ptr<Entity> attackBoxEntity = entity->getComponent<Crimson>().getAttackBox();
		AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
		attackBox.activateAttackBox(L"CrimsonSkill", entity);
		attackBoxEntity->getComponent<Transform>().position_ = p_pos;

		shared_ptr<Entity> effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/Effect/mapleEnemy/crimsonskill");
		effect->getComponent<CommonEffect>().setEffect(entity, false, _vec3(0.f, 0.f, 0.f), 0.f, 1.f);
		effect->getComponent<Transform>().position_ = p_pos;


	}
	if (anim.isSpriteEnd() && !anim.isStopState())
	{

		stateMachine.transitionState(IDLE);
	}

}

void Attack2::exit(Entity* entity)
{

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();

	shared_ptr<Entity> attackBoxEntity = entity->getComponent<Crimson>().getAttackBox();
	AttackBox& attackBox = attackBoxEntity->getComponent<AttackBox>();
	attackBox.deactivate();
}

void Attack2::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(IDLE);
}

void BeHitted::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"damaged");



}

void BeHitted::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(0.5f, bind(&BeHitted::stopEndTrigger, this, entity));

}

void BeHitted::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();
}

void BeHitted::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(HITTEDTOMOVE);
}






void BeHitted0::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"damaged0");


}

void BeHitted0::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(1.f, bind(&BeHitted0::stopEndTrigger, this, entity));

}

void BeHitted0::exit(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.resumeAnimation();
}

void BeHitted0::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(HITTEDTOMOVE);
}


void Die::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	anim.changeMotion(L"die");


}

void Die::update(Entity* entity)
{
	//StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	//	anim.stopAnimation(1.f, bind(&BeHitted0::stopEndTrigger, this, entity));

}

void Die::exit(Entity* entity)
{
	//	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		//anim.resumeAnimation();
}

void Die::stopEndTrigger(Entity* entity)
{
	//StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//stateMachine.transitionState(HITTEDTOMOVE);
}