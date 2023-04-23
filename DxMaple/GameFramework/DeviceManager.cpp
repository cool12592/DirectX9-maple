#include "stdafx.h"
#include "DeviceManager.h"

#include "Functor.h"
IMPLEMENT_SINGLETON(DeviceManager)
DeviceManager::DeviceManager():d3d_(nullptr),d3dDevice_(nullptr),renderTarget_(nullptr)
{
}


DeviceManager::~DeviceManager()
{
	release();
}

HRESULT DeviceManager::initialize(HWND hWnd, bool isWindowed, int screenWidth, int screenHeight)
{
	if (nullptr == (d3d_ = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	isWindowed_ = isWindowed;
	screenWidth_ = (float)screenWidth;
	screenHeight_= (float)screenHeight;
	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = isWindowed_;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;



	// Create the D3DDevice
	if (FAILED(d3d_->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &d3dDevice_)))
		return E_FAIL;

	hWnd_ = hWnd;
	
	setViewport(screenWidth, screenHeight);

	resourceManagement_ = make_unique<ResourceManagement>();

	return S_OK;
}

HRESULT DeviceManager::setRendertargetShader(const wchar_t* shaderPath)
{
	renderTarget_ = make_unique<RenderTarget>(d3dDevice_);
	if (FAILED(renderTarget_->initialize(shaderPath)))
	{
		renderTarget_.reset();
		return E_FAIL;
	}
	return S_OK;
}

void DeviceManager::release()
{
	resourceManagement_.reset();
	renderTarget_.reset();
	safeRelease(d3dDevice_);
	safeRelease(d3d_);
}

HRESULT DeviceManager::renderBegin(const D3DXCOLOR& clearColor)
{
	ASSERT_MESSAGE(d3d_ != nullptr, "d3d COM isn't created");
	ASSERT_MESSAGE(d3dDevice_ != nullptr, "Device isn't created");

	if (nullptr != renderTarget_)
		renderTarget_->changeTargetForObjects();
	

	d3dDevice_->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	d3dDevice_->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	d3dDevice_->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	d3dDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	d3dDevice_->SetRenderState(D3DRS_LIGHTING, FALSE);
	d3dDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	

	if (FAILED(d3dDevice_->Clear(0, NULL, D3DCLEAR_TARGET, clearColor, 1.f, 0)))
		return E_FAIL;
	if (FAILED(d3dDevice_->BeginScene()))
		return E_FAIL;
	return S_OK;
}


HRESULT DeviceManager::renderEnd(const D3DXCOLOR& targetClearColor)
{
	if (nullptr != renderTarget_)
		renderTarget_->renderSurface(targetClearColor);

	if (FAILED(d3dDevice_->EndScene()))
		return E_FAIL;
	if (FAILED(d3dDevice_->Present(nullptr, nullptr, nullptr, nullptr)))
		return E_FAIL;
	return S_OK;
}

HRESULT DeviceManager::setWorldSpace(const _vec3 & position, const _vec3 & rotation, const _vec3 scale)
{
	D3DXMATRIXA16  matWorld, matTranslate, matRotation, matScale;

	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matRotation);
	D3DXMatrixIdentity(&matScale);


	D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&matTranslate, position.x, position.y, position.z);
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	matWorld = matScale * matRotation*matTranslate;

	ASSERT_MESSAGE_RETURN(SUCCEEDED(d3dDevice_->SetTransform(D3DTS_WORLD, &matWorld)), "world space setting failed", E_FAIL);
	return S_OK;
}

HRESULT DeviceManager::setViewSpace(const _vec3 & eye, const _vec3 & at, const _vec3 & up)
{
	_mat matView;
	D3DXMatrixLookAtLH(&matView, &eye, &at, &up);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(d3dDevice_->SetTransform(D3DTS_VIEW, &matView)),"View space setting failed",E_FAIL);
	return S_OK;
}

HRESULT DeviceManager::setOrthoProjectionSpace(const float & screenWidth, const float & screenHeight, const float & nearPlane, const float & farPlane)
{
	D3DXMATRIXA16 matProj;
	D3DXMatrixOrthoLH(&matProj, screenWidth, screenHeight, nearPlane, farPlane);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(d3dDevice_->SetTransform(D3DTS_PROJECTION, &matProj)), "projection space setting failed", E_FAIL);
	return S_OK;
}

HRESULT DeviceManager::setPerpectiveProjectionSpace(const float & fovy, const float & aspect, const float & nearPlane, const float & farPlane)
{
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, fovy, aspect, nearPlane, farPlane);
	ASSERT_MESSAGE_RETURN(SUCCEEDED(d3dDevice_->SetTransform(D3DTS_PROJECTION, &matProj)), "projection space setting failed", E_FAIL);
	return S_OK;
}

HRESULT DeviceManager::setViewport(const int& screenWidth, const int& screenHeight)
{
	if (nullptr == d3dDevice_)
		return E_FAIL;
	D3DVIEWPORT9 viewport;
	d3dDevice_->GetViewport(&viewport);

	viewport.Width = screenWidth;
	viewport.Height = screenHeight;
	screenWidth_ = (float)screenWidth;
	screenHeight_ = (float)screenHeight;
	d3dDevice_->SetViewport(&viewport);
	return S_OK;
}

HRESULT DeviceManager::setLight(bool isLight)
{
	if (FAILED(d3dDevice_->SetRenderState(D3DRS_LIGHTING, isLight)))
		return E_FAIL;
	return S_OK;
}

HRESULT DeviceManager::setCullmode(DWORD cullmode)
{
	if (FAILED(d3dDevice_->SetRenderState(D3DRS_CULLMODE, cullmode)))
		return E_FAIL;
	return S_OK;
}

HRESULT DeviceManager::createBuffer(wstring bufferName, int width, int height)
{
	if (FAILED(resourceManagement_->createBuffer(d3dDevice_, bufferName, width, height)))
		return E_FAIL;
	return S_OK;
}

HRESULT DeviceManager::createShader(wstring shaderName, const wchar_t * filePath)
{
	if (FAILED(resourceManagement_->createShader(d3dDevice_, shaderName, filePath)))
		return E_FAIL;
	return S_OK;
}

HRESULT DeviceManager::createTexture(wstring textureName, const wchar_t* filePath)
{
	if (FAILED(resourceManagement_->createTexture(d3dDevice_, textureName, filePath)))
		return E_FAIL;
	return S_OK;
}

shared_ptr<Resources>& DeviceManager::getResources(wstring resourceName)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return resourceManagement_->getResource(resourceName);

}

bool DeviceManager::isExistResource(wstring resourceName)
{
	return resourceManagement_->isExist(resourceName);
}
