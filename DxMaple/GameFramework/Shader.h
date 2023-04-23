#pragma once
#include "Resources.h"
#include "Buffer.h"
using namespace std;
class Shader :
	public Resources
{
public:
	Shader(LPDIRECT3DDEVICE9 device);
	virtual ~Shader();

	HRESULT initialize(const wchar_t* filePath);

	//인자 이름, 인자 pair
	HRESULT setValues()
	{
		return S_OK;
	}
	template<typename ValuePair>
	HRESULT setValues(ValuePair& valuePair)
	{
		if (typeid(decltype(valuePair.second)) == typeid(bool))
			shader_->SetBool(valuePair.first, (bool)valuePair.second);
		else
			ASSERT_MESSAGE_RETURN(SUCCEEDED(shader_->SetValue(valuePair.first, &valuePair.second, sizeof(decltype(valuePair.second)))), "setValue failed", E_FAIL);
		return S_OK;
	}
	
	template<typename ValuePair,typename... ValuePairs>
	HRESULT setValues(ValuePair valuePair,ValuePairs... valuePairs)
	{
		if (typeid(decltype(valuePair.second)) == typeid(bool))
			shader_->SetBool(valuePair.first, (bool)valuePair.second);
		else
			ASSERT_MESSAGE_RETURN(SUCCEEDED(shader_->SetValue(valuePair.first, &valuePair.second, sizeof(decltype(valuePair.second)))), "setValue failed", E_FAIL);
		if (FAILED(setValues(valuePairs...)))
			return E_FAIL;
		return S_OK;
	}
	
	HRESULT setTexture(const char* variableName, LPDIRECT3DTEXTURE9 texture);
	virtual void render() {}
	HRESULT begin(UINT* passNum,DWORD flags);
	HRESULT beginPass(UINT passNum);
	HRESULT endPass();
	HRESULT end();

private:
	LPD3DXEFFECT shader_;
};

