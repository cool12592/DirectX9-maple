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

		if (!inventoryList[i].first->getComponent<Item>().pressed_) //���콺�� ������ ���� �ʴٸ�
		{


			
				inventoryList[i].first->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-57.f + 35 * (i - row * 4), 97.f - (row * 35.f), -1.f);
			//����� inventoryList[i].first->getComponent<Item>().���ڻ��� �� �ƴϴ� ���Ⱑ�ƴ϶� �پ����ۋ�
			//item������ �ű�� ���ӸŴ���makenumberfont�� (�ڱ�Ʒ��� ������ġ�ϰԲ�)
			//�̰Ŵ� ������Ʈ�پ��ϰ� GETiTEM�� �ϸ� �ɵ� �׸��� �̼��ڴ� �������� �� 0�̸� �Ⱥ��̰� ü�����ɶ� ������� �ٽø���
			

		//�����Ե� �ƴϰ� �κ��丮���� ���ٸ�
				if (!inventoryList[i].first->getComponent<Item>().inInventory_)
				{
					popItem(i);
					break;
				}


				//�پ����������
				if (inventoryList[i].first->getComponent<Item>().myCount == 0)
				{
					inventoryList[i].first->getComponent<Item>().myCount += 1;//�ȱ׷��� countreset���� count�� -1��
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


	//cout << "��ġ" << position.x;
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
	//���� ���� ������������ ��������
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

	//������ ��������� �ű⿡�߰�
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
	//���� ������ �ִٸ� �������� ����
	//������� ä�����ִٸ� �׳� �ڿ��� emplace_back
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
	
	
	
	//erase��� �̰��� blank�������� �־�����ҵ� (�׷� �������� �ڵ������������� ������۵�)

	//�� ���̴ϴ� makepair�� <����,��ƼƼ������>
	//<����,nullptr>�� �ٲ��ָ� ������� �����ϱ�
	//�׸��� inventoryList �������� ���� nullptr�� �ƴ϶�� ��߰ڴ�
	//inventoryList.erase(inventoryList.begin() + i);


}

void Inventory::EraseItem(int i)
{

	inventoryList[i].first->getComponent<Item>().countReset();
	inventoryList[i].first->setActive(false);
	inventoryList[i].first = nullptr;
	inventoryList[i].second = 0;



}