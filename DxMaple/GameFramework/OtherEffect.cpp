#include "stdafx.h"
#include "OtherEffect.h"

OtherEffect::OtherEffect(wstring atlasPath, _vec3 position, _vec3 scale, _vec2 pivot)
	:atlasPath_(atlasPath), initPosition_(position), initScale_(scale), initPivot_(pivot)
{
}

OtherEffect::~OtherEffect()
{

}

void OtherEffect::initialize()
{
	entity->addComponent<Transform>(initPosition_, _vec3(0.f, 0.f, 0.f), initScale_);
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	wstring spritePath = atlasPath_ + L".png";
	wstring jsonPath = atlasPath_ + L".json";
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.insertSprite(L"effect", spritePath.c_str(), jsonPath.c_str());
	anim.changeCurrentSprite(L"effect");
	anim.setUserPivot(initPivot_);
	anim.destBlendOp_ = D3DBLEND_DESTALPHA;

	//entity->getComponent<Transform>().isInterpolate_ = true;


}

void OtherEffect::update()
{
}

void OtherEffect::lateUpdate()
{
}

void OtherEffect::render()
{
}

void OtherEffect::release()
{
}
