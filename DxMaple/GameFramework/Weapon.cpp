#include "stdafx.h"
#include "Weapon.h"
#include "GameManager.h"
Weapon::Weapon(wstring weaponName)
{
	weaponName_ = weaponName;
	playerEntity_ = GameManager::getInstance()->getPlayer();
}

Weapon::~Weapon()
{
}

void Weapon::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f,0.f,0.f),_vec3(0.f,0.f,0.f),_vec3(1.f,1.f,1.f));
	entity->addComponent<WeaponStatus>();
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	WeaponStatus& weaponStatus = entity->getComponent<WeaponStatus>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	//anim.setUserPivot(_vec2(DEFAULT_USER_PIVOT_X, DEFAULT_USER_PIVOT_Y));
	anim.setAnimationSpeed(DEFAULT_ANIMATION_SPEED);

	if (wcscmp(weaponName_.c_str(), L"dress1_front") == 0)
	{
		weaponStatus.setStatus(weaponName_,WeaponStatus::WEAPONTYPE::KNUCKLE,100.f,100.f);
		anim.insertSprite(L"dress1", L"../AtlasFiles/Item/dress1.png", L"../AtlasFiles/Item/dress1.json");
		anim.changeCurrentSprite(L"dress1");
	}
	else if(wcscmp(weaponName_.c_str(), L"dress2_front") == 0)
	{
		weaponStatus.setStatus(weaponName_, WeaponStatus::WEAPONTYPE::KNUCKLE, 100.f, 100.f);
		anim.insertSprite(L"dress2", L"../AtlasFiles/Item/dress2.png", L"../AtlasFiles/Item/dress2.json");
		anim.changeCurrentSprite(L"dress2");
	}
	else if (wcscmp(weaponName_.c_str(), L"cap_back") == 0)
	{
		weaponStatus.setStatus(weaponName_, WeaponStatus::WEAPONTYPE::KNUCKLE, 100.f, 100.f);
		anim.insertSprite(L"cap", L"../AtlasFiles/Item/cap.png", L"../AtlasFiles/Item/cap.json");
		anim.changeCurrentSprite(L"cap");
	}

	
}

void Weapon::update()
{
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	//if (!weaponFront_.expired())
	//{
		shared_ptr<Entity>& player = playerEntity_.lock();
		//if (weapon->hasComponent<Transform>() && weapon->hasComponent<AtlasAnimation>())
		//{
			Transform& playerTransform = player->getComponent<Transform>();
			AtlasAnimation& playerAnim = player->getComponent<AtlasAnimation>();

			anim.setRight(playerAnim.getIsRight());
			anim.setCurrentIndex(playerAnim.getCurrentIndex());
			
		
			float x;
			float y;
			
			anim.setUserPivot(playerAnim.getUserPivot()+_vec2(0.f,-5.f));
			if ((int)anim.getCurrentIndex() == 25 || (int)anim.getCurrentIndex() == 26)
			{
				x = 0.f;
			}
			else if (playerAnim.getIsRight())
			{
				x = -3.f;

				if (weaponName_ == L"dress2_front")
					x = 1.f;
				
			}
			else
			{
				x = 3.f;

				if (weaponName_ == L"dress2_front")
					x = -1.f;
				
			}
			
			if (weaponName_ == L"cap_back")
				y = 23.f;
			else if(weaponName_ == L"dress2_front")
				y = -20.f;
			else
				y = -18.f;
			transform.position_ = playerTransform.position_ + _vec3(x, y, 0.f);
			transform.position_.z -= 0.01f;

			

	

		//}
	//}

}

void Weapon::lateUpdate()
{
	//updateEffectPositionAndAnimation();
}

void Weapon::render()
{
}

void Weapon::release()
{
}

void Weapon::updateEffectPositionAndAnimation()
{
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (!weaponEffect_.expired())
	{
		shared_ptr<Entity>& weaponEffect = weaponEffect_.lock();
		if (weaponEffect->hasComponent<Transform>() && weaponEffect->hasComponent<AtlasAnimation>())
		{
			Transform& effectTransform = weaponEffect->getComponent<Transform>();
			AtlasAnimation& effectAnim = weaponEffect->getComponent<AtlasAnimation>();
			effectTransform.position_ = transform.position_;
			effectTransform.position_.z -= 0.01f;

			effectAnim.setRight(anim.getIsRight());
			effectAnim.setCurrentIndex(anim.getCurrentIndex());

		}
	}
}
