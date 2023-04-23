#pragma once
#include "MonoBehaviour.h"
class Inventory :
	public MonoBehaviour
{
public:
	Inventory(Entity* player) { myPlayer_ = player; }
	// Component을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;


	void getGold(Entity* itementity);
	void getItem(Entity* itementity);
	void popItem(int i);
	void EraseItem(int i);
	int myMoney_ = 0;
	Entity* myPlayer_;
	vector<pair<Entity*, int>> inventoryList;

	weak_ptr<Entity> quickItem;
private:
	_vec3 position_=_vec3(0.f,0.f,20000.f);
//	int myMoney_=0;
	
	

	RECT RT_;
	wstring Str_;
	float myZ = 20000.f;


};

