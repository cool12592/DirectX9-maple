#include "stdafx.h"
#include "ResourceManagement.h"

#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
ResourceManagement::ResourceManagement()
{
}


ResourceManagement::~ResourceManagement()
{
}

HRESULT ResourceManagement::createBuffer(LPDIRECT3DDEVICE9 d3dDevice, wstring& bufferName, int width, int height)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(d3dDevice != nullptr, "device is nullptr",E_FAIL);

	auto& find_iter = mapResources.find(bufferName);
	ASSERT_MESSAGE_RETURN(find_iter == mapResources.end(), "resource name exists already",E_FAIL);
#endif

	shared_ptr<Buffer> newBuffer = make_shared<Buffer>(d3dDevice);

	if (FAILED(newBuffer->initialize(CUSTOMVERTEX(), CUSTOMINDEX(), D3DFVF_CUSTOMVERTEX, D3DFMT_INDEX16, width, height)))
		return E_FAIL;
	mapResources.emplace(bufferName, move(newBuffer));
	return S_OK;
}

HRESULT ResourceManagement::createShader(LPDIRECT3DDEVICE9 d3dDevice, wstring & shaderName, const wchar_t * filePath)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(d3dDevice != nullptr, "device is nullptr", E_FAIL);

	auto& find_iter = mapResources.find(shaderName);
	ASSERT_MESSAGE_RETURN(find_iter == mapResources.end(), "resource name exists already", E_FAIL);
#endif
	shared_ptr<Shader> newShader = make_shared<Shader>(d3dDevice);

	if (FAILED(newShader->initialize(filePath)))
		return E_FAIL;
	mapResources.emplace(shaderName, move(newShader));
	return S_OK;
}

HRESULT ResourceManagement::createTexture(LPDIRECT3DDEVICE9 d3dDevice, wstring& textureName, const wchar_t* filePath)
{
#ifdef _DEBUG
	ASSERT_MESSAGE_RETURN(d3dDevice != nullptr, "device is nullptr", E_FAIL);

	auto& find_iter = mapResources.find(textureName);
	ASSERT_MESSAGE_RETURN(find_iter == mapResources.end(), "resource name exists already", E_FAIL);
#endif
	shared_ptr<Texture> newTexture = make_shared<Texture>(d3dDevice);

	if (FAILED(newTexture->initialize(filePath)))
		return E_FAIL;
	mapResources.emplace(textureName, move(newTexture));
	return S_OK;
}

shared_ptr<Resources>& ResourceManagement::getResource(wstring & resourceName)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	auto& find_iter = mapResources.find(resourceName);
	ASSERT_MESSAGE(mapResources.end() != find_iter, "resource does not exist");

	return find_iter->second;
}

bool ResourceManagement::isExist(wstring& resourceName)
{
	auto& find_iter = mapResources.find(resourceName);
	if (mapResources.end() == find_iter)
		return false;
	return true;
}
