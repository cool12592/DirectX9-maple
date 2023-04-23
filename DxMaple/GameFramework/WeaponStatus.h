#pragma once
#include "ECS.h"
class WeaponStatus :
    public Component
{
public:
    enum class WEAPONTYPE{KNUCKLE,BEAMSWORD};
public:
    WeaponStatus();
    virtual ~WeaponStatus();
public:
    void setStatus(wstring weaponName,WEAPONTYPE weaponType, float physicalDamage, float magicalAttack);
public:
    // Component을(를) 통해 상속됨
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;
public:
    wstring weaponName_;
    WEAPONTYPE weaponType_;
    float physicalDamage_, magicalDamage_;
};

