#pragma once
#include "ECS.h"
#include "Define.h"
#include "SceneManager.h"
#include "EntityManager.h"
#include "MonoBehaviourHeader.h"

class GameManager
{

	DECLARE_SINGLETON(GameManager)

public:
	GameManager();
	~GameManager();
public:

	void setPlayer(shared_ptr<Entity> player) { player_ = player; }
	void setBoss(shared_ptr<Entity> boss) { boss_ = boss; }
	void setCurrentMap(shared_ptr<Entity> map) { currentMap_ = map; }
	void setMouse(shared_ptr<Entity> mouse) { mouse_ = mouse; }
	void setEnemyHitBox(shared_ptr<Entity> e) { hitbox_ = e; }
	void setShop(shared_ptr<Entity> shop) { shop_ = shop; }

	void setPlayersPosition(_vec3 position);
	void setTarget(shared_ptr<Entity> target) { target_ = target; }
	bool isPlayerSet()const { return !player_.expired(); }
	bool isBossSet()const { return !boss_.expired(); }
	shared_ptr<Entity> getBoss() { return boss_.lock(); }//플레이어 만료도면 어썰트로 메세지처리
	shared_ptr<Entity> getPlayer() { return player_.lock(); }//플레이어 만료도면 어썰트로 메세지처리
	shared_ptr<Entity> getCurrentMap() { return currentMap_.lock(); }//플레이어 만료도면 어썰트로 메세지처리
	shared_ptr<Entity> getEnemyHitBox() { return hitbox_.lock(); }//플레이어 만료도면 어썰트로 메세지처리
	shared_ptr<Entity> getMouse() { return mouse_.lock(); }
	shared_ptr<Entity> getTarget() { return target_.lock(); }
	shared_ptr<Entity> getShop() { return shop_.lock(); }

	void setIcePostion(vector<_vec3> a) { icePostion_ = a; }
	void setFirePostion(vector<_vec3> b) { firePosition_ = b; }
	vector<_vec3>  getIcePosition() { return icePostion_; }
	vector<_vec3>  getFirePosition() { return firePosition_; }
	int getTotalPlayer() const;

	void equipWeapon(const wchar_t* weaponName, Entity* playerEntity);
	void makeWeaponEffect(const wchar_t* texturePath, const wchar_t* atlasPath, Entity* weaponEntity);
	void makePlayerSelf(wstring className, _vec3 position);
	void makePlayerOther(wstring className, _vec3 position, int userIDN, int entityNumber);
	void makeDamageFont(DNFUI::UItype damageUITypedouble, double damage, _vec3 position); //PlayerPostion
	//void makeCriticalDamageFont(double damage, _vec3 position); //PlayerPostion
	//void makeEnemyFont(double damage, _vec3 position); //EnemyPosition
	void makeEnemyHitBox(Entity* attackEntity);
	shared_ptr<Entity> makeEffect(wstring atlasPath); //파일확장자 뺀 나머지경로
	void makeOrUpdateOtherAttackBox(int userIDN, int objectNumber, int objectType, int userType, int attackType, _vec3 position, _vec3 size, double physicalDamage, double magicalDamage);
	//void eraseNetworkEntity(int userIDN, int objectNumber, int objectType); //네트워크 관련 객체 삭제
	void changeSceneAllPlayer(wstring sceneName);

	shared_ptr<Entity> getQuickSlotEntity() { return QuickSlotEntity.lock(); }
	void setQuickSloatEntity(shared_ptr<Entity> quick) { QuickSlotEntity = quick; }
	
private:
	weak_ptr<Entity> player_,hitbox_,boss_,currentMap_,shop_;

	weak_ptr<Entity> checkBox_;
	weak_ptr<Entity> mouse_;
	weak_ptr<Entity> target_;
	weak_ptr<Entity> center_,mdidleTop_,middleBot_,magmaTrap_;
	vector<shared_ptr<Entity>> niddleTrap_;
	std::queue<int> Damage_;

	vector<_vec3> icePostion_;
	vector<_vec3> firePosition_;

	weak_ptr<Entity>QuickSlotEntity;
};

