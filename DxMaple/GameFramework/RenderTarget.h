#pragma once
#include <variant>
class RenderTarget
{
public:
	RenderTarget(LPDIRECT3DDEVICE9 device);
	~RenderTarget();

	HRESULT initialize(const wchar_t* shaderPath);
	void release();


	HRESULT changeTargetForObjects();
	HRESULT renderSurface(const D3DXCOLOR& clearColor);

	//셰이더 value를 컨테이너에 보관
	HRESULT readyShaderValues()
	{
		return S_OK;
	}
	template<typename ValuePair>
	HRESULT readyShaderValues(ValuePair& valuePair)
	{
		ASSERT_MESSAGE_RETURN(nullptr!=shader_, "shader is nullptr", E_FAIL);
		auto& find_iter = mapShaderValues_.find(valuePair.first);
		ASSERT_MESSAGE_RETURN(mapShaderValues_.end() == find_iter, "value name already exist", E_FAIL);

		mapShaderValues_.emplace(valuePair.first, valuePair.second);
		return S_OK;
	}

	template<typename ValuePair, typename... ValuePairs>
	HRESULT readyShaderValues(ValuePair valuePair, ValuePairs... valuePairs)
	{
		ASSERT_MESSAGE_RETURN(nullptr != shader_, "shader is nullptr", E_FAIL);
		auto& find_iter = mapShaderValues_.find(valuePair.first);
		ASSERT_MESSAGE_RETURN(mapShaderValues_.end() == find_iter, "value name already exist", E_FAIL);

		mapShaderValues_.emplace(valuePair.first, valuePair.second);
		if (FAILED(readyShaderValues(valuePairs...)))
			return E_FAIL;
		return S_OK;
	}
private:
	HRESULT setShaderValuesAll();
private:
	LPDIRECT3DTEXTURE9 originalTexture_;
	LPDIRECT3DSURFACE9 originalSurface_;
	LPDIRECT3DSURFACE9 screenSurface_;
	LPDIRECT3DVERTEXBUFFER9 buffer_;
	LPD3DXEFFECT shader_;

	LPDIRECT3DDEVICE9 d3dDevice_;

	map<const char*, variant<bool, int, float, double, _vec2, _vec3, _mat>> mapShaderValues_;
};

