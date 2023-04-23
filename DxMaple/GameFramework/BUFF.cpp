#include "stdafx.h"
#include "BUFF.h"
#include "GameManager.h"

void BUFF::initialize()
{

	originalAttackSpeed = entity->getComponent<Status>().attackSpeed_;
	originalMoveSpeed= entity->getComponent<Status>().moveSpeed_;


}

void BUFF::update()
{

	for (int i = 0; i < buffList.size(); i++)
	{
		_vec3 camera_position = entity->getComponent<Camera>().position_;
		buffList[i].first->getComponent<Transform>().position_ = _vec3(camera_position.x+SCREEN_WIDTH/2.f - 32.f * (i + 1) , camera_position.y+SCREEN_HEIGHT/2.f - 16.f , -1.f);

		if (buffList[i].second > 0)
		{
			buffList[i].second -= TimeManager::getInstance()->getDeltaTime();
			if (buffList[i].second <= 0)
			{
				offBuff(buffList[i].first,i);
				break;
			}
		}

	}


	if (!shadowPartnerEntity_.expired())
	{
		AtlasAnimation& anim = shadowPartnerEntity_.lock()->getComponent<AtlasAnimation>();

		if (!entity->getComponent<AtlasAnimation>().getIsRight())
			shadowPartnerEntity_.lock()->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-20.f, 5.f, 1.f);
		else
			shadowPartnerEntity_.lock()->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(20.f, 5.f, 1.f);


		if (anim.getCurrentAnim() == L"dead")
		{
			nowShadow = false;
			if (anim.isSpriteEnd())
				shadowPartnerEntity_.lock()->setActive(false);

			return;
		}
		else
			nowShadow = true;
		
		anim.setCurrentIndex(entity->getComponent<AtlasAnimation>().getCurrentIndex());
		anim.setRight(entity->getComponent<AtlasAnimation>().getIsRight());
		anim.setUserPivot(entity->getComponent<AtlasAnimation>().getUserPivot());
		
		
	}
	



}

void BUFF::lateUpdate()
{

}

void BUFF::render()
{
	
}

void BUFF::release()
{

}

void BUFF::onBuff(wstring name)
{
	if (name == L"darksite")
	{
		//이미 이 버프 진행중이면 없애고 다시만듬
		for (int i = 0; i < buffList.size(); i++)
		{
			if (buffList[i].first->getName() == name)
			{
				offBuff(buffList[i].first, i);
				//break;
				return; //다크사이트는 다시쓰면 해제임
			}
		}

		shared_ptr<Entity> buffEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		buffEntity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, name);
		buffEntity->addComponent<EmptyUI>();
		EntityManager::getInstance()->insertEntity(buffEntity);
		buffEntity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		buffEntity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/skillicon/darksite.png");

		//현재 진행중인 버프 리스트에집어넣음
		buffList.emplace_back(make_pair(buffEntity, buffTime));
		//버프효과
		entity->getComponent<PlayerController>().alpha = true;
		entity->getComponent<Status>().invincible_ = true;

	}

	else if (name == L"shadow")
	{
		//이미 이 버프 진행중이면 없애고 다시만듬
		for (int i = 0; i < buffList.size(); i++)
		{
			if (buffList[i].first->getName() == name)
			{
				shadowPartnerEntity_.lock()->setActive(false);
				buffList[i].first->setActive(false);
				buffList.erase(buffList.begin() + i);
				break;
			}
		}

		shared_ptr<Entity> buffEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		buffEntity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, name);
		buffEntity->addComponent<EmptyUI>();
		EntityManager::getInstance()->insertEntity(buffEntity);
		buffEntity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		buffEntity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/skillicon/shadow.png");


		

		//현재 진행중인 버프 리스트에집어넣음
		buffList.emplace_back(make_pair(buffEntity, buffTime*2.f));
		//버프효과

		shared_ptr<Entity> shadowpartner = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		shadowpartner->setTypeAndName(Entity::ENTITYTYPE::DNFUI, name);
		shadowpartner->addComponent<EmptyUI>();
		EntityManager::getInstance()->insertEntity(shadowpartner);
		shadowpartner->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

		AtlasAnimation& anim = shadowpartner->getComponent<AtlasAnimation>();
		anim.insertSprite(L"shadow", L"../AtlasFiles/shadowpartner.png", L"../AtlasFiles/shadowpartner.json");
		anim.insertSprite(L"dead", L"../AtlasFiles/shadowdead.png", L"../AtlasFiles/shadowdead.json");

		anim.changeCurrentSprite(L"shadow");

	
		shadowPartnerEntity_ = shadowpartner;
	}

	else if (name == L"haist")
	{
		//이미 그 버프 있으면 시간만 초기화
		//하려고했는데 없애고 다시 하는게 맞는듯.. (버프아이콘위치바뀌자나)
		for (int i = 0; i < buffList.size(); i++)
		{
			if (buffList[i].first->getName() == name)
			{
				offBuff(buffList[i].first,i);	
				break;
			}
		}


		shared_ptr<Entity> buffEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		buffEntity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, name);
		buffEntity->addComponent<EmptyUI>();
		EntityManager::getInstance()->insertEntity(buffEntity);
		buffEntity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		buffEntity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/skillicon/haist.png");

		buffList.emplace_back(make_pair(buffEntity,buffTime));
		entity->getComponent<Status>().moveSpeed_ *= 1.5f;

	}
	else if (name == L"boast")
	{

		for (int i = 0; i < buffList.size(); i++)
		{
			if (buffList[i].first->getName() == name)
			{
				offBuff(buffList[i].first, i);
				break;
			}
		}


		shared_ptr<Entity> buffEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		buffEntity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, name);
		buffEntity->addComponent<EmptyUI>();
		EntityManager::getInstance()->insertEntity(buffEntity);
		buffEntity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		buffEntity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/skillicon/boast.png");

		buffList.emplace_back(make_pair(buffEntity, buffTime));
		entity->getComponent<Status>().attackSpeed_ *= 1.5f;
	}
}

void BUFF::offBuff(shared_ptr<Entity> buffEntity,int index)
{
	if (buffEntity->getName() == L"darksite")
	{
		entity->getComponent<PlayerController>().alpha = false;
		entity->getComponent<Status>().invincible_ = false;
		buffList[index].first->setActive(false);
		buffList.erase(buffList.begin() + index);

	}

	else if (buffEntity->getName() == L"shadow")
	{
		shadowPartnerEntity_.lock()->getComponent<AtlasAnimation>().changeCurrentSprite(L"dead"); 
		shadowPartnerEntity_.lock()->getComponent<AtlasAnimation>().setAnimationSpeed(4.f);
		buffList[index].first->setActive(false);
		buffList.erase(buffList.begin() + index);
	}

	else if (buffEntity->getName() == L"haist")
	{

		entity->getComponent<Status>().moveSpeed_ = originalMoveSpeed;
		buffList[index].first->setActive(false);
		buffList.erase(buffList.begin() + index);

	}
	else if (buffEntity->getName() == L"boast")
	{
		entity->getComponent<Status>().attackSpeed_ = originalAttackSpeed;
		buffList[index].first->setActive(false);

		buffList.erase(buffList.begin() + index);
	}
}

