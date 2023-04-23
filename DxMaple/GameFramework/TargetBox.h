#pragma once
#include "MonoBehaviour.h"
class TargetBox :
	public MonoBehaviour
{
public:
	

	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	Entity* getRightTarget()
	{
		return rightTarget_;
	}
	Entity* getLeftTarget()
	{
		return leftTarget_;
	}
public:
	void enterCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getType() == Entity::ENTITYTYPE::ENEMY)
		{
			for (int i = 0; i < EnemyList_.size(); i++)
			{

				if (EnemyList_[i] == colliderEntity)
				{
					return;
				}
			}
			EnemyList_.emplace_back(colliderEntity);
		}
	}

	void stayCollider(Entity* colliderEntity)
	{
		
	}

	void exitCollider(Entity* colliderEntity)
	{
		for (int i = 0; i < EnemyList_.size(); i++)
		{

			if (EnemyList_[i] == colliderEntity)
			{
				EnemyList_.erase(EnemyList_.begin() + i);
 				break;
			}
		}
		
	}

private:
	void CheckTarget();
private:


	Entity * rightTarget_;
	Entity * leftTarget_;
	vector<Entity*> EnemyList_;
	weak_ptr<Entity> player_;

};

