#pragma once
#include "ECS.h"
#include "MonoBehaviour.h"
#include "UIState.h"
#include "DXFont.h"
//하위로 빌더패턴을 사용할수있음. (상위 클래스 + 추가기능)


/*/ these classes are has all same parent = UIComponent /*/ 

/*/ Window = 2D image /*/  //ok
/*/ Button = Window + clickable,  using result + action()/*/ //ok
/*/ text = Button + typing /*/ //ok
/*/ scroll = Button + movable /*/ //ok
/*/ label = Window + font + life always /*/ //ok
/*/ StatusBar = scroll + Auto number calculate /*/ //
/*/ radiobutton = button + OnOff action() /*/ //ok
/*/ dropdown = text or label + list /*/ //ok
/*/ balloon = text + Window + life OnOff /*/ //ok

//로그인(텍스트,버튼),버튼(로그인씬)
//파티원목록 (텍스트리스트) 현재접속인원 파티초대창 파티승낙창 파티상태창(파탈,)

//Layout형태.
class UIComponent :	public MonoBehaviour
{
protected:
	bool click_;
	bool move_;
	bool render_;
	bool live_;
	float time_;
	int moveX_;
	int moveY_;
	float screenWidth_, screenHeight_;

public:
	virtual void initialize();
	virtual void update();
	virtual void lateUpdate();
	virtual void render();
	virtual void release();
public:
	virtual bool OnMouse() { return true; };
	virtual bool OnClick() { return true; };
	virtual bool OnIdle() { return true; };
	virtual bool OnMove() { return true; };
	virtual void commandInput(int x, int y) {};
public:
	virtual void mouseOn() {};
	virtual void mouseClick() {};
	//virtual void setOpt(unordered_map<string,bool> optOn) {};
	virtual void setFont(string fontName, int fontSize, int x, int y, wstring text, D3DXCOLOR col);


public:
	UIComponent();
	virtual ~UIComponent();
};

