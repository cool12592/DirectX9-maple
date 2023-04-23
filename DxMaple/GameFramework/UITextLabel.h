#pragma once
#include "DXFont.h"
#include "UIComponent.h"
class UITextLabel : public UIComponent
{
private:
	_vec3 pos_;
	RECT RT_;
	wstring Str_;
public:
	UITextLabel() {};
	virtual ~UITextLabel() {};
	void setTextBox(_vec3 pos, wstring buffer, wstring shader, const wchar_t* texture) {
		pos_ = pos;
		entity->addComponent<Sprite>(buffer, shader);
		entity->getComponent<Sprite>().insertTexture(texture);
		entity->getComponent<Sprite>().setAddPos(pos_);
		entity->addComponent<DXFont>();
		entity->addComponent<Ray>();
		D3DXIMAGE_INFO imgInfo = entity->getComponent<Sprite>().getTextureInfo();
		entity->addComponent<BoxCollider>(pos_, _vec3(0.f, 0.f, 0.f), _vec3((float)(imgInfo.Width), (float)(imgInfo.Height), 1.f)); //ID


		RT_.left = (LONG)(((SCREEN_WIDTH)/2)+ entity->getComponent<BoxCollider>().getColliderRect2D().left);
		RT_.right = (LONG)(((SCREEN_WIDTH) / 2) + entity->getComponent<BoxCollider>().getColliderRect2D().right);
		RT_.top = (LONG)(((SCREEN_HEIGHT) / 2)+ entity->getComponent<BoxCollider>().getColliderRect2D().bottom);
		RT_.bottom = (LONG)(((SCREEN_HEIGHT) / 2) + entity->getComponent<BoxCollider>().getColliderRect2D().top);

	}
	void setRect(RECT rt) { RT_ = rt; }
	void setText(wstring text) {Str_ = text;}
	void initialize()
	{
		//entity->getComponent<Sprite>().setAddPos(pos_);
	}

	void update() 
	{
				entity->getComponent<DXFont>().SetScript("serif", 25, FW_SEMIBOLD, RT_, Str_.c_str(), D3DXCOLOR(1, 1, 1, 1));
	}
};

