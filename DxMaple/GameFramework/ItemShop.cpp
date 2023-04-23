#include "stdafx.h"
#include "ItemShop.h"
#include "GameManager.h"



void ItemShop::initialize()
{
	
	
	entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	//entity->addComponent<BoxCollider>(_vec3(0.f, 170.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(250.f, 100.f, 100.f));
	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	
	if(shopType_==0)
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/�����̹���.png");
	if (shopType_ == 1)
	{
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/����2.png");
		entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/��Ƽ�̹���.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(-210.f, 170.f, 0.f));
	}
	entity->addComponent<DXFont>();


	//bornSceneName_ = SceneManager::getInstance()->GetCurrentSceneName();

	RT_.left = (LONG)(SCREEN_WIDTH/2+220);
	RT_.right = (LONG)(SCREEN_WIDTH);
	RT_.top = (LONG)(SCREEN_HEIGHT/2-270);
	RT_.bottom = (LONG)(SCREEN_HEIGHT);

	entity->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT_, L"", D3DXCOLOR(0, 0, 0, 1));


	if (shopType_ == 0)
	{
		emptyUI[0] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		emptyUI[0]->addComponent<EmptyUI>(entity);
		emptyUI[0]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"���������");
		EntityManager::getInstance()->insertEntity(emptyUI[0]);
		//wstring text = L"������\n   100 �޼�";
		//emptyUI[0]->addComponent<DXFont>();
		//emptyUI[0]->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT_, text.c_str(), D3DXCOLOR(0, 0, 0, 1));


		emptyUI[1] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		emptyUI[1]->addComponent<EmptyUI>(entity);
		emptyUI[1]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"������ȯ���");
		EntityManager::getInstance()->insertEntity(emptyUI[1]);

		emptyUI[2] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		emptyUI[2]->addComponent<EmptyUI>(entity);
		emptyUI[2]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"������");
		EntityManager::getInstance()->insertEntity(emptyUI[2]);
	}
	else if (shopType_ == 1)
	{
		emptyUI[0] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		emptyUI[0]->addComponent<EmptyUI>(entity);
		emptyUI[0]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"ȭ��Ʈ�����˻��");
		EntityManager::getInstance()->insertEntity(emptyUI[0]);
	}
	emptyUI[3] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	emptyUI[3]->addComponent<EmptyUI>(entity);
	emptyUI[3]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"����������");
	EntityManager::getInstance()->insertEntity(emptyUI[3]);

	emptyUI[4] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	emptyUI[4]->addComponent<EmptyUI>(entity);
	emptyUI[4]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"�����ۻ��");
	EntityManager::getInstance()->insertEntity(emptyUI[4]);

	emptyUI[5] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	emptyUI[5]->addComponent<EmptyUI>(entity);
	emptyUI[5]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"�������ȱ�");
	EntityManager::getInstance()->insertEntity(emptyUI[5]);

	emptyUI[6] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	emptyUI[6]->addComponent<EmptyUI>(entity);
	emptyUI[6]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"ȭ��Ʈ�����˻��");
	EntityManager::getInstance()->insertEntity(emptyUI[6]);




	entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
	entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/Shop.select.png");
	entity->getComponent<Sprite>().setAddPos(_vec3(-130.f,-5000.f, 0.f));

	for (int i = 0; i < 5; i++)
	{
		playerItem[i] = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		playerItem[i]->addComponent<Item>(L"blank");
		playerItem[i]->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"shopItem");
		EntityManager::getInstance()->insertEntity(playerItem[i]);
		playerItem[i]->getComponent<Item>().ShopNumber_ = i + 5+1;
		playerItem[i]->getComponent<Item>().SetParentEntity(entity);


		playerItem[i]->getComponent<Item>().RT2_.left= (LONG)(SCREEN_WIDTH / 2 + 61);
		playerItem[i]->getComponent<Item>().RT2_.right = (LONG)(SCREEN_WIDTH );
		playerItem[i]->getComponent<Item>().RT2_.top = (LONG)(SCREEN_HEIGHT / 2 - 205 + (i) * 52);
		playerItem[i]->getComponent<Item>().RT2_.bottom= (LONG)(SCREEN_HEIGHT);

		wstring temptext = L" ";
		playerItem[i]->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, playerItem[i]->getComponent<Item>().RT2_, temptext.c_str(), D3DXCOLOR(0, 0, 0, 1));

		
	//	playerItem[i]->addComponent<DXFont>();
	}
	
	inventoryEntity_ = GameManager::getInstance()->getPlayer()->getComponent<PlayerController>().inventory_.lock();

	
	//ShopOpen();

	shopHide();
}

