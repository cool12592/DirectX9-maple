#pragma once
#include "MonoBehaviour.h"
class OtherPlayerController :
    public MonoBehaviour
{
public:
    OtherPlayerController(wstring className, _vec3 position);
    ~OtherPlayerController() {}
    // MonoBehaviour을(를) 통해 상속됨
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;

	void setOnMouse(bool onMouse) { onMouse_ = onMouse; }
private:
    wstring className_;
    _vec3 initPosition_;
	bool onMouse_;
};

