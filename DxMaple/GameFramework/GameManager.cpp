#include "stdafx.h"
#include "GameManager.h"
#include "ExcelLoader.h"
#include "BossRoom.h"
#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"
#include "Room5.h"
#include "RoomAirport.h"
#include "RoomCash.h"
#include "RoomBlue1.h"
#include "RoomBlue2.h"
#include "RoomBlue3.h"
#include "RoomBlue2_2.h"
IMPLEMENT_SINGLETON(GameManager)

GameManager::GameManager()
{
}
GameManager::~GameManager()
{
}

void GameManager::setPlayersPosition(_vec3 position)
{
	//auto playerEntities = EntityManager::getInstance()->getEntityList(Entity::ENTITYTYPE::PLAYER);
	auto player = GameManager::getInstance()->getPlayer();//(Entity::ENTITYTYPE::PLAYER);

	//for (auto& playerEntity : *playerEntities)
	//{
		//if (playerEntity->hasComponent<PlayerController>() || playerEntity->hasComponent<OtherPlayerController>())
		//{
			//srand((unsigned int)time(NULL));
			//int randumNumberX = rand() % 3;
			//int randumNumberZ = rand() % 3;
			//randumNumberX -= 1; //-1,0,1
			//randumNumberZ -= 1; //-1,0,1

			Transform& transform = player->getComponent<Transform>();
			transform.position_ = position; //+ _vec3((float)randumNumberX*10.f, 0.f, (float)randumNumberZ*10.f);
	//	}
//	}

}

int GameManager::getTotalPlayer() const
{
	int playerCount = 0;
	auto playerEntities = EntityManager::getInstance()->getEntityList(Entity::ENTITYTYPE::PLAYER);
	for (auto& playerEntity : *playerEntities)
	{
		if (playerEntity->hasComponent<PlayerController>() || playerEntity->hasComponent<OtherPlayerController>())
			++playerCount;
	}

	return playerCount;
}

void GameManager::equipWeapon(const wchar_t* weaponName, Entity* playerEntity)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(nullptr != playerEntity, "player entity is nullptr");
	ASSERT_MESSAGE_NULLRETURN(playerEntity->hasComponent<PlayerController>(), "this is not player");
#endif
	wstring frontName = weaponName;
	wstring backName = weaponName;

	frontName += L"_front";
	backName += L"_back";

	if (weaponName != L"cap")
	{
		shared_ptr<Entity> frontWeaponEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		frontWeaponEntity->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"frontWeapon");
		frontWeaponEntity->addComponent<Weapon>(frontName);
		EntityManager::getInstance()->insertEntity(frontWeaponEntity);

		playerEntity->getComponent<PlayerController>().setWeaponFront(frontWeaponEntity);
	}
	else
	{
		shared_ptr<Entity> backWeaponEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		backWeaponEntity->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"backWeapon");
		backWeaponEntity->addComponent<Weapon>(backName);
		EntityManager::getInstance()->insertEntity(backWeaponEntity);

		playerEntity->getComponent<PlayerController>().setWeaponBack(backWeaponEntity);
	}
}

void GameManager::makeWeaponEffect(const wchar_t* texturePath, const wchar_t* atlasPath, Entity* weaponEntity)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(nullptr != weaponEntity, "weapon entity is nullptr");
	ASSERT_MESSAGE_NULLRETURN(weaponEntity->hasComponent<Weapon>(), "this is not weapon");
#endif
	shared_ptr<Entity> weaponEffect = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	weaponEffect->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"weaponEffect");
	weaponEffect->addComponent<WeaponEffect>(texturePath,atlasPath);
	EntityManager::getInstance()->insertEntity(weaponEffect);

	weaponEntity->getComponent<Weapon>().setWeaponEffect(weaponEffect);


}

