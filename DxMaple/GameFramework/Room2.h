#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class Room2 :public IScene
{
public:
	Room2() {}
	virtual ~Room2() {}

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
		entity->addComponent<FarBackGround>(3);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);
		map = entity;


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
		entity->addComponent<BackGround>();
		entityManager_->insertEntity(entity);
		





		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData-ship4.json", ifstream::binary); //데이터에 다 읽어옴

		//std::string data;
		Json::Reader reader; //json리더기
		Json::Value root; //값을받아올 루트
		reader.parse(data, root); // 읽어온 데이터를 루트에 값으로 파싱해줌
		const Json::Value& arr = root["Point"]; //루트에 point부분(인덱스) 가져옴 
		int k = 0;
		int obbTile = 0;
		for (auto obj : arr)
		{

			auto jsonName = obj["Name"].asDouble();

			auto X = obj["X"].asDouble();
			auto Y = obj["Y"].asDouble();

			auto Width = obj["Width"].asDouble();
			auto Height = obj["Height"].asDouble();

			if (jsonName == 0)
			{
				if (Y<515.f&&Y > -90.F)
				{
					obbTile += 1;

					if (obbTile == 1)
					{
						entity = sceneObjectPool_.acquire();
						entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
						entity->addComponent<BounDary>(0, _vec3(X+70.f, Y - 50.f, 0.f), _vec3(500.f, 5.f, 1.f));
						entityManager_->insertEntity(entity);
						entity->getComponent<BoxCollider>().transform_.rotation_.z = 18.3f;
						entity->getComponent<BounDary>().isOBB = true;
						entity->getComponent<BounDary>().hill = -1;
					
					}
					else if (obbTile == 2)
					{
						entity = sceneObjectPool_.acquire();
						entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
						entity->addComponent<BounDary>(0, _vec3(X, Y +20.f, 0.f), _vec3(800.f, 5.f, 1.f));
						entityManager_->insertEntity(entity);
						entity->getComponent<BoxCollider>().transform_.rotation_.z = 18.548f;
						entity->getComponent<BounDary>().isOBB = true;
						obbmap = entity;
						entity->getComponent<BounDary>().hill = -1;

					}
					else if (obbTile == 3)
					{
						entity = sceneObjectPool_.acquire();
						entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
						entity->addComponent<BounDary>(0, _vec3(X, Y +10.F, 0.f), _vec3(Width, 5.f, 1.f));
						entityManager_->insertEntity(entity);
						entity->getComponent<BoxCollider>().transform_.rotation_.z = 0.386f;
						//entity->getComponent<BounDary>().isOBB = true;
					}
					else if (obbTile == 4)
					{
						entity = sceneObjectPool_.acquire();
						entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
						entity->addComponent<BounDary>(0, _vec3(X, Y, 0.f), _vec3(800.f, 5.f, 1.f));
						entityManager_->insertEntity(entity);
						entity->getComponent<BoxCollider>().transform_.rotation_.z = 6.3;//6.34;
						//entity->getComponent<BounDary>().isOBB = true;
					}
					else if (obbTile == 5)
					{
						entity = sceneObjectPool_.acquire();
						entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
						entity->addComponent<BounDary>(0, _vec3(X+100.F, Y + 60.f, 0.f), _vec3(500.f, 5.f, 1.f));
						entityManager_->insertEntity(entity);
						entity->getComponent<BoxCollider>().transform_.rotation_.z = 6.85;//6.34;
						entity->getComponent<BounDary>().isOBB = true;
					}
					else if (obbTile == 6)
					{
						entity = sceneObjectPool_.acquire();
						entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
						entity->addComponent<BounDary>(0, _vec3(X, Y - 20.f, 0.f), _vec3(Width, Height, 1.f));
						entityManager_->insertEntity(entity);
						
					}
					continue;
				}
				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"땅");
				entity->addComponent<BounDary>(0, _vec3(X, Y-20, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

			

			}
			//문
			else if (jsonName == 1)
			{


				if (k == 1 || k == 3)
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"miniPortal");
					entity->addComponent<MiniPortal>();
					entity->getComponent<Transform>().position_ = _vec3(X, Y, 0.f);
					entityManager_->insertEntity(entity);
					miniportal.emplace_back(entity);
				}
				else
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"door");
					entity->addComponent<Door>(L"Room1");
					entity->getComponent<Transform>().position_ = _vec3(X, Y, 0.f);
					entity->getComponent<AtlasAnimation>().setAddPos(_vec3(5000.f, 0.f, 0.f));
					entityManager_->insertEntity(entity);
					doorEntity_.emplace_back(entity);
				}
				k++;



				
			
			}
			//밧줄
			else if (jsonName == 2)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);


			}

		}

		for (int i = 0; i < miniportal.size(); i++)
		{
			if (!miniportal[i].expired())
			{
				
			    if (i == 0)
					miniportal[i].lock()->getComponent<MiniPortal>().destination_ = miniportal[1].lock()->getComponent<Transform>().position_;
				
				else 
					miniportal[i].lock()->getComponent<MiniPortal>().destination_ = miniportal[0].lock()->getComponent<Transform>().position_;
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

		




	

		/*
		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<GsSujue>();
		entity->getComponent<Transform>().position_ = { 600.f,0.f,-0.f };
		entityManager_->insertEntity(entity);*/




		
		player->getComponent<PlayerController>().setReCameraSetting();
		if (player->getComponent<PlayerController>().tempPastArea == 1)
			player->getComponent<Transform>().position_ = doorEntity_[0].lock()->getComponent<Transform>().position_;
		else if (player->getComponent<PlayerController>().tempPastArea == 2)
			player->getComponent<Transform>().position_ = doorEntity_[1].lock()->getComponent<Transform>().position_;
		else
			player->getComponent<Transform>().position_ = _vec3(0.f,40.f,0.f);

		if (player->getComponent<Rigidbody>().inRope_ == true)
		{
			player->getComponent<Rigidbody>().inRope_ = false;
			player->getComponent<Rigidbody>().topRope_ = false;
		}
	
		
	}

	virtual void update() override
	{
		entityManager_->update();

		if (InputManager::getInstance()->keyDown(DIK_B))
			rotationstop = 1;
		if (InputManager::getInstance()->keyDown(DIK_N))
			rotationstop = -1;
		if (InputManager::getInstance()->keyDown(DIK_V))
			rotationstop = 0;
		if (rotationstop==1)
		{
			obbmap.lock()->getComponent<BoxCollider>().transform_.rotation_.z += 0.003f;
			cout << "각도도도" << obbmap.lock()->getComponent<BoxCollider>().transform_.rotation_.z << endl;
		}
		if (rotationstop == -1)
		{
			obbmap.lock()->getComponent<BoxCollider>().transform_.rotation_.z -= 0.003f;
			cout << "각도도도" << obbmap.lock()->getComponent<BoxCollider>().transform_.rotation_.z << endl;
		}

		for (int i = 0; i < miniportal.size(); i++)
		{
			if (!miniportal[i].expired())
			{
				if (InputManager::getInstance()->keyDown(DIK_UP))
					miniportal[i].lock()->getComponent<MiniPortal>().playerTransmission();
			}
		}

		for (int i = 0; i < doorEntity_.size(); i++)
		{
			if (!doorEntity_[i].expired())
			{
				if (InputManager::getInstance()->keyDown(DIK_UP))
					doorEntity_[i].lock()->getComponent<Door>().checkAndChangeScene();
			}
		}
		if (!map.expired())
		{
			if (map.lock()->getComponent<FarBackGround>().nextMapReady)
			{
				if (InputManager::getInstance()->keyDown(DIK_N))
				{
					GameManager::getInstance()->changeSceneAllPlayer(L"RoomBlue1");
				}
			}
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
	vector<weak_ptr<Entity>> miniportal;
	vector<weak_ptr<Entity>>  doorEntity_;
	vector<shared_ptr<Entity>> remainMonster;
	shared_ptr<Entity> MapControllerEntity;
	weak_ptr<Entity> map;

	weak_ptr<Entity> obbmap;
	int rotationstop = 0;
};