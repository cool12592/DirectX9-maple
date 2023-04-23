#include "stdafx.h"
#include "CommonEffect.h"
#include "GameManager.h"
CommonEffect::CommonEffect(wstring atlasPath)
	:atlasPath_(atlasPath),isInstant_(true),duration_(0.f),timer_(0.f),userEntity_(nullptr), onVanish_(false),vanishAlpha_(1.f),vanishSpeed_(0.f),onCameraLock_(false)
{
}

CommonEffect::~CommonEffect()
{
}

void CommonEffect::setDuration(float duration)
{
	isInstant_ = false;
	duration_ = duration;
	timer_ = 0.f;
}

void CommonEffect::setAnimSpeed(float speed)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Effect must need AtlasAnimation component");
#endif
	entity->getComponent<AtlasAnimation>().setAnimationSpeed(speed);
}

void CommonEffect::setEffect(Entity* userEntity, bool traceUser, _vec3 localPos, float angle, float size)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Effect must need Transform component");
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Effect must need AtlasAnimation component");

	if (nullptr != userEntity)
	{
		ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<AtlasAnimation>(), "user must need AtlasAnimation component");
		ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<Transform>(), "user must need Transform component");

	}
#endif
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if (nullptr == userEntity)
	{
		transform.position_ = localPos;
		transform.rotation_ = { 0.f, 0.f, D3DXToRadian(angle) };
		transform.scale_ = { size,size,size };
	}
	else
	{
		Transform& userTransform = userEntity->getComponent<Transform>();
		AtlasAnimation& userAnim = userEntity->getComponent<AtlasAnimation>();

		anim.setRight(userAnim.getIsRight());

		localPos_ = localPos;

		if (!userAnim.getIsRight())
			localPos.x *= -1.f;
		

		transform.position_ = userTransform.position_ + localPos;
		transform.rotation_ = { 0.f, 0.f, D3DXToRadian(angle) };
		transform.scale_ = { size,size,size };

		userEntity_ = userEntity;
		attackBoxEntity_ = userEntity_;
		traceUser_ = traceUser;
	}
}

void CommonEffect::setEffect(Entity* userEntity, bool traceUser, const wchar_t* effectName)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Effect must need Transform component");
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Effect must need AtlasAnimation component");

	if (nullptr != userEntity)
	{
		ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<AtlasAnimation>(), "user must need AtlasAnimation component");
		ASSERT_MESSAGE_NULLRETURN(userEntity->hasComponent<Transform>(), "user must need Transform component");

	}
#endif
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	double localPosX, localPosY, localPosZ;
	float angle, size;
	wchar_t szTemp[MAX_BUF];
	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"localPosX", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	localPosX = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"localPosY", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	localPosY = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"localPosZ", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	localPosZ = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"angle", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	angle = (float)_ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"size", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	size = (float)_ttof(szTemp);

	_vec3 localPos = { (float)localPosX,(float)localPosY,(float)localPosZ };

	if (nullptr == userEntity)
	{
		transform.position_ = localPos;
		transform.rotation_ = { 0.f, 0.f, D3DXToRadian(angle) };
		transform.scale_ = { size,size,size };
	}
	else
	{
		Transform& userTransform = userEntity->getComponent<Transform>();
		AtlasAnimation& userAnim = userEntity->getComponent<AtlasAnimation>();

		anim.setRight(userAnim.getIsRight());

		localPos_ = localPos;

		if (!userAnim.getIsRight())
			localPos.x *= -1.f;


		transform.position_ = userTransform.position_ + localPos;
		transform.rotation_ = { 0.f, 0.f, D3DXToRadian(angle) };
		transform.scale_ = { size,size,size };

		userEntity_ = userEntity;
		traceUser_ = traceUser;
	}
}

void CommonEffect::setCameraLockEffect(const wchar_t* effectName)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Effect must need Transform component");
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Effect must need AtlasAnimation component");

#endif
	Transform& transform = entity->getComponent<Transform>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();

	onCameraLock_ = true;
	anim.destBlendOp_ = D3DBLEND_INVSRCALPHA;
	anim.isZRender = false;


	double localPosX, localPosY, localPosZ;
	float angle, size;
	wchar_t szTemp[MAX_BUF];
	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"localPosX", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	localPosX = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"localPosY", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	localPosY = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"localPosZ", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	localPosZ = _ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"angle", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	angle = (float)_ttof(szTemp);

	ZeroMemory(szTemp, sizeof(wchar_t) * MAX_BUF);
	GetPrivateProfileString(effectName, L"size", L"0.0", szTemp, MAX_BUF, L"../iniFiles/effectData.ini");
	size = (float)_ttof(szTemp);

	_vec3 localPos = { (float)localPosX,(float)localPosY,(float)localPosZ };

	localPosition_ = localPos;
	transform.rotation_ = { 0.f, 0.f, D3DXToRadian(angle) };
	transform.scale_ = { size,size,size };
}

void CommonEffect::setEffect(_vec3 worldPos, float angle, float size)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Effect must need Transform component");
#endif
	Transform& transform = entity->getComponent<Transform>();

	transform.position_ = worldPos;
	transform.rotation_ = { 0.f, 0.f, D3DXToRadian(angle) };
	transform.scale_ = { size,size,size };
}

