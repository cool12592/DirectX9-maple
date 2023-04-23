#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class BossRoom :public IScene
{
public:
	BossRoom() {}
	virtual ~BossRoom() {}


	// IScene을(를) 통해 상속됨
	virtual void initialize() override
	{
		if (!sceneObjectPool_.isEmpty())
			return;

		shared_ptr<Entity>& entity = sceneObjectPool_.acquire();
		entity->addComponent<PartyUI>();
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"PartyUI");
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->addComponent<Mouse>();
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"mouse");
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setMouse(entity);




		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
		entity->addComponent<FarBackGround>(6);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);








		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData-HornTail.json", ifstream::binary); //데이터에 다 읽어옴

		//std::string data;
		Json::Reader reader; //json리더기
		Json::Value root; //값을받아올 루트
		reader.parse(data, root); // 읽어온 데이터를 루트에 값으로 파싱해줌
		const Json::Value& arr = root["Point"]; //루트에 point부분(인덱스) 가져옴 

		for (auto obj : arr)
		{

			auto jsonName = obj["Name"].asDouble();

			auto X = obj["X"].asDouble();
			auto Y = obj["Y"].asDouble();

			auto Width = obj["Width"].asDouble();
			auto Height = obj["Height"].asDouble();

			if (jsonName == 0)
			{
				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
				entity->addComponent<BounDary>(0, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

			}
			else if (jsonName == 1)
			{

			
			}

			else if (jsonName == 2)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);


			}

		}

		/////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////
		vector<_vec3> iceLocation;
		vector<_vec3> fireLocation;

		ifstream data2("GameData-hornTailSkill2.json", ifstream::binary); //데이터에 다 읽어옴

		//std::string data;
		Json::Reader reader2; //json리더기
		Json::Value root2; //값을받아올 루트
		reader2.parse(data2, root2); // 읽어온 데이터를 루트에 값으로 파싱해줌
		const Json::Value& arr2 = root2["Point"]; //루트에 point부분(인덱스) 가져옴 

		//shared_ptr<Entity> effect;
		for (auto obj : arr2)
		{

			auto jsonName = obj["Name"].asDouble();

			auto X = obj["X"].asDouble();
			auto Y = obj["Y"].asDouble();

			auto Width = obj["Width"].asDouble();
			auto Height = obj["Height"].asDouble();
		
			if (jsonName == 0)
			{
			//	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/midattack2effect");
			//	effect->getComponent<CommonEffect>().setEffect(nullptr, false, _vec3(X, Y+100.f, 0.f), 0.f, 1.f);
	
				fireLocation.emplace_back(_vec3(X, Y+100.f, 0));
			}
			else if (jsonName == 1)
			{
			//	effect = GameManager::getInstance()->makeEffect(L"../AtlasFiles/HornTail/Skill/leftattack2effect");
			//	effect->getComponent<CommonEffect>().setEffect(nullptr, false, _vec3(X, Y+170.f, 0.f), 0.f, 1.f);
				


				iceLocation.emplace_back(_vec3(X, Y+170.f, 0));

			}

			else if (jsonName == 2)
			{

			

			}

		}
		GameManager::getInstance()->setIcePostion(iceLocation);
		GameManager::getInstance()->setFirePostion(fireLocation);

		/////////////////////////////////////////////////////////////////////////
		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Summons_HonTail");
		entity->addComponent<Door>(L"NULL");
		entity->getComponent<Transform>().position_ = _vec3(480.f , 15.f, 0.f);
		entity->getComponent<AtlasAnimation>().setAddPos(_vec3(5000.f, 0.f, 0.f));
		entityManager_->insertEntity(entity);

		_vec2 mapSize = GameManager::getInstance()->getCurrentMap()->getComponent<FarBackGround>().mapSize_;
		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(-mapSize.x / 2, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(mapSize.x / 2 - 10.f, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);



	

	


	/*	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"HornTail");
		entity->addComponent<HornTail>(L"start");
		EntityManager::getInstance()->insertEntity(entity);*/



		auto player = GameManager::getInstance()->getPlayer();
		player->getComponent<Transform>().position_ = _vec3(0.f,-300.f,0.f);
		player->getComponent<PlayerController>().setReCameraSetting();

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
		//entityManager_->releaseAll();
		entityManager_->releaseEntity(Entity::ENTITYTYPE::UNKNOWN);
		//entityManager_->releaseEntity(Entity::ENTITYTYPE::PLAYER);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::ENEMY);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::MAP);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::TRAP);
		entityManager_->releaseEntity(Entity::ENTITYTYPE::EFFECT);
	}

	virtual void refresh()override
	{
		entityManager_->refresh();
	}
private:
	bool stageClear_ = false;
	weak_ptr<Entity> doorEntity_;
	weak_ptr<Entity> doorEntity_2;
	vector<shared_ptr<Entity>> remainMonster;
	shared_ptr<Entity> MapControllerEntity;



};