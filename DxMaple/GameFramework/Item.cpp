#include "stdafx.h"
#include "Item.h"
#include "GameManager.h"
#include "ExcelLoader.h"
void Item::initialize()
{
	entity->addComponent<Transform>(_vec3(10000.f, -100.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	
	
	entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(30.f, 30.f, 50.f));
	entity->getComponent<BoxCollider>().bindColliderFunction(
		bind(&Item::enterCollider, this, placeholders::_1),
		bind(&Item::stayCollider, this, placeholders::_1),
		bind(&Item::exitCollider, this, placeholders::_1));
	
	entity->addComponent<Rigidbody>().setMass(1.f);
	entity->getComponent<Rigidbody>().setDrag(DRAG_LIMIT);
	entity->getComponent<Rigidbody>().setUseGravity(true);

	Setting();

	bornSceneName_ = SceneManager::getInstance()->GetCurrentSceneName();

	entity->addComponent<DXFont>();




}

void Item::update()
{
	
	if (absorb)
	{
		auto player = GameManager::getInstance()->getPlayer();


		_vec3 POS = entity->getComponent<Transform>().position_;
		_vec3 P_POS = player->getComponent<Transform>().position_;
		
		_vec3 dis = P_POS - POS;

		float distance = fabsf(dis.x) + fabsf(dis.y);
		if (distance < 15.f)
		{
			if (entity->getType() == Entity::ENTITYTYPE::FILDITEM)
			{
				player->getComponent<PlayerController>().inventory_.lock()->getComponent<Inventory>().getItem(entity);
				absorb = false;
			}
			else if (entity->getType() == Entity::ENTITYTYPE::GOLD)
			{
				player->getComponent<PlayerController>().inventory_.lock()->getComponent<Inventory>().getGold(entity);
				absorb = false;
			}
		}
		if (dis.x>0.f)
			entity->getComponent<Transform>().position_.x += 400.f * TimeManager::getInstance()->getDeltaTime();
		else
			entity->getComponent<Transform>().position_.x -= 400.f * TimeManager::getInstance()->getDeltaTime();

		if (dis.y > 0.f)
			entity->getComponent<Transform>().position_.y += 200.f * TimeManager::getInstance()->getDeltaTime();
		else
			entity->getComponent<Transform>().position_.y -= 200.f*TimeManager::getInstance()->getDeltaTime();
	}

	if (GameManager::getInstance()->getQuickSlotEntity().get() == entity)
		return;

	if (bornSceneName_ != SceneManager::getInstance()->GetCurrentSceneName())
	{
		if (inInventory_ == false)
			entity->setActive(false);
	}

	
}

void Item::lateUpdate()
{
	if (recoverHP > 0)
	{
		Status& status = GameManager::getInstance()->getPlayer()->getComponent<Status>();
		status.Recover(recoverHP/100, 0);
		recoverHP -= recoverHP/100;
	}

	if (recoverMP > 0)
	{
		Status& status = GameManager::getInstance()->getPlayer()->getComponent<Status>();
		status.Recover(0, recoverMP / 100);
		recoverMP -= recoverMP / 100;
	}



}



void Item::render()
{

	////�����۵� ���ڶ���
	//if (ShopNumber_ > 0)
	//{
	//	if (name_ == L"blank")
	//	{
	//		//��������

	//		/*RT2_.left = (LONG)(SCREEN_WIDTH / 2 + 61);
	//		RT2_.right = (LONG)(SCREEN_WIDTH / 2 + 61 + 20);
	//		RT2_.top = (LONG)(SCREEN_HEIGHT / 2 - 205 + (ShopNumber_-6) * 52);
	//		RT2_.bottom = (LONG)(SCREEN_HEIGHT / 2 - 205 + (ShopNumber_-6) * 52 - 20);*/


	//		text_ = L"";
	//		//entity->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT2_, text_.c_str(), D3DXCOLOR(0, 0, 0, 1));
	//		entity->getComponent<DXFont>().setStr(text_.c_str());
	//	}
	//	else
	//	{


	//		text_ = name_ + L"\n\n" + to_wstring(price_) + L" �޼�";

	//		//entity->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT2_, text_.c_str(), D3DXCOLOR(0, 0, 0, 1));

	//		entity->getComponent<DXFont>().setStr(text_.c_str());
	//	}

	//}

		
	

	

}

void Item::release()
{
	
}

void Item::Setting()
{
	ExcelLoader::loadItemData(L"../ExcelFiles/itemInfo.xlsx", entity, name_);

	//if (name_ == L"blank")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/blank.png");

	//	price_ = 0;
	//}

	//if (name_ == L"coin")
	//{
	//	if (!entity->hasComponent<AtlasAnimation>())
	//		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	//	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Item/coin.png", L"../AtlasFiles/Item/coin.json");
	//	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");

	//	price_ = 50;
	//}
	//if (name_ == L"money")
	//{
	//	if (!entity->hasComponent<AtlasAnimation>())
	//		entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	//	entity->getComponent<AtlasAnimation>().insertSprite(L"idle", L"../AtlasFiles/Item/money.png", L"../AtlasFiles/Item/money.json");
	//	entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");

	//	price_ = 100;
	//}
	//if (name_ == L"��Ȳ ������ ��")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/a.png");

	//	price_ = 15;
	//}
	//if (name_ == L"������")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/b.png");

	//	price_ = 20;
	//}
	//if (name_ == L"���� ��ȯ �ֹ���")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/c.png");

	//	price_ = 15;
	//}
	//if (name_ == L"���")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/d.png");

	//	price_ = 10;
	//}

	//if (name_ == L"�ʷϹ����� ��")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/F.png");

	//	price_ = 10;
	//}
	//if (name_ == L"������� ������")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/G.png");

	//	price_ = 50;
	//}
	//if (name_ == L"��ũ ������� ������")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/H.png");

	//	price_ = 60;
	//}
	//if (name_ == L"���̷����� ��")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/I.png");

	//	price_ = 90;
	//}
	//if (name_ == L"ȭ��Ʈ ������")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/white.png");

	//	price_ = 200;
	//}
	//if (name_ == L"���� ������")
	//{
	//	if (!entity->hasComponent<Sprite>())
	//		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	//	entity->getComponent<Sprite>().insertTexture(L"../SpriteFiles/ITEM/surigum.png");

	//	price_ = 100;
	//}

}


void Item::addCount()
{
	myCount += 1;

	//������������
	for (int i = 0; i < 3; i++)
	{
		if (number[i] != nullptr)
		{
			number[i]->setActive(false);
			number[i] = nullptr;
		}
	}

	int initNumber = (int)myCount;

	vector<int> kk;

	//���ڸ����� kk���Ϳ�������� �� kk�� back()���� ���ڸ����ִ°���
	do
	{
		int NUM = (int)initNumber % 10;
		kk.push_back(NUM);


		if (initNumber / 10 == 0)
			break;

		initNumber /= 10;

	} while (1);


	//kk�� back �� ���ڸ����ں��� ���ʷ� ����
	//number�� �θ� ��ƼƼ�� �������� ����ٴ�(��preesed�϶� ����)
	int i = 0;
	do
	{

		int NUM = kk[kk.size() - 1];
		kk.pop_back();
		number[i] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		//������������, �ڸ���, �θ�ƼƼ(��)
		number[i]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"itemFont");
		number[i]->addComponent<Number>(NUM, i, entity);
		
		EntityManager::getInstance()->insertEntity(number[i]);

		if (kk.size() == 0)
			break;

		i++;
	} while (1);
}

