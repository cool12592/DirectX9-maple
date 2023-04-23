#include "stdafx.h"
#include "TargetBox.h"
#include "GameManager.h"
void TargetBox::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f) , _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


	

	
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1000.f, 200.f, 50.f));
	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&TargetBox::enterCollider, this, placeholders::_1),
		bind(&TargetBox::stayCollider, this, placeholders::_1),
		bind(&TargetBox::exitCollider, this, placeholders::_1));




	
}

void TargetBox::update()
{

	//if (player_.lock() == nullptr)
	//{
	//	player_ = GameManager::getInstance()->getPlayer();
	//	return;
	//}
	//
	//entity->getComponent<Transform>().position_ = player_.lock()->getComponent<Transform>().position_;

	//if (EnemyList_.size() != 0)
	//{
	//	CheckTarget();
	//}
	//else
	//{
	//	rightTarget_ = nullptr;
	//	leftTarget_ = nullptr;
	//}

}



void TargetBox::lateUpdate()
{

}

void TargetBox::render()
{
}

void TargetBox::release()
{
}


void TargetBox::CheckTarget()
{
	
	int mySize = EnemyList_.size();
	float RightEnemyMinX=10000;
	float LeftEnemyMinX=-10000;
	float myX = entity->getComponent<Transform>().position_.x;
	for (int i = 0; i < mySize; i++)
	{
		if (EnemyList_[i]->isActive() == false)
		{
			EnemyList_.erase(EnemyList_.begin() + i);
			continue;
		}
		_vec3 EnemyPosition = EnemyList_[i]->getComponent<Transform>().position_;
		float EnemyX = EnemyPosition.x;

		//적이오른쪽에있음
		if (myX <= EnemyX)
		{
			if (EnemyX < RightEnemyMinX)
			{
				RightEnemyMinX = EnemyX;
				rightTarget_ = EnemyList_[i];
			}
		}
		else
		{
			if (EnemyX > LeftEnemyMinX)
			{
				RightEnemyMinX = EnemyX;
				leftTarget_= EnemyList_[i];
			}
		}
		
	}

	if (RightEnemyMinX == 10000)
		rightTarget_ = nullptr;
	if (LeftEnemyMinX = 10000)
		leftTarget_ = nullptr;
	
	

}

