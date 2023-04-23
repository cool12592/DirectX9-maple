#pragma once
#include "MonoBehaviour.h"
class BUFF :
	public Component
{
public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void onBuff(wstring name);
	void offBuff(shared_ptr<Entity> entity,int index);
	bool nowShadow = false;
private:
	float buffTime = 40.f;

	wstring name_;
	vector<pair<shared_ptr<Entity>,float>> buffList;

	weak_ptr<Entity> shadowPartnerEntity_;
	float originalMoveSpeed = 0.f;
	float originalAttackSpeed = 0.f;

};

