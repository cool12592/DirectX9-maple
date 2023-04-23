#pragma once
#include "ECS.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include "DeviceManager.h"
class Sprite :
	public Component
{
public:
	Sprite(wstring bufferName, wstring shaderName);
	virtual ~Sprite();
	void SetMultiple(int row,int col);
	void setAddPos(_vec3 addPos);
	UINT* getImageSize()
	{
		D3DXIMAGE_INFO& imgInfo = texture_.lock()->getImgInfo();
		UINT imageSize[2];
		imageSize[0] = imgInfo.Width;
		imageSize[1] = imgInfo.Height; 
		return imageSize; 
	}
public:
	HRESULT setBuffer(wstring bufferName);
	HRESULT setShader(wstring shaderName);

	HRESULT insertTexture(const wchar_t* filePath); //텍스쳐 삽입
	HRESULT insertTexture(const wchar_t* filePath, int row, int col); //텍스쳐 삽입 (멀티용)


	//셰이더 value를 컨테이너에 보관
	HRESULT readyShaderValues()
	{
		return S_OK;
	}
	template<typename ValuePair>
	HRESULT readyShaderValues(ValuePair& valuePair)
	{
		ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader is not set", E_FAIL);
		auto& find_iter = mapShaderValues_.find(valuePair.first);
		ASSERT_MESSAGE_RETURN(mapShaderValues_.end() == find_iter, "value name already exist", E_FAIL);

		mapShaderValues_.emplace(valuePair.first, valuePair.second);
		return S_OK;
	}

	template<typename ValuePair, typename... ValuePairs>
	HRESULT readyShaderValues(ValuePair valuePair, ValuePairs... valuePairs)
	{
		ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader is not set", E_FAIL);
		auto& find_iter = mapShaderValues_.find(valuePair.first);
		ASSERT_MESSAGE_RETURN(mapShaderValues_.end() == find_iter, "value name already exist", E_FAIL);

		mapShaderValues_.emplace(valuePair.first, valuePair.second);
		if (FAILED(readyShaderValues(valuePairs...)))
			return E_FAIL;
		return S_OK;
	}
	D3DXIMAGE_INFO getTextureInfo() { if (!texture_.expired()) { return  texture_.lock()->getImgInfo(); } }

private:

	HRESULT readyTransforms(int row, int col);
	HRESULT setShaderValuesAll();

public:
	// Component을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;

private:
	LPDIRECT3DDEVICE9	device_;
	

	weak_ptr<Texture>	texture_;

	weak_ptr<Buffer>	buffer_;
	weak_ptr<Shader>	shader_;
	map<const char*, variant<bool, int, float, double, _vec2, _vec3, _mat>> mapShaderValues_;

	int row_ = 1,col_=1;
	_vec3  addPos_=_vec3(0.f,0.f,0.f);

public:
	bool isZRender_ = true;
public:
	DWORD destBlendOp_;
	DWORD srcBlendOp_;
	bool blendEnable_;

};

