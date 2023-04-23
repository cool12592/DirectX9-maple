#pragma once
#include "DXFont.h"
#include "UIComponent.h"
class UITextBox : public UIComponent
{
private:
	_vec3 pos_;
	RECT RT_;
	bool On_ = false;
	wstring Str_;
	int StrMax_=8;
	wstring AsterikStr_;
	bool AsterikOn_=false;
	bool CapitalOn_=false;
public:
	wstring getString() { return Str_; }
	UITextBox() {};
	virtual ~UITextBox() {};
	void setTextBox(_vec3 pos, wstring buffer, wstring shader, const wchar_t* texture) {
		_vec3 basicPos = _vec3(0, 0, 0.0f);

		entity->addComponent<Transform>(basicPos, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));

		pos_ = pos;
		entity->addComponent<Sprite>(buffer, shader);
		entity->getComponent<Sprite>().insertTexture(texture);
		entity->getComponent<Sprite>().setAddPos(pos_);
		entity->addComponent<DXFont>();
		entity->addComponent<Ray>();
		D3DXIMAGE_INFO imgInfo = entity->getComponent<Sprite>().getTextureInfo();
		entity->addComponent<BoxCollider>(pos_, _vec3(0.f, 0.f, 0.f), _vec3((float)(imgInfo.Width), (float)(imgInfo.Height), 1.f)); //ID
		//RT_.left = ((-SCREEN_WIDTH) / 2) + pos_.x;
		//RT_.right = RT_.left + imgInfo.Width;
		//RT_.top = ((SCREEN_HEIGHT) / 2) - pos_.y;
		//RT_.bottom = RT_.top + imgInfo.Height;
		RT_.left = (LONG)(((SCREEN_WIDTH)/2)+ entity->getComponent<BoxCollider>().getColliderRect2D().left);
		RT_.right = (LONG)(((SCREEN_WIDTH) / 2)+entity->getComponent<BoxCollider>().getColliderRect2D().right);
		RT_.top = (LONG)(((SCREEN_HEIGHT) / 2)+10+ entity->getComponent<BoxCollider>().getColliderRect2D().bottom);
		RT_.bottom = (LONG)(((SCREEN_HEIGHT) / 2)+10 + entity->getComponent<BoxCollider>().getColliderRect2D().top);

	}
	void setCapitial(bool Capital) { CapitalOn_ = Capital; }
	void setRect(RECT rt) { RT_ = rt; }
	void setPassword(bool bPassword) { AsterikOn_ = bPassword; }
	void setStringMax(int max) { StrMax_ = max; };
	void initialize()
	{
		//entity->getComponent<Sprite>().setAddPos(pos_);
	}

	void update() 
	{
		if (entity->getComponent<Ray>().rayCastCollider2D(entity->getComponent<BoxCollider>().getColliderRect2D()))
		{
			if (InputManager::getInstance()->mouseDown(InputManager::MOUSEBUTTONTYPE::LEFT))
			{
				On_ = true;
			}

		}
		else
		{
			if (InputManager::getInstance()->mouseDown(InputManager::MOUSEBUTTONTYPE::LEFT))
			{
				On_ = false;
			}

		}
		if (InputManager::getInstance()->keyUp(DIK_CAPITAL))
		{
			setCapitial(!CapitalOn_);
		}
		if (entity->getComponent<Ray>().rayCastCollider2D(entity->getComponent<BoxCollider>().getColliderRect2D()))
		{
			if (InputManager::getInstance()->keyUp(DIK_BACKSPACE))
			{
				if (Str_.length() > 0)
					Str_.pop_back();
			}
		}

		if (On_)
		{
			if (Str_.length()< StrMax_)
			{
				if (Input.keyUp(DIK_0))
				{
					Str_.append(L"0");
				}
				if (Input.keyUp(DIK_1))
				{
					Str_.append(L"1");
				}
				if (Input.keyUp(DIK_2))
				{
					Str_.append(L"2");
				}
				if (Input.keyUp(DIK_3))
				{
					Str_.append(L"3");

				}
				if (Input.keyUp(DIK_4))
				{
					Str_.append(L"4");

				}
				if (Input.keyUp(DIK_5))
				{
					Str_.append(L"5");

				}
				if (Input.keyUp(DIK_6))
				{
					Str_.append(L"6");

				}
				if (Input.keyUp(DIK_7))
				{
					Str_.append(L"7");

				}
				if (Input.keyUp(DIK_8))
				{
					Str_.append(L"8");

				}
				if (Input.keyUp(DIK_9))
				{
					Str_.append(L"9");
				}
				if (CapitalOn_)
				{
					if (Input.keyUp(DIK_A))
					{
						Str_.append(L"A");
					}
					if (Input.keyUp(DIK_B))
					{
						Str_.append(L"B");
					}
					if (Input.keyUp(DIK_C))
					{
						Str_.append(L"C");
					}
					if (Input.keyUp(DIK_D))
					{
						Str_.append(L"D");
					}
					if (Input.keyUp(DIK_E))
					{
						Str_.append(L"E");
					}
					if (Input.keyUp(DIK_F))
					{
						Str_.append(L"F");
					}
					if (Input.keyUp(DIK_G))
					{
						Str_.append(L"G");
					}
					if (Input.keyUp(DIK_H))
					{
						Str_.append(L"H");
					}
					if (Input.keyUp(DIK_I))
					{
						Str_.append(L"I");
					}
					if (Input.keyUp(DIK_J))
					{
						Str_.append(L"J");
					}
					if (Input.keyUp(DIK_K))
					{
						Str_.append(L"K");
					}
					if (Input.keyUp(DIK_L))
					{
						Str_.append(L"L");
					}
					if (Input.keyUp(DIK_M))
					{
						Str_.append(L"M");
					}
					if (Input.keyUp(DIK_N))
					{
						Str_.append(L"N");
					}
					if (Input.keyUp(DIK_O))
					{
						Str_.append(L"O");
					}
					if (Input.keyUp(DIK_P))
					{
						Str_.append(L"P");
					}
					if (Input.keyUp(DIK_Q))
					{
						Str_.append(L"Q");
					}
					if (Input.keyUp(DIK_R))
					{
						Str_.append(L"R");
					}
					if (Input.keyUp(DIK_S))
					{
						Str_.append(L"S");
					}
					if (Input.keyUp(DIK_T))
					{
						Str_.append(L"T");
					}
					if (Input.keyUp(DIK_U))
					{
						Str_.append(L"U");
					}
					if (Input.keyUp(DIK_V))
					{
						Str_.append(L"V");
					}
					if (Input.keyUp(DIK_W))
					{
						Str_.append(L"W");
					}
					if (Input.keyUp(DIK_X))
					{
						Str_.append(L"X");
					}
					if (Input.keyUp(DIK_Y))
					{
						Str_.append(L"Y");
					}
					if (Input.keyUp(DIK_Z))
					{
						Str_.append(L"Z");
					}
				}
				else
				{
				if (Input.keyUp(DIK_A))
				{
					Str_.append(L"a");
				}
				if (Input.keyUp(DIK_B))
				{
					Str_.append(L"b");
				}
				if (Input.keyUp(DIK_C))
				{
					Str_.append(L"c");
				}
				if (Input.keyUp(DIK_D))
				{
					Str_.append(L"d");
				}
				if (Input.keyUp(DIK_E))
				{
					Str_.append(L"e");
				}
				if (Input.keyUp(DIK_F))
				{
					Str_.append(L"f");
				}
				if (Input.keyUp(DIK_G))
				{
					Str_.append(L"g");
				}
				if (Input.keyUp(DIK_H))
				{
					Str_.append(L"h");
				}
				if (Input.keyUp(DIK_I))
				{
					Str_.append(L"i");
				}
				if (Input.keyUp(DIK_J))
				{
					Str_.append(L"j");
				}
				if (Input.keyUp(DIK_K))
				{
					Str_.append(L"k");
				}
				if (Input.keyUp(DIK_L))
				{
					Str_.append(L"l");
				}
				if (Input.keyUp(DIK_M))
				{
					Str_.append(L"m");
				}
				if (Input.keyUp(DIK_N))
				{
					Str_.append(L"n");
				}
				if (Input.keyUp(DIK_O))
				{
					Str_.append(L"o");
				}
				if (Input.keyUp(DIK_P))
				{
					Str_.append(L"p");
				}
				if (Input.keyUp(DIK_Q))
				{
					Str_.append(L"q");
				}
				if (Input.keyUp(DIK_R))
				{
					Str_.append(L"r");
				}
				if (Input.keyUp(DIK_S))
				{
					Str_.append(L"s");
				}
				if (Input.keyUp(DIK_T))
				{
					Str_.append(L"t");
				}
				if (Input.keyUp(DIK_U))
				{
					Str_.append(L"u");
				}
				if (Input.keyUp(DIK_V))
				{
					Str_.append(L"v");
				}
				if (Input.keyUp(DIK_W))
				{
					Str_.append(L"w");
				}
				if (Input.keyUp(DIK_X))
				{
					Str_.append(L"x");
				}
				if (Input.keyUp(DIK_Y))
				{
					Str_.append(L"y");
				}
				if (Input.keyUp(DIK_Z))
				{
					Str_.append(L"z");
				}
 }
			}
		}
		if (!On_)
		{
			//IDstr_.clear();
		}
		if (!AsterikOn_)
		{
			if (Str_.length() >= 0)
				entity->getComponent<DXFont>().SetScript("serif", 22, FW_SEMIBOLD, RT_, Str_.c_str(), D3DXCOLOR(0,0,0,1));
		}
		else
		{
			if (Str_.length() >= 0)
			{
				AsterikStr_.append(L"*", Str_.length());
				entity->getComponent<DXFont>().SetScript("serif", 22, FW_SEMIBOLD, RT_, Str_.c_str(), D3DXCOLOR(0, 0, 0, 1));
			}
		}
	}
};

