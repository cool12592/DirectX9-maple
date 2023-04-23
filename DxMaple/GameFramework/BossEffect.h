#pragma once

#include "MonoBehaviour.h"
class BossEffect :
    public MonoBehaviour
{
public:
	BossEffect() {}
	~BossEffect();
	BossEffect(int type, _vec3 position) {
		type_ = type; position_= position;
	};
	BossEffect(int type, _vec3 position,int option) {
		type_ = type; position_ = position; option_ = option;
	};
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void setDirection();
	void resetCircles() {
		for (int i = 0;i < 3;i++)
		{
			circle[i]->setActive(false);circle[i] = nullptr;
			
		}
	
	}
private:
	void sendEffectData();
private:
	int type_;
	_vec3 position_;
	int option_=-1;
	float animPauseCount_ = 0.f;
	float timeCount = 0.f;
	shared_ptr<Entity> shot[2];
	shared_ptr<Entity> circle[3];

	bool timeStop_=false;
	int count = 0;

	shared_ptr<Entity> Chainexplosion1;
	shared_ptr<Entity> Chainexplosion2;
	float revolution = 0.f;
	bool first1 = true;
	bool first2 = true;
	weak_ptr<Entity> attackBox_;

	weak_ptr<Entity> attackBoxGroup_[3];
	_vec3 initPosition_[3];
	wstring atlasPath_;
	
};



