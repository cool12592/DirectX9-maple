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
		//����
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
				cout << "����" << endl;
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
					cout << "��ü" << endl;
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


		//0.5���̻� �������� exit
		if (exitTime)
		{
			exitTimer += TimeManager::getInstance()->getDeltaTime();
			if (exitTimer > 0.5f)
			{
				exitTime = false;
				player_->getComponent<Rigidbody>().rbOBB_ = nullptr;
				player_->getComponent<Rigidbody>().onGround_ = false;
				exitTimer = 0.f;

				cout << "�ƿ�" << endl;

			}
		}
	}
	
}



//widhth > height�̸� ���� ���� ��or �Ʒ��� �ִ»�Ȳ
//height > width�� ���� ���� ����or ������ �ִ»�Ȳ
//�׳� width height������ 
//���� ���������� �� width�� ��� ������
//���� �� ���� ���� �� height�� ��� ������ ¥���


//4���� ���γ���  1. ���� �����ʾƷ� 2. ���� �� ������ �Ʒ� 3. ���� �� ������ 4. ���� �� ��������


//1��� width = ��������- ������ 
// width�� ����� �Ǵ� ��Ȳ = ���������� Ŀ���»�Ȳ= ���� ������ �ִ»�Ȳ
//height =    ����-���Ʒ� 
//  height�� Ŀ���� ��Ȳ= ������ �� ���� ��Ȳ = ���� �� ���� �ִ� ��Ȳ

//2,3,4�� ����
//2����� width = �������� - �� ����
//height = �� ���� - �� �Ʒ���

//3����� �� ������ - ������
// �� ��- ���Ʒ�

//���� ������ ��ȣ�� ���������� �����ְ� ���� �۱⶧���� ����


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
		width = boundaryMax.x - collideMin.x; //�ö�Ÿ������ width�� ������ǰ� �ۿ����� �� width�� ��������
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
