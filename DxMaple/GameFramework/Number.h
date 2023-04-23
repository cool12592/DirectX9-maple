#pragma once
#include "MonoBehaviour.h"
class Number :
	public MonoBehaviour
{
public:
	Number(int type, int add, Entity* itemEntity) { type_ = type; add_ = add; itemEntity_ = itemEntity; }
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

private:
	int type_;
	int add_;
	Entity* itemEntity_;
};

