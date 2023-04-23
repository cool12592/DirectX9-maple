#pragma once
#include "ECS.h"
//#include "MonoBehaviour.h"
#include "DeviceManager.h"
struct DXScript
{
	wstring str;
	RECT rt; 
	D3DXCOLOR col;
	int size;
	LPD3DXFONT font;
};
class DXFont : public Component  // : public MonoBehaviour
{
private:
	//map<int, DXScript*> Script_Map;
	static int ScriptNum;
	LPDIRECT3DDEVICE9	device_;
	DXScript* script;

public:
	void initialize();
	void update() {};
	virtual void lateUpdate() {};
	void render();
	void SetScript(const char* FontName, int fontSize, int FontOption, RECT rt, LPCWSTR str, D3DXCOLOR color);
	void SetScript( int fontSize, RECT rt, LPCWSTR str, D3DXCOLOR color);
	virtual void release();
	void setStr(LPCWSTR tempstr) 
	{
		if (script != nullptr)
			script->str = tempstr;
	}
public:
	DXFont() {};
	DXFont(const char* FontName, int fontSize, int FontOption, RECT rt, LPCWSTR str, D3DXCOLOR color) { SetScript(FontName, fontSize, FontOption, rt, str, color); } //rt´Â È­¸éÁÂÇ¥.
	virtual ~DXFont() {};

};

