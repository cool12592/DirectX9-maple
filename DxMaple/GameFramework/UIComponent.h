#pragma once
#include "ECS.h"
#include "MonoBehaviour.h"
#include "UIState.h"
#include "DXFont.h"
//������ ���������� ����Ҽ�����. (���� Ŭ���� + �߰����)


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

//�α���(�ؽ�Ʈ,��ư),��ư(�α��ξ�)
//��Ƽ����� (�ؽ�Ʈ����Ʈ) ���������ο� ��Ƽ�ʴ�â ��Ƽ�³�â ��Ƽ����â(��Ż,)

//Layout����.
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

