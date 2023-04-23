#include "stdafx.h"
#include "Light.h"


void Light::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, -0.1f), _vec3(0.f, 0.f, 0.f), _vec3(500.F, 100.f, 1.f));



	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(6.f);
	//entity->getComponent<AtlasAnimation>().setUserPivot(_vec2(0.f, 60.f));
	entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;


	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.insertSprite(L"door", L"../AtlasFiles/Map/portal.png", L"../AtlasFiles/Map/portal.json");
	anim.changeCurrentSprite(L"door");

	anim.setCurrentIndex(4.F);
	anim.PauseAnimation();


	
	

}

void Light::update()
{


}

void Light::lateUpdate()
{
	if (Input.keyPressing(DIK_0))
		sunPower = 0.1f;

	if (Input.keyPressing(DIK_8))
		sunPower += 0.0004f;

	if (Input.keyPressing(DIK_9))
		sunPower -= 0.0004f;


}

void Light::render()
{
	

	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.readyShaderValues(make_pair("I_AM_SUN", true), make_pair("sunPower", sunPower));
	

}

void Light::release()
{
}



