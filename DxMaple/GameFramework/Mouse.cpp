#include "stdafx.h"
#include "Mouse.h"
#include "EntityManager.h"
#include "GameManager.h"
void Mouse::onCheckCollider()
{
	Ray& ray = entity->getComponent<Ray>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	vector<shared_ptr<Entity>> colliderEntities;
	colliderEntities.clear();
	EntityManager::getInstance()->getColliderEntities(colliderEntities);
	
	collideEntity_.reset();

	for (auto& entity : colliderEntities)
	{
		
		if (!entity->hasComponent<BoxCollider>())
			continue;

		BoxCollider& collider = entity->getComponent<BoxCollider>();

		COLLIDERRECT2D colliderRect = collider.getColliderRect2D();
		if (ray.rayCastCollider2D(colliderRect))
		{
			collideEntity_ = entity;

			if (entity->hasComponent<OtherPlayerController>())
				entity->getComponent<OtherPlayerController>().setOnMouse(true);
			break;
		}
		else
		{
			if (entity->hasComponent<OtherPlayerController>())
				entity->getComponent<OtherPlayerController>().setOnMouse(false);
	
		}
	}


	//충돌객체에 외곽선 셰이더on, 마우스 포인터 변화
	if (!collideEntity_.expired())
	{
		anim.changeMotion(L"onObject");
	}
	else
	{
		anim.changeMotion(L"idle");
	}

}


void Mouse::updateMouseTransform()
{
	Transform& transform = entity->getComponent<Transform>();
	Ray& ray = entity->getComponent<Ray>();
	RECT rc;

	GetClientRect(Device.getHwnd(), &rc);
	float width, height;
	width = (float)(rc.right - rc.left);
	height = (float)(rc.bottom - rc.top);
	
	int mouseX, mouseY;
	Input.getMousePosition(mouseX, mouseY);

	_vec3 mousePos = { (float)(mouseX - width * 0.5f),(float)(-mouseY + height * 0.5f),-10000.f };

	if (!GameManager::getInstance()->isPlayerSet())
		transform.position_ = mousePos;
	else
	{
		shared_ptr<Entity> player = GameManager::getInstance()->getPlayer();
		Camera& camera = player->getComponent<Camera>();

	

		_vec3 cameraPos = { camera.position_.x,camera.position_.y,0.f };

		transform.position_ = mousePos + cameraPos;
	}
	
}

void Mouse::initialize()
{
	entity->addComponent<Transform>(_vec3(0.f, 0.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	entity->addComponent<Ray>();
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");
	entity->getComponent<AtlasAnimation>().insertSprite(L"mouse", L"../AtlasFiles/UI/mouse.png", L"../AtlasFiles/UI/mouse.json");
	entity->getComponent<AtlasAnimation>().insertMotionData(L"mouse", L"idle", 0, 0);
	entity->getComponent<AtlasAnimation>().insertMotionData(L"mouse", L"onObject", 1, 1);

	entity->getComponent<AtlasAnimation>().changeMotion(L"idle");

	entity->getComponent<AtlasAnimation>().isZRender = false;
}

void Mouse::update()
{
	updateMouseTransform();
	onCheckCollider();

	timer_ += Time.getDeltaTime();
	if (timer_ >= 1.f)
		timer_ = 0.f;
}

void Mouse::lateUpdate()
{
}

void Mouse::render()
{
	if (!collideEntity_.expired())
	{
		entity->getComponent<AtlasAnimation>().readyShaderValues(make_pair("onTint", true), make_pair("tintTimer", 0.5f), make_pair("tintColor", _vec3(0.f,0.f,1.f)));

	}
}

void Mouse::release()
{
}