void GameManager::makePlayerSelf(wstring className, _vec3 position)
{
	shared_ptr<Entity> playerSelf = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();

	playerSelf->addComponent<PlayerController>(className, position);
	playerSelf->setTypeAndName(Entity::ENTITYTYPE::PLAYER, className);
	EntityManager::getInstance()->insertEntity(playerSelf);
	player_ = playerSelf;
}

void GameManager::makePlayerOther(wstring className, _vec3 position, int userIDN, int entityNumber)
{
	shared_ptr<Entity> playerOther = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();


	playerOther->addComponent<OtherPlayerController>(className, position);
	playerOther->setTypeAndName(Entity::ENTITYTYPE::PLAYER, className);
	playerOther->setUserIDN(userIDN);
	playerOther->setEntityNumber(entityNumber);

	EntityManager::getInstance()->insertEntity(playerOther);
}




void GameManager::makeDamageFont(DNFUI::UItype damageUIType, double damage, _vec3 position)
{
	shared_ptr<Entity> damageFont;

	int intDamage = (int)damage;

	_vec3 fontPosition = position;
	do
	{
		int digit = (int)intDamage % 10;

		damageFont = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		damageFont->addComponent<DNFUI>(static_cast<DNFUI::UItype>(damageUIType + digit), fontPosition);
		damageFont->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"damagefont");
		EntityManager::getInstance()->insertEntity(damageFont);

		if (intDamage / 10 == 0)
			break;

		intDamage /= 10;
		fontPosition += _vec3(-25.f, 0.f, -1.f);
	} while (1);
}
//
//void GameManager::makeCriticalDamageFont(double damage, _vec3 position)
//{
//	shared_ptr<Entity> damageFont;
//
//	int intDamage = (int)damage;
//
//
//	_vec3 fontPosition = position - _vec3(0.f, 40.f, 0.f);
//	do
//	{
//		int digit = (int)intDamage % 10;
//
//		damageFont = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
//		damageFont->addComponent<DNFUI>(static_cast<DNFUI::UItype>(DNFUI::UItype::Cnum0 + digit), fontPosition);
//		damageFont->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"damagefont");
//		EntityManager::getInstance()->insertEntity(damageFont);
//
//		if (intDamage / 10 == 0)
//			break;
//
//		intDamage /= 10;
//		fontPosition += _vec3(-25.f, 0.f, -0.0001f);
//	} while (1);
//
//}
//
//void GameManager::makeEnemyFont(double damage, _vec3 position)
//{
//
//	shared_ptr<Entity> damageFont;
//
//	int intDamage = (int)damage;
//	
//
//	_vec3 fontPosition = position - _vec3(0.f, 40.f, 0.f);
//	do
//	{
//		int digit = (int)intDamage % 10;
//
//		damageFont = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
//		damageFont->addComponent<DNFUI>(static_cast<DNFUI::UItype>(DNFUI::UItype::Hnum0 + digit), fontPosition);
//		damageFont->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"damagefont");
//		EntityManager::getInstance()->insertEntity(damageFont);
//
//		if (intDamage / 10 == 0)
//			break;
//
//		intDamage /= 10;
//		fontPosition += _vec3(-25.f, 0.f, -1.f);
//	} while (1);
//
//}


void GameManager::makeEnemyHitBox( Entity* attackEntity)
{

#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(nullptr != attackEntity, "attackEntity  is nullptr");
	//ASSERT_MESSAGE_NULLRETURN(weaponEntity->hasComponent<Weapon>(), "this is not weapon");
#endif
	shared_ptr<Entity> hitBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();

	//hitBox->addComponent<WeaponEffect>(texturePath, atlasPath);
	EntityManager::getInstance()->insertEntity(hitBox);

	attackEntity->getComponent<Weapon>().setWeaponEffect(hitBox);

}

shared_ptr<Entity> GameManager::makeEffect(wstring atlasPath)
{
	
	shared_ptr<Entity> effect = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	effect->addComponent<CommonEffect>(atlasPath);
	effect->setTypeAndName(Entity::ENTITYTYPE::EFFECT, L"effect");
	EntityManager::getInstance()->insertEntity(effect);

	return effect;
}

