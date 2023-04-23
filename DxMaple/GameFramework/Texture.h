#pragma once
#include "Resources.h"
class Texture
	: public Resources
{
public:
	explicit Texture(LPDIRECT3DDEVICE9 device);
	virtual ~Texture();

	HRESULT initialize(const wchar_t* filePath);
	void release();

	LPDIRECT3DTEXTURE9 getTexture();
	D3DXIMAGE_INFO& getImgInfo();

	// Resources¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void render() override; //æ» æ∏
private:
	LPDIRECT3DTEXTURE9 texture_;
	D3DXIMAGE_INFO imgInfo_;
};

