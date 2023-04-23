#include "stdafx.h"
#include "Sprite.h"
#include "Transform.h"


Sprite::Sprite(wstring bufferName, wstring shaderName) :device_(DeviceManager::getInstance()->getDevice()), destBlendOp_(D3DBLEND_INVSRCALPHA), srcBlendOp_(D3DBLEND_SRCALPHA), blendEnable_(true),isZRender_(true)
{
	ASSERT_MESSAGE(SUCCEEDED(setBuffer(bufferName)), "buffer setting failed");
	ASSERT_MESSAGE(SUCCEEDED(setShader(shaderName)), "shader setting failed");

}

Sprite::~Sprite()
{
	release();
}

void Sprite::SetMultiple(int row, int col)
{

	row_ = row;
	col_ = col;
}

void Sprite::setAddPos(_vec3 addPos)
{
	addPos_ = addPos;
}



HRESULT Sprite::setBuffer(wstring bufferName)
{
	buffer_ = dynamic_pointer_cast<Buffer>(DeviceManager::getInstance()->getResources(bufferName));
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(!buffer_.expired(), "buffer does not exist", E_FAIL);
#endif
	return S_OK;
}

HRESULT Sprite::setShader(wstring shaderName)
{
	shader_ = dynamic_pointer_cast<Shader>(DeviceManager::getInstance()->getResources(shaderName));
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader does not exist", E_FAIL);
#endif
	return S_OK;
}

HRESULT Sprite::insertTexture(const wchar_t* filePath)
{
	if (!DeviceManager::getInstance()->isExistResource(filePath))
	{
		//텍스쳐 경로가 곧 텍스쳐 이름
		if (FAILED(DeviceManager::getInstance()->createTexture(filePath, filePath)))
			return E_FAIL;
	}

	shared_ptr<Texture> texture = dynamic_pointer_cast<Texture>(DeviceManager::getInstance()->getResources(filePath));

	texture_ = texture;

	return S_OK;
}


HRESULT Sprite::insertTexture(const wchar_t* filePath, int row,int col)
{


	if (!DeviceManager::getInstance()->isExistResource(filePath))
	{
		//텍스쳐 경로가 곧 텍스쳐 이름
		if (FAILED(DeviceManager::getInstance()->createTexture(filePath, filePath)))
			return E_FAIL;
	}

	shared_ptr<Texture> texture = dynamic_pointer_cast<Texture>(DeviceManager::getInstance()->getResources(filePath));

	texture_ = texture;
	row_ = row;
	col_ = col;

	return S_OK;
}






HRESULT Sprite::readyTransforms(int row,int col)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(entity->hasComponent<Transform>(), "Entity does not have Transform component", E_FAIL);
	ASSERT_MESSAGE_RETURN(!texture_.expired(), "texture not set", E_FAIL);
#endif

	//ASSERT_MESSAGE(0, "sdflkj");/
	D3DXIMAGE_INFO& imgInfo = texture_.lock()->getImgInfo();
	Transform& transform = entity->getComponent<Transform>();
	_mat matTranslation, matRotation, matScale;
	D3DXMatrixIdentity(&matTranslation);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScale);

	if(isZRender_)
		D3DXMatrixTranslation(&matTranslation, transform.position_.x+row*imgInfo.Width+ addPos_.x, transform.position_.y+col*imgInfo.Height+addPos_.y/*+transform.position_.z+ addPos_.z*/, 0.f);
	else
		D3DXMatrixTranslation(&matTranslation, transform.position_.x + row * imgInfo.Width + addPos_.x, transform.position_.y + col * imgInfo.Height + addPos_.y, 0.f);

	D3DXMatrixRotationYawPitchRoll(&matRotation, transform.rotation_.y, transform.rotation_.x, transform.rotation_.z);
	D3DXMatrixScaling(&matScale, transform.scale_.x* imgInfo.Width, transform.scale_.y * imgInfo.Height, transform.scale_.z);

	_mat matWorld = matScale * matRotation * matTranslation;
	_mat matView, matProjection;
	device_->GetTransform(D3DTS_VIEW, &matView);
	device_->GetTransform(D3DTS_PROJECTION, &matProjection);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(readyShaderValues(make_pair("worldMatrix", matWorld),
		make_pair("viewMatrix", matView),
		make_pair("projectionMatrix", matProjection))), "ready shader values failed", E_FAIL);


	return S_OK;
}

HRESULT Sprite::setShaderValuesAll()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader not set", E_FAIL);
#endif
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

void Sprite::initialize()
{
}

void Sprite::update()
{
}

void Sprite::lateUpdate()
{
}

void Sprite::render()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_NULLRETURN(entity->hasComponent<Transform>(), "AtlasAnimation component need Transform Component");
	ASSERT_MESSAGE_NULLRETURN(!buffer_.expired(), "buffer not set");
	ASSERT_MESSAGE_NULLRETURN(!shader_.expired(), "shader not set");
	ASSERT_MESSAGE_NULLRETURN(!texture_.expired(), "texture not set");
#endif
	const Transform& transform = entity->getComponent<Transform>();

	//ASSERT_MESSAGE_NULLRETURN(SUCCEEDED(readyTransforms()), "setting transform values failed");

	shared_ptr<Shader>& shader = shader_.lock();
	shared_ptr<Buffer>& buffer = buffer_.lock();
	shared_ptr<Texture>& texture = texture_.lock();
	UINT num = 0;

	device_->SetRenderState(D3DRS_ALPHABLENDENABLE, blendEnable_);
	device_->SetRenderState(D3DRS_DESTBLEND, destBlendOp_);
	device_->SetRenderState(D3DRS_SRCBLEND, srcBlendOp_);


	if (FAILED(shader->begin(&num, 0)))
		return;

	for (UINT k = 0; k < num; ++k)
	{
		shader->beginPass(k);

		for (int i = 0;i < col_;++i)
		{
			for (int j = 0;j < row_;++j)
			{

				ASSERT_MESSAGE_NULLRETURN(SUCCEEDED(readyTransforms(j, i)), "setting transform values failed");

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

void Sprite::release()
{
}
