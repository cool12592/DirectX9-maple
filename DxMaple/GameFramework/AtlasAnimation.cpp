#include "stdafx.h"
#include "AtlasAnimation.h"

#include "DeviceManager.h"
#include "TimeManager.h"
#include "Transform.h"
AtlasAnimation::AtlasAnimation(wstring bufferName, wstring shaderName):device_(DeviceManager::getInstance()->getDevice()),animationSpeed_(DEFAULT_ANIMATION_SPEED), baseAnimationSpeed_(DEFAULT_ANIMATION_SPEED),isRight_(true),userPivot_(_vec2(0.f,0.f)),isInterpolate_(false),interSpriteIndex_(0.f),isZRender(true),
		destBlendOp_(D3DBLEND_INVSRCALPHA),srcBlendOp_(D3DBLEND_SRCALPHA), blendEnable_(true),currentSpriteName_(L"")
{
	ASSERT_MESSAGE(SUCCEEDED(setBuffer(bufferName)),"buffer setting failed");
	ASSERT_MESSAGE(SUCCEEDED(setShader(shaderName)), "shader setting failed");
}


AtlasAnimation::~AtlasAnimation()
{
	release();
}


HRESULT AtlasAnimation::setBuffer(wstring bufferName)
{
	unique_lock<mutex> lock(animLock_);


	buffer_ = dynamic_pointer_cast<Buffer>(DeviceManager::getInstance()->getResources(bufferName));
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(!buffer_.expired(), "buffer does not exist", E_FAIL);
#endif
	return S_OK;
}

HRESULT AtlasAnimation::setShader(wstring shaderName)
{
	unique_lock<mutex> lock(animLock_);


	shader_ = dynamic_pointer_cast<Shader>(DeviceManager::getInstance()->getResources(shaderName));
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader does not exist", E_FAIL);
#endif
	return S_OK;
}

HRESULT AtlasAnimation::insertSprite(wstring spriteName, const wchar_t* spritePath, const wchar_t* atlasPath)
{
	unique_lock<mutex> lock(animLock_);


#ifdef _DEBUG
	auto& find_iter = mapSprites_.find(spriteName);
	ASSERT_MESSAGE_RETURN(mapSprites_.end() == find_iter, "sprite name already exist", E_FAIL);
#endif

	if (!DeviceManager::getInstance()->isExistResource(spritePath))
	{
		//텍스쳐 경로가 곧 텍스쳐 이름
		if (FAILED(DeviceManager::getInstance()->createTexture(spritePath, spritePath)))
			return E_FAIL;
	}

	shared_ptr<Texture> texture = dynamic_pointer_cast<Texture>(DeviceManager::getInstance()->getResources(spritePath));

	Atlas::ATLASINFO atlasInfo;

	if (FAILED(Atlas::loadAtlasInfo(atlasInfo, atlasPath)))
		return E_FAIL;

	currentSpriteName_ = spriteName;
	startSpriteIndex_ = 0.f;
	endSpriteIndex_ = (float)atlasInfo.frames.size()-1.f;
	currentSpriteIndex_ = 0.f;

	mapSprites_.emplace(spriteName, make_pair(texture, move(atlasInfo)));
	return S_OK;
}

HRESULT AtlasAnimation::insertMotionData(wstring spriteName, wstring motionName, int startIndex, int endIndex)
{
	unique_lock<mutex> lock(animLock_);

#ifdef _DEBUG
	auto& sprite_find_iter = mapSprites_.find(spriteName);
	ASSERT_MESSAGE_RETURN(mapSprites_.end() != sprite_find_iter, "sprite name does not exist", E_FAIL);

	auto& index_find_iter = find_if(mapSpriteIndexData_[spriteName].begin(), mapSpriteIndexData_[spriteName].end(), [&](const tuple<wstring, int, int>& motionData) {
		if (get<0>(motionData) == motionName)
			return true;
		return false;
		});
	ASSERT_MESSAGE_RETURN(mapSpriteIndexData_[spriteName].end() == index_find_iter, "motion data already exist", E_FAIL);
	
	ASSERT_MESSAGE_RETURN(startIndex >= 0 && startIndex < (int)mapSprites_[spriteName].second.frames.size(), "sprite index exceed", E_FAIL);
	ASSERT_MESSAGE_RETURN(endIndex >= 0 && endIndex < (int)mapSprites_[spriteName].second.frames.size(), "sprite index exceed", E_FAIL);

#endif
	if (mapSpriteIndexData_[spriteName].empty())
	{
		mapSpriteIndexData_[spriteName].emplace_back(motionName, startIndex, endIndex);
		changeMotion(motionName);
	}
	else
		mapSpriteIndexData_[spriteName].emplace_back(motionName, startIndex, endIndex);

	return S_OK;
}

