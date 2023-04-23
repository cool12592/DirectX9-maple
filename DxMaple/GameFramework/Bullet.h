#pragma once
#include "MonoBehaviour.h"
class Bullet :
	public MonoBehaviour
{
public:
	Bullet(bool isMain, _vec3 pos, bool right, wstring nowSurigum) { isMain_ = isMain; position_ = pos; right_ = right; nowSurigum_ = nowSurigum; }

	// MonoBehaviour을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void changeSurigum(wstring surigumName) { entity->getComponent<AtlasAnimation>().changeCurrentSprite(surigumName); }
public:
	void enterCollider(Entity* colliderEntity)
	{
		if (colliderEntity->getType() == Entity::ENTITYTYPE::ENEMY)
		{
			expired();
		}
	}

	void stayCollider(Entity* colliderEntity)
	{
	
	}

	void exitCollider(Entity* colliderEntity)
	{
	
	}
private:
	void expired();

	_vec3 position_;
	bool right_ = true;
	float timeCount = 0.f;
	weak_ptr<Entity> attackBox1_, attackBox2_, attackBox3_;
	vector<shared_ptr<Entity>> EnemyList_;
	bool isMain_;

	_vec3 dest_ ;

	wstring nowSurigum_ = L"surigum";

};

