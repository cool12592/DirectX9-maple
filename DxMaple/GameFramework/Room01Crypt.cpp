#include "stdafx.h"
#include "Room01Crypt.h"

void Room01Crypt::initialize()
{

	_vec3 basicPos= _vec3(-130.f,100.f,9000.0f);
	entity->addComponent<Transform>(basicPos , _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));


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

	//시계
	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");

	entity->getComponent<Sprite>().setAddPos(_vec3(basicPos.x - 350.f, basicPos.y - 130.f, 0.f));

	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/Map/crypt_of_pain/rightaltar01.img/1.png");
	entity->getComponent<Sprite>().isZRender_ = false;

	//토치불1

	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);
	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x + 500.f, basicPos.y - 200.f, 0.f));
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/torchlight.png", L"../AtlasFiles/Map/torchlight.json");
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
	entity->getComponent<AtlasAnimation>().isZRender = false;
	//토치불2

	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);
	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x+300.f, basicPos.y - 320.f, 0.f));
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/torchlight.png", L"../AtlasFiles/Map/torchlight.json");
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
	entity->getComponent<AtlasAnimation>().isZRender = false;
	//맨아래 애님1

	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);
	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x - 300.f, basicPos.y - 477.f,-9000.f));
	entity->getComponent<AtlasAnimation>().SetMultiple(3, 1);
	entity->getComponent<AtlasAnimation>().setSpacing(2.f);
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/magma_down_tile2.png", L"../AtlasFiles/Map/magma_down_tile2.json");
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
	//entity->getComponent<AtlasAnimation>().isZRender = false;
	
	
	//맨아래 애님2

		
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	entity->getComponent<AtlasAnimation>().setAnimationSpeed(2.5f);

	entity->getComponent<AtlasAnimation>().SetMultiple(3, 1);

	entity->getComponent<AtlasAnimation>().setSpacing(2.f);
	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Map/magma_down_tile1.png", L"../AtlasFiles/Map/magma_down_tile1.json");
	entity->getComponent<AtlasAnimation>().setAddPos(_vec3(basicPos.x - 300.f + entity->getComponent<AtlasAnimation>().getAltInfo().x, basicPos.y - 477.f, -9000.f));
	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");


//	entity->getComponent<AtlasAnimation>().isZRender = false;

}
