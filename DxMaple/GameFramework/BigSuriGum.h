#pragma once
#include "MonoBehaviour.h"
class BigSuriGum :
	public MonoBehaviour
{
public:
	BigSuriGum( _vec3 pos, bool right) {  position_ = pos; right_ = right; }

	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
public:
	
private:
	void expired();

	_vec3 position_;
	bool right_ = true;
	float timeCount = 0.f;

	float timeCount2 = 0.f;

	weak_ptr<Entity> attackBox1_;

	bool stop_=false;
	int page_=0;

};
