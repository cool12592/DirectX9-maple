#pragma once
#include "MapBasic.h"
class Door :
    public MapBasic
{
public:
	Door() {};
	~Door() {};
	Door(wstring sceneName) { sceneName_ = sceneName; }
    virtual void initialize() override;

	virtual void update() override;
	virtual void render() override;

	void checkAndChangeScene();
public:
	void enterCollider(Entity* colliderEntity);
	void stayCollider(Entity* colliderEntity);

	void exitCollider(Entity* colliderEntity);

	//���ʵ� �� Ȱ��ȭ
	void setOnActiveTimer(float timer);

	//ȭ�� ���̵���,�ƿ�
	void onFade();
private:
	wstring sceneName_;
//	NetworkManager* networkManager_;
	vector<Entity*> players_;

	bool onTimer_ = false;
	float timer_ = 0.f;
	float activeTimer_ = 0.f;

	bool isEnterDoor_ = false;
	float fadeValue_ = 0.99f;
};

