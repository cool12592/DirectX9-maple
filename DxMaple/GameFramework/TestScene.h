#pragma once
#include "IScene.h"
class TestScene :public IScene
{
public:
	TestScene() {}
	virtual ~TestScene() {}


	// IScene을(를) 통해 상속됨
	virtual void initialize() override
	{
		if (!sceneObjectPool_.isEmpty())
			return;

		shared_ptr<Entity>& entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"axel");
		entity->addComponent<PlayerController>();

		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"blaze");
		entity->addComponent<TestController>();

		entityManager_->insertEntity(entity);

		
	}

	virtual void update() override
	{
		entityManager_->update();
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