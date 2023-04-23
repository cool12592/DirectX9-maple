#pragma once
#include "MonoBehaviour.h"
class WeaponEffect :
    public MonoBehaviour
{
public:
    WeaponEffect(const wchar_t* texturePath, const wchar_t* atlasPath);
    virtual ~WeaponEffect();
    // MonoBehaviour을(를) 통해 상속됨
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;
private:
    wstring texturePath_;
    wstring atlasPath_;
};

