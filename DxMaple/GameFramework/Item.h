#pragma once
#include "MonoBehaviour.h"
class Item :
	public MonoBehaviour
{
public:
	Item(wstring name) { name_ = name; }
	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void Setting();
	void Positioning(_vec3 position) { Transform& transform = entity->getComponent<Transform>(); transform.position_ = position; }
	void addCount();
	void MinusCount();
	void countReset();
	int getmyCount() { return myCount; }
	void CopyItem(wstring itemName, int count,int option=0);
	void SetParentEntity(Entity* parentEntity) { parentEntity_ = parentEntity; }
	Entity* getParentEntity() { return parentEntity_; }



	void useItem(bool real=true);

	void Absorb() 
	{
		absorb = true;
	}
	void enterCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getName() == L"땅")
		{
		//	if (entity->getComponent<Rigidbody>().getUseGravity())
			{
				entity->getComponent<Rigidbody>().setUseGravity(false);
				//entity->getComponent<Transform>().position_.y = colliderEntity->getComponent<BoxCollider>().transform_.position_.y + colliderEntity->getComponent<BoxCollider>().transform_.scale_.y / 2.f + 12.f;
			}
		}
	}

	void stayCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getName() == L"땅")
		{
			//if (entity->getComponent<Rigidbody>().getUseGravity())
			{
				entity->getComponent<Rigidbody>().setUseGravity(false);
			//	entity->getComponent<Transform>().position_.y = colliderEntity->getComponent<BoxCollider>().transform_.position_.y + colliderEntity->getComponent<BoxCollider>().transform_.scale_.y / 2.f + 12.f;
			}
		}
		if (colliderEntity->getName() == L"inventory")
			inInventoryUI = true;


	}

	void exitCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getName() == L"inventory")
			inInventoryUI = false;

	//	if (colliderEntity->getName() == L"QuickSlot")
		//	inQuickSlot = false;
	}

	int ShopNumber_ = 0;
	bool inInventory_=false;
	bool pressed_=false;

	bool inInventoryUI=false;
	bool inQuickSlot = false;
	int price_ = 0;
	wstring name_;
	int myCount = 0; //내 갯수

	RECT RT2_;
	int kinds; //종류
private:
	
	
	shared_ptr<Entity> number[3]; //숫자엔티티 (일단세자리)

	//아이템은 자기의 숫자를 가지고있음(몇개인지)

	Entity* parentEntity_;
	bool absorb;
	double recoverHP=0;
	double recoverMP=0;
	
	wstring bornSceneName_;
	wstring text_;

	

};

