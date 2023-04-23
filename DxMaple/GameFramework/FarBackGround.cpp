#include "stdafx.h"
#include "FarBackGround.h"
#include "GameManager.h"

void FarBackGround::initialize()
{
	if (type_ == 1)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		//	entity->getComponent<Sprite>().setAddPos(_vec3(basicPos.x, basicPos.y ,0.f));
			//entity->getComponent<Sprite>().SetMultiple(5, 1);
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/Areve2.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;
		
	}
	
	if (type_ == 2)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		//	entity->getComponent<Sprite>().setAddPos(_vec3(basicPos.x, basicPos.y ,0.f));
			//entity->getComponent<Sprite>().SetMultiple(5, 1);
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/PRACTICE.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;

	}
	if (type_ == 3)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 9000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	
		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().insertSprite(L"0", L"../AtlasFiles/Map/ship-0.png", L"../AtlasFiles/Map/ship-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"1", L"../AtlasFiles/Map/ship-1.png", L"../AtlasFiles/Map/ship-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"2", L"../AtlasFiles/Map/ship-2.png", L"../AtlasFiles/Map/ship-2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"3", L"../AtlasFiles/Map/ship-3.png", L"../AtlasFiles/Map/ship-3.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"4", L"../AtlasFiles/Map/ship-4.png", L"../AtlasFiles/Map/ship-4.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"5", L"../AtlasFiles/Map/ship-5.png", L"../AtlasFiles/Map/ship-5.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"6", L"../AtlasFiles/Map/ship-6.png", L"../AtlasFiles/Map/ship-6.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"7", L"../AtlasFiles/Map/ship-7.png", L"../AtlasFiles/Map/ship-7.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"8", L"../AtlasFiles/Map/ship-8.png", L"../AtlasFiles/Map/ship-8.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"9", L"../AtlasFiles/Map/ship-9.png", L"../AtlasFiles/Map/ship-9.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"10", L"../AtlasFiles/Map/ship-10.png", L"../AtlasFiles/Map/ship-10.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"11", L"../AtlasFiles/Map/ship-11.png", L"../AtlasFiles/Map/ship-11.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"12", L"../AtlasFiles/Map/ship-12.png", L"../AtlasFiles/Map/ship-12.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"13", L"../AtlasFiles/Map/ship-13.png", L"../AtlasFiles/Map/ship-13.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"14", L"../AtlasFiles/Map/ship-14.png", L"../AtlasFiles/Map/ship-14.json");
		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"0");
		

		entity->getComponent<AtlasAnimation>().insertSprite(L"15", L"../AtlasFiles/Map/Crimson-0.png", L"../AtlasFiles/Map/Crimson-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"16", L"../AtlasFiles/Map/Crimson-1.png", L"../AtlasFiles/Map/Crimson-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"17", L"../AtlasFiles/Map/Crimson-2.png", L"../AtlasFiles/Map/Crimson-2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"18", L"../AtlasFiles/Map/Crimson-3.png", L"../AtlasFiles/Map/Crimson-3.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"19", L"../AtlasFiles/Map/Crimson-4.png", L"../AtlasFiles/Map/Crimson-4.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"20", L"../AtlasFiles/Map/Crimson-5.png", L"../AtlasFiles/Map/Crimson-5.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"21", L"../AtlasFiles/Map/Crimson-6.png", L"../AtlasFiles/Map/Crimson-6.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"22", L"../AtlasFiles/Map/Crimson-7.png", L"../AtlasFiles/Map/Crimson-7.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"23", L"../AtlasFiles/Map/Crimson-8.png", L"../AtlasFiles/Map/Crimson-8.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"24", L"../AtlasFiles/Map/Crimson-9.png", L"../AtlasFiles/Map/Crimson-9.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"25", L"../AtlasFiles/Map/Crimson-10.png", L"../AtlasFiles/Map/Crimson-10.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"26", L"../AtlasFiles/Map/Crimson-11.png", L"../AtlasFiles/Map/Crimson-11.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"27", L"../AtlasFiles/Map/Crimson-12.png", L"../AtlasFiles/Map/Crimson-12.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"28", L"../AtlasFiles/Map/Crimson-13.png", L"../AtlasFiles/Map/Crimson-13.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"29", L"../AtlasFiles/Map/Crimson-14.png", L"../AtlasFiles/Map/Crimson-14.json");
		mapSize_.x = 1750.f;
		mapSize_.y = 1500.f;

		
	

		/*string playSoundBG[] = {
			"../resource/mySound/UponTheSky.MP3",
				

		};
		entity->addComponent<Sound>().CreateBGSound(_countof(playSoundBG), playSoundBG);
		if (!entity->getComponent<Sound>().IsPlayingBGM(0))
			entity->getComponent<Sound>().PlaySoundBG(0);*/


	/*	if (!entity->getComponent<Sound>().IsPlayingBGM(0))
			entity->getComponent<Sound>().PlaySoundBG(0);
		if (entity->getComponent<Sound>().IsPlayingBGM(1))
			entity->getComponent<Sound>().StopSoundBG(1);
		if (entity->getComponent<Sound>().IsPlayingBGM(2))
			entity->getComponent<Sound>().StopSoundBG(2);*/
	}


	//inShip
	if (type_ == 4)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/inship.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;

	}
	//Airport
	if (type_ == 5)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		

		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/Airport.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;

	}

	//È¥Å×ÀÏ¸Ê
	if (type_ == 6)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));



		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/HornTailMap.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;

	}

	//Ä³½¬¼¥
	if (type_ == 7)
	{
		_vec3 basicPos = _vec3(100.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));



		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/cashshop3.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;

	}
	//bluemap1
	if (type_ == 8)
	{
		_vec3 basicPos = _vec3(-150.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.5f, 1.f, 1.f));



		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/blue1.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;


	}
	//bluemap2
	if (type_ == 9)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


		//far
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/map/blue2.png");

		mapSize_.x = entity->getComponent<Sprite>().getTextureInfo().Width;
		mapSize_.y = entity->getComponent<Sprite>().getTextureInfo().Height;




	}
	//bluemap3
	if (type_ == 10)
	{
		_vec3 basicPos = _vec3(0.f, 0.f, 0.0f);
		entity->addComponent<Transform>(basicPos + _vec3(0.f, 0.f, 10000.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
		entity->getComponent<AtlasAnimation>().insertSprite(L"0", L"../AtlasFiles/Map/blue3anim-0.png", L"../AtlasFiles/Map/blue3anim-0.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"1", L"../AtlasFiles/Map/blue3anim-1.png", L"../AtlasFiles/Map/blue3anim-1.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"2", L"../AtlasFiles/Map/blue3anim-2.png", L"../AtlasFiles/Map/blue3anim-2.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"3", L"../AtlasFiles/Map/blue3anim-3.png", L"../AtlasFiles/Map/blue3anim-3.json");
		entity->getComponent<AtlasAnimation>().insertSprite(L"4", L"../AtlasFiles/Map/blue3anim-4.png", L"../AtlasFiles/Map/blue3anim-4.json");

		entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"0");

		mapSize_.x = 1440.f;
		mapSize_.y = 790.f;


	}
}

void FarBackGround::update()
{
	if (type_ == 3)
	{
		
		static int count = 0;
		static int i = 0;
		static float accumulatedTime=0.f;
		accumulatedTime += TimeManager().getInstance()->getDeltaTime();
		
		if (accumulatedTime > 0.1f)
		{
			accumulatedTime = 0.f;
			if(page_==1)
				entity->getComponent<AtlasAnimation>().changeCurrentSprite(ani[i]);
			else
				entity->getComponent<AtlasAnimation>().changeCurrentSprite(ani2[i]);
			i++;
			count++;
			if (i > 14)
				i = 0;

			if (count >300.f && page_ == 1)
			{
				page_ = 2;
				SceneManager::getInstance()->SetCurrentSceneName(L"CRIMSON");

				crimsonEntity[0] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				crimsonEntity[0]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
				crimsonEntity[0]->addComponent<Crimson>(_vec3(200.f,0.f,-1.1f));
				//crimsonEntity[0]->getComponent<Transform>().position_ = { 200.f,0.f,-1.1f };
				EntityManager::getInstance()->insertEntity(crimsonEntity[0]);


				crimsonEntity[1] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				crimsonEntity[1]->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"MOB");
				crimsonEntity[1]->addComponent<Crimson>(_vec3(160.f, 0.f, -1.1f));
				//entity->getComponent<Transform>().position_ = { 160.f,0.f,-1.1f };
				EntityManager::getInstance()->insertEntity(crimsonEntity[1]);
			}
		}

		if (page_ == 2)
		{
			if (crimsonEntity[0]->isActive()==false && crimsonEntity[1]->isActive() == false)
			{
				nextMapReady = true;
			}
	
		}


	}









	else if (type_ == 10)
	{

	
		static int i = 0;
		static float accumulatedTime = 0.f;
		accumulatedTime += TimeManager().getInstance()->getDeltaTime();

		if (accumulatedTime > 0.2f)
		{
			accumulatedTime = 0.f;
	
			entity->getComponent<AtlasAnimation>().changeCurrentSprite(ani[i]);
			
			i++;
			
			if (i >4 )
				i = 0;

		}

		


	}
}
