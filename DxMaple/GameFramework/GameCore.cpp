#include "stdafx.h"
#include "GameCore.h"

#include "TestScene.h"
#include "Wooseok.h"
#include "Gyeongbeen.h"
#include "Room1.h"
#include "Room2.h"
#include "Room3.h"
#include "Room4.h"
#include "Room5.h"
#include "BossRoom.h"
#include "ExcelLoader.h"
GameCore::GameCore()
{
}


GameCore::~GameCore()
{
	release();
}

HRESULT GameCore::initialize(HWND hWnd)
{

	ExcelLoader::initialize();

	deviceManager_ = DeviceManager::getInstance();
	ASSERT_MESSAGE_RETURN(nullptr != deviceManager_, "device manager is nullptr", E_FAIL);

	entityManager_ = EntityManager::getInstance();
	ASSERT_MESSAGE_RETURN(nullptr != entityManager_, "entity manager is nullptr", E_FAIL);

	inputManager_ = InputManager::getInstance();
	ASSERT_MESSAGE_RETURN(nullptr != inputManager_, "input manager is nullptr", E_FAIL);

	timeManager_ = TimeManager::getInstance();
	ASSERT_MESSAGE_RETURN(nullptr != timeManager_, "time manager is nullptr", E_FAIL);

	sceneManager_ = SceneManager::getInstance();
	ASSERT_MESSAGE_RETURN(nullptr != sceneManager_, "scene manager is nullptr", E_FAIL);

	gameManager_ = GameManager::getInstance();
	ASSERT_MESSAGE_RETURN(nullptr != gameManager_, "Game manager is nullptr", E_FAIL);

	

	//고정 프레임 데이터 삽입
	if (FAILED(timeManager_->insertTargetFrame(L"30FPS", 30.f)))
		return E_FAIL;
	if(FAILED(timeManager_->insertTargetFrame(L"60FPS", 60.f)))
		return E_FAIL;
	if (FAILED(timeManager_->insertTargetFrame(L"120FPS", 120.f)))
		return E_FAIL;
	
	//고정 프레임 세팅
	timeManager_->setTargetFrame(L"60FPS");

	//장치 초기화
	ASSERT_MESSAGE_RETURN(SUCCEEDED(deviceManager_->initialize(hWnd,true,SCREEN_WIDTH,SCREEN_HEIGHT)), "device manager intializing failed", E_FAIL);

	inputManager_->initialize(hWnd,SCREEN_WIDTH,SCREEN_HEIGHT);
	//deviceManager_->setViewSpace(_vec3(0.f, 0.f, -1.f), _vec3(0.f, 0.f, 0.f), _vec3(0.f, 1.f, 0.f));
	//deviceManager_->setOrthoProjectionSpace(SCREEN_WIDTH, SCREEN_HEIGHT, 0.1f, 100.f);

	//렌더타깃 셰이더 세팅
	deviceManager_->setRendertargetShader(L"../ShaderFiles/screenShader.fx");

	//리소스 생성 및 보관
	deviceManager_->createBuffer(L"DebugBuffer", 1, 1); //디버깅용 버퍼
	deviceManager_->createShader(L"DebugShader", L"../ShaderFiles/DebugShader.fx"); //디버깅용 셰이더


	//deviceManager_->createBuffer(L"AtlasBuffer", 1, 1); //디버깅용 버퍼
	//deviceManager_->createShader(L"myLightShader", L"../ShaderFiles/myLightShader.fx"); //빛 셰이더


	deviceManager_->createBuffer(L"AtlasBuffer", 1, 1);
	deviceManager_->createShader(L"AtlasShader", L"../ShaderFiles/AtlasShader.fx");
	deviceManager_->createShader(L"TextureShader", L"../ShaderFiles/TextureShader.fx");
	deviceManager_->createShader(L"StatusShader", L"../ShaderFiles/StatusShader.fx");
	
	//씬 생성 및 보관

	
	sceneManager_->insertScene(L"Room5", new Room5);
	sceneManager_->changeScene(L"Room5");
	
	return S_OK;
}

void GameCore::release()
{
	//networkManager_->destroyInstance();
	gameManager_->destroyInstance();
	sceneManager_->destroyInstance();
	entityManager_->destroyInstance(); 

	inputManager_->destroyInstance();
	deviceManager_->destroyInstance();
}


bool GameCore::update()
{
	if (gameOver)
		return false;
	//타임매니저 갱신
	
	return true;
}

bool GameCore::executeLogic()
{
	if (gameOver)
		return false;

	
	
	timeManager_->update();
	inputManager_->readKeyboard();

	inputManager_->readMouse();

	inputManager_->processInput();


	//씬 업데이트
	sceneManager_->update();

	sceneManager_->lateUpdate();

	{
		lock_guard<mutex> lock(gameCoreLock_);
		sceneManager_->refresh(); //active 상태 아닌 entity들 빼주기


	}

	//게임종료키: esc
	if (inputManager_->keyDown(DIK_ESCAPE))
		gameOver = true;
	//Sleep(1);
	//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	return true;
}

bool GameCore::render()
{
	//렌더
	if (gameOver)
		return false;

	if (timeManager_->isTargetFrame()) //프레임 체크
	{
		deviceManager_->renderBegin(D3DXCOLOR(0.f, 0.f, 0.f, 255.f));
		{
			lock_guard<mutex> lock(gameCoreLock_);
			sceneManager_->render();
		}
		deviceManager_->renderEnd(D3DXCOLOR(0.f, 0.f, 0.f, 255.f));
	}
	
	return true;
}
