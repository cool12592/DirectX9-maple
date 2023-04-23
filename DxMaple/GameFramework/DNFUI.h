#pragma once
#include "MonoBehaviour.h"

class NetworkManager;
class DNFUI :
	public MonoBehaviour
{
public:
	enum UItype {�ϴܹ�,������,Hp,Mp,inventory,bossRed, bossBack, bossIcon,
		num0, num1, num2, num3, num4, num5, num6, num7, num8, num9,
	Hnum0, Hnum1, Hnum2,Hnum3, Hnum4, Hnum5, Hnum6, Hnum7, Hnum8, Hnum9,
	 Cnum0, Cnum1, Cnum2, Cnum3, Cnum4, Cnum5, Cnum6, Cnum7, Cnum8, Cnum9 ,
	Dnum0, Dnum1, Dnum2, Dnum3, Dnum4, Dnum5, Dnum6, Dnum7, Dnum8, Dnum9  };

	// 1 2 3 4 5 6 7 8: enemy 9: boss
	DNFUI(UItype type, _vec3 position) {
		type_ = type; position_ = position;
	};
	//DNFUI(int type, _vec3 position) {
	//	int a;	//type_ = type; position_ = position;
	//};
	DNFUI() {}
	virtual ~DNFUI() {}

	void SetClick(wstring AtlasName, int index);

	void SetOn(wstring AtlasName, int index);

	void SetIdle(wstring AtlasName, int index);
	wstring getString()const { return Str_; }
	void initialize();
	bool OnMouse();
	bool OnClick();
	bool OnIdle();
	void update();
	void lateUpdate();
	void render();
	void release();

	void SetUV(float x)
	{
		gauge_ = x / 1.f;
		if (gauge_ <= 0.0f)
		{
			gauge_ = 0.0f;
		}
	}

	void insertTextNumber(int number)
	{
		if (bHit_ == true)
		{
			enemyDamage_.push(number);
		}
		if (bDamaged_ == true)
		{
			myDamage_.push(number);
		}
	}
public:
	int getMyDamage() { if(myDamage_.size()>0) return myDamage_.back(); }
	int getEnemyDamage() { if (enemyDamage_.size() > 0) return enemyDamage_.back(); }
	float bossMaxHp = 0.f;
	shared_ptr<Entity> QuickSlotEntity;
private:
	UItype type_;
	_vec3 position_;
	RECT RT_;
	bool On_;
	wstring Str_;
	float gauge_ = 1.0f; //����ü�º��� 1����.
	float cooltime_= 0.0f; //����ü�º��� 1����.
	int StrMax_ = 8;

	int hitDamage_;
	int enemyHP_;

	std::queue<int> myDamage_;		//��¿�
	std::queue<int> enemyDamage_;	//��¿�

	void setStringMax(int max) { StrMax_ = max; };

	bool enemyHit_=false;
	bool partyOn_ = true;

	RECT othreRT[4];
	wstring partyMem[4];
	wstring partyMember_;

	float timer = 0.f;

	float deletetime_ = 0.f;
	bool bHit_ = false; //������ == ���� ������

	bool bDamaged_ = true; // == ���� ������


	float rgbColor = 1.0f; //2�ʵ��� rgb�� 1�θ��� �������.
	bool onVanish=true;
	float VanishAlpha_ = 1.0f;
	int nowPartyMemCount = 0;
	//hit-���� ������
	//damaged- ���� ������

	weak_ptr<Entity> bossEntity;
	
};

//type 1~3 �α���ȭ��
//type 4~8 �ΰ���,�κ�� �⺻ DNFUI // 4�� ����� 5�� ü�� 6�� ���� 7�� ��Ƽ�ο��� 8�� ��Ƽ�̸�
//type 20~33 ��ų DNFUI
//type 40~54 Ű����Ŀ�ǵ�
//type 60 ���� ü��
//type 61 �� ü��

//type 70~79 ������ ��Ʈ
//type 100~109 ������ ��Ʈ