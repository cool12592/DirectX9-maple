#include "stdafx.h"
#include "PlayerController.h"

#include "FighterState.h"
#include "GameManager.h"

#include "ExcelLoader.h"
#include "SceneManager.h"

#include "Inventory.h"
#include "ItemShop.h"
PlayerController::PlayerController():className_(L"fighter"),initPosition_(_vec3(-300.f,0.f,-100.f))
{
}

PlayerController::PlayerController(wstring className, _vec3 position):className_(className),initPosition_(position)
{
}

PlayerController::~PlayerController()
{
}


void PlayerController::updateWeaponPositionAndAnimation()
{
	/*Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (!weaponFront_.expired())
	{
		shared_ptr<Entity>& weapon = weaponFront_.lock();
		if (weapon->hasComponent<Transform>()&& weapon->hasComponent<AtlasAnimation>())
		{
			Transform& weaponTransform = weapon->getComponent<Transform>();
			AtlasAnimation& weaponAnim = weapon->getComponent<AtlasAnimation>();
			if(anim.getIsRight())
				weaponTransform.position_=transform.position_+_vec3(-3.f,-18.f,0.f);
			else
				weaponTransform.position_ = transform.position_ + _vec3(3.f, -18.f, 0.f);
			weaponTransform.position_.z -= 0.01f;

			weaponAnim.setRight(anim.getIsRight());
			weaponAnim.setCurrentIndex(anim.getCurrentIndex());

		}
	}*/

	//if (!weaponBack_.expired())
	//{
	//	shared_ptr<Entity>& weapon = weaponBack_.lock();
	//	if (weapon->hasComponent<Transform>() && weapon->hasComponent<AtlasAnimation>())
	//	{
	//		Transform& weaponTransform = weapon->getComponent<Transform>();
	//		AtlasAnimation& weaponAnim = weapon->getComponent<AtlasAnimation>();
	//		weaponTransform.position_ = transform.position_;
	//		weaponTransform.position_.z -= 0.01f;

	//		weaponAnim.setRight(anim.getIsRight());
	//		weaponAnim.setCurrentIndex(anim.getCurrentIndex());

	//	}
	//}
}

void PlayerController::setReCameraSetting()
{
	
	//카메라좌표-카메라width/2 =끝좌표 (2968/2)
	_vec2 mapSize = GameManager::getInstance()->getCurrentMap()->getComponent<FarBackGround>().mapSize_;
	entity->getComponent<Camera>().setOnLock(_vec2(0.f - mapSize.x / 2.f + SCREEN_WIDTH / 2, 0.f - mapSize.y / 2.f + SCREEN_HEIGHT / 2-110.f), _vec2(0.f + mapSize.x / 2.f - SCREEN_WIDTH / 2, 0.f + mapSize.y / 2.f - SCREEN_HEIGHT / 2));
	
}

void PlayerController::OnMove()
{
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Player Controller need transform component");
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Status& status = entity->getComponent<Status>();


	//if (stateMachine.getCurrentStateName() == L"flash")
		//return;




	rigidbody.direction_ = { 0.f,0.f,0.f };
	if (Input.keyPressing(DIK_UP) && rigidbody.inRope_ && !rigidbody.topRope_)
		stateMachine.transitionState(ROPE);
	
	if (Input.keyPressing(DIK_DOWN) && rigidbody.inRope_ && rigidbody.topRope_)
		stateMachine.transitionState(ROPE);
	if (Input.keyPressing(DIK_DOWN) && !rigidbody.inRope_ && rigidbody.onGround_)
		stateMachine.transitionState(KNEELDOWN);
	
		if (Input.keyPressing(DIK_LEFT))
			rigidbody.direction_ += {-(float)status.moveSpeed_/200.f, 0.f, 0.f};


		if (Input.keyPressing(DIK_RIGHT))
			rigidbody.direction_ += {(float)status.moveSpeed_/200.f, 0.f, 0.f};

		
	
	D3DXVec3Normalize(&rigidbody.direction_, &rigidbody.direction_);

	float moveLen = D3DXVec3Length(&rigidbody.direction_);
	if (moveLen > 0.f)
	{
		/*if(Input.commandCheck(anim.getIsRight(),DIK_RIGHT, DIK_RIGHT))
			stateMachine.transitionState(DASH);
		else*/
			stateMachine.transitionState(WALK);

	}
	if (invincibleTimer_)
	{
		invincibleTime_ += TimeManager::getInstance()->getDeltaTime();
		if (invincibleTime_ > 2.f)
		{
			entity->getComponent<Status>().invincible_ = false;
			invincibleTime_ = 0.f;
			invincibleTimer_ = false;
		}

	}

		
	if (Input.keyDown(DIK_2))
		equip(2);
	if (Input.keyDown(DIK_3))
		equip(3);
	if (Input.keyDown(DIK_4))
		equip(4);
	if (Input.keyDown(DIK_5))
		equip(5);
	if (Input.keyDown(DIK_6))
		equip(6);
	//if (Input.keyDown(DIK_6))
		//equip(0);



}

