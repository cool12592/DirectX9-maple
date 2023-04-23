#include "stdafx.h"
#include "BossEffect.h"
#include "GameManager.h"
BossEffect::~BossEffect()
{
	if (!attackBox_.expired())
		attackBox_.lock()->setActive(false);
}
void BossEffect::initialize()
{


	if (type_ == -1)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));



		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		anim.insertSprite(L"effect1", L"../AtlasFiles/effect1.png", L"../AtlasFiles/effect1.json");
		anim.changeCurrentSprite(L"effect1");
		if (option_ == 1)
			anim.setRight(false);

	}

	//보스넉백
	if (type_ == 0)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(10000.f, 10000.f, 10000.f));


	}

	//넨폭발
	if (type_ == 1)
	{
	
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//	anim.SetMultiple(5, 1);
		anim.insertSprite(L"nenexplosion", L"../AtlasFiles/Enemy/effect/nenexplosion.png", L"../AtlasFiles/Enemy/effect/nenexplosion.json");
		anim.changeCurrentSprite(L"nenexplosion");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/nenexplosion";

		//공격체 세팅
		shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
		EntityManager::getInstance()->insertEntity(attackBox);
		attackBox->getComponent<AttackBox>().activateAttackBox(L"BossAttack1", entity);
		attackBox_ = attackBox;


	}
	
	//넨꽃
	if (type_ == 3)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
		//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		

		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	
		anim.insertSprite(L"flowerbullet", L"../AtlasFiles/effect/mapleEnemy/crimsonbullet.png", L"../AtlasFiles/effect/mapleEnemy/crimsonbullet.json");
		anim.changeCurrentSprite(L"flowerbullet");
		timeCount = 0.f;


		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 10000, 0, 0, 0, 0, 0, 0);
		//공격체 세팅
		shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
		EntityManager::getInstance()->insertEntity(attackBox);
		attackBox->getComponent<AttackBox>().activateAttackBox(L"nenbullet", entity);
		attackBox_ = attackBox;
	}

	//넨수
	if (type_ == 4)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(8.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		//	anim.SetMultiple(5, 1);
		anim.insertSprite(L"beast", L"../AtlasFiles/Enemy/effect/beast0.png", L"../AtlasFiles/Enemy/effect/beast0.json");
		anim.changeCurrentSprite(L"beast");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/beast0";

		entity->addComponent<Rigidbody>().setMass(1.f);
		entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);
		entity->getComponent<Rigidbody>().setUseGravity(true);
		animPauseCount_ = 0.f;

		anim.insertMotionData(L"beast", L"0", 0, 0);
		anim.insertMotionData(L"beast", L"1", 1, 1);
		anim.insertMotionData(L"beast", L"2", 2, 2);
		anim.insertMotionData(L"beast", L"3", 3, 3);
		anim.insertMotionData(L"beast", L"4", 4, 4);
		anim.insertMotionData(L"beast", L"5", 5, 5);
		anim.insertMotionData(L"beast", L"6", 6, 6);
		anim.insertMotionData(L"beast", L"0_2", 0, 2);
		anim.insertMotionData(L"beast", L"3_5", 3, 5);
		if(option_==0)
		anim.changeMotion(L"0_2");
		if (option_ == 1)
			anim.changeMotion(L"3_5");

		first1 = true;
		first2 = true;

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 10000, 0, 0, 0, 0, 0, 0);
	}


	//넨수공격
	if (type_ == 5)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


		animPauseCount_ = 0.f;

	//	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/crypt_of_pain/1.png");


		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().insertSprite(L"beastattackeffect", L"../AtlasFiles/Enemy/effect/louder2.png", L"../AtlasFiles/Enemy/effect/louder2.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"beastattackeffect");

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().insertSprite(L"beastattackeffect", L"../AtlasFiles/Enemy/effect/louder3.png", L"../AtlasFiles/Enemy/effect/louder3.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"beastattackeffect");

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(8.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().insertSprite(L"beastattackeffect", L"../AtlasFiles/Enemy/effect/beastattackeffect.png", L"../AtlasFiles/Enemy/effect/beastattackeffect.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"beastattackeffect");

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(8.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(-130, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().insertSprite(L"beastattackeffect", L"../AtlasFiles/Enemy/effect/startlouder.png", L"../AtlasFiles/Enemy/effect/startlouder.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"beastattackeffect");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/beastattackeffect";

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 10000, 0, 0, 0, 0, 0, 0);

		if (entity->getComponent<AtlasAnimation>().getIsRight())
		{
			//공격체 세팅
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"beastlouder");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"beastlouder", entity);
			attackBox_ = attackBox;
		}
		else
		{
			//공격체 세팅
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"beastlouder");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"beastlouder2", entity);
			attackBox_ = attackBox;
		}
		
	}
	//도는 원 본체
	if (type_ == 6)
	{
		entity->addComponent<Transform>(position_+_vec3(0.f,0.f,0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		animPauseCount_ = 0.f;

		Transform& t = entity->getComponent<Transform>();

		

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(8.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().setAddPos(_vec3(100.f, 0.f, 0.f));
		entity->getComponent<AtlasAnimation>().insertSprite(L"circle", L"../AtlasFiles/Map/magmaTrap01.png", L"../AtlasFiles/Map/magmaTrap01.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"circle");
		entity->getComponent<AtlasAnimation>().PauseAnimation();
		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 10000, 0, 0, 0, 0, 0, 0);

		atlasPath_ = L"../AtlasFiles/Map/magmaTrap01";

		initPosition_[0] = _vec3(210.f, -250.f, 0.f);
		circle[0] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		circle[0]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"circle");
		circle[0]->addComponent<BossEffect>(7, initPosition_[0]);
		circle[0]->getComponent<Transform>().setParentMatrix(&t.worldMatrix2D_);
		EntityManager::getInstance()->insertEntity(circle[0]);
		

		initPosition_[1] = _vec3(-210.f, -250.f, 0.f);
		circle[1] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		circle[1]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"circle");
		circle[1]->addComponent<BossEffect>(7, initPosition_[1]);
		circle[1]->getComponent<Transform>().setParentMatrix(&t.worldMatrix2D_);
		EntityManager::getInstance()->insertEntity(circle[1]);


		initPosition_[2] = _vec3(0.f, 230.f, 0.f);
		circle[2] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		circle[2]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"circle");
		circle[2]->addComponent<BossEffect>(7, initPosition_[2]);
		circle[2]->getComponent<Transform>().setParentMatrix(&t.worldMatrix2D_);
		EntityManager::getInstance()->insertEntity(circle[2]);


		//공격체 세팅
		
	
		for (int i = 0;i < 3;i++)
		{
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"BossCircle", entity);
			attackBoxGroup_[i] = attackBox;
			attackBoxGroup_[i].lock()->getComponent<Transform>().setParentMatrix(&t.worldMatrix_);
		}

	}

	if (type_ == 7)
	{
		

		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(0.5f, 0.5f, 0.5f));
	


		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(40, 135));
		//entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().insertSprite(L"circle", L"../AtlasFiles/Enemy/effect/circleb.png", L"../AtlasFiles/Enemy/effect/circleb.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"circle");
		
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(16.f);
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(30, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
		entity->getComponent<AtlasAnimation>().insertSprite(L"circle", L"../AtlasFiles/Enemy/effect/circlea.png", L"../AtlasFiles/Enemy/effect/circlea.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"circle");










		timeCount = 0.f;

	

		animPauseCount_ = 0.f;
		



		

		
	}



	//ad몬스터용
	if (type_ == 8)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(0.1f, 0.1f, 0.1f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"bullet", L"../AtlasFiles/Enemy/ADmonsterSkill.png", L"../AtlasFiles/Enemy/ADmonsterSkill.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"bullet");
		atlasPath_ = L"../AtlasFiles/Enemy/ADmonsterSkill";

		timeCount = 0.f;

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 1000, 0, 0, 0, 0, 0, 0);
		
		//공격체 세팅
		shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
		EntityManager::getInstance()->insertEntity(attackBox);
		attackBox->getComponent<AttackBox>().activateAttackBox(L"ADmonsterAttack1", entity);
		attackBox_ = attackBox;

	}

	//ad몬스터용
	if (type_ == 9)
	{
		entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(0.2f, 0.2f, 0.2f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(50, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"bullet", L"../AtlasFiles/Enemy/ADmonsterSkill.png", L"../AtlasFiles/Enemy/ADmonsterSkill.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"bullet");
		atlasPath_ = L"../AtlasFiles/Enemy/ADmonsterSkill";

		timeCount = 0.f;

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 1000, 0, 0, 0, 0, 0, 0);
		
		
		//공격체 세팅
	    shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
		EntityManager::getInstance()->insertEntity(attackBox);
		
		attackBox->getComponent<AttackBox>().activateAttackBox(L"ADmonsterAttack1", entity);

		attackBox_ = attackBox;

		
		

		

		
	}


	//뒤에그림자
	if (type_ == 10)
	{
		entity->addComponent<Transform>(position_+_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(30, 65));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"mandarinshadow", L"../AtlasFiles/Enemy/effect/mandarinshadow.png", L"../AtlasFiles/Enemy/effect/mandarinshadow.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"mandarinshadow");

		atlasPath_ = L"../AtlasFiles/Enemy/effect/mandarinshadow";

	}

	//garder
	if (type_ == 11)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, -100.f, 100.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(20, 95));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"bullet", L"../AtlasFiles/Enemy/effect/mandarinulti-0.png", L"../AtlasFiles/Enemy/effect/mandarinulti-0.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"bullet");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/mandarinulti-0";

	}

	//text
	if (type_ == 12)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f,0.f ), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(20, 95));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"mandarintexture", L"../AtlasFiles/Enemy/effect/mandarintexture.png", L"../AtlasFiles/Enemy/effect/mandarintexture.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"mandarintexture");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/mandarintexture";

	}

	////backcircle1
	if (type_ == 13)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(0, 95));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"backcircle1", L"../AtlasFiles/Enemy/effect/backcircle1.png", L"../AtlasFiles/Enemy/effect/backcircle1.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"backcircle1");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/backcircle1";

	}

	//backcircle2
	if (type_ == 14)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(35, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"backcircle2", L"../AtlasFiles/Enemy/effect/backcircle2.png", L"../AtlasFiles/Enemy/effect/backcircle2.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"backcircle2");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/backcircle2";

	}



	//sidebeam
	if (type_ == 15)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.5f, 1.5f, 1.f));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(35, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"sidebeam", L"../AtlasFiles/Enemy/effect/sidebeam.png", L"../AtlasFiles/Enemy/effect/sidebeam.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"sidebeam");

		atlasPath_ = L"../AtlasFiles/Enemy/effect/sidebeam";

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 30000, 0, 0, 0, 0, 0, 0);

		if (option_==0)
		{
			//공격체 세팅
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"sidebeam");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"sidebeam", entity);
			attackBox_ = attackBox;
		}
		else
		{
			//공격체 세팅
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"sidebeam2");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"sidebeam2", entity);
			attackBox_ = attackBox;

		}
	}

	//sideWave
	if (type_ == 16)
	{
		if(option_==1)
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 60.f), _vec3(2.f, 2.f, 1.f));
		else
			entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, -60.f), _vec3(2.f, 2.f, 1.f));
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(35, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"sidewave", L"../AtlasFiles/Enemy/effect/sidewave.png", L"../AtlasFiles/Enemy/effect/sidewave.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"sidewave");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/sidewave";


		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 50000, 0, 0, 0, 0, 0, 0);

		//왼쪽
		if (option_ == 1)
		{
			//공격체 세팅
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"sidebeam");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"sidewave", entity);
			attackBox_ = attackBox;
		}
		else
		{
			//공격체 세팅
			shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			attackBox->addComponent<AttackBox>();
			attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"sidebeam2");
			EntityManager::getInstance()->insertEntity(attackBox);
			attackBox->getComponent<AttackBox>().activateAttackBox(L"sidewave2", entity);
			attackBox_ = attackBox;

		}

	}
	//cutsin
	if (type_ == 17)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/crypt_of_pain/0.png");
	}

	//gather2
	if (type_ == 18)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(3.0f, 3.0f, 3.0));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(500, 600));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"gather2", L"../AtlasFiles/Enemy/effect/gather2.png", L"../AtlasFiles/Enemy/effect/gather2.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"gather2");
		entity->getComponent<AtlasAnimation>().setAnimationSpeed(24.f);

		atlasPath_ = L"../AtlasFiles/Enemy/effect/gather2";

	}

	//넨꽃 원

	if (type_ == 19)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.0f, 1.0f, 1.0));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(35, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"flowerCircle", L"../AtlasFiles/Enemy/effect/flowerCircle.png", L"../AtlasFiles/Enemy/effect/flowerCircle.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"flowerCircle");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/flowerCircle";

		entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(100.f, 100.f, 100.f));
	}


	//넨꽃흡수되는거(3번스킬)
	if (type_ == 20)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.0f, 1.0f, 1.0));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(155, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"particleb-0", L"../AtlasFiles/Enemy/effect/particleb-0.png", L"../AtlasFiles/Enemy/effect/particleb-0.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"particleb-0");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/particleb-0";

	}

	//4번스킬 양쪽으로 터지는거
	if (type_ == 21)
	{
		entity->addComponent<Transform>(position_ + _vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.0f, 1.0f, 1.0));

		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(155, 125));
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		entity->getComponent<AtlasAnimation>().insertSprite(L"particlea", L"../AtlasFiles/Enemy/effect/particlea.png", L"../AtlasFiles/Enemy/effect/particlea.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"particlea");
		atlasPath_ = L"../AtlasFiles/Enemy/effect/particlea";

		entity->addComponent<Status>();
		entity->getComponent<Status>().setStatus(Status::CLASSTYPE::ETC, 0, 0, 10000, 0, 0, 0, 0, 0, 0);
		
	

	}


}