void ItemShop::update()
{



	if (SceneManager::getInstance()->GetCurrentSceneName() != bornSceneName_)
	{
		ShopDelete();
		
	}




	if (!isOn_)
		return;


	if (clikcCoolTime > 0.f)
	{
		clikcCoolTime -= TimeManager::getInstance()->getDeltaTime();

	}

	if (GameManager::getInstance()->getPlayer() != nullptr)
	{


		if(isOn_)
		entity->getComponent<Transform>().position_ = GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition() + _vec3(0.f, 150.f, 2.f);
		emptyUI[0]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-150.f, 43.f, 1.f);
		emptyUI[0]->getComponent<BoxCollider>().transform_.scale_.x = 150.f;

		if (emptyUI[1] != nullptr)
		{
			emptyUI[1]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-150.f, -10.f, 1.f);
			emptyUI[1]->getComponent<BoxCollider>().transform_.scale_.x = 150.f;
		}

		if (emptyUI[2] != nullptr)
		{
			emptyUI[2]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-150.f, -60.f, 1.f);
			emptyUI[2]->getComponent<BoxCollider>().transform_.scale_.x = 150.f;
		}



		emptyUI[3]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-55.f, 160.f, 1.f);
		emptyUI[4]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(-55.f, 120.f, 1.f);
		emptyUI[5]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(230.f, 160.f, 1.f);

		InventoryLink();
		for (int i = 0; i < 5; i++)
		{
		//	if(playerItem[i]->hasComponent<Transform>())
			playerItem[i]->getComponent<Transform>().position_ = entity->getComponent<Transform>().position_ + _vec3(30.f, 40.f - (i * 52.f), -0.5f);
		}
	}


	//int tempMoney = inventoryEntity_->getComponent<Inventory>().myMoney_;
	//entity->getComponent<DXFont>().setStr(to_wstring(tempMoney).c_str());

	//int myMoneyDigit = 0;
	//do
	//{
	//	tempMoney = int(tempMoney / 10);
	//	myMoneyDigit++;
	//} while (tempMoney > 0);


	if (InputManager::getInstance()->keyDown(DIK_V))
	{
		InventoryLink(1);
	}
	





//	shopInventory = inventoryEntity_->getComponent<Inventory>().inventoryList;

	//if (InputManager::getInstance()->keyDown(DIK_O))
	//{
	//	ShopOpen();
	//}
}

void ItemShop::lateUpdate()
{
}

void ItemShop::render()
{
}

void ItemShop::release()
{
}



void ItemShop::ShopOpen()
{
	isOn_ = true;

}

void ItemShop::ShopDelete()
{
	//isOn_ = false;
	for (int i = 0; i < 10; i++)
		if (emptyUI[i] != nullptr)
			emptyUI[i]->setActive(false);
	for (int i = 0; i < 5; i++)
		if (playerItem[i] != nullptr)
		{
			playerItem[i]->getComponent<Item>().countReset();
			playerItem[i]->setActive(false);
		}
	GameManager::getInstance()->setShop(nullptr);
	entity->setActive(false);
}

void ItemShop::shopHide()
{
	isOn_ = false;
	for (int i = 0; i < 10; i++)
		if (emptyUI[i] != nullptr)
			emptyUI[i]->getComponent<Transform>().position_ = _vec3(0.f, 0.f, 10001.f);
	for (int i = 0; i < 5; i++)
		if (playerItem[i] != nullptr)
		{
			playerItem[i]->getComponent<Item>().countReset();
			playerItem[i]->getComponent<Transform>().position_ = _vec3(0.f, 0.f, 10002.f);
		}
	entity->getComponent<Transform>().position_ = _vec3(0.f, 0.f, 10003.f);
	//GameManager::getInstance()->setShop(nullptr);
	//entity->setActive(false);
}

