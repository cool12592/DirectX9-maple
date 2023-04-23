#include "stdafx.h"
#include "Buffer.h"


Buffer::Buffer(LPDIRECT3DDEVICE9 device)
	:Resources(device),vertexBuffer_(nullptr),indexBuffer_(nullptr),vertexSize_(0),vertexFormat_(0),indexFormat_(D3DFMT_INDEX16),width_(0),height_(0)
{
}


Buffer::~Buffer()
{
	release();
}



HRESULT Buffer::release()
{
	safeRelease(vertexBuffer_);
	safeRelease(indexBuffer_);
	return S_OK;
}

void Buffer::render()
{
	ASSERT_MESSAGE(SUCCEEDED(d3dDevice_->SetStreamSource(0, vertexBuffer_, 0, vertexSize_)),"failed");
	ASSERT_MESSAGE(SUCCEEDED(d3dDevice_->SetFVF(vertexFormat_)),"failed");
	ASSERT_MESSAGE(SUCCEEDED(d3dDevice_->SetIndices(indexBuffer_)),"failed");

	ASSERT_MESSAGE(SUCCEEDED(d3dDevice_->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount_, 0, triangleCount_)),"failed");
}
