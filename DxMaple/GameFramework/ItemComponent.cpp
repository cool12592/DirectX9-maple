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

		else if (myitem[i] == L"��Ȳ ������ ��")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"��Ȳ ������ ��");
			itemEntity->addComponent<Item>(L"��Ȳ ������ ��");
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

		else if (myitem[i] == L"�ʷϹ����� ��")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"�ʷϹ����� ��");
			itemEntity->addComponent<Item>(L"�ʷϹ����� ��");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"������� ������")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"������� ������");
			itemEntity->addComponent<Item>(L"������� ������");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"��ũ ������� ������")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"��ũ ������� ������");
			itemEntity->addComponent<Item>(L"��ũ ������� ������");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"���̷����� ��")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"���̷����� ��");
			itemEntity->addComponent<Item>(L"���̷����� ��");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}

		else if (myitem[i] == L"ȭ��Ʈ ������")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"ȭ��Ʈ ������");
			itemEntity->addComponent<Item>(L"ȭ��Ʈ ������");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}


		else if (myitem[i] == L"���� ������")
		{

			shared_ptr<Entity> itemEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			itemEntity->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, L"���� ������");
			itemEntity->addComponent<Item>(L"���� ������");
			itemEntity->getComponent<Item>().Positioning(entity->getComponent<Transform>().position_ + _vec3(space*(i - 1), 0.f, 0.f));
			itemEntity->getComponent<Rigidbody>().addForce(_vec3(0.f, JUMP_FORCE, 0.f));
			EntityManager::getInstance()->insertEntity(itemEntity);
		}
	}
}