void ItemShop::select(int option)
{
	
	if (clikcCoolTime > 0.f)
		return;
	if (option == -1)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/����22.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(-130.f, 37.f, 0.f));
		selectItem = -1;
	}
	if (option == 1)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/111.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(-130.f, 37.f, 0.f));
		selectItem = 1;
	}

	else if (option == 2)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/222.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(-130.f, 37.f-50.f, 0.f));
		selectItem = 2;
	}

	else if (option == 3)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/333.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(-130.f, 37.f-100.f, 0.f));
		selectItem = 3;
	}
	else if (option == 4)
	{
		

		shopHide();

	
	}

	else if (option == 5)
	{
		if (selectItem == 1)
			BuyItem(L"������");
		else if (selectItem == 2)
			BuyItem(L"���� ��ȯ �ֹ���");
		else if (selectItem == 3)
			BuyItem(L"���");
		else if (selectItem == -1)
			BuyItem(L"ȭ��Ʈ ������");

		InventoryLink(1);
	}
	else if (option == 11)
	{
		if (selectItem <= 3)
			return;
		
		for (int i = 0; i < inventoryEntity_->getComponent<Inventory>().inventoryList.size(); i++)
			if (inventoryEntity_->getComponent<Inventory>().inventoryList[i].first != nullptr)
			{
				if (playerItem[selectItem - 6]->getComponent<Item>().name_ == inventoryEntity_->getComponent<Inventory>().inventoryList[i].first->getComponent<Item>().name_)
				{
					//������
					inventoryEntity_->getComponent<Inventory>().myMoney_ += inventoryEntity_->getComponent<Inventory>().inventoryList[i].first->getComponent<Item>().price_ * inventoryEntity_->getComponent<Inventory>().inventoryList[i].first->getComponent<Item>().myCount;

					//�κ���������
					inventoryEntity_->getComponent<Inventory>().EraseItem(i);
					//�����ΰ�ħ
					InventoryLink(1);
					//������ ���������(��ĭ���ö󰡴ϱ�)

					for (int i = 4; i >= 0; i--)
					{
						if (playerItem[i]->getComponent<Item>().name_ != L"blank")
						{
							//��ũȭ
							playerItem[i]->getComponent<Item>().CopyItem(L"blank", 0);
							playerItem[i]->getComponent<Item>().countReset();
							wstring test = playerItem[i]->getComponent<Item>().name_;
							////��������
							//RT2_.left = (LONG)(SCREEN_WIDTH / 2 + 61);
							//RT2_.right = (LONG)(SCREEN_WIDTH);
							//RT2_.top = (LONG)(SCREEN_HEIGHT / 2 - 205 + (i) * 52);
							//RT2_.bottom = (LONG)(SCREEN_HEIGHT);
							//wstring text = L"";
							//playerItem[i]->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT2_, text.c_str(), D3DXCOLOR(0, 0, 0, 1));


							clikcCoolTime += 1.f;

							return;
						}
					}



				}
			}
	}
	else if (option == 6)
	{
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/Shop.select.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(160.f, 37.f -50*(option-6), 0.f));
		selectItem = 6;
	}
	else if (option == 7)
	{
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/Shop.select.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(160.f, 37.f - 50 * (option - 6), 0.f));
		selectItem = 7;
	}
	else if (option == 8)
	{
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/Shop.select.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(160.f, 37.f - 50 * (option - 6), 0.f));
		selectItem = 8;
	}
	else if (option == 9)
	{
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/Shop.select.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(160.f, 37.f - 50 * (option - 6), 0.f));
		selectItem = 9;
	}
	else if (option == 10)
	{
		entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/Shop.select.png");
		entity->getComponent<Sprite>().setAddPos(_vec3(160.f, 37.f - 50 * (option - 6), 0.f));
		selectItem = 10;
	}
	clikcCoolTime += 1.f;
}

void ItemShop::BuyItem(wstring itemName)
{

	shared_ptr<Entity> newItem =SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	newItem->addComponent<Item>(itemName);
	newItem->setTypeAndName(Entity::ENTITYTYPE::DNFUI, itemName);
	EntityManager::getInstance()->insertEntity(newItem);
	newItem->getComponent<Rigidbody>().setUseGravity(false);
	inventoryEntity_->getComponent<Inventory>().getItem(newItem.get());
	inventoryEntity_->getComponent<Inventory>().myMoney_ -= newItem->getComponent<Item>().price_;

}

void ItemShop::InventoryLink(int option)
{
	
	int endCount = 0;
	
	//�κ��丮��ŭ�ϱ��ϳ� 5���Ѿ�� �ٷγ�
	for (int i = 0; i < inventoryEntity_->getComponent<Inventory>().inventoryList.size(); i++)
	{
		if (inventoryEntity_->getComponent<Inventory>().inventoryList[i].first != nullptr)
		{
			playerItem[endCount]->getComponent<Item>().CopyItem(inventoryEntity_->getComponent<Inventory>().inventoryList[i].first->getComponent<Item>().name_, inventoryEntity_->getComponent<Inventory>().inventoryList[i].first->getComponent<Item>().myCount,option);
			

			/*	RT2_.left = (LONG)(SCREEN_WIDTH / 2 + 61);
				RT2_.right = (LONG)(SCREEN_WIDTH);
				RT2_.top = (LONG)(SCREEN_HEIGHT / 2 - 205 + endCount * 52);
				RT2_.bottom = (LONG)(SCREEN_HEIGHT);

				wstring text = playerItem[endCount]->getComponent<Item>().name_ + L"\n\n" + to_wstring(playerItem[endCount]->getComponent<Item>().price_)+L" �޼�";
				playerItem[endCount]->getComponent<DXFont>().SetScript("Arial", 13, FW_SEMIBOLD, RT2_, text.c_str(), D3DXCOLOR(0, 0, 0, 1));*/

			
			endCount += 1;

		
		}


		if (endCount >= 5)
			break;
	}

}
