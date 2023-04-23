#include "stdafx.h"
#include "BounDary.h"
#include "EntityManager.h"
#include "GameManager.h"
#include "CollisionDetection.h"
void BounDary::initialize()
{

	
	


		entity->addComponent<Transform>(position_, _vec3(0.f,0.f, 0.f), _vec3(1.f, 1.f, 1.f));
		entity->addComponent<BoxCollider>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), scale_);

		entity->getComponent<BoxCollider>().bindColliderFunction(
			bind(&BounDary::enterCollider, this, placeholders::_1),
			bind(&BounDary::stayCollider, this, placeholders::_1),
			bind(&BounDary::exitCollider, this, placeholders::_1));

		BoxCollider& Box = entity->getComponent<BoxCollider>();
		//로프
		if (type_ == 1)
		{

			shared_ptr<Entity> topRope = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			topRope->setTypeAndName(Entity::ENTITYTYPE::MAP, L"topRope");
			topRope->addComponent<BounDary>(2, position_ + _vec3(0.f, Box.transform_.scale_.y*0.5f, 0.f), _vec3(50.f, 20.f, 10.f));
			EntityManager::getInstance()->insertEntity(topRope);
		}

		//if (D3DXToRadian(entity->getComponent<BoxCollider>().transform_.rotation_.z) > 0.3f)
		//	hill = -1;
}

void BounDary::update()
{

	
	
	if (isOBB)
	{

		
		if (player_ == nullptr)
			player_ = GameManager::getInstance()->getPlayer();
		/*if (CollisionDetection::OBBColliderDetection(player_.get(), entity))
		{
			float dis = entity->getComponent<Transform>().position_.x+entity->getComponent<BoxCollider>().transform_.scale_.x/2.f - player_->getComponent<Transform>().position_.y;
			float rot = entity->getComponent<BoxCollider>().transform_.rotation_.z;
			player_->getComponent<Transform>().position_.y = entity->getComponent<Transform>().position_.y + -dis*sinf(D3DXToRadian(rot+0.5f));
			player_->getComponent<Rigidbody>().onGround_ = true;
		}*/
		/////////////
		if (CollisionDetection::OBBColliderDetection(player_.get(), entity))
		{
			if (player_->getComponent<Rigidbody>().rbOBB_ == nullptr)
			{
				player_->getComponent<Rigidbody>().onGround_ = true;
				player_->getComponent<Rigidbody>().rbOBB_ = entity;
				exitTime = false;
				exitTimer = 0.f;
				cout << "입장" << endl;
				cout <<entity->getComponent<BounDary>().hill<< endl;
			}
			else
			{
				if (player_->getComponent<Rigidbody>().rbOBB_->getComponent<Transform>().position_.y > entity->getComponent<Transform>().position_.y)
				{
					player_->getComponent<Rigidbody>().onGround_ = true;
					player_->getComponent<Rigidbody>().rbOBB_ = entity;
					exitTime = false;
					exitTimer = 0.f;
					cout << "교체" << endl;
				}
			}
			if (player_->getComponent<Rigidbody>().rbOBB_ == entity)
			{
			

				if (InputManager::getInstance()->keyPressing(DIK_RIGHT))
				{
					float rot = (entity->getComponent<BoxCollider>().transform_.rotation_.z);
					//int num = hill * -1;
					//if (hill * -1 > 0)num = hill*-1 * 0.99f;
					
					player_->getComponent<Rigidbody>().direction_ = _vec3(cosf(rot)*0.8f,  -1*hill*sinf(rot - D3DXToRadian(180.f) * 0.5f)*0.5f, 0.f);
					Status& status = player_->getComponent<Status>();
					player_->getComponent<Rigidbody>().setForce(player_->getComponent<Rigidbody>().direction_ * (float)status.moveSpeed_);

				}
				if (InputManager::getInstance()->keyPressing(DIK_LEFT))
				{
					//int num = hill;
					//if (hill > 0)num = hill * 0.99f;
					float rot = (entity->getComponent<BoxCollider>().transform_.rotation_.z);
					player_->getComponent<Rigidbody>().direction_ = _vec3(-cosf(rot)*0.8f,hill *sinf(rot - D3DXToRadian(180.f) * 0.5f)*0.5f, 0.f);
					Status& status = player_->getComponent<Status>();
					player_->getComponent<Rigidbody>().setForce(player_->getComponent<Rigidbody>().direction_ * (float)status.moveSpeed_);

				}
			}
			
		}
		else
		{
			
			if (player_->getComponent<Rigidbody>().rbOBB_ ==entity)
			{
				//exitTime = true;
				player_->getComponent<Rigidbody>().rbOBB_ = nullptr;
				player_->getComponent<Rigidbody>().onGround_ = false;
				
			}
		}


		//0.5초이상 떨어져야 exit
		if (exitTime)
		{
			exitTimer += TimeManager::getInstance()->getDeltaTime();
			if (exitTimer > 0.5f)
			{
				exitTime = false;
				player_->getComponent<Rigidbody>().rbOBB_ = nullptr;
				player_->getComponent<Rigidbody>().onGround_ = false;
				exitTimer = 0.f;

				cout << "아웃" << endl;

			}
		}
	}
	
}



