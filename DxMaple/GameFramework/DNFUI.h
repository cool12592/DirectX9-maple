#pragma once
#include "MonoBehaviour.h"

class NetworkManager;
class DNFUI :
	public MonoBehaviour
{
public:
	enum UItype {하단바,퀵슬롯,Hp,Mp,inventory,bossRed, bossBack, bossIcon,
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
	float gauge_ = 1.0f; //현재체력비율 1이하.
	float cooltime_= 0.0f; //현재체력비율 1이하.
	int StrMax_ = 8;

	int hitDamage_;
	int enemyHP_;

	std::queue<int> myDamage_;		//출력용
	std::queue<int> enemyDamage_;	//출력용

	void setStringMax(int max) { StrMax_ = max; };

	bool enemyHit_=false;
	bool partyOn_ = true;

	RECT othreRT[4];
	wstring partyMem[4];
	wstring partyMember_;

	float timer = 0.f;

	float deletetime_ = 0.f;
	bool bHit_ = false; //때릴때 == 적이 맞을때

	bool bDamaged_ = true; // == 내가 맞을때


	float rgbColor = 1.0f; //2초동안 rgb를 1로만들어서 흰색으로.
	bool onVanish=true;
	float VanishAlpha_ = 1.0f;
	int nowPartyMemCount = 0;
	//hit-내가 때릴떄
	//damaged- 내가 맞을때

	weak_ptr<Entity> bossEntity;
	
};

//type 1~3 로그인화면
//type 4~8 인게임,로비용 기본 DNFUI // 4는 보톰바 5는 체력 6은 마나 7은 파티인원수 8은 파티이름
//type 20~33 스킬 DNFUI
//type 40~54 키보드커맨드
//type 60 보스 체력
//type 61 적 체력

//type 70~79 때릴때 폰트
//type 100~109 맞을때 폰트