void PlayerController::OnAttack()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	if (Input.keyPressing(DIK_X))
	{
		if(stateMachine.getCurrentStateName()!=L"attack_1")
			stateMachine.transitionState(ATTACK);

		
	}
}

void PlayerController::OnJump()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Rigidbody& rb = entity->getComponent<Rigidbody>();
	if (Input.keyDown(DIK_C))
	{
		if (stateMachine.getCurrentStateName() == L"kneeldown")
		{
			rb.addForce(_vec3(0.f, -100.f, 0.f));
			//entity->getComponent<BoxCollider>().setBoxActive(false);
			//entity->getComponent<BoxCollider>().setBoxActive(false);
		}
		stateMachine.transitionState(JUMP);
		stateMachine.transitionState(STAND);

	}

	if (Input.keyDown(DIK_SPACE))
	{
	
		if(stateMachine.getCurrentStateName()==L"jump")
		stateMachine.changeState(L"flash");

	}

	if(!rb.onGround_ && rb.getUseGravity() &&!rb.topRope_)
		stateMachine.transitionState(JUMP);

}

void PlayerController::OnSkill()
{
	entity->getComponent<Skill>().checkSkillAvailableAndExecute();
	//sound_.lock()->getComponent<Sound>().PlaySoundEffect(0);

}

void PlayerController::commandInput()
{
	Input.keyDown(DIK_UP);
	Input.keyDown(DIK_DOWN);
	Input.keyDown(DIK_LEFT);
	Input.keyDown(DIK_RIGHT);
	Input.keyDown(DIK_Z);
	Input.keyDown(DIK_X);
	Input.keyDown(DIK_C);
	Input.keyDown(DIK_SPACE);
}
//
//void PlayerController::sendPlayerData()
//{
//#ifdef _DEBUG
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Entity must need Transform component");
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Entity must need AtlasAnimation component");
//#endif
//	Transform& transform = entity->getComponent<Transform>();
//	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
//
//	unique_ptr<UdpCharacter> characterData = make_unique<UdpCharacter>();
//	int userIDN, entityNumber;
//	Entity::ENTITYTYPE entityType;
//	entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);
//
//	characterData->objectType_ = 1;
//
//	characterData->userIDN_ = userIDN;
//	characterData->objectNumber_ = entityNumber;
//	characterData->subType_ = 1; //1: fighter, 2: swordman
//	characterData->currentSpriteIndex_ = anim.getCurrentIndex();
//	characterData->pX_ = transform.position_.x;
//	characterData->pY_ = transform.position_.y;
//	characterData->pZ_ = transform.position_.z;
//	characterData->isRight_ = anim.getIsRight();
//
//
//	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(characterData));
//
//
//}

