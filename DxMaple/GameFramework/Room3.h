#pragma once
#include "IScene.h"
#include "GameManager.h"
#include "SceneManager.h"

class Room3 :public IScene
{
public:
	Room3() {}
	virtual ~Room3() {}


	// IScene¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
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
		entity->addComponent<FarBackGround>(2);
		entityManager_->insertEntity(entity);
		GameManager::getInstance()->setCurrentMap(entity);








		_vec3 playerPosition;
		//////////////////////////////////////////////////////////////
		ifstream data("GameData(PRACTICE).json", ifstream::binary); //µ•¿Ã≈Õø° ¥Ÿ ¿–æÓø»

		//std::string data;
		Json::Reader reader; //json∏Æ¥ı±‚
		Json::Value root; //∞™¿ªπﬁæ∆ø√ ∑Á∆Æ
		reader.parse(data, root); // ¿–æÓø¬ µ•¿Ã≈Õ∏¶ ∑Á∆Æø° ∞™¿∏∑Œ ∆ƒΩÃ«ÿ¡‹
		const Json::Value& arr = root["Point"]; //∑Á∆Æø° point∫Œ∫–(¿Œµ¶Ω∫) ∞°¡Æø» 

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
				entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"∂•");
				entity->addComponent<BounDary>(0, _vec3(X, Y, 0.f), _vec3(Width, Height, 1.f));
				entityManager_->insertEntity(entity);

			}
			else if (jsonName == 1)
			{


				if (doorEntity_.lock() == nullptr)
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door");
					entity->addComponent<Door>(L"Room4");
					entity->getComponent<Transform>().position_ = _vec3(X, Y - 257 / 2 + 172 / 2 - 45.f, -1.f);
					entityManager_->insertEntity(entity);
					doorEntity_ = entity;


					if (SceneManager::getInstance()->pastSceneName_ == L"Room4")
					{


						playerPosition = _vec3(_vec3(X, Y - 257 / 2 + 172 / 2 - 45.f - 20.f, 0.f));

					}



				}
				else
				{
					entity = sceneObjectPool_.acquire();
					entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Door");
					entity->addComponent<Door>(L"RoomAirport");
					entity->getComponent<Transform>().position_ = _vec3(X, Y - 257 / 2 + 172 / 2 - 45.f, -1.f);
					entityManager_->insertEntity(entity);
					doorEntity_2 = entity;

					if (SceneManager::getInstance()->pastSceneName_ == L"RoomAirport")
					{
						playerPosition = _vec3(_vec3(X, Y - 257 / 2 + 172 / 2 - 45.f - 20.f, 0.f));

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

		//πÂ¡Ÿ
	/*	entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"boundary");
		entity->addComponent<BounDary>(1, _vec3(-525, -800.f, 0.f), _vec3(2, 170.f, 1.f));
		entityManager_->insertEntity(entity);*/

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
		entity->addComponent<CommonEnemy>(L"¥Ÿ≈©Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 100.f,80.f,-0.f };
		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"¥Ÿ≈©Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 150.f,80.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"¥Ÿ≈©Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 200.f,80.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"¥Ÿ≈©Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 100.f,80.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"¥Ÿ≈©Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 0.f,80.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);




		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 200.f,-215.f,-0.f };
		entityManager_->insertEntity(entity);


		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 0.f,-215.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);



		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 300.f,-215.f,-0.f };
		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 350.f,-215.f,-0.f };
		entity->getComponent<AtlasAnimation>().setRight(false);

		entityManager_->insertEntity(entity);

		entity = sceneObjectPool_.acquire();
		entity->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
		entity->addComponent<CommonEnemy>(L"Ω∫≈Ê∞Ò∑Ω");
		entity->getComponent<Transform>().position_ = { 170.f,-215.f,-0.f };
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
		weak_ptr<Entity> doorEntity_,doorEntity_2;
		vector<shared_ptr<Entity>> remainMonster;
		shared_ptr<Entity> MapControllerEntity;
};