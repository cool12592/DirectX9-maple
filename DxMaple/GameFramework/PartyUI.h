#pragma once
#include "MonoBehaviour.h"
class PartyUI
	:public MonoBehaviour
{
public:
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	
private:
	void onInvitePlayer();
	void onMakeParty();
	void onCheckPartyRequest();
	void onExitParty();

private:
	weak_ptr<Entity> partyMemberCount_;
	weak_ptr<Entity> partyMemberList_;
	shared_ptr<Entity> HontailStart;
	shared_ptr<Entity> shop;
	int testnum = 0;
};

