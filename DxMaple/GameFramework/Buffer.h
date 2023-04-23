#pragma once
#include "Resources.h"
#include "AtlasLoader.h"
class Buffer :
	public Resources
{
public:
	explicit Buffer(LPDIRECT3DDEVICE9 device);
	virtual ~Buffer();

	template<typename T,typename U>
	HRESULT initialize(T vertexType, U indexType, DWORD vertexFormat,D3DFORMAT indexFormat,int width,int height);
	
	HRESULT release();
	// Resources을(를) 통해 상속됨
	virtual void render() override;

//public:
//	template<typename T>
//	HRESULT setAtlasUV(T vertexType, const Atlas::ATLASINFO& atlasInfo, int atlasIndex);//임시적으로 사용하는 함수. 나중에 쉐이더로 처리할듯
private:
	LPDIRECT3DVERTEXBUFFER9		vertexBuffer_;
	LPDIRECT3DINDEXBUFFER9		indexBuffer_;
	UINT						vertexSize_;
	UINT						indexSize_;
	DWORD						vertexFormat_;
	D3DFORMAT					indexFormat_;
	int							width_, height_;
	int							vertexCount_, triangleCount_;

	
};

template<typename T,typename U>
inline HRESULT Buffer::initialize(T vertexType, U indexType, DWORD vertexFormat, D3DFORMAT indexFormat, int width, int height)
{

	ASSERT_MESSAGE(d3dDevice_ != nullptr, "device is not created");
	//vertex,index 타입 제대로 됐는지 판단을 아직 못함..

	width_ = width;
	height_ = height;
	vertexFormat_ = vertexFormat;
	indexFormat_ = indexFormat;
	vertexCount_ = (width_ + 1)*(height_ + 1);
	triangleCount_ = width_*height_ * 2;
	vertexSize_ = sizeof(decltype(vertexType));

	decltype(vertexType)* vertices = new decltype(vertexType)[vertexCount_];
	ZeroMemory(vertices, vertexSize_*vertexCount_);
	for (int i = 0; i < height_ + 1; ++i)
	{
		for (int j = 0; j < width_ + 1; ++j)
		{
			int index = i*(width_ + 1) + j;
			vertices[index] = { -0.5f+(1.f/width_)*j,0.5f-(1.f/height_)*i,0.f,0xffffffff,(1.f/width_)*j,(1.f/height_)*i };
		}
	}
		
	if (FAILED(d3dDevice_->CreateVertexBuffer(vertexSize_*vertexCount_, 0, vertexFormat, D3DPOOL_DEFAULT, &vertexBuffer_, nullptr)))
	{
		delete[] vertices;
		return E_FAIL;
	}

	void* pVertices;
	if (FAILED(vertexBuffer_->Lock(0, vertexSize_*vertexCount_, (void**)&pVertices, 0)))
	{
		delete[] vertices;
		return E_FAIL;
	}
	memcpy(pVertices, vertices, vertexSize_*vertexCount_);
	vertexBuffer_->Unlock();
	delete[] vertices;


	indexSize_ = sizeof(decltype(indexType));
	decltype(indexType)* indices = new decltype(indexType)[triangleCount_];
	ZeroMemory(indices, indexSize_*triangleCount_);

	for (int i = 0; i < height_; ++i)
	{
		for (int j = 0; j < width_; ++j)
		{
			int index = (i*width_ + j) * 2;
			int indicesIndex = i*(width+1) + j;
			indices[index] = { (WORD)indicesIndex,(WORD)(indicesIndex + 1),(WORD)(indicesIndex + width_ + 1) };
			indices[index + 1] = { (WORD)(indicesIndex +1),(WORD)(indicesIndex +width_+2),(WORD)(indicesIndex + width_ + 1) };

		}
	}

	if (FAILED(d3dDevice_->CreateIndexBuffer(indexSize_*triangleCount_, 0, indexFormat_, D3DPOOL_DEFAULT, &indexBuffer_, nullptr)))
	{
		delete[] indices;
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(indexBuffer_->Lock(0, indexSize_*triangleCount_, (void**)&pIndices, 0)))
	{
		delete[] indices;
		return E_FAIL;
	}
	memcpy(pIndices, indices, indexSize_*triangleCount_);
	indexBuffer_->Unlock();
	delete[] indices;

	return S_OK;
}

//
//template<typename T>
//inline HRESULT Buffer::setAtlasUV(T vertexType, const Atlas::ATLASINFO & atlasInfo, int atlasIndex)
//{
//	ASSERT_MESSAGE_RETURN(nullptr != vertexBuffer_, "vertex buffer is nullptr", E_FAIL);
//	ASSERT_MESSAGE_RETURN(nullptr != indexBuffer_, "index buffer is nullptr", E_FAIL);
//
//	float totalWidth = (float)atlasInfo.meta.size.w;
//	float totalHeight = (float)atlasInfo.meta.size.h;
//
//	const Atlas::FRAMEINFO& frameInfo = atlasInfo.frames[atlasIndex];
//
//	float uWidth, vHeight;
//	float uOffset, vOffset;
//	if (frameInfo.rotated)
//	{
//		uWidth = (float)frameInfo.frame.h / totalWidth;
//		vHeight = (float)frameInfo.frame.w / totalHeight;
//	}
//	else
//	{
//		uWidth = (float)frameInfo.frame.w / totalWidth;
//		vHeight = (float)frameInfo.frame.h / totalHeight;
//	}
//
//
//	uOffset = (float)frameInfo.frame.x / totalWidth;
//	vOffset = (float)frameInfo.frame.y / totalHeight;
//
//
//	decltype(vertexType)* vertices = new decltype(vertexType)[vertexCount_];
//	ZeroMemory(vertices, vertexSize_*vertexCount_);
//	for (int i = 0; i < height_ + 1; ++i)
//	{
//		for (int j = 0; j < width_ + 1; ++j)
//		{
//			int index = i*(width_ + 1) + j;
//			if (frameInfo.rotated)
//				vertices[index] = { -0.5f + (1.f / width_)*j,0.5f - (1.f / height_)*i,0.f,0xffffffff,uOffset + uWidth - uWidth*(1.f / width_)*i,vOffset + vHeight*(1.f / height_)*j };
//			else
//				vertices[index] = { -0.5f + (1.f / width_)*j,0.5f - (1.f / height_)*i,0.f,0xffffffff,uOffset + uWidth*(1.f / width_)*j,vOffset + vHeight*(1.f / height_)*i };
//
//		}
//	}
//	void* pVertices;
//	if (FAILED(vertexBuffer_->Lock(0, vertexSize_*vertexCount_, (void**)&pVertices, 0)))
//	{
//		delete[] vertices;
//		return E_FAIL;
//	}
//	memcpy(pVertices, vertices, vertexSize_*vertexCount_);
//	vertexBuffer_->Unlock();
//	delete[] vertices;
//
//	return S_OK;
//}