void BossEffect::update()
{

	//AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//if (anim.isSpriteEnd() && anim.getCurrentAnim() == L"nenguardstart")
		//anim.changeCurrentSprite(L"nenguard");

	//넨꽃
	if (type_ == -1)
	{

		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		if (anim.isSpriteEnd())
			entity->setActive(false);
	}


	//넨꽃
	if (type_ == 3)
	{
		
		timeCount += TimeManager::getInstance()->getDeltaTime();


		if (timeCount > 5.f)
		{
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
		}
		else
		{
			if(option_==1)
			entity->getComponent<Transform>().position_+=_vec3(-500.f,0.f,0.f)*TimeManager::getInstance()->getDeltaTime();
			else if(option_==2)
			entity->getComponent<Transform>().position_ += _vec3(500.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();
			
		}
	}
	//넨수
	if (type_ == 4)
	{
		
		
		Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
		
	
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	
		if(!timeStop_)
		animPauseCount_ += TimeManager::getInstance()->getDeltaTime();
		_vec3 direction;




		if (animPauseCount_ < 0.5f)
		{

			if (anim.getIsRight())
				direction = { -1.0f, 3.f, 0.f };
			else
				direction = { +1.0f, 3.f, 0.f };
			rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);


			if (anim.isSpriteEnd() && !anim.isStopState()   )
			{


				anim.PauseAnimation();
				


			}

		}
		else if ((animPauseCount_ < 1.f))
		{
			if (anim.getIsRight())
				direction = { -1.0f, -3.f, 0.f };
			else
				direction = { 1.0f, -3.f, 0.f };
			rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);
		}
		//얻드리는자세
		else if ((animPauseCount_ > 1.0f) && count == 0)
		{	
		
				timeStop_ = true;
				if (option_ == 1)
					anim.changeMotion(L"1");
				else
					anim.changeMotion(L"4");
				if (entity->getComponent<AtlasAnimation>().getIsRight())
				{
					if (attackBox_.lock() == nullptr)
					{
						//공격체 세팅
						shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
						attackBox->addComponent<AttackBox>();
						attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"beastlouder");
						EntityManager::getInstance()->insertEntity(attackBox);
						attackBox->getComponent<AttackBox>().activateAttackBox(L"beast", entity);
						attackBox_ = attackBox;
					}
				}
				else
				{
					if (attackBox_.lock() == nullptr)
					{
						//공격체 세팅
						shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
						attackBox->addComponent<AttackBox>();
						attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"beastlouder");
						EntityManager::getInstance()->insertEntity(attackBox);
						attackBox->getComponent<AttackBox>().activateAttackBox(L"beast2", entity);
						attackBox_ = attackBox;
					}
				}
			
				timeStop_ = false;
				count = 1;
				
			
		}
		//준비자세
		else if ((animPauseCount_ > 1.4f)&& count == 1)
		{
			
				timeStop_ = true;
				if (attackBox_.lock() != nullptr)
				{
					attackBox_.lock()->getComponent<AttackBox>().deactivate();
					attackBox_.lock() = nullptr;
				}
				if (option_ == 1)
					anim.changeMotion(L"0");
				else
					anim.changeMotion(L"3");
				timeStop_ = false;
				count = 2;
			
		}

		else if ((animPauseCount_ > 2.0f) && count == 2)  //1타
		{
			
				timeStop_ = true;
				if (anim.getIsRight() == false)
				{



					if (option_ == 1)
						anim.changeMotion(L"6");
					else
						anim.changeMotion(L"6");

					if (first1 && option_ == 0)
					{
						first1 = false;
						shot[0] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
						shot[0]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"nenbeastshot");
						shot[0]->addComponent<BossEffect>(5, entity->getComponent<Transform>().position_ - _vec3(200.f, 0.f, 0.f));
						//shot->getComponent<AtlasAnimation>().setRight(false);
						EntityManager::getInstance()->insertEntity(shot[0]);
					}


				}
				timeStop_ = false;
				count = 3;
			
		}

		else if ((animPauseCount_ >3.0f)&&count == 3)
		{
			
				timeStop_ = true;
				if (anim.getIsRight() == false)
				{
					if (option_ == 1)
						anim.changeMotion(L"0");
					else
						anim.changeMotion(L"3");
				}
				timeStop_ = false;
				count = 4;
			
		}

		else if ((animPauseCount_ > 3.3f)&& count == 4)  //2타
		{
			
				timeStop_ = true;
				if (anim.getIsRight() == true)
				{



					if (option_ == 1)
						anim.changeMotion(L"6");
					else
						anim.changeMotion(L"6");

					if (first2 && option_ == 0)
					{
						first2 = false;
						shot[1] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
						shot[1]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"nenbeastshot");
						shot[1]->addComponent<BossEffect>(5, entity->getComponent<Transform>().position_ + _vec3(200.f, 0.f, 0.f));
						shot[1]->getComponent<AtlasAnimation>().setRight(false);
						EntityManager::getInstance()->insertEntity(shot[1]);
					}


				}
				timeStop_ = false;
				count = 5;
			

		}

		else if ((animPauseCount_ > 3.7f)&& count == 5)
		{
		
				timeStop_ = true;
				if (anim.getIsRight() == true)
				{
					if (option_ == 1)
						anim.changeMotion(L"0");
					else
						anim.changeMotion(L"3");
				}
				count = 6;
				timeStop_ = false;
			
		}
		else if ((animPauseCount_ > 4.0f)&& count == 6)
		{

			
				timeStop_ = true;
				shot[0] = nullptr;
				shot[1] = nullptr;
				entity->setActive(false);
				timeStop_ = false;
			
		}






	}

	//넨수 샤우팅
	if (type_ == 5)
	{


		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		if (anim.isSpriteEnd() && !anim.isStopState())
		{

			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);


		}


	}

	//필살기빙빙도는거 센터본체
	if (type_ == 6)
	{
		if (revolution >= D3DXToRadian(360.f))
			revolution -=D3DXToRadian(360.f);
		else if(revolution<0.f)
			revolution += D3DXToRadian(360.f);

		revolution+=TimeManager::getInstance()->getDeltaTime()*D3DXToRadian(360.f)/2.5f;
		if (circle[0] != nullptr)
		{
			circle[0]->getComponent<Transform>().setRevolution(revolution);
			circle[1]->getComponent<Transform>().setRevolution(revolution);
			circle[2]->getComponent<Transform>().setRevolution(revolution);
		}
		_mat matTrans,matRevolution, matTotal;
		_vec3 totalPosition;

		for (int i = 0;i < 3;i++)
		{
			D3DXMatrixTranslation(&matTrans, initPosition_[i].x, initPosition_[i].y, initPosition_[i].z);
			D3DXMatrixRotationZ(&matRevolution, revolution);
			matTotal = matTrans * matRevolution*attackBoxGroup_[i].lock()->getComponent<Transform>().getParentPositionMatrix();
			memcpy(&totalPosition, matTotal.m[3], sizeof(_vec3));
			attackBoxGroup_[i].lock()->getComponent<Transform>().position_ = totalPosition;
	
		}
		timeCount += TimeManager::getInstance()->getDeltaTime();
		if (timeCount > 7.0f)
		{
			for (int i = 0;i < 3;i++)
				attackBoxGroup_[i].lock()->getComponent<AttackBox>().deactivate();
		}

	}

	//필살기빙빙도는거(작은원)
	if (type_ == 7)
	{
		/*if (revolution >= D3DXToRadian(360.f))
			revolution -= D3DXToRadian(360.f);
		else if (revolution < 0.f)
			revolution += D3DXToRadian(360.f);

		revolution += TimeManager::getInstance()->getDeltaTime()*D3DXToRadian(360.f) / 3.f;*/
		
		
	
	}

	//ad몬스터용
	if (type_ == 8)
	{

		timeCount += TimeManager::getInstance()->getDeltaTime();


		if (timeCount > 3.f)
		{
			
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
			
		}
		else
		{
			if (option_ == 1)
				entity->getComponent<Transform>().position_ += _vec3(500.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();
			else
				entity->getComponent<Transform>().position_ += _vec3(-500.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();
			
		}
	}

	if (type_ == 9)
	{

		timeCount += TimeManager::getInstance()->getDeltaTime();


		if (timeCount > 3.f)
		{
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
		}
		else
		{
			if (option_ == 1)
				entity->getComponent<Transform>().position_ += _vec3(500.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();
			else
				entity->getComponent<Transform>().position_ += _vec3(-500.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();

		}
	}
	//backcircle1
	if (type_ == 13)
	{


		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		if ((int)anim.getCurrentIndex()==4 )
			anim.PauseAnimation();

	}
	//backcircle2
	if (type_ == 14)
	{


		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		if (anim.isSpriteEnd())
			anim.PauseAnimation();

	}

	//sidebeam
	if (type_ == 15)
	{
		timeCount += TimeManager::getInstance()->getDeltaTime();

		if (timeCount > 0.2f)
		{

			attackBox_.lock()->getComponent<AttackBox>().deactivate();
		}
	
	}

	//sideWave
	if (type_ == 16)
	{
		timeCount += TimeManager::getInstance()->getDeltaTime();

		if (timeCount > 2.f)
		{
		
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
		}
	
			if (option_ == 1)
				entity->getComponent<Transform>().position_ += _vec3(-300.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();
			else
				entity->getComponent<Transform>().position_ += _vec3(300.f, 0.f, 0.f)*TimeManager::getInstance()->getDeltaTime();

		

	}


	//flowerCircle
	if (type_ == 19)
	{
		

		

		
			entity->getComponent<Transform>().rotation_.z += TimeManager::getInstance()->getDeltaTime()*3.f;
			if ((int)entity->getComponent<AtlasAnimation>().getCurrentIndex()==8)
			{
				entity->getComponent<AtlasAnimation>().PauseAnimation();
			}
			



	}
	
	
	//넨폭발
	if (type_ == 1)
	{
		if (option_ == 5)
		{
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
			return;
		}
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

		timeCount += TimeManager::getInstance()->getDeltaTime();

		if (timeCount > 0.1f && Chainexplosion1 == nullptr)
		{

			Chainexplosion1 = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			Chainexplosion1->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"nenexplosion2");


			if (entity->getComponent<AtlasAnimation>().getIsRight())
			{
				Chainexplosion1->addComponent<BossEffect>(1, entity->getComponent<Transform>().position_ + _vec3(100.f, 0.f, 0.f), option_ + 1);
				EntityManager::getInstance()->insertEntity(Chainexplosion1);
				Chainexplosion1->getComponent<AtlasAnimation>().setRight(true);
			}
			else
			{
				Chainexplosion1->addComponent<BossEffect>(1, entity->getComponent<Transform>().position_ - _vec3(100.f, 0.f, 0.f), option_ + 1);
				EntityManager::getInstance()->insertEntity(Chainexplosion1);
				Chainexplosion1->getComponent<AtlasAnimation>().setRight(false);
			}
		}


		if (anim.isSpriteEnd())
		{
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
		}


	}

	//넨폭발
	if (type_ == 21)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		timeCount += TimeManager::getInstance()->getDeltaTime();
		if (attackBox_.expired())
		{
			if (anim.getIsRight() == false)
			{
				//공격체 세팅
				shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				attackBox->addComponent<AttackBox>();
				attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
				EntityManager::getInstance()->insertEntity(attackBox);
				attackBox->getComponent<AttackBox>().activateAttackBox(L"nenexplosion", entity);
				attackBox_ = attackBox;
			}
			else
			{
				//공격체 세팅
				shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				attackBox->addComponent<AttackBox>();
				attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
				EntityManager::getInstance()->insertEntity(attackBox);
				attackBox->getComponent<AttackBox>().activateAttackBox(L"nenexplosion2", entity);
				attackBox_ = attackBox;
			}
		}

		if (option_ == 5)
		{
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
			return;
		}


		if(Chainexplosion2 == nullptr)
		{

			Chainexplosion2 = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			Chainexplosion2->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"nenexplosion2");
		

			if (entity->getComponent<AtlasAnimation>().getIsRight())
			{
				Chainexplosion2->addComponent<BossEffect>(21, entity->getComponent<Transform>().position_ + _vec3(50.f, 0.f, 0.f), option_ + 1);
				EntityManager::getInstance()->insertEntity(Chainexplosion2);
				Chainexplosion2->getComponent<AtlasAnimation>().setRight(true);
			}
			else
			{
				Chainexplosion2->addComponent<BossEffect>(21, entity->getComponent<Transform>().position_ - _vec3(50.f, 0.f, 0.f), option_ + 1);
				EntityManager::getInstance()->insertEntity(Chainexplosion2);
				Chainexplosion2->getComponent<AtlasAnimation>().setRight(false);
			}
		}
		


		if ((int)anim.getCurrentIndex() == 20)
		{
			attackBox_.lock()->getComponent<AttackBox>().deactivate();
			entity->setActive(false);
		}
		if (anim.isSpriteEnd())
		{
		
			entity->setActive(false);
		}


	}
	//if (SceneManager::getInstance()->GetCurrentSceneName == L"BossRoom")
	//{
	//	if (entity->isActive() == true)
	//	{
	//		if (!GameManager::getInstance()->isBossSet() || GameManager::getInstance()->getBoss()->isActive() == false)
	//		{
	//			if (attackBox_.lock() != nullptr)
	//			{
	//				attackBox_.lock()->setActive(false);
	//				attackBox_.lock() = nullptr;
	//			}
	//			entity->setActive(false);
	//		}
	//	}
	//}

	sendEffectData();


}

void BossEffect::lateUpdate()
{
}

void BossEffect::render()
{
}

void BossEffect::release()
{
}


void BossEffect::setDirection()
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	_vec3 pos = entity->getComponent<Transform>().position_;
	auto p = GameManager::getInstance()->getPlayer();
	_vec3 p_pos = p->getComponent<Transform>().position_;

	if (p_pos.x > pos.x)
		anim.setRight(true);
	else
		anim.setRight(false);
}

