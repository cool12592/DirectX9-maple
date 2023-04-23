#pragma once
#include "ResourceManagement.h"
#include "RenderTarget.h"
#include <memory>
class DeviceManager
{
	DECLARE_SINGLETON(DeviceManager)
public:
	explicit DeviceManager();
	~DeviceManager();

public:
	HRESULT initialize(HWND hWnd,bool isWindowed,int screenWidth,int screenHeight);
	HRESULT setRendertargetShader(const wchar_t* shaderPath);
	void release();
public:
	HRESULT renderBegin(const D3DXCOLOR& clearColor);
	HRESULT renderEnd(const D3DXCOLOR& targetClearColor);

public:
	HRESULT setWorldSpace(const _vec3& position, const _vec3& rotation, const _vec3 scale);
	HRESULT setViewSpace(const _vec3& eye, const _vec3& at, const _vec3& up);
	HRESULT setOrthoProjectionSpace(const float& screenWidth, const float& screenHeight, const float& nearPlane, const float& farPlane);
	HRESULT setPerpectiveProjectionSpace(const float& fovy, const float& aspect, const float& nearPlane, const float& farPlane);
	HRESULT setViewport(const int& screenWidth,const int& screenHeight);

	HRESULT setLight(bool isLight);
	HRESULT setCullmode(DWORD cullmode);
	LPDIRECT3DDEVICE9 getDevice()const { return d3dDevice_; }
	void getScreenSize(OUT float& screenWidth, OUT float& screenHeight)
	{
		screenWidth = screenWidth_;
		screenHeight = screenHeight_;
	}
	HWND getHwnd() { return hWnd_; }

	HRESULT createBuffer(wstring bufferName, int width, int height);
	HRESULT createShader(wstring shaderName, const wchar_t* filePath);
	HRESULT createTexture(wstring textureName, const wchar_t* filePath);
	shared_ptr<Resources>& getResources(wstring resourceName); //해당 이름의 리소스를 가져옴
	bool isExistResource(wstring resourceName);

	RenderTarget* getRenderTargetPtr() { return renderTarget_.get(); }
private:
	HWND					hWnd_;
	LPDIRECT3D9				d3d_ = nullptr; 
	LPDIRECT3DDEVICE9		d3dDevice_ = nullptr;
	unique_ptr<ResourceManagement>		resourceManagement_;

	bool isWindowed_;
	float screenWidth_, screenHeight_;

	//화면 셰이더 전용
	unique_ptr<RenderTarget> renderTarget_;
};