void Item::MinusCount()
{
	if (myCount == 1)
	{
		if (GameManager::getInstance()->getQuickSlotEntity().get() == entity)
		{
			CopyItem(L"blank", 0, 1);
			countReset();
			return;
		}
		
		
	}

	myCount -= 1;

	//������������
	for (int i = 0; i < 3; i++)
	{
		if (number[i] != nullptr)
		{
			number[i]->setActive(false);
			number[i] = nullptr;
		}
	}

	int initNumber = (int)myCount;

	vector<int> kk;

	//���ڸ����� kk���Ϳ�������� �� kk�� back()���� ���ڸ����ִ°���
	do
	{
		int NUM = (int)initNumber % 10;
		kk.push_back(NUM);


		if (initNumber / 10 == 0)
			break;

		initNumber /= 10;

	} while (1);


	//kk�� back �� ���ڸ����ں��� ���ʷ� ����
	//number�� �θ� ��ƼƼ�� �������� ����ٴ�(��preesed�϶� ����)
	int i = 0;
	do
	{

		int NUM = kk[kk.size() - 1];
		kk.pop_back();
		number[i] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		//������������, �ڸ���, �θ�ƼƼ(��)
		number[i]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"itemFont");
		number[i]->addComponent<Number>(NUM, i, entity);

		EntityManager::getInstance()->insertEntity(number[i]);

		if (kk.size() == 0)
			break;

		i++;
	} while (1);


	
}

void Item::countReset()
{
	//addCount���� +1���ٰű⶧���� -1����
	myCount-=1;

	//��������
	for (int i = 0; i < 3; i++)
	{
		if (number[i] != nullptr)
		{
			number[i]->setActive(false);
			number[i] = nullptr;
		}
	}
}

void Item::CopyItem(wstring name,int count,int option)
{

	if (option == 1)
	{
		myCount = count - 1;
		addCount();
		
		if (GameManager::getInstance()->getQuickSlotEntity().get() != entity)
		{
			if (GameManager::getInstance()->getQuickSlotEntity()->getComponent<Item>().name_ != L"blank")
			{
				if (GameManager::getInstance()->getQuickSlotEntity()->getComponent<Item>().name_ == name_)
				{
					GameManager::getInstance()->getQuickSlotEntity()->getComponent<Item>().CopyItem(name_, myCount, 1);
				}
			}
		}

	}


	//else if (myCount != count)
	//{
	//	myCount = count - 1;
	//	addCount();
	//}

	if (name_ == name)
		return;


	name_ = name;
	myCount = count - 1;
	addCount();
	
	Setting();
	
}



void Item::useItem(bool real)
{
	
	if (name_ == L"������")
	{
		if (real)
		{
			Status& status = GameManager::getInstance()->getPlayer()->getComponent<Status>();
			recoverHP += status.maxHp_ / 2;
			recoverMP += status.maxMp_ / 2;
		
		}
		MinusCount();
	
		//�����Ծ������̸� �κ����ִºθ�ƼƼ�� �ٿ���(false�� ȿ���ȳ��� ��������)
		if (GameManager::getInstance()->getQuickSlotEntity().get() == entity)
			parentEntity_->getComponent<Item>().useItem(false);
	}
	else if (name_ == L"���")
	{
		if (real)
		{
			Status& status = GameManager::getInstance()->getPlayer()->getComponent<Status>();
			recoverHP += 10;
		
		}

		MinusCount();

		//�����Ծ������̸� �κ����ִºθ�ƼƼ�� �ٿ���(false�� ȿ���ȳ��� ��������)
		if (GameManager::getInstance()->getQuickSlotEntity().get() == entity)
			parentEntity_->getComponent<Item>().useItem(false);

	}
	
}



