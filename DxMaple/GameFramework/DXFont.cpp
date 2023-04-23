#include "stdafx.h"
#include "DXFont.h"

int DXFont::ScriptNum = 0;

void DXFont::initialize()
{
	script = new DXScript();
}

void DXFont::render()
{
	//for (auto iter = Script_Map.begin(); iter != Script_Map.end(); iter++)
		//((*iter).second->font)->DrawText(NULL, (*iter).second->str.c_str(), -1, &(*iter).second->rt, DT_LEFT | DT_WORDBREAK, (*iter).second->col); 
	if(script->font!=nullptr)
		script->font->DrawText(NULL, script->str.c_str(), -1, &script->rt, DT_LEFT | DT_WORDBREAK, script->col);
	//script->font->DrawText(NULL, script->str.c_str(), -1, &script->rt, DT_LEFT | DT_CALCRECT , script->col);

}
void DXFont::SetScript(const char* FontName, int fontSize, int FontOption, RECT rt, LPCWSTR str, D3DXCOLOR color)
{
	
	script->rt = rt;
	script->col = color;
	script->str = str;

	LPD3DXFONT font;
	D3DXFONT_DESCW fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESCW));

	fontDesc.CharSet = HANGUL_CHARSET;
	//wprintf(fontDesc.FaceName, FontName);
	fontDesc.Height = fontSize -2;
	fontDesc.Width = fontSize-7;
	fontDesc.Weight = FW_NORMAL;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = 0;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.PitchAndFamily = FF_DONTCARE;
	D3DXCreateFontIndirect(DeviceManager::getInstance()->getDevice(), &fontDesc, &script->font);
	//script->font = font;

	//Script_Map.insert(make_pair(ScriptNum++, script));

}
//void DXFont::SetScript( int fontSize, RECT rt, LPCWSTR str, D3DXCOLOR color=D3DXCOLOR(1,1,1,1))
//{
//
//	script->rt = rt;
//	script->col = color;
//	script->str = str;
//
//	D3DXFONT_DESCW fontDesc;
//	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESCW));
//
//	fontDesc.CharSet = HANGUL_CHARSET;
//	//wprintf(fontDesc.FaceName, FontName);
//	fontDesc.Height = fontSize;
//	fontDesc.Width = fontSize - 2;
//	fontDesc.Weight = FW_NORMAL;
//	fontDesc.Quality = DEFAULT_QUALITY;
//	fontDesc.MipLevels = 1;
//	fontDesc.Italic = 0;
//	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
//	fontDesc.PitchAndFamily = FF_DONTCARE;
//	D3DXCreateFontIndirect(DeviceManager::getInstance()->getDevice(), &fontDesc, &script->font);
//
//
//
//	//script->font = font;
//
//	//Script_Map.insert(make_pair(ScriptNum++, script));
//
//}

void DXFont::release()
{
	//for (auto iter = Script_Map.begin(); iter != Script_Map.end(); iter++)
	//	((*iter).second->font->Release());
	script->font->Release();
}