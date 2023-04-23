#include "stdafx.h"
#include "Shader.h"


Shader::Shader(LPDIRECT3DDEVICE9 device) :Resources(device),shader_(nullptr)
{
}


Shader::~Shader()
{
	safeRelease(shader_);
}

HRESULT Shader::initialize(const wchar_t * filePath)
{

	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	ASSERT_MESSAGE_RETURN(SUCCEEDED(D3DXCreateEffectFromFile(d3dDevice_, filePath,
		nullptr, nullptr, dwShaderFlags, nullptr, &shader_, nullptr)),"create shader failed",E_FAIL);

	return S_OK;
}

HRESULT Shader::setTexture(const char * variableName, LPDIRECT3DTEXTURE9 texture)
{
	ASSERT_MESSAGE_RETURN(SUCCEEDED(shader_->SetTexture(variableName, texture)), "texture setting failed", E_FAIL);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(shader_->CommitChanges()), "commitchanges failed", E_FAIL);

	return S_OK;
}

HRESULT Shader::begin(UINT * passNum, DWORD flags)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(nullptr != shader_, "D3DXEFFECT is nullptr", E_FAIL);
#endif
	if (FAILED(shader_->Begin(passNum, flags)))
		return E_FAIL;
	return S_OK;
}

HRESULT Shader::beginPass(UINT passNum)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(nullptr != shader_, "D3DXEFFECT is nullptr", E_FAIL);
#endif
	if (FAILED(shader_->BeginPass(passNum)))
		return E_FAIL;
	return S_OK;
}

HRESULT Shader::endPass()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(nullptr != shader_, "D3DXEFFECT is nullptr", E_FAIL);
#endif
	if (FAILED(shader_->EndPass()))
		return E_FAIL;
	return S_OK;
}

HRESULT Shader::end()
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(nullptr != shader_, "D3DXEFFECT is nullptr", E_FAIL);
#endif
	if (FAILED(shader_->End()))
		return E_FAIL;
	return S_OK;
}