HRESULT AtlasAnimation::changeCurrentSprite(wstring spriteName)
{
	unique_lock<mutex> lock(animLock_);

#ifdef _DEBUG
	auto& find_iter = mapSprites_.find(spriteName);
	ASSERT_MESSAGE_RETURN(mapSprites_.end() != find_iter, "Sprite does not exist", E_FAIL);
#endif
	currentSpriteName_ = spriteName;
	endSpriteIndex_ = (float)mapSprites_[spriteName].second.frames.size()-1.f;
	startSpriteIndex_ = 0.f;
	currentSpriteIndex_ = 0.f;
	

	return S_OK;
}

HRESULT AtlasAnimation::changeMotion(wstring motionName)
{

#ifdef _DEBUG
	auto& motion_find_iter = mapSpriteIndexData_.find(currentSpriteName_);
	ASSERT_MESSAGE_RETURN(mapSpriteIndexData_.end() != motion_find_iter, "Sprite name data does not exist", E_FAIL);
#endif

	auto& index_find_iter=find_if(mapSpriteIndexData_[currentSpriteName_].begin(),mapSpriteIndexData_[currentSpriteName_].end(), [&](const tuple<wstring, int, int>& motionData) {
		if (get<0>(motionData) == motionName)
			return true;
		return false;
		});

	ASSERT_MESSAGE_RETURN(mapSpriteIndexData_[currentSpriteName_].end() != index_find_iter, "motion data does not exist", E_FAIL);

	currentMotionName_ = motionName;
	startSpriteIndex_ = (float)get<1>(*index_find_iter);
	endSpriteIndex_ = (float)get<2>(*index_find_iter);
	currentSpriteIndex_ = startSpriteIndex_;
	return S_OK;
}

void AtlasAnimation::setCurrentIndex(float index)
{
	unique_lock<mutex> lock(animLock_);


#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(index >= 0 && index < (int)mapSprites_[currentSpriteName_].second.frames.size(), "exceed index");
#endif
	currentSpriteIndex_ = (float)index; 
}

wstring AtlasAnimation::getCurrentAnim()
{
	return currentSpriteName_;
}

wstring AtlasAnimation::getCurrentMotionName()
{
	return currentMotionName_;
}

_vec2 AtlasAnimation::getAltInfo()
{
	 Atlas::ATLASINFO& atlasInfo = mapSprites_[currentSpriteName_].second;
	_vec2 atlasScale = { (float)atlasInfo.frames[(int)currentSpriteIndex_].sourceSize.w,(float)atlasInfo.frames[(int)currentSpriteIndex_].sourceSize.h };
	return atlasScale; 
}

bool AtlasAnimation::isSpriteEnd()
{
	if (endSpriteIndex_-0.3f <= currentSpriteIndex_)
		return true;
	return false;
}


void AtlasAnimation::stopAnimation(float duration, function<void()> stopEndTrigger)
{
	isStop = true;
	stopEndTrigger_ = stopEndTrigger;
	stopDuration = duration;
	stopTimer = 0.f;
}

void AtlasAnimation::resumeAnimation()
{
	isStop = false;
	isPause = false;
}

void AtlasAnimation::PauseAnimation()
{
	isPause = true;
}


void AtlasAnimation::initialize()
{
}

void AtlasAnimation::update()
{
	if (wcscmp(L"", currentSpriteName_.c_str()) == 0)
		return;
	if (isPause) return;

	if (isInterpolate_)
	{
		currentSpriteIndex_ = ws::Math::lerp(currentSpriteIndex_, interSpriteIndex_, TimeManager::getInstance()->getDeltaTime());
	}
	else
	{
		if (isStop)
		{
			stopTimer += TimeManager::getInstance()->getDeltaTime();
			if (stopTimer >= stopDuration)
			{
				isStop = false;
				stopEndTrigger_();
			}
		}
		else
			currentSpriteIndex_ += TimeManager::getInstance()->getDeltaTime() * animationSpeed_;

		if (currentSpriteIndex_ > endSpriteIndex_)
			currentSpriteIndex_ = startSpriteIndex_;
	}

	
	readyPreShaderValues();

}

