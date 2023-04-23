#include "stdafx.h"
#include "Room02Crypt.h"
#include "GameManager.h"
void Room02Crypt::initialize()
{

	_vec3 basicPos = _vec3(-130.f, 100.f, 9000.0f);
	entity->addComponent<Transform>(basicPos, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


	////far
	//entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//entity->getComponent<Sprite>().setAddPos(basicPos);
	//entity->getComponent<Sprite>().SetMultiple(5, 1);
	//entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/crypt_of_pain/background.img/0.png");

	////그아래배경
	//entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	//entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);
	//entity->getComponent<AtlasAnimation>().SetMultiple(12, 1);
	//entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x - 395.f, basicPos.y - 237.f, -10000.f));
	//entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/magma_bg.png", L"../AtlasFiles/Map/magma_bg.json");
	//entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");




	//그아래 스프라이트 (땅)
	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().SetMultiple(5, 1);
	entity->getComponent<Sprite>().setAddPos(_vec3(basicPos.x - 470.f, basicPos.y - 350.f, 0.f));

	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/crypt_of_pain/tile/doubleTile.jpg");
	entity->getComponent<Sprite>().isZRender_ = false;

	
	

	

	

	//맨아래 애님1

	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);
	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x - 300.f, basicPos.y - 477.f, -9000.f));
	entity->getComponent<AtlasAnimation>().SetMultiple(3, 1);
	entity->getComponent<AtlasAnimation>().setSpacing(2.f);
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/magma_down_tile2.png", L"../AtlasFiles/Map/magma_down_tile2.json");
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
//	entity->getComponent<AtlasAnimation>().isZRender = false;



	//맨아래 애님2


	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);

	entity->getComponent<AtlasAnimation>().SetMultiple(3, 1);

	entity->getComponent<AtlasAnimation>().setSpacing(2.f);
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/magma_down_tile1.png", L"../AtlasFiles/Map/magma_down_tile1.json");
	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x - 300.f + entity->getComponent<AtlasAnimation>().getAltInfo().x, basicPos.y - 477.f, -9000.f));
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
	//entity->getComponent<AtlasAnimation>().isZRender = false;

	//큰원 위
	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");

	entity->getComponent<Sprite>().setAddPos(_vec3(basicPos.x + 300.f, basicPos.y - 260.F, 0.f));

	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/crypt_of_pain/floorsquare.img/0.png");
	entity->getComponent<Sprite>().isZRender_ = false;
	
	


	//왼쪽벽
	shared_ptr<Entity> entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(0, _vec3(-600.f, 0.f, 0.f));
	EntityManager::getInstance()->insertEntity(entity);

	//오른쪽벽
	 entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(1, _vec3(800.f, 0.f, 0.f));
	EntityManager::getInstance()->insertEntity(entity);

	//Z축 시리즈
	/////////////왼쪽

	//z축벽
	 entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(3, _vec3(-450.f, 0.f, -60.f),_vec3(300.f,100.f,100.f));
	EntityManager::getInstance()->insertEntity(entity);

	//z축벽
	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(4, _vec3(-450.f, 0.f, -200.f), _vec3(300.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);

	/////////////가운데

		//z축벽
	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(3, _vec3(0.f, 0.f, 10.f), _vec3(700.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);

	//z축벽
	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(4, _vec3(0.f, 0.f, -300.f), _vec3(700.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);

	/////////////오른쪽

	//z축벽
	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(3, _vec3(550.f, 0.f, -60.f), _vec3(400.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);

	//z축벽
	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(4, _vec3(550.f, 0.f, -200.f), _vec3(400.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);

	//X축 시리즈(미니)
	
	//왼쪽벽
	 entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(0, _vec3(-250.f, 0.f, 20.f), _vec3(10.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);

	//오른쪽벽
	entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	entity->setTypeAndName(Entity::ENTITYTYPE::MAP, L"Room02Crypt");
	entity->addComponent<BounDary>(0, _vec3(-270.f, 0.f, -250.f), _vec3(10.f, 100.f, 100.f));
	EntityManager::getInstance()->insertEntity(entity);



}
