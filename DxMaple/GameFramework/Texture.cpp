#include "stdafx.h"
#include "Texture.h"

Texture::Texture(LPDIRECT3DDEVICE9 device):Resources(device), texture_(nullptr)
{
}

Texture::~Texture()
{
	release();
}

HRESULT Texture::initialize(const wchar_t* filePath)
{
	if (FAILED(D3DXCreateTextureFromFile(d3dDevice_, filePath, &texture_)))
		return E_FAIL;
	if (FAILED(D3DXGetImageInfoFromFile(filePath, &imgInfo_)))
		return E_FAIL;
	return S_OK;
}

void Texture::release()
{
	safeRelease(texture_);
}

LPDIRECT3DTEXTURE9 Texture::getTexture()
{
#ifdef _DEBUG
	ASSERT_MESSAGE(nullptr != texture_, "texture is nullptr");
#endif
	return texture_;
}

D3DXIMAGE_INFO& Texture::getImgInfo()
{
	// TODO: 여기에 return 문을 삽입합니다.
	return imgInfo_;
}

void Texture::render()
{
}