void AtlasAnimation::lateUpdate()
{
}

void AtlasAnimation::render()
{
	if (wcscmp(L"", currentSpriteName_.c_str()) == 0)
		return;

	unique_lock<mutex> lock(animLock_);

#ifdef _DEBUG
	ASSERT_MESSAGE(entity->hasComponent<Transform>(), "AtlasAnimation component need Transform Component");
	ASSERT_MESSAGE(!buffer_.expired(), "buffer not set");
	ASSERT_MESSAGE(!shader_.expired(), "shader not set");
	ASSERT_MESSAGE(!mapSprites_[currentSpriteName_].first.expired(), "texture not set");
#endif


	const Transform& transform = entity->getComponent<Transform>();
	
	shared_ptr<Buffer>& buffer = buffer_.lock();
	shared_ptr<Shader>& shader = shader_.lock();
	shared_ptr<Texture>& texture = mapSprites_[currentSpriteName_].first.lock();
	UINT num = 0;

	
	device_->SetRenderState(D3DRS_DESTBLEND, destBlendOp_);
	device_->SetRenderState(D3DRS_SRCBLEND, srcBlendOp_);
	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, blendEnable_);


	if (FAILED(shader->begin(&num, 0)))
		return;

	for (UINT i = 0; i < num; ++i)
	{
		shader->beginPass(i);


		for (int i = 0; i < col_; ++i)
		{
			for (int j = 0; j < row_; ++j)
			{

				if (isZRender)
				{
					ASSERT_MESSAGE_NULLRETURN(SUCCEEDED(readyTransforms(j, i)), "setting transform values failed");
				}
				else
				{
					ASSERT_MESSAGE_NULLRETURN(SUCCEEDED(readyTransformsNotZRender(j, i)), "setting transform values failed");
				}


				ASSERT_MESSAGE_NULLRETURN(SUCCEEDED(readyAtlasValues()), "setting atlas values failed");
				ASSERT_MESSAGE(SUCCEEDED(setShaderValuesAll()), "setting shader values failed");

				shader->setTexture("baseTexture", texture->getTexture());

				buffer->render();
			}
		}

		
		shader->endPass();
	}

	if (FAILED(shader->end()))
		return;
	
	
}

void AtlasAnimation::release()
{
	
}


HRESULT AtlasAnimation::readyAtlasValues()
{
	int atlasIndex = (int)currentSpriteIndex_;
	Atlas::ATLASINFO& atlasInfo = mapSprites_[currentSpriteName_].second;
	_vec2 totalSize = { (float)atlasInfo.meta.size.w ,(float)atlasInfo.meta.size.h };
	_vec2 frameSize = { (float)atlasInfo.frames[atlasIndex].frame.w,(float)atlasInfo.frames[atlasIndex].frame.h };
	_vec2 frameOffset = { (float)atlasInfo.frames[atlasIndex].frame.x,(float)atlasInfo.frames[atlasIndex].frame.y };
	_vec2 sourceSizeOffset = { (float)atlasInfo.frames[atlasIndex].spriteSourceSize.x ,(float)atlasInfo.frames[atlasIndex].spriteSourceSize.y };
	_vec2 originalSize = { (float)atlasInfo.frames[atlasIndex].sourceSize.w,(float)atlasInfo.frames[atlasIndex].sourceSize.h };
	ASSERT_MESSAGE_RETURN(SUCCEEDED(readyShaderValues(make_pair("totalSize", totalSize), make_pair("frameSize", frameSize),
		make_pair("frameOffset", frameOffset),make_pair("sourceSizeOffset",sourceSizeOffset),make_pair("originalSize",originalSize))), "ready shader values failed", E_FAIL);

	return S_OK;
}

