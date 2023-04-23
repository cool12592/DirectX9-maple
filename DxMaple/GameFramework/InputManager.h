#pragma once
#include <dinput.h>
#include "Define.h"
class InputManager
{
	DECLARE_SINGLETON(InputManager)
public:
	enum class MOUSEBUTTONTYPE{LEFT,RIGHT,MIDDLE,TYPE_END};
public:
	explicit InputManager();
	~InputManager();

public:
	HRESULT initialize(HWND hWnd,int screenWidth,int screenHeight);
	void	release();

	//키 누름 관련 함수
	bool	keyDown(BYTE keyCode); //누른 순간
	bool	keyPressing(BYTE keyCode); //누르는 중
	bool	keyUp(BYTE keyCode); //뗏을 때

	bool LastKeyCheck(BYTE keyCode)
	{
		if (keyboardQueue_[keyboardQueue_.size() - 1] == keyCode)
			return true;
		else
			return false;
	}

	bool	commandCheck(bool isRight, const vector<int>& keyCodes);


	bool	commandCheck(bool isRight, deque<BYTE>::iterator iter, int keyCode)
	{
		if (!isRight)
		{
			if (keyCode == DIK_RIGHT)
				keyCode = DIK_LEFT;
			else if (keyCode == DIK_LEFT)
				keyCode = DIK_RIGHT;
		}

		for (; iter != keyboardQueue_.end(); ++iter)
		{
			if (keyCode == *iter)
				return true;
		}
		return false;
	}

	template<typename... Ints>
	bool	commandCheck(bool isRight, deque<BYTE>::iterator iter, int keyCode, Ints... keyCodes)
	{
		if (!isRight)
		{
			if (keyCode == DIK_RIGHT)
				keyCode = DIK_LEFT;
			else if(keyCode == DIK_LEFT)
				keyCode = DIK_RIGHT;
		}

		for (; iter != keyboardQueue_.end(); ++iter)
		{
			if (keyCode == *iter)
			{
				return commandCheck(isRight, iter + 1, keyCodes...);
			}
		}
		return false;
	}

	template<typename... Ints>
	bool	commandCheck(bool isRight, Ints... keyCodes)
	{
		return commandCheck(isRight, keyboardQueue_.begin(), keyCodes...);
	}


	//마우스 버튼 관련 함수
	bool	mouseDown(MOUSEBUTTONTYPE buttonType);
	bool	mousePressing(MOUSEBUTTONTYPE buttonType);
	bool	mouseUp(MOUSEBUTTONTYPE buttonType);

	void	setScreen(const int & screenWidth, const int & screenHeight);
	void	getMousePosition(OUT int& mousePositionX, OUT int& mousePositionY);
public:
	HRESULT readKeyboard();
	HRESULT readMouse();
	void	processInput();
	
private:
	IDirectInput8* directInput_;
	IDirectInputDevice8* keyboard_;
	IDirectInputDevice8* mouse_;


	unsigned char keyboardState_[MAX_KEY_COUNT];
	unsigned char prevKeyboardState_[MAX_KEY_COUNT];

	deque<BYTE> keyboardQueue_;
	float		keyboardQueueTimer_ = 0.f;


	DIMOUSESTATE mouseState_;
	DIMOUSESTATE prevMouseState_;

	int screenWidth_, screenHeight_;
	int mouseX_, mouseY_;
	HWND hWnd_;
};

