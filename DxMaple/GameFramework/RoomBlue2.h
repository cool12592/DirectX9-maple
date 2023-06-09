#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class RoomBlue2 :public IScene
{
public:
	RoomBlue2() {}
	virtual ~RoomBlue2() {}


	// IScene��(��) ���� ��ӵ�
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
		entity->addComponent<FarBackGround>(9);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);








		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData-bluemap2.json", ifstream::binary); //�����Ϳ� �� �о��

		//std::string data;
		Json::Reader reader; //json������
		Json::Value root; //�����޾ƿ� ��Ʈ
		reader.parse(data, root); // �о�� �����͸� ��Ʈ�� ������ �Ľ�����
		const Json::Value& arr = root["Point"]; //��Ʈ�� point�κ�(�ε���) ������ 

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
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"��");
				entity->addComponent<BounDary>(0, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

			}
			else if (jsonName == 1)
			{


				if (doorEntity_.lock() == nullptr)
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door2");
					entity->addComponent<Door>(L"RoomBlue2_2");
					entity->getComponent<Transform>().position_ = _vec3(X, Y +50.f, -1.f);
					entityManager_->insertEntity(entity);
					doorEntity_ = entity;


					if (SceneManager::getInstance()->pastSceneName_ == L"RoomBlue2_2")
					{


						playerPosition = _vec3(_vec3(X, Y +50.f, 0.f));

					}



				}
				else
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door2");
					entity->addComponent<Door>(L"RoomBlue1");
					entity->getComponent<Transform>().position_ = _vec3(X, Y + 30.f, -1.f);
					entityManager_->insertEntity(entity);
					doorEntity_2 = entity;

					if (SceneManager::getInstance()->pastSceneName_ == L"RoomBlue1")
					{
						playerPosition = _vec3(X, Y + 30.f, 0.f);

					}

				}
			}

			else if (jsonName == 2)
			{

				entity = sceneObjectPool_.acquire();
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
				entity->addComponent<BounDary>(1, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
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





		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { -200.f,-240.f,-0.f };
		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { -100.f,-240.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 0.f,-240.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 100.f,-240.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 200.f,-240.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 300.f,-240.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 400.f,-240.f,-0.f };
		entityManager_->insertEntity(entity);






		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 0.f,150.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { -100.f,150.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { -200.f,150.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 100.f,150.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"���̷���");
		entity->getComponent<Transform>().position_ = { 200.f,150.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		auto player = GameManager::getInstance()->getPlayer();
		player->getComponent<Transform>().position_ = playerPosition;
		player->getComponent<PlayerController>().setReCameraSetting();

	}

	virtual void update() override
	{
		entityManager_->update();



		if (!doorEntity_.expired())
		{
			if (InputManager::getInstance()->keyDown(DIK_UP))
				doorEntity_.lock()->getComponent<Door>().checkAndChangeScene();
		}
		if (!doorEntity_2.expired())
		{
			if (InputManager::getInstance()->keyDown(DIK_UP))
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

		//entityManager_->releaseEntity(Entity::ENTITYTYPE::GOLD);
		//entityManager_->releaseEntity(Entity::ENTITYTYPE::FILDITEM);
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