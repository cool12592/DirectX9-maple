#pragma once
#include "MonoBehaviour.h"
#include "Define.h"


class ItemShop :
	public MonoBehaviour
{


public:
	ItemShop(int type = 0) { shopType_ = type; }
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	
	void ShopOpen();
	void ShopDelete();
	void shopHide();

	void select(int option);
	void BuyItem(wstring itemName);
	void InventoryLink(int option=0);
	wstring bornSceneName_;
	shared_ptr<Entity> playerItem[5];
	bool isOn_ = true;
private:
	shared_ptr<Entity> inventoryEntity_;
	RECT RT_;
	RECT RT2_;
	vector<pair<Entity*, int>> shopInventory;


	shared_ptr<Entity> emptyUI[10];
	


	int selectItem=-1;

	//shared_ptr<Entity> playerItem[5];

	float clikcCoolTime = 0.f;

	int shopType_;
};

