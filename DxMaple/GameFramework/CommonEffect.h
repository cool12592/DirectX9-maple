#pragma once
#include "MonoBehaviour.h"
#include "AttackBox.h"
class CommonEffect :
    public MonoBehaviour
{
public:
    CommonEffect(wstring atlasPath);
    virtual ~CommonEffect();

    void setDuration(float duration);
    void setAnimSpeed(float speed);
    void setEffect(Entity* userEntity,bool traceUser, _vec3 localPos, float angle, float size);
    void setEffect(Entity* userEntity, bool traceUser, const wchar_t* effectName);
    void setCameraLockEffect(const wchar_t* effectName);
    void setEffect(_vec3 worldPos,float angle,float size);
	void deactivate() 
	{ 
		if (attackBox_.lock() != nullptr) attackBox_.lock()->setActive(false); entity->setActive(false);
	}


	void setAttackBox( wstring path,int startIndex, _vec3 plusPosition);
	void setAttackEnity(Entity* entityy) {attackBoxEntity_ = entityy;}
	


    void setOnVanish(float vanishSpeed);
    // MonoBehaviour을(를) 통해 상속됨
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;
private:
    void traceUser();
    void traceCamera();
	void sendEffectData();
private:
    wstring atlasPath_;

    bool isInstant_;
    float duration_;
    float timer_;
    Entity* userEntity_;
    _vec3 localPos_;

    bool onCameraLock_;
    _vec3 localPosition_;
private:
	bool traceUser_=false;
    bool onVanish_;
    float vanishAlpha_;
    float vanishSpeed_;
	weak_ptr<Entity> attackBox_;

	int startAttackBoxIndex_=-1;
	wstring attackBoxTitle_;
	Entity* attackBoxEntity_;

};

