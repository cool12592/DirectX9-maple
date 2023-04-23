#include "stdafx.h"
#include "RenderTarget.h"

RenderTarget::RenderTarget(LPDIRECT3DDEVICE9 device):d3dDevice_(device),originalTexture_(nullptr),originalSurface_(nullptr),screenSurface_(nullptr),buffer_(nullptr),shader_(nullptr)
{
}

RenderTarget::~RenderTarget()
{
	release();
}

HRESULT RenderTarget::initialize(const wchar_t* shaderPath)
{
	//서피스,텍스쳐 설정
	D3DVIEWPORT9 viewport;
	d3dDevice_->GetViewport(&viewport);
	if (FAILED(d3dDevice_->CreateTexture(
		viewport.Width, viewport.Height, 1, D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &originalTexture_, NULL)))
		return E_FAIL;
	if (FAILED(originalTexture_->GetSurfaceLevel(0, &originalSurface_)))
		return E_FAIL;

	//셰이더 생성
	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;
#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
	D3DXCreateEffectFromFile(d3dDevice_, shaderPath,
		NULL, NULL, dwShaderFlags, NULL, &shader_, &pError);

	//버텍스 설정
	SCREENVERTEX vertices[] =
	{
			{0.f, 0.f , 0.1f, 1.0f, 0.0f, 0.0f},
			{ (float)viewport.Width, 0.f, 0.1f, 1.0f, 1.0f, 0.0f},
			{0.f, (float)viewport.Height, 0.1f, 1.0f, 0.0f, 1.0f},
			{ (float)viewport.Width, (float)viewport.Height, 0.1f, 1.0f, 1.0f, 1.0f}
	};


	if (FAILED(d3dDevice_->CreateVertexBuffer(4 * sizeof(SCREENVERTEX),
		0, D3DFVF_SCREENVERTEX, D3DPOOL_DEFAULT, &buffer_, NULL)))
		return E_FAIL;

	void* pVertices;
	if (FAILED(buffer_->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	buffer_->Unlock();
	return S_OK;
}

void RenderTarget::release()
{
	safeRelease(originalSurface_);
	safeRelease(originalTexture_);
	safeRelease(screenSurface_);
	safeRelease(buffer_);
	safeRelease(shader_);

}

HRESULT RenderTarget::changeTargetForObjects()
{
	ASSERT_MESSAGE_RETURN(nullptr != originalSurface_, "original surface is nullptr", E_FAIL);
	d3dDevice_->GetRenderTarget(0, &screenSurface_);
	d3dDevice_->SetRenderTarget(0, originalSurface_);
	return S_OK;
}

HRESULT RenderTarget::renderSurface(const D3DXCOLOR& clearColor)
{
	ASSERT_MESSAGE_RETURN(nullptr != shader_, "shader is nullptr", E_FAIL);

	d3dDevice_->SetRenderTarget(0, screenSurface_);
	screenSurface_->Release();

	d3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, clearColor, 1.0f, 0);
	d3dDevice_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	d3dDevice_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);


	d3dDevice_->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	d3dDevice_->SetFVF(D3DFVF_SCREENVERTEX);

	d3dDevice_->SetStreamSource(0, buffer_, 0, sizeof(SCREENVERTEX));

	UINT numPasses;
	shader_->Begin(&numPasses, NULL);
	{
		shader_->BeginPass(0);
		{
			setShaderValuesAll();
			d3dDevice_->SetTexture(0, originalTexture_);
			d3dDevice_->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		}
		shader_->EndPass();
	}
	shader_->End();
	return S_OK;
}




HRESULT RenderTarget::setShaderValuesAll()
{
	ASSERT_MESSAGE_RETURN(nullptr!=shader_, "shader is nullptr", E_FAIL);
	
	for (auto& var : mapShaderValues_)
	{
		visit([&](auto&& value) {
			if (typeid(decltype(value)) == typeid(bool))
				shader_->SetBool(var.first, (bool)value);
			else
				shader_->SetValue(var.first,&value,sizeof(value));
			}, var.second);
	}

	mapShaderValues_.clear();//컨테이너 비우기
	return S_OK;
}