void PlayerController::checkExpiredAndMakeAttackbox()
{
	if (attackBox_.expired())
	{
		shared_ptr<Entity>& attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->addComponent<AttackBox>();
		attackBox->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"attackbox");
		EntityManager::getInstance()->insertEntity(attackBox);

		attackBox_ = attackBox;
	}
}
//
//void PlayerController::checkHostSceneChanged()
//{
//	//호스트가 아닌 파티원들만 메시지 체크
//	if (NetworkManager::getInstance()->networkStruct_.party.hostIDN_ == NetworkManager::getInstance()->thisUser_.userIDN_)
//		return;
//
//	int currentSceneNumber = SceneManager::getInstance()->getSceneNumberByName(SceneManager::getInstance()->GetCurrentSceneName());
//
//	//씬 변경 메시지 받음
//	if (NetworkManager::getInstance()->networkStruct_.currentState == currentSceneNumber)//바뀌지 않음
//		return;
//
//	wstring changeSceneName = SceneManager::getInstance()->getSceneNameByNumber(NetworkManager::getInstance()->networkStruct_.currentState);
//	if (wcscmp(L"", changeSceneName.c_str()) == 0) //해당하는 씬이 없음
//		return;
//
//
//	SceneManager::getInstance()->changeScene(changeSceneName);
//
//}



void PlayerController::getDamaged(Entity* attackboxEntity)
{
	if (entity->getComponent<Status>().isSuperArmor_)
		return;


	
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	stateMachine.changeState(L"damaged");

	float myX = entity->getComponent<Transform>().position_.x;
	float attackBoxX = attackboxEntity->getComponent<Transform>().position_.x;

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();


	_vec3 direction;


	//오른쪽에서 온 공격이면 왼쪽으로튕김
	if (myX < attackBoxX)
		direction = { -1.1f, 0.f, 0.f };
	else
		direction = { +1.1f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);

	entity->getComponent<Sound>().PlaySoundEffect(13);
}

void PlayerController::getDowned(Entity* attackboxEntity)
{
	if (entity->getComponent<Status>().isSuperArmor_)
		return;
	float myX = entity->getComponent<Transform>().position_.x;
	float attackBoxX = attackboxEntity->getComponent<Transform>().position_.x;

	Rigidbody& rigidbody = entity->getComponent<Rigidbody>();


	_vec3 direction;
	//오른쪽에서 온 공격이면 왼쪽으로튕김
	if (myX < attackBoxX)
		direction = { -1.f, 0.f, 0.f };
	else
		direction = { +1.f, 0.f, 0.f };

	rigidbody.setForce((rigidbody.direction_ + direction) * ATTACK_ACCEL);
	entity->getComponent<Sound>().PlaySoundEffect(12);

}

void PlayerController::getStunned(Entity* attackboxEntity)
{
}

void PlayerController::enterCollider(Entity * colliderEntity)
{
	


	

	if (colliderEntity->getType() == Entity::ENTITYTYPE::ENEMY && colliderEntity->getName() != L"attackbox")
	{
		Status& status = entity->getComponent<Status>();
	
		if (status.invincible_)
			return;
		invincibleTimer_ = true;
		entity->getComponent<Status>().invincible_ = true;

		Status &enemyStatus = colliderEntity->getComponent<Status>();
		
		float totalDamage = enemyStatus.magicalAttack_ + enemyStatus.physicalAttack_;
		GameManager::getInstance()->makeDamageFont(DNFUI::UItype::Dnum0,totalDamage, entity->getComponent<Transform>().position_ + _vec3(0.f, 100.f, 0.f));
		status.hp_ -= totalDamage;
		getDamaged(colliderEntity);
	}

	if (colliderEntity->getName() == L"attackbox")
	{
		Status& status = entity->getComponent<Status>();
		Status& enemyStatus = colliderEntity->getComponent<Status>();
		if (status.invincible_)
			return;
		invincibleTimer_ = true;
		entity->getComponent<Status>().invincible_ = true;
		getDamaged(colliderEntity);
	}

}

void PlayerController::stayCollider(Entity * colliderEntity)
{
	

	if (colliderEntity->getType() == Entity::ENTITYTYPE::FILDITEM || colliderEntity->getType() == Entity::ENTITYTYPE::GOLD )
	{
		if (Input.keyDown(DIK_Z))
		{
			entity->getComponent<Sound>().PlaySoundEffect(0);
			colliderEntity->getComponent<Item>().Absorb();
			
			
		}
	}

	
}

