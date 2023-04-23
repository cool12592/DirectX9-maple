#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class Room5 :public IScene
{
public:
	Room5() {}
	virtual ~Room5() {}


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

		if (GameManager::getInstance()->getPlayer().get() == nullptr)
		{
			//bottom
			entity = sceneObjectPool_.acquire();
			entity->addComponent<DNFUI>(DNFUI::UItype::하단바, _vec3(0, -190, -1000.f));
			entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");
			entityManager_->insertEntity(entity);
			//bottom
			entity = sceneObjectPool_.acquire();
			entity->addComponent<DNFUI>(DNFUI::UItype::퀵슬롯, _vec3(0, -190, -1000.f));
			entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"QuickSlot");
			entityManager_->insertEntity(entity);
			//hp
			entity = sceneObjectPool_.acquire();
			entity->addComponent<DNFUI>(DNFUI::UItype::Hp, _vec3(-280, -190, -1001.f));
			entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");

			entityManager_->insertEntity(entity);
			//mp
			entity = sceneObjectPool_.acquire();
			entity->addComponent<DNFUI>(DNFUI::UItype::Mp, _vec3(280, -190, -1001.f));
			entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");

			entityManager_->insertEntity(entity);
			
			////inventory
			//entity = sceneObjectPool_.acquire();
			//entity->addComponent<DNFUI>(7, _vec3(0, 0, 20000));
			//entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"inventoryTitle");
			//entityManager_->insertEntity(entity);

	

		
		}


	    entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
		entity->addComponent<FarBackGround>(1);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);


		
	
		



		_vec3 playerPosition;

	//////////////////////////////////////////////////////////////
		ifstream data("GameData(Areve).json", ifstream::binary); //데이터에 다 읽어옴

		//std::string data;
		Json::Reader reader; //json리더기
		Json::Value root; //값을받아올 루트
		reader.parse(data, root); // 읽어온 데이터를 루트에 값으로 파싱해줌
		const Json::Value & arr = root["Point"]; //루트에 point부분(인덱스) 가져옴 

		for ( auto obj : arr)
		{
			
			auto jsonName = obj["Name"].asDouble();
			
			auto X = obj["X"].asDouble();
			auto Y = obj["Y"].asDouble();
			
			auto Width = obj["Width"].asDouble();
			auto Height = obj["Height"].asDouble();
			
			if (jsonName == 0)
			{
				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(0, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

				

			}
			else if (jsonName == 1)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door");
				entity->addComponent<Door>(L"Room4");
				entity->getComponent<Transform>().position_ = _vec3(X, Y+20.f, -1.f);
				entityManager_->insertEntity(entity);
				
				doorEntity_ = entity;
				
				if (X >700)
				{

				
					if (GameManager::getInstance()->getPlayer().get() == nullptr)
					{

						playerPosition = _vec3(X - 800, Y, 0.f);
						
					}
					else
					{
						playerPosition= _vec3(X, Y, 0.f);
				
					}

				}

			}
		
		}
		
		//밧줄
	/*	entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(1, _vec3(-525, -800.f, 0.f), _vec3(2, 170.f, 1.f));
		entityManager_->insertEntity(entity);*/

		_vec2 mapSize = GameManager::getInstance()->getCurrentMap()->getComponent<FarBackGround>().mapSize_;
		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(-mapSize.x/2, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(3, _vec3(mapSize.x/2-10.f, 0.f, 0.f), _vec3(10, 5000.f, 1.f));
		entityManager_->insertEntity(entity);
		

	
		if (GameManager::getInstance()->getPlayer().get() == nullptr)
		{


			entity = sceneObjectPool_.acquire();
			entity->setTypeAndName(Entity::ENTITYTYPE::PLAYER, L"player");
			entity->addComponent<PlayerController>();
			entity->getComponent<Transform>().position_ = playerPosition;
			GameManager::getInstance()->setPlayer(entity);
			entityManager_->insertEntity(entity);

			entity = sceneObjectPool_.acquire();
			entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"Light");
			entity->addComponent<Light>();
			entityManager_->insertEntity(entity);
		}
		else
		{
		
			auto player = GameManager::getInstance()->getPlayer();
			player->getComponent<Transform>().position_ = playerPosition;
			player->getComponent<PlayerController>().setReCameraSetting();
		}

	
	}

	virtual void update() override
	{
		entityManager_->update();
		if (!doorEntity_.expired())
		{
			if (InputManager::getInstance()->keyDown(DIK_UP))
				doorEntity_.lock()->getComponent<Door>().checkAndChangeScene();
		}
			
	

	}

	virtual void lateUpdate() override
	{
	//	aa.lock()->getComponent<BoxCollider>().transform_.rotation_.z += 0.001f;
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
	vector<shared_ptr<Entity>> remainMonster;
	shared_ptr<Entity> MapControllerEntity;

	weak_ptr<Entity> aa;

};