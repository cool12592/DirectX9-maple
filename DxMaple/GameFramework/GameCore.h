#pragma once
#include "EntityManager.h"
#include "DeviceManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "GameManager.h"

class GameCore
{
public:
	explicit GameCore();
	~GameCore();

	HRESULT initialize(HWND hWnd);
	void release();

	bool networkUpdate();
	bool update();
	bool executeLogic();
	bool render();
private:
	EntityManager*	entityManager_;
	DeviceManager*	deviceManager_;
	InputManager*	inputManager_;
	TimeManager*	timeManager_;
	SceneManager*	sceneManager_;
	GameManager*     gameManager_;
	NetworkManager* networkManager_;
	mutex gameCoreLock_;
};