void BossEffect::sendEffectData()
{
	//if (L"" == atlasPath_)
	//	return;
	//if (!entity->hasComponent<Transform>() || !entity->hasComponent<AtlasAnimation>())
	//	return;

	//Transform& transform = entity->getComponent<Transform>();
	//AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	////unique_ptr<UdpEffect> effectData = make_unique<UdpEffect>();
	//int userIDN, entityNumber;
	//Entity::ENTITYTYPE entityType;
	//entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);

	//effectData->objectType_ = 6;

	//effectData->userIDN_ = userIDN;
	//effectData->objectNumber_ = entityNumber;

	//effectData->effectName_ = string(atlasPath_.begin(), atlasPath_.end());
	//effectData->currentSpriteIndex_ = anim.getCurrentIndex();
	//effectData->pX_ = transform.position_.x;
	//effectData->pY_ = transform.position_.y;
	//effectData->pZ_ = transform.position_.z;
	//effectData->sizeX_ = transform.scale_.x;
	//effectData->sizeY_ = transform.scale_.y;
	//effectData->sizeZ_ = transform.scale_.z;

	//effectData->pivotX_ = anim.getUserPivot().x;
	//effectData->pivotY_ = anim.getUserPivot().y;
	//effectData->isRight_ = anim.getIsRight();


//	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(effectData));
}

