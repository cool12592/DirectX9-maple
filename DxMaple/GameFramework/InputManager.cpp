#include "stdafx.h"
#include "InputManager.h"
#include "TimeManager.h"
IMPLEMENT_SINGLETON(InputManager)
InputManager::InputManager()
{
}


InputManager::~InputManager()
{
	release();
}

HRESULT InputManager::initialize(HWND hWnd, int screenWidth, int screenHeight)
{
	hWnd_ = hWnd;
	ShowCursor(false);
	// Directinput8를 생성합니다.
	ASSERT_MESSAGE_RETURN(SUCCEEDED(DirectInput8Create(GetModuleHandle(0), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput_, nullptr)), "Create Direct input failed", E_FAIL);

	//키보드 생성
	if (FAILED(directInput_->CreateDevice(GUID_SysKeyboard, &keyboard_, nullptr)))
		return E_FAIL;	
	if (FAILED(keyboard_->SetDataFormat(&c_dfDIKeyboard))) 
		return E_FAIL;
	if (FAILED(keyboard_->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE)))
		return E_FAIL;
	if (FAILED(keyboard_->Acquire()))
		return E_FAIL;
	

	//마우스 생성
	if (FAILED(directInput_->CreateDevice(GUID_SysMouse, &mouse_, nullptr)))
		return E_FAIL;
	if (FAILED(mouse_->SetDataFormat(&c_dfDIMouse))) 
		return E_FAIL;
	if (FAILED(mouse_->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
		return E_FAIL;
	if (FAILED(mouse_->Acquire()))
		return E_FAIL;

	screenWidth_ = screenWidth;
	screenHeight_ = screenHeight;
	return S_OK;
}

void InputManager::release()
{
	if (nullptr != keyboard_)
		keyboard_->Unacquire();
	safeRelease(keyboard_);

	if (nullptr != mouse_)
		mouse_->Unacquire();
	safeRelease(mouse_);

	safeRelease(directInput_);
}

bool InputManager::keyDown(BYTE keyCode)
{
	if (keyboardState_[keyCode] && !prevKeyboardState_[keyCode])
	{
		keyboardQueue_.push_back(keyCode);
		return true;
	}

	return false;
}

bool InputManager::keyPressing(BYTE keyCode)
{
	return (keyboardState_[keyCode] & 0x80) ? true : false;
}

bool InputManager::keyUp(BYTE keyCode)
{
	return (!keyboardState_[keyCode] && prevKeyboardState_[keyCode]) ? true : false;
}

bool InputManager::commandCheck(bool isRight, const vector<int>& keyCodes)
{
	bool checkOn = false;
	size_t checkCount = 0;
	size_t commandCount = keyCodes.size();
	

	for (auto& queueIter = keyboardQueue_.begin(); queueIter != keyboardQueue_.end(); ++queueIter)
	{
		int checkKeyCode = keyCodes[checkCount];
		if (!isRight)
		{
			if (checkKeyCode == DIK_RIGHT)
				checkKeyCode = DIK_LEFT;
			else if (checkKeyCode == DIK_LEFT)
				checkKeyCode = DIK_RIGHT;
		}
		if (!checkOn)
		{
			if (*queueIter == checkKeyCode)
			{
				checkOn = true;
				checkCount++;
				if (checkCount == commandCount)
					return true;
			}
		}
		else
		{
			if (*queueIter == checkKeyCode)
			{
				checkCount++;
				if (checkCount == commandCount)
					return true;
			}
			else
			{
				checkOn = false;
				checkCount = 0;
			}
		}
	}

	return false;
}

bool InputManager::mouseDown(MOUSEBUTTONTYPE buttonType)
{
	return (mouseState_.rgbButtons[static_cast<int>(buttonType)] && !prevMouseState_.rgbButtons[static_cast<int>(buttonType)]) ? true : false;
}

bool InputManager::mousePressing(MOUSEBUTTONTYPE buttonType)
{
	return (mouseState_.rgbButtons[static_cast<int>(buttonType)] & 0x80) ? true : false;
}

bool InputManager::mouseUp(MOUSEBUTTONTYPE buttonType)
{
	return (!mouseState_.rgbButtons[static_cast<int>(buttonType)] && prevMouseState_.rgbButtons[static_cast<int>(buttonType)]) ? true : false;
}


void InputManager::setScreen(const int & screenWidth, const int & screenHeight)
{
	screenWidth_ = screenWidth;
	screenHeight_ = screenHeight;
}

void InputManager::getMousePosition(OUT int & mousePositionX, OUT int & mousePositionY)
{
	mousePositionX = mouseX_;
	mousePositionY = mouseY_;
}

HRESULT InputManager::readKeyboard()
{
	memcpy(prevKeyboardState_, keyboardState_, sizeof(unsigned char) * MAX_KEY_COUNT);

	//키보드 큐 꽉차면 하나뺌
	
	
	if (keyboardQueue_.size() > MAX_KEYBOARD_QUEUESIZE)
		keyboardQueue_.pop_front();

	
	if (!keyboardQueue_.empty())
	{
		if (keyboardQueueTimer_ > KEYBOARD_QUEUE_POP_TIMER)
		{
			keyboardQueue_.pop_front();
			keyboardQueueTimer_ = 0.f;
		}
		keyboardQueueTimer_ += TimeManager::getInstance()->getDeltaTime();
	}
	

	HRESULT result;

	result = keyboard_->GetDeviceState(sizeof(keyboardState_), (LPVOID)&keyboardState_);
	if (FAILED(result)) 
	{ 
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			keyboard_->Acquire();
		else
			return E_FAIL;
	}
	
	return S_OK;
}

HRESULT InputManager::readMouse()
{
	memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));

	HRESULT result;

	result = mouse_->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState_);
	if (FAILED(result))
	{
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
			mouse_->Acquire();
		else
			return E_FAIL;
		
	}

	return S_OK;
}

void InputManager::processInput()
{
	/*mouseX_ += mouseState_.lX;
	mouseY_ += mouseState_.lY;
	if (mouseX_ < 0)
		mouseX_ = 0;
	else if (mouseX_ > screenWidth_)
		mouseX_ = screenWidth_;

	if (mouseY_ < 0)
		mouseY_ = 0;
	else if (mouseY_ > screenHeight_)
		mouseY_ = screenHeight_;*/
	POINT mousePt;
	GetCursorPos(&mousePt);
	ScreenToClient(hWnd_, &mousePt);
	mouseX_ = mousePt.x;
	mouseY_ = mousePt.y;
}
