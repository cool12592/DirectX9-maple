#pragma once
#include "MonoBehaviour.h"
class Weapon :
    public MonoBehaviour
{
public:
    Weapon(wstring weaponName);
    virtual ~Weapon();

public:
    void setWeaponEffect(shared_ptr<Entity>& effectEntity) { weaponEffect_ = effectEntity; }
    // MonoBehaviour을(를) 통해 상속됨
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;
private:
    void updateEffectPositionAndAnimation();
private:
    wstring weaponName_;
    weak_ptr<Entity> weaponEffect_;
    weak_ptr<Entity> playerEntity_;
};