void GameManager::makeOrUpdateOtherAttackBox(int userIDN, int objectNumber, int objectType, int userType, int attackType, _vec3 position, _vec3 size, double physicalDamage, double magicalDamage)
{
	Entity* findEntity = EntityManager::getInstance()->findEntity(userIDN, objectNumber, (Entity::ENTITYTYPE)objectType);
	if (nullptr != findEntity)
	{
		//해당 엔티티 업데이트
#ifdef _DEBUG
		ASSERT_MESSAGE_NULLRETURN(findEntity->hasComponent<OtherAttackBox>(), "this entity must have OtherAttackBox component");
#endif
		findEntity->getComponent<OtherAttackBox>().updatePosition(position);

	}
	else
	{
		//생성
		shared_ptr<Entity> attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		attackBox->setUserIDN(userIDN);
		attackBox->setEntityNumber(objectNumber);
		attackBox->setTypeAndName((Entity::ENTITYTYPE)objectType, L"attackbox");
		attackBox->addComponent<OtherAttackBox>((OtherAttackBox::USER)userType, (OtherAttackBox::ATTACKTYPE)attackType, position, size, physicalDamage, magicalDamage);
		EntityManager::getInstance()->insertEntity(attackBox);
	}

}

//잘못옮긴듯경빈
//
//void GameManager::eraseNetworkEntity(int userIDN, int objectNumber,int objectType)
//{
//	
//	EntityManager::getInstance()->eraseEntity(userIDN, objectNumber, (Entity::ENTITYTYPE)objectType);
//
//}

void GameManager::changeSceneAllPlayer(wstring sceneName)
{
	if (player_.expired())
		return;

	if(sceneName==L"Room5")
		SceneManager::getInstance()->insertScene(L"Room5", new Room5);
	else if (sceneName == L"Room4")
		SceneManager::getInstance()->insertScene(L"Room4", new Room4);
	else if (sceneName == L"Room3")
		SceneManager::getInstance()->insertScene(L"Room3", new Room3);
	else if (sceneName == L"Room2")
		SceneManager::getInstance()->insertScene(L"Room2", new Room2);
	else if (sceneName == L"Room1")
		SceneManager::getInstance()->insertScene(L"Room1", new Room1);

	else if (sceneName == L"RoomAirport")
		SceneManager::getInstance()->insertScene(L"RoomAirport", new RoomAirport);
	else if (sceneName == L"BossRoom")
		SceneManager::getInstance()->insertScene(L"BossRoom", new BossRoom);
	else if (sceneName == L"RoomCash")
		SceneManager::getInstance()->insertScene(L"RoomCash", new RoomCash);
	else if (sceneName == L"RoomBlue1")
		SceneManager::getInstance()->insertScene(L"RoomBlue1", new RoomBlue1);
	else if (sceneName == L"RoomBlue2")
		SceneManager::getInstance()->insertScene(L"RoomBlue2", new RoomBlue2);
	else if (sceneName == L"RoomBlue2_2")
		SceneManager::getInstance()->insertScene(L"RoomBlue2_2", new RoomBlue2_2);
	else if (sceneName == L"RoomBlue3")
		SceneManager::getInstance()->insertScene(L"RoomBlue3", new RoomBlue3);

	SceneManager::getInstance()->changeScene(sceneName);
	int sceneNumber = SceneManager::getInstance()->getSceneNumberByName(sceneName);
	if (-1 == sceneNumber)
		return;

	//NetworkManager::getInstance()->networkStruct_.currentState = sceneNumber;
	//NetworkManager::getInstance()->tcpClient_.inputEnterStageSelectMessage(sceneNumber);

}



//void GameManager::makePlayerSelf(int classType, _vec3 position)
//{
//	shared_ptr<Entity> playerSelf = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
//	playerSelf->addComponent<PlayerController>(classType, position);
//
//	EntityManager::getInstance()->insertEntity(playerSelf);
//}