void PlayerController::initialize()
{

	//addComponent할 때, 인자 넣어야하는 컴포넌트 있음(각각의 컴포넌트 생성자 참고)
	entity->addComponent<Status>();
	entity->getComponent<Status>().setDamagedFunction(bind(&PlayerController::getDamaged, this, placeholders::_1));
	entity->getComponent<Status>().setDownedFunction(bind(&PlayerController::getDowned, this, placeholders::_1));
	entity->getComponent<Status>().setStunnedFunction(bind(&PlayerController::getStunned, this, placeholders::_1));

	//entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<Transform>(initPosition_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

	entity->addComponent<BoxCollider>(_vec3(0.f, -15.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 50.f, 10.f));
	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&PlayerController::enterCollider, this, placeholders::_1),
		bind(&PlayerController::stayCollider, this, placeholders::_1),
		bind(&PlayerController::exitCollider, this, placeholders::_1));

	entity->addComponent<Rigidbody>().setMass(1.f);
	entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);
	entity->getComponent<Rigidbody>().setUseGravity(true);
	entity->getComponent<Rigidbody>().onGround_ = true;

	entity->addComponent<Camera>(Camera::CAMERA_MODE::ORTHOGONAL, _vec3(0.f, 0.f, -1.f), _vec3(0.f, 0.f, 1.f), SCREEN_WIDTH , SCREEN_HEIGHT);
	entity->getComponent<Camera>().setOnTrace(50.f, 50.f);
	//카메라좌표-카메라width/2 =끝좌표 (2968/2)
	_vec2 mapSize = GameManager::getInstance()->getCurrentMap()->getComponent<FarBackGround>().mapSize_;
	entity->getComponent<Camera>().setOnLock(_vec2(0.f - mapSize.x / 2.f + SCREEN_WIDTH / 2, 0.f - mapSize.y / 2.f + SCREEN_HEIGHT / 2-110.f), _vec2(0.f + mapSize.x / 2.f - SCREEN_WIDTH / 2, 0.f + mapSize.y / 2.f - SCREEN_HEIGHT / 2));

	
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	entity->addComponent<Skill>();
	entity->addComponent<StateMachine>();

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.setUserPivot(_vec2(0.f, 5.f));

	//플레이어 데이터 로드
	ExcelLoader::loadPlayerData(L"../ExcelFiles/PlayerInfo.xlsx", entity, className_.c_str());


	entity->getComponent<Status>().attackSpeed_=6;
	entity->addComponent<BUFF>();

	//공격체 세팅
	shared_ptr<Entity>& attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	attackBox->addComponent<AttackBox>();
	attackBox->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"attackbox");
	EntityManager::getInstance()->insertEntity(attackBox);

	attackBox_ = attackBox;






	//inventory

	shared_ptr<Entity> inventory = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	inventory->addComponent<Inventory>(entity);
	inventory->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"inventory");
	EntityManager::getInstance()->insertEntity(inventory);
	inventory_ = inventory;

	//기본표창


	shared_ptr<Entity> basicSurigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	basicSurigum->setTypeAndName(Entity::ENTITYTYPE::ITEM, L"뇌전 수리검");
	basicSurigum->addComponent<Item>(L"뇌전 수리검");
	EntityManager::getInstance()->insertEntity(basicSurigum);
	inventory_.lock()->getComponent<Inventory>().getItem(basicSurigum.get());
	basicSurigum->getComponent<Rigidbody>().setUseGravity(false);
	playerSurigumName_ = L"surigum";

	//사용중 표창 표시


	usingWeaponUI = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	usingWeaponUI->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"usingWeaponUI");
	usingWeaponUI->addComponent<EmptyUI>(basicSurigum.get());
	EntityManager::getInstance()->insertEntity(usingWeaponUI);

	usingWeaponUI->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	usingWeaponUI->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/itemActive.png");
	usingWeaponUI->getComponent<BoxCollider>().transform_.scale_ = _vec3(0.f, 0.f, 0.f);


	string playSound[] = {
		"../resource/soundEffect/basic/get.mp3", //아이템획득  0
	"../resource/soundEffect/basic/portion.mp3", //포션  1
	"../resource/soundEffect/basic/jump.ogg",   //점프   2
	  

		"../resource/soundEffect/simpleskill/boast.mp3",   //부스터 3   
			"../resource/soundEffect/simpleskill/haist.mp3",   //헤이스트 4
			"../resource/soundEffect/simpleskill/flashJump.mp3",   //플래시점프 5
			"../resource/soundEffect/simpleskill/darksite.mp3",   //다크사이트 6
			"../resource/soundEffect/simpleskill/shadowPartner.mp3",   //쉐도우파트너 7


			"../resource/soundEffect/attack/normalThrow.mp3",   //표창던지기 8
			"../resource/soundEffect/attack/normalHit.mp3",   //표창맞음 9

			"../resource/soundEffect/attack/tripleHit.mp3",   //트리플맞음 10
			"../resource/soundEffect/attack/use3.mp3",   //트리플 11


			"../resource/soundEffect/attack/shineHit.mp3",   //샤인힛 12
			"../resource/soundEffect/attack/bigHit.mp3",   //빅힛 13

			"../resource/soundEffect/attack/shineUse.mp3",   //샤인유즈 14

				"../resource/soundEffect/bigsurigum/use.mp3",   //use 15
				"../resource/soundEffect/bigsurigum/loop.mp3",   //loop 16
					"../resource/soundEffect/bigsurigum/die.mp3",   //die 17
	};


	entity->addComponent<Sound>().CreateEffectSound(_countof(playSound), playSound);

	entity->addComponent<DXFont>();

	RT_.left = (LONG)(SCREEN_WIDTH / 2 + 61);
	RT_.right = (LONG)(SCREEN_WIDTH);
	RT_.top = (LONG)(SCREEN_HEIGHT / 2 - 205 + (0) * 52-60);
	RT_.bottom = (LONG)(SCREEN_HEIGHT);

	text_ = L"";
	entity->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT_, text_.c_str(), D3DXCOLOR(0, 0, 0, 1));

}


