#include "stdafx.h"
#include "Bullet.h"
#include "GameManager.h"
void Bullet::initialize()
{
	entity->addComponent<Transform>(position_-_vec3(0.f,0.f,0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
	//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
	entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//	anim.SetMultiple(5, 1);

	
	anim.insertSprite(L"surigum", L"../AtlasFiles/surigum.png", L"../AtlasFiles/surigum.json");
	anim.insertSprite(L"whiteSurigum", L"../AtlasFiles/whiteSurigum.png", L"../AtlasFiles/whiteSurigum.json");

	

	anim.changeCurrentSprite(nowSurigum_);
	anim.setRight(right_);
	timeCount = 0.f;
	if(!anim.getIsRight())
		entity->addComponent<BoxCollider>(_vec3(-20.f,0.f,0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 25.f, 50.f));
	else
		entity->addComponent<BoxCollider>(_vec3(20.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 25.f, 50.f));
	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&Bullet::enterCollider, this, placeholders::_1),
		bind(&Bullet::stayCollider, this, placeholders::_1),
		bind(&Bullet::exitCollider, this, placeholders::_1));
	

	entity->addComponent<Status>();
	float baseDamage=5000.f;
	
	if (isMain_)
	{

		
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 100, 0, 0, 0, 0, 0, 0);
		//공격체 세팅
		shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"nenbullet");
		EntityManager::getInstance()->insertEntity(attackBox);
		attackBox->getComponent<AttackBox>().activateAttackBox(L"nenbullet", entity);
		attackBox1_ = attackBox;

		if(!GameManager::getInstance()->getPlayer()->getComponent<BUFF>().nowShadow)
			attackBox1_.lock()->getComponent<AttackBox>().multiHit(3);
		else
			attackBox1_.lock()->getComponent<AttackBox>().multiHit(6);


		

	}



}

void Bullet::update()
{
	timeCount += TimeManager::getInstance()->getDeltaTime();
	if (timeCount > 3.f)
		expired();


	//Transform& transform = entity->getComponent<Transform>();

	/*if (dest_ == _vec3(0.f,0.f,0.f))
	{*/
		//왼쪽으로 가는 표창
		if (right_)
			entity->getComponent<Transform>().position_ += _vec3(-600.f, 0.f, 0.f) * TimeManager::getInstance()->getDeltaTime();
		else
			entity->getComponent<Transform>().position_ += _vec3(600.f, 0.f, 0.f) * TimeManager::getInstance()->getDeltaTime();
	//}
	//else
	//{
	//	//오른쪽으로가는 표창
	//	if (!right_)
	//	{
	//		if (transform.position_.x < dest_.x)
	//			entity->getComponent<Transform>().position_ += _vec3(700.f, 0.f, 0.f) * TimeManager::getInstance()->getDeltaTime();



	//	}
	//	else
	//	{

	//		if (transform.position_.x > dest_.x)
	//			entity->getComponent<Transform>().position_ += _vec3(-700.f, 0.f, 0.f) * TimeManager::getInstance()->getDeltaTime();

	//	}


	//	if (transform.position_.y < dest_.y)
	//		transform.position_.y += 700.f * TimeManager::getInstance()->getDeltaTime();

	//	if (transform.position_.y > dest_.y)
	//		transform.position_.y -= 700.f * TimeManager::getInstance()->getDeltaTime();

	//}




	
	
}



void Bullet::lateUpdate()
{

}

void Bullet::render()
{
}

void Bullet::release()
{
}

void Bullet::expired()
{
	if (isMain_)
	{
		attackBox1_.lock()->setActive(false);
		attackBox1_.lock() = nullptr;
		/*attackBox2_.lock()->setActive(false);
		attackBox2_.lock() = nullptr;
		attackBox3_.lock()->setActive(false);
		attackBox3_.lock() = nullptr;*/
	}
	entity->setActive(false);
}
