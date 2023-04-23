#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class RoomCash :public IScene
{
public:
	RoomCash() {}
	virtual ~RoomCash() {}


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
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"AA");
		entity->addComponent<FarBackGround>(7);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);








		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData-cash.json", ifstream::binary); //데이터에 다 읽어옴

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
				entity->addComponent<BounDary>(0, _vec3(X+100.f, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

			}
			else if (jsonName == 1)
			{


					playerPosition = _vec3(_vec3(X, Y + 10.f, 0.f));




				
			}

			else if (jsonName == 2)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X+100.f, Y, 0.f), _vec3(Width, Height, 1.f));
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











		auto player = GameManager::getInstance()->getPlayer();
		player->getComponent<Transform>().position_ = playerPosition;
		player->getComponent<PlayerController>().setReCameraSetting();

	}

	virtual void update() override
	{
		entityManager_->update();

		if (InputManager::getInstance()->keyDown(DIK_1))
			GameManager::getInstance()->changeSceneAllPlayer(SceneManager::getInstance()->pastSceneName_);

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