#pragma once
#include "MonoBehaviour.h"
class OtherEffect :
	public MonoBehaviour
{
public:
	OtherEffect(wstring atlasPath, _vec3 position,_vec3 scale, _vec2 pivot);
	virtual ~OtherEffect();
public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
private:
	wstring atlasPath_;
	_vec3 initPosition_;
	_vec3 initScale_;
	_vec2 initPivot_;
};