HRESULT AtlasAnimation::readyTransforms(int row, int col)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Transform>(), "Entity does not have Transform component", E_FAIL);
#endif
	Atlas::ATLASINFO& atlasInfo = mapSprites_[currentSpriteName_].second;
	_vec2 atlasScale = { (float)atlasInfo.frames[(int)currentSpriteIndex_].sourceSize.w,(float)atlasInfo.frames[(int)currentSpriteIndex_].sourceSize.h };
	_vec2 atlasPivot= { (float)atlasInfo.frames[(int)currentSpriteIndex_].pivot.x,(float)atlasInfo.frames[(int)currentSpriteIndex_].pivot.y };
	Transform& transform = entity->getComponent<Transform>();
	_mat matTranslation, matRotation, matScale;
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScale);

	if(isRight_)
		D3DXMatrixTranslation(&matTranslation, transform.position_.x + ((0.5f-atlasPivot.x)*atlasScale.x)*transform.scale_.x - userPivot_.x + (row * transform.scale_.x * atlasScale.x *spacing_)+addPos_.x, transform.position_.y+((atlasPivot.y-0.5f)*atlasScale.y ) * transform.scale_.y + userPivot_.y + (col*transform.scale_.y* atlasScale.y )+addPos_.y/*+transform.position_.z + addPos_.z*/, 0.f);
	else
		D3DXMatrixTranslation(&matTranslation, transform.position_.x - ((0.5f - atlasPivot.x) * atlasScale.x) * transform.scale_.x + userPivot_.x + (row*transform.scale_.x* atlasScale.x * spacing_)+addPos_.x, transform.position_.y + ((atlasPivot.y - 0.5f) * atlasScale.y) * transform.scale_.y + userPivot_.y + (col * transform.scale_.y* atlasScale.y  )+addPos_.y /*+ transform.position_.z + addPos_.z*/, 0.f);

	D3DXMatrixRotationYawPitchRoll(&matRotation, transform.rotation_.y, transform.rotation_.x, transform.rotation_.z);
	D3DXMatrixScaling(&matScale, transform.scale_.x * atlasScale.x, transform.scale_.y * atlasScale.y, transform.scale_.z);

	_mat matWorld;
	if(nullptr==transform.parentMatrix_)
		matWorld= matScale * matRotation * matTranslation;
	else
	{
		_mat matRevolution;
		D3DXMatrixRotationZ(&matRevolution, transform.revolutionAngle_);
		matWorld = matScale * matRotation * matTranslation * matRevolution * *transform.parentMatrix_;
	}
	_mat matView, matProjection;
	device_->GetTransform(D3DTS_VIEW, &matView);
	device_->GetTransform(D3DTS_PROJECTION, &matProjection);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(readyShaderValues(make_pair("worldMatrix", matWorld),
		make_pair("viewMatrix", matView),
		make_pair("projectionMatrix", matProjection))), "ready shader values failed", E_FAIL);


	return S_OK;
}

HRESULT AtlasAnimation::readyTransformsNotZRender(int row, int col)
{

#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Transform>(), "Entity does not have Transform component", E_FAIL);
#endif
	Atlas::ATLASINFO& atlasInfo = mapSprites_[currentSpriteName_].second;
	_vec2 atlasScale = { (float)atlasInfo.frames[(int)currentSpriteIndex_].sourceSize.w,(float)atlasInfo.frames[(int)currentSpriteIndex_].sourceSize.h };
	_vec2 atlasPivot = { (float)atlasInfo.frames[(int)currentSpriteIndex_].pivot.x,(float)atlasInfo.frames[(int)currentSpriteIndex_].pivot.y };
	Transform& transform = entity->getComponent<Transform>();
	_mat matTranslation, matRotation, matScale;
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScale);

	if (isRight_)
		D3DXMatrixTranslation(&matTranslation, transform.position_.x + ((0.5f - atlasPivot.x)*atlasScale.x)*transform.scale_.x - userPivot_.x + (row * transform.scale_.x * atlasScale.x *(1 + spacing_)) + addPos_.x, transform.position_.y + ((atlasPivot.y - 0.5f)*atlasScale.y) * transform.scale_.y + userPivot_.y + (col*transform.scale_.y* atlasScale.y) + addPos_.y, 0.f);
	else
		D3DXMatrixTranslation(&matTranslation, transform.position_.x - ((0.5f - atlasPivot.x) * atlasScale.x) * transform.scale_.x + userPivot_.x + (row*transform.scale_.x* atlasScale.x + spacing_) + addPos_.x, transform.position_.y + ((atlasPivot.y - 0.5f) * atlasScale.y) * transform.scale_.y + userPivot_.y + (col * transform.scale_.y* atlasScale.y) + addPos_.y, 0.f);

	D3DXMatrixRotationYawPitchRoll(&matRotation, transform.rotation_.y, transform.rotation_.x, transform.rotation_.z);
	D3DXMatrixScaling(&matScale, transform.scale_.x * atlasScale.x, transform.scale_.y * atlasScale.y, transform.scale_.z);

	_mat matWorld = matScale * matRotation * matTranslation;
	_mat matView, matProjection;
	device_->GetTransform(D3DTS_VIEW, &matView);
	device_->GetTransform(D3DTS_PROJECTION, &matProjection);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(readyShaderValues(make_pair("worldMatrix", matWorld),
		make_pair("viewMatrix", matView),
		make_pair("projectionMatrix", matProjection))), "ready shader values failed", E_FAIL);


	return S_OK;
}

