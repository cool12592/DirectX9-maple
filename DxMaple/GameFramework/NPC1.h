#pragma once
#include "MonoBehaviour.h"
class NPC1 :
    public MonoBehaviour
{
public:
	NPC1(wstring npcName=L"Ű��") { npcName_ = npcName; }
	// MonoBehaviour��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	float timer=0.f;

private:
	wstring npcName_;
};

