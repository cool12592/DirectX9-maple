#pragma once
#include "MonoBehaviour.h"
class OtherEnemyController :
	public MonoBehaviour
{
public:
	OtherEnemyController(int subType, _vec3 position, _vec2 pivot);
	virtual ~OtherEnemyController();

public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

private:
	int subType_;
	_vec3 initPosition_;
	_vec2 initPivot_;
};

