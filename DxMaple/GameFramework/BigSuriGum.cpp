#include "stdafx.h"
#include "BigSuriGum.h"
#include "GameManager.h"
void BigSuriGum::initialize()
{
	entity->addComponent<Transform>(position_ - _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
	//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
	//entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//	anim.SetMultiple(5, 1);
	anim.insertSprite(L"bigsurigum0", L"../AtlasFiles/Effect/mapleChar/bigsurigum/startsurigum.png", L"../AtlasFiles/Effect/mapleChar/bigsurigum/startsurigum.json");
	anim.insertSprite(L"bigsurigum1", L"../AtlasFiles/Effect/mapleChar/bigsurigum/bigsurigum1.png", L"../AtlasFiles/Effect/mapleChar/bigsurigum/bigsurigum1.json");
	anim.insertSprite(L"bigsurigum2", L"../AtlasFiles/Effect/mapleChar/bigsurigum/bigsurigum2.png", L"../AtlasFiles/Effect/mapleChar/bigsurigum/bigsurigum2.json");
	anim.insertSprite(L"bigsurigum3", L"../AtlasFiles/Effect/mapleChar/bigsurigum/bigsurigum3.png", L"../AtlasFiles/Effect/mapleChar/bigsurigum/bigsurigum3.json");

	anim.changeCurrentSprite(L"bigsurigum0");
	anim.setRight(right_);
	timeCount = 0.f;



	entity->addComponent<Status>();
	float baseDamage = 5000.f;

	


		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 1000, 0, 0, 0, 0, 0, 0);
		//공격체 세팅
		shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"bigsurigum");
		EntityManager::getInstance()->insertEntity(attackBox);
		attackBox->getComponent<AttackBox>().activateAttackBox(L"bigsurigum", entity);
		attackBox1_ = attackBox;





	



}

void BigSuriGum::update()
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	
	
	timeCount2 += TimeManager::getInstance()->getDeltaTime();
	if (timeCount2 >0.5f)
	{
		timeCount2 = 0.f;
		attackBox1_.lock()->getComponent<AttackBox>().deactivate();
	}
	else
	{
		attackBox1_.lock()->getComponent<AttackBox>().activateAttackBox(L"bigsurigum", entity);
	}



	if (page_ < 3)
	{
		timeCount += TimeManager::getInstance()->getDeltaTime();

		if (timeCount > 4.f)
		{
			anim.changeCurrentSprite(L"bigsurigum3");
			GameManager::getInstance()->getPlayer()->getComponent<Sound>().PlaySoundEffect(17);
			page_ = 3;//expired();

		}
	}

	if (page_ == 0)
	{
		if (anim.isSpriteEnd())
		{
			if (anim.getCurrentAnim() == L"bigsurigum0")
			{
				page_ = 1;
				anim.changeCurrentSprite(L"bigsurigum1");
				

			}
		}
	}
	else if (page_ == 1)
	{




		if (InputManager::getInstance()->keyPressing(DIK_F))
		{
			page_ = 2;
			GameManager::getInstance()->getPlayer()->getComponent<Sound>().PlaySoundEffect(16);
			anim.changeCurrentSprite(L"bigsurigum2");
		}
		
			//왼쪽으로 가는 표창
			if (right_)
				entity->getComponent<Transform>().position_ += _vec3(-700.f, 0.f, 0.f) * TimeManager::getInstance()->getDeltaTime();
			else
				entity->getComponent<Transform>().position_ += _vec3(700.f, 0.f, 0.f) * TimeManager::getInstance()->getDeltaTime();
		
	}
	else if (page_ == 2)
	{

	}
	else if (page_ == 3)
	{
		if (anim.isSpriteEnd())
			expired();
	}
}



void BigSuriGum::lateUpdate()
{

}

void BigSuriGum::render()
{
}

void BigSuriGum::release()
{
}

void BigSuriGum::expired()
{
	
	attackBox1_.lock()->setActive(false);
	attackBox1_.lock() = nullptr;
	entity->setActive(false);
}
