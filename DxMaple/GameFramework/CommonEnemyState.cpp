#include "stdafx.h"
#include "CommonEnemyState.h"
#include "ComponentsHeader.h"
#include "GameManager.h"
#include "MonoBehaviour.h"
USING(CommonEnemyState)

Idle Idle::instance;
Move Move::instance;
Attack Attack::instance;
BeHitted BeHitted::instance;
Die Die::instance;

void Idle::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"idle");

	thinkTime = 1.5f;

	srand((unsigned int)time(NULL));
	thinkTime += rand() % 3;
	myTimer = 0.F;
}

void Idle::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	myTimer += TimeManager::getInstance()->getDeltaTime();

	if (myTimer > thinkTime)
	{
		srand((unsigned int)time(NULL));
		int randomNum = rand() % 2;
	
		if (randomNum == 0)
			anim.setRight(!anim.getIsRight());
		stateMachine.transitionState(MOVE);
	}

}

void Idle::exit(Entity* entity)
{
}

void Move::enter(Entity* entity)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"move");
	myTimer = 0.F;

	srand((unsigned int)time(NULL));

	randomNum = float(rand() % 10);
	randomNum += 3;

	//#include<random>
	/*std::random_device rd; std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> die(5, 10);
	randomNum = die(mersenne);*/
}

void Move::update(Entity* entity)
{
	Transform& transform = entity->getComponent<Transform>();

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	myTimer += TimeManager::getInstance()->getDeltaTime();

	if (anim.getIsRight())
		transform.position_.x += -50.f * (TimeManager::getInstance()->getDeltaTime());
	else
		transform.position_.x += 50.f * (TimeManager::getInstance()->getDeltaTime());


	if(transform.position_.x>1450.f-1000.f || transform.position_.x < -1000.f+ 340.f)
		anim.setRight(!anim.getIsRight());
	/*if (!rigidbody.onGround_)
	{
		anim.setRight(!anim.getIsRight());
	}*/

	//340 1450
	if (myTimer > randomNum)
	{
		cout<<"aa" << randomNum << endl;
		stateMachine.transitionState(IDLE);
		myTimer = 0.f;
	}


}

void Move::exit(Entity* entity)
{
}




void Attack::enter(Entity* entity)
{
	
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.changeMotion(L"attack");



}

void Attack::update(Entity* entity)
{
	Transform& transform = entity->getComponent<Transform>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	_vec3 pos = entity->getComponent<Transform>().position_;

	auto p = GameManager::getInstance()->getPlayer();
	_vec3 p_pos = p->getComponent<Transform>().position_;
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();

	float fDis = fabs(pos.x - p_pos.x);

	//플레이어와 70보다 멀면 플레이어가 있는방향을봄
	if (fDis > 70.f)
	{
		if (p_pos.x > pos.x)
			anim.setRight(false);
		else
			anim.setRight(true);
	}

	if (transform.position_.x < 1450.f - 1000.f && transform.position_.x > -1000.f + 340.f)
	{
		//몬스터가 바라보는쪽으로 전진함 
		if (anim.getIsRight())
			transform.position_.x += -50.f * (TimeManager::getInstance()->getDeltaTime());
		else
			transform.position_.x += 50.f * (TimeManager::getInstance()->getDeltaTime());
	}





	if (fDis > 500.f)
		stateMachine.transitionState(MOVE);

}

void Attack::exit(Entity* entity)
{



}

void Attack::stopEndTrigger(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.transitionState(IDLE);
}


void BeHitted::enter(Entity* entity)
{

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.changeMotion(L"damaged");



}

void BeHitted::update(Entity* entity)
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (anim.isSpriteEnd() && !anim.isStopState())
		anim.stopAnimation(1.f, bind(&BeHitted::stopEndTrigger, this, entity));

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