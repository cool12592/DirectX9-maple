#include "stdafx.h"
#include "Inventory.h"
#include "GameManager.h"
void Inventory::initialize()
{
	
	entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<BoxCollider>(_vec3(0.f, 170.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(250.f, 100.f, 100.f));
	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/inventory1.png");

	entity->addComponent<DXFont>();

	
	
}

void Inventory::update()
{
	_vec3 C_POS = myPlayer_->getComponent<Camera>().position_;

	int tempMoney = myMoney_;
	int myMoneyDigit = 0;
	do
	{
		tempMoney = int(tempMoney / 10);
		myMoneyDigit++;
	} while (tempMoney > 0);


	_vec3 position = entity->getComponent<Transform>().position_;
	//position.x-C_POS.x

	RT_.left = (LONG)(position.x - C_POS.x + 613 - (myMoneyDigit - 1) * 7);
	RT_.right = (LONG)(SCREEN_WIDTH);
	RT_.top = (LONG)(-position.y + C_POS.y + 535);
	RT_.bottom = (LONG)(SCREEN_HEIGHT);
	wstring mymoney = to_wstring(myMoney_);

	entity->getComponent<DXFont>().SetScript("serif", 13, FW_SEMIBOLD, RT_, mymoney.c_str(), D3DXCOLOR(0, 0, 0, 1));


	if (quickItem.lock() != GameManager::getInstance()->getQuickSlotEntity())
	{
		quickItem = GameManager::getInstance()->getQuickSlotEntity();
	}

	if (InputManager::getInstance()->keyDown(DIK_V))
	{
	

		myPlayer_->getComponent<Sound>().PlaySoundEffect(1);
		quickItem.lock()->getComponent<Item>().useItem();

	}



}

void Inventory::lateUpdate()
{

	
	

	//////////////////////////////////////////////////////////
	int row = 0;

	for (int i = 0; i < inventoryList.size(); i++)
	{
		row = (i / 4);
		if (inventoryList[i].first == nullptr)
			continue;

		if (!inventoryList[i].first->getComponent<Item>().pressed_) //마우스에 잡히고 있지 않다면
		{


			
				inventoryList[i].first->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-57.f + 35 * (i - row * 4), 97.f - (row * 35.f), -1.f);
			//여기다 inventoryList[i].first->getComponent<Item>().숫자생성 씀 아니다 여기가아니라 겟아이템떄
			//item에서는 거기다 게임매니져makenumberfont씀 (자기아래에 숫자위치하게끔)
			//이거는 업데이트다안하고 GETiTEM때 하면 될듯 그리고 이숫자는 안지워짐 단 0이면 안보이고 체인지될땐 사라지고 다시만듬
			

		//퀵슬롯도 아니고 인벤토리에도 없다면
				if (!inventoryList[i].first->getComponent<Item>().inInventory_)
				{
					popItem(i);
					break;
				}


				//다쓴템은사라짐
				if (inventoryList[i].first->getComponent<Item>().myCount == 0)
				{
					inventoryList[i].first->getComponent<Item>().myCount += 1;//안그러면 countreset에서 count값 -1됨
					inventoryList[i].first->getComponent<Item>().countReset();

					inventoryList[i].first->getComponent<Transform>().position_ = _vec3(100000.f, 0.f, 0.f);
					//inventoryList[i].first->setActive(false);
					inventoryList[i].first = nullptr;
					inventoryList[i].second = 0;

					break;
				}

		}

	
		
	
	}
	

	_vec3 C_POS = myPlayer_->getComponent<Camera>().position_;
	float myZ;
	
	if (InputManager::getInstance()->keyDown(DIK_I))
	{
		if (entity->getComponent<Transform>().position_.z == 20000.f)
		{
			myZ = -2.f;
			entity->getComponent<Transform>().position_ = _vec3(C_POS.x + 200.f, C_POS.y + 200.f, myZ);
		}
		else
		{
			myZ = 20000.f;
			entity->getComponent<Transform>().position_ = _vec3(C_POS.x + 200000.f, C_POS.y + 200.f, myZ);
		}
	}


	//cout << "위치" << position.x;
}

void Inventory::render()
{
}

void Inventory::release()
{
}

void Inventory::getGold(Entity* itementity)
{
	myMoney_ += itementity->getComponent<Item>().price_;
	itementity->setActive(false);
}


void Inventory::getItem(Entity* itementity)
{
	//같은 종류 아이템있을시 갯수증가
	for (int i = 0; i < inventoryList.size(); i++)
	{
		if (inventoryList[i].first == nullptr)
			continue;
		if (inventoryList[i].first->getName() == itementity->getName())
		{
			inventoryList[i].second += 1;
			inventoryList[i].first->getComponent<Item>().addCount();

			itementity->setActive(false);
			return;
		}
	
	}
	itementity->setTypeAndName(Entity::ENTITYTYPE::ITEM, itementity->getName());

	//아이템 빈곳있으면 거기에추가
	for (int i = 0; i < inventoryList.size(); i++)
	{
		if (inventoryList[i].second == 0)
		{
			itementity->getComponent<Item>().inInventory_ = true;
			itementity->getComponent<Item>().addCount();

			inventoryList[i] = make_pair(itementity, itementity->getComponent<Item>().getmyCount());
			return;
		}
	}
	//만약 공백이 있다면 위에들어가고 리턴
	//공백없이 채워져있다면 그냥 뒤에서 emplace_back
	itementity->getComponent<Item>().inInventory_ = true;
	inventoryList.emplace_back(make_pair(itementity,  1));
	itementity->getComponent<Item>().addCount();

	
	

}

void Inventory::popItem(int i)
{

	inventoryList[i].first->setTypeAndName(Entity::ENTITYTYPE::FILDITEM, inventoryList[i].first->getName());
	inventoryList[i].first->getComponent<Transform>().position_ = myPlayer_->getComponent<Transform>().position_+_vec3(0.f,30.f,-3.f);
	inventoryList[i].first->getComponent<Rigidbody>().setUseGravity(true);
	inventoryList[i].first->getComponent<Item>().countReset();
	inventoryList[i].first = nullptr;
	inventoryList[i].second = 0;

	
//	inventoryList[i]->getComponent<Item>().inInventory_ = false;
	
	
	
	//erase대신 이곳에 blank아이템을 넣어줘야할듯 (그럼 아이템은 자동으로지워지고 빈아이템들어감)

	//아 아이니다 makepair로 <숫자,엔티티로하자>
	//<숫자,nullptr>로 바꿔주면 사라지지 않으니까
	//그리고 inventoryList 쓸때마다 전부 nullptr이 아니라면 써야겠다
	//inventoryList.erase(inventoryList.begin() + i);


}

void Inventory::EraseItem(int i)
{

	inventoryList[i].first->getComponent<Item>().countReset();
	inventoryList[i].first->setActive(false);
	inventoryList[i].first = nullptr;
	inventoryList[i].second = 0;



}