//widhth > height이면 내가 벽에 위or 아래에 있는상황
//height > width면 내가 벽에 왼쪽or 오른쪽 있는상황
//그냥 width height공식을 
//내가 벽위에있을 땐 width가 양수 나오게
//내가 벽 옆에 있을 땐 height가 양수 나오게 짜면됨


//4가지 경우로나눔  1. 내가 벽왼쪽아래 2. 내가 벽 오른쪽 아래 3. 내가 벽 왼쪽위 4. 내가 벽 오른쪽위


//1경우 width = 나오른쪽- 벽왼쪽 
// width가 양수가 되는 상황 = 내오른쪽이 커지는상황= 내가 벽위에 있는상황
//height =    내위-벽아래 
//  height가 커지는 상황= 내위가 더 높은 상황 = 내가 벽 옆에 있는 상황

//2,3,4도 같은
//2번경우 width = 벽오른쪽 - 내 왼쪽
//height = 내 위쪽 - 벽 아래쪽

//3번경우 내 오른쪽 - 벽왼쪽
// 벽 위- 내아래

//선을 넘으면 구호가 같아지지만 넘은애가 아주 작기때문에 노상관


void BounDary::enterCollider(Entity* colliderEntity)
{
	if (isOBB)
	{
		
		
		return;
	}
	if (colliderEntity->getName() != L"player" && colliderEntity->getType() != Entity::ENTITYTYPE::ENEMY)
		return;
	if (!colliderEntity->hasComponent<Rigidbody>())
		return;
	
	Rigidbody& rb = colliderEntity->getComponent<Rigidbody>();

	

	if (type_ == 1 && colliderEntity->getName() == L"player")
	{
		rb.inRope_ = true;
		return;
	}

	if (type_ == 2)
	{
		rb.topRope_ = true;
		return;
	}

	if (rb.getUseGravity() == false)
		return;

	Transform& boundaryTransform = entity->getComponent<Transform>();
	Transform& collideTransform = colliderEntity->getComponent<Transform>();
	BoxCollider& boundaryCollider = entity->getComponent<BoxCollider>();
	BoxCollider& collideCollider = colliderEntity->getComponent<BoxCollider>();


	float boundaryWidth = boundaryCollider.transform_.scale_.x;
	float boundaryHeight = boundaryCollider.transform_.scale_.y;
	float collideWidth = collideCollider.transform_.scale_.x;
	float collideHeight = collideCollider.transform_.scale_.y;

	_vec3 boundaryMin = boundaryTransform.position_ - boundaryCollider.transform_.scale_ * 0.5f;
	_vec3 boundaryMax = boundaryTransform.position_ + boundaryCollider.transform_.scale_ * 0.5f;
	_vec3 collideMin = collideTransform.position_ - collideCollider.transform_.scale_ * 0.5f;
	_vec3 collideMax = collideTransform.position_ + collideCollider.transform_.scale_ * 0.5f;

	const _vec3& boundaryPosition = boundaryTransform.position_;
	const _vec3& collidePosition = collideTransform.position_;

	float width, height;




	if (collidePosition.x < boundaryPosition.x && collidePosition.y < boundaryPosition.y)
	{
		width = collideMax.x - boundaryMin.x;
		height = collideMax.y- boundaryMin.y;
		if (width > height)
		{
			
		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x - boundaryWidth * 0.5f - collideWidth * 0.5f;
	}
	else if (collidePosition.x >= boundaryPosition.x && collidePosition.y < boundaryPosition.y)
	{
		width = boundaryMax.x - collideMin.x;
		height = collideMax.y- boundaryMin.y;
		if (width > height)
		{
		
		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x + boundaryWidth * 0.5f + collideWidth * 0.5f;
	}
	else if (collidePosition.x < boundaryPosition.x && collidePosition.y >= boundaryPosition.y)
	{
		width = collideMax.x - boundaryMin.x;
		height = boundaryMax.y - collideMin.y;
		if (width > height)
		{
			colliderEntity->getComponent<Transform>().position_.y = boundaryPosition.y + boundaryHeight * 0.5f + collideHeight * 0.5f+ 15.f;
			if (type_ == 0) rb.onGround_ = true;

		
		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x - boundaryWidth * 0.5f - collideWidth * 0.5f;
	}
	else if (collidePosition.x >= boundaryPosition.x && collidePosition.y >= boundaryPosition.y)
	{
		width = boundaryMax.x - collideMin.x; //올라타있을땐 width가 양수가되고 밖에있을 땐 width가 음수가됨
		height = boundaryMax.y - collideMin.y;
		if (width > height)
		{

			colliderEntity->getComponent<Transform>().position_.y = boundaryPosition.y + boundaryHeight * 0.5f + collideHeight * 0.5f+ 15.f;
			if (type_ == 0) rb.onGround_ = true;
		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x + boundaryWidth * 0.5f + collideWidth * 0.5f;
	}
}

void BounDary::stayCollider(Entity* colliderEntity)
{
	
	if (isOBB)
	{
	
		return;
	}
	if (colliderEntity->getName() != L"player" && colliderEntity->getType() != Entity::ENTITYTYPE::ENEMY)
		return;
	if (!colliderEntity->hasComponent<Rigidbody>())
		return;

	Rigidbody& rb = colliderEntity->getComponent<Rigidbody>();



	if (type_ == 1 && colliderEntity->getName() == L"player")
	{
		if(!rb.getUseGravity())
		colliderEntity->getComponent<Transform>().position_.x = entity->getComponent<Transform>().position_.x;
		return;
	}

	if (type_ == 2)
	{
		rb.topRope_ = true;
		return;
	}

	
	if (rb.getUseGravity() == false)
		return;
	
	Transform& boundaryTransform = entity->getComponent<Transform>();
	Transform& collideTransform = colliderEntity->getComponent<Transform>();
	BoxCollider& boundaryCollider = entity->getComponent<BoxCollider>();
	BoxCollider& collideCollider = colliderEntity->getComponent<BoxCollider>();


	float boundaryWidth = boundaryCollider.transform_.scale_.x;
	float boundaryHeight = boundaryCollider.transform_.scale_.y;
	float collideWidth = collideCollider.transform_.scale_.x;
	float collideHeight = collideCollider.transform_.scale_.y;

	_vec3 boundaryMin = boundaryTransform.position_ - boundaryCollider.transform_.scale_ * 0.5f;
	_vec3 boundaryMax = boundaryTransform.position_ + boundaryCollider.transform_.scale_ * 0.5f;
	_vec3 collideMin = collideTransform.position_ - collideCollider.transform_.scale_ * 0.5f;
	_vec3 collideMax = collideTransform.position_ + collideCollider.transform_.scale_ * 0.5f;

	const _vec3& boundaryPosition = boundaryTransform.position_;
	const _vec3& collidePosition = collideTransform.position_;

	float width, height;
	if (collidePosition.x < boundaryPosition.x && collidePosition.y < boundaryPosition.y)
	{
		width = collideMax.x - boundaryMin.x;
		height = collideMax.y- boundaryMin.y;
		if (width > height)
		{
		
		}
		else if(type_==3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x - boundaryWidth * 0.5f - collideWidth * 0.5f;
	}
	else if (collidePosition.x >= boundaryPosition.x && collidePosition.y < boundaryPosition.y)
	{
		width = boundaryMax.x - collideMin.x;
		height = collideMax.y- boundaryMin.y;
		if (width > height)
		{
			
		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x + boundaryWidth * 0.5f + collideWidth * 0.5f;
	}
	else if (collidePosition.x < boundaryPosition.x && collidePosition.y >= boundaryPosition.y)
	{
		width = collideMax.x - boundaryMin.x;
		height = boundaryMax.y - collideMin.y;
		if (width > height)
		{
			
		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x - boundaryWidth * 0.5f - collideWidth * 0.5f;
	}
	else if (collidePosition.x >= boundaryPosition.x && collidePosition.y >= boundaryPosition.y)
	{
		width = boundaryMax.x - collideMin.x;
		height = boundaryMax.y - collideMin.y;
		if (width > height)
		{

		}
		else if (type_ == 3)
			colliderEntity->getComponent<Transform>().position_.x = boundaryPosition.x + boundaryWidth * 0.5f + collideWidth * 0.5f;
	}
}
