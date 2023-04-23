#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class Room1 :public IScene
{
public:
	Room1() {}
	virtual ~Room1() {}
	shared_ptr<Entity> player = GameManager::getInstance()->getPlayer();

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
		entity->addComponent<FarBackGround>(4);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);








		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData-inship2.json", ifstream::binary); //데이터에 다 읽어옴

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


				if (doorEntity_.lock() == nullptr)
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door2");
					entity->addComponent<Door>(L"Room2");
					entity->getComponent<Transform>().position_ = _vec3(X, Y, 0.f);
					entity->getComponent<AtlasAnimation>().setAddPos(_vec3(5000.f, 0.f, 0.f));
					entityManager_->insertEntity(entity);
					doorEntity_ = entity;


					
					



				}
				else
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door2");
					entity->addComponent<Door>(L"Room2");
					entity->getComponent<Transform>().position_ = _vec3(X, Y , 0.f);
					entity->getComponent<AtlasAnimation>().setAddPos(_vec3(5000.f, 0.f, 0.f));
					entityManager_->insertEntity(entity);
					doorEntity_2 = entity;

					

				}
			}

			else if (jsonName == 2)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);


				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X-350.f, Y+185.f, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);


			}

		}



		_vec2 mapSize = GameManager::getInstance()->getCurrentMap()->getComponent<FarBackGround>().mapSize_;
		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(-mapSize.x / 2, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(mapSize.x / 2 - 10.f, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);






	/*	entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<GsSujue>();
		entity->getComponent<Transform>().position_ = { 200.f,0.f,-0.f };
		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<GsSujue>();
		entity->getComponent<Transform>().position_ = { 0.f,0.f,-0.f };
		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<GsSujue>();
		entity->getComponent<Transform>().position_ = { 600.f,0.f,-0.f };
		entityManager_->insertEntity(entity);*/




		
		player->getComponent<Transform>().position_ = _vec3(0.f,-100.f,0.f);
		player->getComponent<Camera>().setOnLock(_vec2(0.f,0.f), _vec2(0.f, 0.f));

	}

	virtual void update() override
	{
		entityManager_->update();

		if (!doorEntity_.expired())
		{
			
			player->getComponent<PlayerController>().tempPastArea = 2;
			doorEntity_.lock()->getComponent<Door>().checkAndChangeScene();
			
		}
		if (!doorEntity_2.expired())
		{
			
			player->getComponent<PlayerController>().tempPastArea = 1;
			doorEntity_2.lock()->getComponent<Door>().checkAndChangeScene();
			
		}
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