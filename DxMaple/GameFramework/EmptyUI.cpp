#include "stdafx.h"
#include "EmptyUI.h"
#include "DXFont.h"
void EmptyUI::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, -100.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(50.f, 50.f, 100.f));
	entity->addComponent<DXFont>();
}

void EmptyUI::update()
{
	
}

void EmptyUI::lateUpdate()
{

	
	
	if (entity->getName() == L"usingWeaponUI")
	{
		if(parentsEntity_!=nullptr)
		entity->getComponent<Transform>().position_ = parentsEntity_->getComponent<Transform>().position_;

	}


}

void EmptyUI::render()
{
}

void EmptyUI::release()
{
}
