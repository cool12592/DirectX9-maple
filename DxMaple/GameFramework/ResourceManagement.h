#pragma once
#include "Resources.h"
#include <memory>
class ResourceManagement
{
public:
	explicit ResourceManagement();
	~ResourceManagement();
public:
	HRESULT createBuffer(LPDIRECT3DDEVICE9 d3dDevice,wstring& bufferName,int width,int height);
	HRESULT createShader(LPDIRECT3DDEVICE9 d3dDevice, wstring& shaderName, const wchar_t* filePath);
	HRESULT createTexture(LPDIRECT3DDEVICE9 d3dDevice, wstring& textureName, const wchar_t* filePath);

	shared_ptr<Resources>& getResource(wstring& resourceName);
	bool isExist(wstring& resourceName);
private:
	map<wstring, shared_ptr<Resources>> mapResources;
};