void PlayerController::update()
{
	//updateWeaponPositionAndAnimation();
	checkExpiredAndMakeAttackbox();
	commandInput();

	OnMove();
	OnAttack();
	OnJump();
	OnSkill();
	


	if (Input.keyDown(DIK_M))
	{
		//entity->getComponent<Transform>().position_ = { 0.f, 200.f, 0.f };
		entity->getComponent<Status>().mp_ = entity->getComponent<Status>().maxMp_;
	}

	
	Transform& trans=entity->getComponent<Transform>();
	AtlasAnimation& anim= entity->getComponent<AtlasAnimation>();

	//if(STAGE_PLAY_SCENE/1000 == NetworkManager::getInstance()->networkStruct_.currentState/1000)
		//sendPlayerData();

	if (shoot_)
	{
		shootTimer_ += TimeManager::getInstance()->getDeltaTime();

		if (!entity->getComponent<BUFF>().nowShadow)
		{
			if (shootTimer_ > 0.2f)
			{

				if (!anim.getIsRight())
					surigumDir_ = _vec3(30.f, 0.f, 0.f);
				else
					surigumDir_ = _vec3(-30.f, 0.f, 0.f);

				shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
				surigum->addComponent<Bullet>(!shootCount_, trans.position_ + surigumDir_, anim.getIsRight(), playerSurigumName_);
				EntityManager::getInstance()->insertEntity(surigum);
				entity->getComponent<Sound>().PlaySoundEffect(8);


				shootCount_ += 1;
				shootTimer_ = 0.f;
				if (shootCount_ >= 3)
				{
					shoot_ = false;
					shootCount_ = 0;
				}
			}
		}
		else
		{
			if (shootTimer_ > 0.13f)
			{

				if (!anim.getIsRight())
				{
					surigumDir_ = _vec3(30.f, 0.f, 0.f);
				//	shadowSurigumDir_= _vec3(-20.f, 0.f, 0.f);
				}
				else
				{
					surigumDir_ = _vec3(-30.f, 0.f, 0.f);
					//shadowSurigumDir_ = _vec3(20.f, 0.f, 0.f);
				}

				shared_ptr<Entity> surigum = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				surigum->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
				surigum->addComponent<Bullet>(!shootCount_, trans.position_ + surigumDir_, anim.getIsRight(), playerSurigumName_);
				EntityManager::getInstance()->insertEntity(surigum);
				entity->getComponent<Sound>().PlaySoundEffect(8);

				//shared_ptr<Entity> surigum2 = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				//surigum2->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"surigum,");
				//surigum2->addComponent<Bullet>(false, trans.position_ + surigumDir_+shadowSurigumDir_, anim.getIsRight(), playerSurigumName_);
				//EntityManager::getInstance()->insertEntity(surigum2);


				shootCount_ += 1;
				shootTimer_ = 0.f;
				if (shootCount_ >= 6)
				{
					shoot_ = false;
					shootCount_ = 0;
				}
			}
		}
	}

	

}

