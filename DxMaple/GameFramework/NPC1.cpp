#include "stdafx.h"
#include "NPC1.h"
#include "GameManager.h"

void NPC1::initialize()
{


	entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

	if (npcName_ == L"Å°Äí")
	{
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Å°Äí.png");
	}
	else
	{
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		anim.insertSprite(L"idle", L"../AtlasFiles/npc/npc2.png", L"../AtlasFiles/npc/npc2.json");

		anim.changeCurrentSprite(L"idle");
	}
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(70.f, 70.f, 70.f));



	
	
}

void NPC1::update()
{
	return;
	
		if (timer > 8.f)
			return;


		timer += TimeManager::getInstance()->getDeltaTime();

		if (timer > 1.f)
		{
			if (GameManager::getInstance()->getShop() == nullptr)
			{
				shared_ptr<Entity> shop = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				shop->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"SHOP");
				
				if (npcName_ == L"Å°Äí")
				shop->addComponent<ItemShop>();

				if (npcName_ == L"¿¹Æ¼")
					shop->addComponent<ItemShop>(1);

				EntityManager::getInstance()->insertEntity(shop);
				GameManager::getInstance()->setShop(shop);
				if (npcName_ == L"Å°Äí")
				shop->getComponent<ItemShop>().bornSceneName_ = L"Room4";
				if (npcName_ == L"¿¹Æ¼")
					shop->getComponent<ItemShop>().bornSceneName_ = L"RoomBlue1";

				timer = 10.f;
				return;
			}
		}
	

	
}

void NPC1::lateUpdate()
{
	
}

void NPC1::render()
{


}

void NPC1::release()
{
}



