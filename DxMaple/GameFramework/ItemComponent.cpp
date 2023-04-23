#include "stdafx.h"
#include "ItemComponent.h"
#include "GameManager.h"
void ItemComponent::initialize()
{
	
}

void ItemComponent::update()
{


}

void ItemComponent::lateUpdate()
{

	

}

void ItemComponent::render()
{
}

void ItemComponent::release()
{
}

void ItemComponent::dropItem()
{
	int space = myitem.size() - 1 * 35;
	for (int i = 0; i < myitem.size(); i++)
	{
		
		if (myitem[i] == L"coin")
		{
		
			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::GOLD, L"gold");
			itemEntity->addComponent<Item>(L"coin");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_+_vec3(space*(i-1),0.f,0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"ÁÖÈ² ¹ö¼¸ÀÇ °«")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"ÁÖÈ² ¹ö¼¸ÀÇ °«");
			itemEntity->addComponent<Item>(L"ÁÖÈ² ¹ö¼¸ÀÇ °«");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}


		else if (myitem[i] == L"money")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::GOLD, L"money");
			itemEntity->addComponent<Item>(L"money");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"ÃÊ·Ï¹ö¼¸ÀÇ °«")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"ÃÊ·Ï¹ö¼¸ÀÇ °«");
			itemEntity->addComponent<Item>(L"ÃÊ·Ï¹ö¼¸ÀÇ °«");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢");
			itemEntity->addComponent<Item>(L"½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"´ÙÅ© ½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"´ÙÅ© ½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢");
			itemEntity->addComponent<Item>(L"´ÙÅ© ½ºÅæ°ñ·½ÀÇ µ¹Á¶°¢");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"½ºÄÌ·¹°ïÀÇ »Ô")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"½ºÄÌ·¹°ïÀÇ »Ô");
			itemEntity->addComponent<Item>(L"½ºÄÌ·¹°ïÀÇ »Ô");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"È­ÀÌÆ® ¼ö¸®°Ë")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"È­ÀÌÆ® ¼ö¸®°Ë");
			itemEntity->addComponent<Item>(L"È­ÀÌÆ® ¼ö¸®°Ë");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}


		else if (myitem[i] == L"³úÀü ¼ö¸®°Ë")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"³úÀü ¼ö¸®°Ë");
			itemEntity->addComponent<Item>(L"³úÀü ¼ö¸®°Ë");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}
	}
}