void PlayerController::lateUpdate()
{

	if (GameManager::getInstance()->getShop() != nullptr )
	{
		
		ItemShop& shop = GameManager::getInstance()->getShop()->getComponent<ItemShop>();
		text_ = L"";
		if (shop.isOn_)
		{
			text_ += L"                                         " + to_wstring(inventory_.lock()->getComponent<Inventory>().myMoney_);
			text_+= L"\n\n\n\n\n";

			for (int i = 0; i < 5; i++)
			{
				if (shop.playerItem[i]->getComponent<Item>().name_ == L"blank")
					continue;
				text_ += shop.playerItem[i]->getComponent<Item>().name_ + L"\n\n" + to_wstring(shop.playerItem[i]->getComponent<Item>().price_) + L" 메소";
				text_ += L"\n\n\n";
			}

		}
		
		entity->getComponent<DXFont>().setStr(text_.c_str());


	}
	
}

void PlayerController::render()
{
	Status& status = entity->getComponent<Status>();
	//entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("onOutline", status.isSuperArmor_), make_pair("outlineTimer", status.superArmorTimer_*3.f));
	//entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("onTint", status.isAttackUp_), make_pair("tintColor", _vec3(1.f, 0.f, 0.f)),make_pair("tintTimer",sinf(status.attackUpTimer_*5.f)/2.f+0.5f));
	
	////
	if (alpha)
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;
	else
		entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_INVSRCALPHA;
		

	entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("onVanish", alpha), make_pair("vanishAlpha", 0.9f));
	////

	//entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("onTint", status.isAttackUp_));

	entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("damagedShader", entity->getComponent<Status>().invincible_));
}

void PlayerController::release()
{
}

void PlayerController::equip(int type)
{
	if (type == 2)
	{
		if (weaponBack_.lock() != nullptr)
		{
			weaponBack_.lock()->setActive(false);
			weaponBack_.lock() = nullptr;
		}
		GameManager::getInstance()->equipWeapon(L"cap", entity);
	}
	else if (type == 3)
	{
		if (weaponFront_.lock() != nullptr)
		{
			weaponFront_.lock()->setActive(false);
			weaponFront_.lock() = nullptr;
		}
		GameManager::getInstance()->equipWeapon(L"dress1", entity);
	}
	else if (type == 4)
	{
		if (weaponFront_.lock() != nullptr)
		{
			weaponFront_.lock()->setActive(false);
			weaponFront_.lock() = nullptr;
		}
		GameManager::getInstance()->equipWeapon(L"dress2", entity);
	}
	else if (type == 6)
	{
		GameManager::getInstance()->changeSceneAllPlayer(L"RoomCash");

	}
	else
	{
		if (weaponFront_.lock() != nullptr)
		{
			weaponFront_.lock()->setActive(false);
			weaponFront_.lock() = nullptr;
		}
		if (weaponBack_.lock() != nullptr)
		{
			weaponBack_.lock()->setActive(false);
			weaponBack_.lock() = nullptr;
		}
	}
}


