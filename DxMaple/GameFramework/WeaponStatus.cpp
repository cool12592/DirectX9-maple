#include "stdafx.h"
#include "WeaponStatus.h"

WeaponStatus::WeaponStatus():weaponType_(WEAPONTYPE::KNUCKLE),physicalDamage_(0.f),magicalDamage_(0.f),weaponName_(L"")
{
}

WeaponStatus::~WeaponStatus()
{
}

void WeaponStatus::setStatus(wstring weaponName,WEAPONTYPE weaponType, float physicalDamage, float magicalDamage)
{
	weaponName_ = weaponName;
	weaponType_ = weaponType;
	physicalDamage_ = physicalDamage;
	magicalDamage_ = magicalDamage;
}

void WeaponStatus::initialize()
{
}

void WeaponStatus::update()
{
}

void WeaponStatus::lateUpdate()
{
}

void WeaponStatus::render()
{
}

void WeaponStatus::release()
{
}
