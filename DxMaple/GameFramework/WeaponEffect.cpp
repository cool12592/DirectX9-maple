#include "stdafx.h"
#include "WeaponEffect.h"

WeaponEffect::WeaponEffect(const wchar_t* texturePath, const wchar_t* atlasPath)
{
	texturePath_ = texturePath;
	atlasPath_ = atlasPath;
}

WeaponEffect::~WeaponEffect()
{
}

void WeaponEffect::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	anim.setUserPivot(_vec2(DEFAULT_USER_PIVOT_X, DEFAULT_USER_PIVOT_Y));
	anim.setAnimationSpeed(DEFAULT_ANIMATION_SPEED);

	anim.insertSprite(L"effect", texturePath_.c_str(), atlasPath_.c_str());
	anim.changeCurrentSprite(L"effect");
}

void WeaponEffect::update()
{
}

void WeaponEffect::lateUpdate()
{
}

void WeaponEffect::render()
{
}

void WeaponEffect::release()
{
}
