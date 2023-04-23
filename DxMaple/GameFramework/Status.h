#pragma once
#include "ECS.h"
class Status :
    public Component
{
public:
	//�÷��̾� �ܿ� ���������
    enum class CLASSTYPE{FIGHTER,SWORDMAN,ETC};
public:
    Status();
    virtual ~Status();
public:
	void damaged(double physicalDamage, double magicalDamage, Entity* attackboxEntity);
	void downed(double physicalDamage, double magicalDamage, Entity* attackboxEntity);
	void stunned(double physicalDamage, double magicalDamage, Entity* attackboxEntity);
public:
    void setStatus(CLASSTYPE classType, double maxHp, double maxMp, double physicalAttack, double physicalDefense,double magicalAttack,double magicalDefense,double moveSpeed,double attackSpeed, double castingSpeed);
	void setDamagedFunction(function<void(Entity*)> damagedFunction) { damagedFunction_ = damagedFunction; }
	void setDownedFunction(function<void(Entity*)> downedFunction) { downedFunction_ = downedFunction; }
	void setStunnedFunction(function<void(Entity*)> stunnedFunction) { stunnedFunction_ = stunnedFunction; }
	void useMp(double spendMp);
	void Recover(double hp, double mp);

    void turnOnSuperarmor(float duration);
    void turnOffSuperarmor();
	void turnOnAttackUp(float duration);
	void turnOffAttackUp();

    void DamageFont(float damage,int multiHit, bool isCritical , int kind );

	// Component��(��) ���� ��ӵ�
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;

public:
    double maxHp_, hp_, maxMp_, mp_, physicalAttack_, physicalDefense_,magicalAttack_,magicalDefense_;//�ɷ�ġ �� �߰��Ұ� ������ �߰��ϼ���
    double moveSpeed_, attackSpeed_,castingSpeed_;
    bool isSuperArmor_;
    float superArmorTimer_;
    float superArmorDuration_;

    bool invincible_;

	bool isAttackUp_;
	float attackUpTimer_;
	float attackUpDuration_;

    CLASSTYPE     classType_;

	function<void(Entity*)> damagedFunction_;
	function<void(Entity*)> downedFunction_;
	function<void(Entity*)> stunnedFunction_;

    float damageFontTime_ = 1.;
    int damageFontCount_ = 0;

     bool isTimer_=false;
  

     //������,��ġ
     queue<pair<float, float>> fontQue;
     //ũ������
     queue<bool> CriQue;

	 queue<int> KindQue;

     float zCount = 0.f;

	 shared_ptr<Entity> hitEffect;
};

