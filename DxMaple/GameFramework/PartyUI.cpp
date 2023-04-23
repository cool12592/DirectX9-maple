#include "stdafx.h"
#include "PartyUI.h"
#include "GameManager.h"

void PartyUI::initialize()
{



}

void PartyUI::update()
{
	onInvitePlayer();
	onMakeParty();
	onCheckPartyRequest();
	onExitParty();
}

void PartyUI::lateUpdate()
{
}

void PartyUI::render()
{
}

void PartyUI::release()
{
}

void PartyUI::onInvitePlayer()
{

	shared_ptr<Entity>& entity = GameManager::getInstance()->getMouse();
	Mouse& mouse = entity->getComponent<Mouse>();
	weak_ptr<Entity> collideEntity = mouse.getCollideEntity();
	if (collideEntity.expired())
		return;

	if (Input.mouseDown(InputManager::MOUSEBUTTONTYPE::LEFT))
	{
		if (collideEntity.lock()->getName() == L"GoToShip")
		{
			GameManager::getInstance()->changeSceneAllPlayer(L"Room2");
			return;
		}
		else if (collideEntity.lock()->getName() == L"Summons_HonTail")
		{
			if (GameManager::getInstance()->getBoss() == nullptr)
			{
				
				testnum += 1;
				HontailStart = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				HontailStart->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"hontailstart");
				HontailStart->addComponent<HornTail>(L"start");
				EntityManager::getInstance()->insertEntity(HontailStart);
				GameManager::getInstance()->setBoss(HontailStart);
			
				return;
			}
		}
		else if (collideEntity.lock()->getName() == L"키쿠")
		{
			if (GameManager::getInstance()->getShop() == nullptr)
			{
				shop = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				shop->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"SHOP");
				shop->addComponent<ItemShop>();
				EntityManager::getInstance()->insertEntity(shop);
				GameManager::getInstance()->setShop(shop);
				shop->getComponent<ItemShop>().bornSceneName_ = L"Room4"; 

				return;
			}
			else
			{
			
				GameManager::getInstance()->getShop()->getComponent<ItemShop>().ShopOpen();

			}
			 return;
		}
		else if (collideEntity.lock()->getName() == L"예티")
		{
			if (GameManager::getInstance()->getShop() == nullptr)
			{
				shop = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
				shop->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"SHOP");
				shop->addComponent<ItemShop>(1);
				EntityManager::getInstance()->insertEntity(shop);
				GameManager::getInstance()->setShop(shop);
				shop->getComponent<ItemShop>().bornSceneName_ = L"RoomBlue1";

				return;
			}
			else
			{

				GameManager::getInstance()->getShop()->getComponent<ItemShop>().ShopOpen();

			}
			return;
		}
		else if (collideEntity.lock()->getName() == L"엘릭서사기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(1);
			return;
		}
		else if (collideEntity.lock()->getName() == L"마을귀환사기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(2);
			return;
		}
		else if (collideEntity.lock()->getName() == L"사과사기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(3);
			return;
		}
		else if (collideEntity.lock()->getName() == L"상점나가기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(4);
			return;
		}
		else if (collideEntity.lock()->getName() == L"아이템사기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(5);
			return;
		}
		else if (collideEntity.lock()->getName() == L"아이템팔기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(11);
			return;
		}
		else if (collideEntity.lock()->getName() == L"화이트수리검사기")
		{
			collideEntity.lock()->getComponent<EmptyUI>().parentsEntity_->getComponent<ItemShop>().select(-1);
			return;
		}
		else if (collideEntity.lock()->getName() == L"shopItem")
		{

			if (collideEntity.lock()->getComponent<Item>().name_ !=L"blank")
			collideEntity.lock()->getComponent<Item>().getParentEntity()->getComponent<ItemShop>().select(collideEntity.lock()->getComponent<Item>().ShopNumber_);
			return;
		}


	
	}




	if (Input.mouseDown(InputManager::MOUSEBUTTONTYPE::RIGHT))
	{

		if (collideEntity.lock()->getName() == L"뇌전 수리검")
		{
			if (collideEntity.lock()->getComponent<Item>().inInventory_ == true)
			{
				GameManager::getInstance()->getPlayer()->getComponent<PlayerController>().playerSurigumName_ = L"surigum";
				//GameManager::getInstance()->getPlayer()->getComponent<PlayerController>().usingWeaponUI->getComponent<Transform>().position_ = collideEntity.lock()->getComponent<Transform>().position_ + _vec3(0.f, 0.f, -1.f);;

				GameManager::getInstance()->getPlayer()->getComponent<PlayerController>().usingWeaponUI->getComponent<EmptyUI>().parentsEntity_ = collideEntity.lock().get();
			}
			return;
		}

		else if (collideEntity.lock()->getName() == L"화이트 수리검")
		{
			if (collideEntity.lock()->getComponent<Item>().inInventory_ == true)
			{
				GameManager::getInstance()->getPlayer()->getComponent<PlayerController>().playerSurigumName_ = L"whiteSurigum";
				GameManager::getInstance()->getPlayer()->getComponent<PlayerController>().usingWeaponUI->getComponent<EmptyUI>().parentsEntity_ = collideEntity.lock().get();
			}
			return;
		}
	}




	if (Input.mousePressing(InputManager::MOUSEBUTTONTYPE::LEFT))
	{
	

		if (collideEntity.lock()->getName() == L"inventory")
		{
			collideEntity.lock()->getComponent<Transform>().position_.x = entity->getComponent<Transform>().position_.x;
			collideEntity.lock()->getComponent<Transform>().position_.y = entity->getComponent<Transform>().position_.y-130.f;
			//return;
		}
		if (collideEntity.lock()->getType() == Entity::ENTITYTYPE::ITEM)
		{
			collideEntity.lock()->getComponent<Item>().pressed_ = true;
			//collideEntity.lock()->getComponent<Item>().inQuickSlot = false;
			collideEntity.lock()->getComponent<Transform>().position_.x = entity->getComponent<Transform>().position_.x;
			collideEntity.lock()->getComponent<Transform>().position_.y = entity->getComponent<Transform>().position_.y; //- 130.f;
			//return;
		}

	}
	else
	{
		if (collideEntity.lock()->getType() == Entity::ENTITYTYPE::ITEM)
		{
			if (collideEntity.lock()->getComponent<Item>().pressed_ == false)
				return;
			collideEntity.lock()->getComponent<Item>().pressed_ = false;
			
			if (collideEntity.lock()->getComponent<Transform>().position_.y <= GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition().y - SCREEN_HEIGHT/2.f + 100.f)
			{
				wstring tempName = collideEntity.lock()->getComponent<Item>().name_;
				int tempCount = collideEntity.lock()->getComponent<Item>().myCount;
				GameManager::getInstance()->getQuickSlotEntity()->getComponent<Item>().CopyItem(tempName, tempCount);
				GameManager::getInstance()->getQuickSlotEntity()->getComponent<Item>().SetParentEntity(collideEntity.lock().get());
				return;
			}

			//if (collideEntity.lock()->getComponent<Item>().inQuickSlot == true)
			//	collideEntity.lock()->getComponent<Item>().inQuickSlot = true;
			
			if (collideEntity.lock()->getComponent<Item>().inInventoryUI == false)
				collideEntity.lock()->getComponent<Item>().inInventory_ = false;

		
		}
	}



	/*if (Input.mouseUp(InputManager::MOUSEBUTTONTYPE::LEFT))
	{
		if (collideEntity.lock()->getType() == Entity::ENTITYTYPE::ITEM)
		{
			
			collideEntity.lock()->getComponent<Item>().pressed_ = false;
			if(collideEntity.lock()->getComponent<Item>().inInventoryUI==false)
			collideEntity.lock()->getComponent<Item>().inInventory_ = false;
		}

	}*/

}