void CommonEffect::setAttackBox(wstring path, int startIndex,_vec3 plusPosition)
{
	//공격체 세팅
	shared_ptr<Entity>& attackBox = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
	attackBox->addComponent<AttackBox>();
	attackBox->setTypeAndName(Entity::ENTITYTYPE::ENEMY, L"attackbox");
	EntityManager::getInstance()->insertEntity(attackBox);

	attackBox_ = attackBox;
	startAttackBoxIndex_ = startIndex;
	attackBoxTitle_ = path;
	attackBox_.lock()->getComponent<AttackBox>().setAbsoluteCoordinates(_vec3(entity->getComponent<Transform>().position_+ plusPosition));
}


void CommonEffect::setOnVanish(float vanishSpeed)
{
	onVanish_ = true;
	vanishAlpha_ = 1.f;
	vanishSpeed_ = vanishSpeed;

}

void CommonEffect::initialize()
{
	entity->addComponent<Transform>(_vec3(-10000.f,-10000.f,-10000.f), _vec3(0.f,0.f,0.f), _vec3(1.f,1.f,1.f));
	entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");

	wstring spritePath = atlasPath_ + L".png";
	wstring jsonPath = atlasPath_ + L".json";
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	anim.insertSprite(L"effect", spritePath.c_str(), jsonPath.c_str());
	//anim.destBlendOp_ = D3DBLEND_DESTALPHA;
}

void CommonEffect::update()
{
	//인스턴트 이펙트는 애니메이션 한번 돌면 삭제 //setduration지정안하면자동으로 인스턴트임
	if (onVanish_)
	{
		vanishAlpha_ = clamp(vanishAlpha_ - TimeManager::getInstance()->getDeltaTime() * vanishSpeed_, 0.f, 1.f);
		if (vanishAlpha_ <= 0.f)
			deactivate();
	}
	else
	{
		if (isInstant_)
		{
			if (entity->getComponent<AtlasAnimation>().isSpriteEnd())
				deactivate();
		}
		else//이외엔 수명시간 지나면 삭제
		{
			if (timer_ > duration_)
				deactivate();
			timer_ = TimeManager::getInstance()->getDeltaTime();
		}
	}

	if ((int)entity->getComponent<AtlasAnimation>().getCurrentIndex() == startAttackBoxIndex_)
	{
		//c_str =은 wsting을 wchar_t로 바꿔줌
		if (attackBox_.lock() != nullptr)
		{
			attackBox_.lock()->getComponent<AttackBox>().activateAttackBox(attackBoxTitle_.c_str(), attackBoxEntity_);
			entity->getComponent<AtlasAnimation>().setCurrentIndex(startAttackBoxIndex_ + 1);
		}
	}
	
	traceUser();
	if(!onCameraLock_)
		sendEffectData();

}

void CommonEffect::lateUpdate()
{
	traceCamera();

}

void CommonEffect::render()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Entity must need AtlasAnimation Component");
#endif
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	if(onVanish_)
		anim.readyShaderValues(make_pair("onVanish", onVanish_), make_pair("vanishAlpha", vanishAlpha_));

}

void CommonEffect::release()
{
}

void CommonEffect::traceUser()
{
	if (traceUser_ == false)
		return;
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Effect must need Transform component");
	ASSERT_MESSAGE_NULLRETURN(userEntity_->hasComponent<Transform>(), "userEntity must need Transform component");
	ASSERT_MESSAGE_NULLRETURN(userEntity_->hasComponent<AtlasAnimation>(), "userEntity must need AtlasAnimation component");

#endif

	Transform& transform = entity->getComponent<Transform>();
	Transform& userTransform = userEntity_->getComponent<Transform>();
	AtlasAnimation& userAnim = userEntity_->getComponent<AtlasAnimation>();

	_vec3 localPos = localPos_;
	if (!userAnim.getIsRight())
	{
		localPos.x *= -1.f;
	}

	transform.position_ = userTransform.position_ + localPos;
		
}

void CommonEffect::traceCamera()
{
	if (!onCameraLock_)
		return;

#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Entity must need Transform component");

#endif
	Transform& transform = entity->getComponent<Transform>();
	Camera& camera = GameManager::getInstance()->getPlayer()->getComponent<Camera>();
	
	transform.position_ = localPosition_ + camera.position_;

}

void CommonEffect::sendEffectData()
{

//#ifdef _DEBUG
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "Entity must need Transform component");
//	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<AtlasAnimation>(), "Entity must need AtlasAnimation component");
//#endif
//	Transform& transform = entity->getComponent<Transform>();
//	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
//
//	unique_ptr<UdpEffect> effectData = make_unique<UdpEffect>();
//	int userIDN, entityNumber;
//	Entity::ENTITYTYPE entityType;
//	entity->getEntityNetworkInfo(userIDN, entityNumber, entityType);
//
//	effectData->objectType_ = 6;
//
//	effectData->userIDN_ = userIDN;
//	effectData->objectNumber_ = entityNumber;
//
//	effectData->effectName_ = string(atlasPath_.begin(), atlasPath_.end());
//	effectData->currentSpriteIndex_ = anim.getCurrentIndex();
//	effectData->pX_ = transform.position_.x;
//	effectData->pY_ = transform.position_.y;
//	effectData->pZ_ = transform.position_.z;
//	effectData->sizeX_ = transform.scale_.x;
//	effectData->sizeY_ = transform.scale_.y;
//	effectData->sizeZ_ = transform.scale_.z;
//
//	effectData->pivotX_ = anim.getUserPivot().x;
//	effectData->pivotY_ = anim.getUserPivot().y;
//	effectData->isRight_ = anim.getIsRight();
//
//
//	NetworkManager::getInstance()->thisUser_.udpDataList_.push_back(move(effectData));
}