HRESULT AtlasAnimation::readyPreShaderValues()
{
	readyShaderValues(make_pair("I_AM_SUN", false));
	readyShaderValues(make_pair("onVanish", false)); //기본적으로 사라지는 효과는 끔
	readyShaderValues(make_pair("onOutline", false));
	
	readyShaderValues(make_pair("yRatio", true)); //기본적으로 사라지는 효과는 끔
	readyShaderValues(make_pair("onTint", false));
	readyShaderValues(make_pair("damagedShader", false));
	readyShaderValues(make_pair("Disappear", false));


	return S_OK;
}


HRESULT AtlasAnimation::setShaderValuesAll()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader not set", E_FAIL);
#endif
	readyShaderValues(make_pair("isRight", isRight_));

	shared_ptr<Shader>& shader = shader_.lock();
	for (auto& var : mapShaderValues_)
	{
		visit([&](auto&& value) {
			shader->setValues(make_pair(var.first, value));
			}, var.second);
	}

	mapShaderValues_.clear();//컨테이너 비우기
	return S_OK;
}



//
//HRESULT AtlasAnimation::setWorldMatrix(const _vec3& position, const _vec3& rotation, const _vec3& scale)
//{
//	_mat matTranslation, matRotation, matScale, matWorld;
//	D3DXMatrixIdentity(&matTranslation);
//	D3DXMatrixIdentity(&matRotation);
//	D3DXMatrixIdentity(&matScale);
//	D3DXMatrixIdentity(&matWorld);
//	D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.y, rotation.x, rotation.z);
//
//	ASSERT_MESSAGE_RETURN(currentSpriteIndex_ < currentSpriteCount_, "sprite index exceeds sprite count", E_FAIL);
//	auto& currentFrame = mapSprites_[currentSpriteName_].second.frames[(int)currentSpriteIndex_];
//	float w = (float)currentFrame.spriteSourceSize.w;
//	float h = (float)currentFrame.spriteSourceSize.h;
//
//	float pivotX = 0, pivotY = 0;
//	pivotX = (float)currentFrame.spriteSourceSize.x + currentFrame.spriteSourceSize.w * 0.5f;
//	pivotY = -(float)currentFrame.spriteSourceSize.y - currentFrame.spriteSourceSize.h * 0.5f;
//
//	D3DXMatrixTranslation(&matTranslation, position.x + pivotX - (float)currentFrame.sourceSize.w * 0.5f, position.y + pivotY + (float)currentFrame.sourceSize.h * 0.5f, position.z);
//	D3DXMatrixScaling(&matScale, scale.x * w, scale.y * h, scale.z);
//
//	matWorld = matScale * matRotation * matTranslation;
//
//	device_->SetTransform(D3DTS_WORLD, &matWorld);
//
//	return S_OK;
//}
//
//HRESULT AtlasAnimation::setAtlasUV(int atlasIndex)
//{
//	ASSERT_MESSAGE_RETURN(!buffer_.expired(), "buffer not set", E_FAIL);
//	if (FAILED(buffer_.lock()->setAtlasUV(CUSTOMVERTEX(), mapSprites_[currentSpriteName_].second, atlasIndex)))
//		return E_FAIL;
//	return S_OK;
//}