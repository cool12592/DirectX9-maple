#pragma once
#include "MonoBehaviour.h"
class EmptyUI :
	public MonoBehaviour
{

public:
	EmptyUI() {}
	EmptyUI(Entity* parentsEntity) { parentsEntity_ = parentsEntity; }
	// MonoBehaviour��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;



	Entity* parentsEntity_;


};

