#pragma once

#include "MonoBehaviour.h"
class MapBasic
	:public MonoBehaviour
{
public:
	// MonoBehaviour��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	bool ready = false;
	bool comeback = false;
	bool poweroff_ = false;
};