void PartyUI::onMakeParty()
{
	/*if (Input.keyDown(DIK_F1))
	{
		if (!partyMemberCount_.expired() || !partyMemberList_.expired())
			return;

		shared_ptr<Entity> entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		entity->addComponent<DNFUI>(7, _vec3(300, 220, -1001.f));
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");
		EntityManager::getInstance()->insertEntity(entity);
		partyMemberCount_ = entity;
		
		entity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
		entity->addComponent<DNFUI>(8, _vec3(0, 0, -1001.f));
		entity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"DNFUI");
		EntityManager::getInstance()->insertEntity(entity);
		partyMemberList_ = entity;

		NetworkManager::getInstance()->tcpClient_.inputMakePartyMessage();
	}*/
}

void PartyUI::onCheckPartyRequest()
{
//	SLNetworkStruct& networkStruct = NetworkManager::getInstance()->networkStruct_;
//
//	if (networkStruct.partyRequestList.size() == 0)
//	{
//		//std::cout << "파티 초대가 없습니다.\n";
//		return;
//	}
//
//	if (!partyMemberCount_.expired() || !partyMemberList_.expired())
//		return;
//
//	int inviteUserIDN;
//
//	networkStruct.networkLock_.lock();
//	inviteUserIDN = networkStruct.partyRequestList[0];
//	networkStruct.partyRequestList.erase(networkStruct.partyRequestList.begin());
//	networkStruct.networkLock_.unlock();
//
//	NetworkManager::getInstance()->tcpClient_.inputAcceptPartyMessage(inviteUserIDN);
//
}

void PartyUI::onExitParty()
{/*
	if (Input.keyDown(DIK_F2))
	{
		if (!partyMemberCount_.expired() && !partyMemberList_.expired())
		{
			partyMemberCount_.lock()->setActive(false);
			partyMemberList_.lock()->setActive(false);
		}

		NetworkManager::getInstance()->tcpClient_.inputExitPartyMessage();

	}*/
}
