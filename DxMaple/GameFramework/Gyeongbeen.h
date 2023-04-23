#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Room3.h"
class Gyeongbeen :public IScene
{
public:
	Gyeongbeen() {}
	virtual ~Gyeongbeen() {}


	// IScene을(를) 통해 상속됨
	virtual void initialize() override
	{
		if (!sceneObjectPool_.isEmpty())
			return;

		shared_ptr<Entity>& entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"aa");
		entity->addComponent<BackGroundFar>();
		entityManager_->insertEntity(entity);
	
		 entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"aa");
		entity->addComponent<BackGround>();
		entityManager_->insertEntity(entity);

		

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"aa");
		entity->addComponent<Tile>();
		entityManager_->insertEntity(entity);

		
		entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
		entity->addComponent<BounDary>(0, _vec3(100.f, 0.f, 0.f),_vec3(110.f,110.f,110.f));
		EntityManager::getInstance()->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"player");
		entity->addComponent<PlayerController>();

		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setPlayer(entity);
	


	}

	virtual void update() override
	{
		entityManager_->update();
	/*	auto p=GameManager::getInstance()->getPlayer();
		if(p->getComponent<Transform>().position_.x>600)
		{
			
			SceneManager::getInstance()->changeScene(L"Room3");
		}*/
		
		if (GetAsyncKeyState(VK_RETURN))
			SceneManager::getInstance()->changeScene(L"Room3");
	}

	virtual void lateUpdate() override
	{
		entityManager_->lateUpdate();

	}

	virtual void render() override
	{
		entityManager_->render();

	}

	virtual void release() override
	{
		entityManager_->releaseAll(&sceneObjectPool_);
	}

	virtual void refresh()override
	{
		entityManager_->refresh(&sceneObjectPool_);
	}
};