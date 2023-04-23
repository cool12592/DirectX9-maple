#include "stdafx.h"
#include "DNFUI.h"
#include "GameManager.h"
void DNFUI::SetClick(wstring AtlasName, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(AtlasName, L"left", index, index);
}
void DNFUI::SetOn(wstring AtlasName, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(AtlasName, L"on", index, index);
}
void DNFUI::SetIdle(wstring AtlasName, int index)
{
	AtlasAnimation& Anim = entity->getComponent<AtlasAnimation>();
	Anim.insertMotionData(AtlasName, L"idle", index, index);
}


//3 4 5 6 7 8

//30~39 아이템숫자

//60 61 66 보스체력 바탕 아이콘

//70~79 때릴때

//80 ~89 때릴떄(크리)

//100~109 맞을떄

void DNFUI::initialize()
{

	//if (makeOnce_ == true)
	{	
		
		
		if (type_== UItype::퀵슬롯)
		{
			
			entity->addComponent<Transform>(position_+_vec3(977.f,0.f,0.f), _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
	
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/UI2.png");
			
//			entity->addComponent<BoxCollider>(_vec3(0.f, 10.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(200.f, 60.f, 100.f));


			QuickSlotEntity = SceneManager::getInstance()->getCurrentScene()->getObjectPool()->acquire();
			QuickSlotEntity->setTypeAndName(Entity::ENTITYTYPE::DNFUI, L"quickslotentity");
			QuickSlotEntity->addComponent<Item>(L"blank");
			QuickSlotEntity->getComponent<Rigidbody>().setUseGravity(false);
			EntityManager::getInstance()->insertEntity(QuickSlotEntity);

			GameManager::getInstance()->setQuickSloatEntity(QuickSlotEntity);

			QuickSlotEntity->getComponent<BoxCollider>().transform_.scale_ = _vec3(0.1f, 0.1f, 0.1f);

		}

		//bottombar //로비, 인게임용
		else if (type_ == UItype::하단바)
		{
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/UI1.png");
	

			string strBGM[] = {
			"../resource/mySound/UponTheSky.MP3",  //0
				"../resource/mySound/ArabPirate.MP3", //1
						"../resource/mySound/QueensGarden.MP3", //2
								"../resource/mySound/RaindropFlower.MP3", //3
										"../resource/mySound/MoonlightShadow.MP3", //4
												"../resource/mySound/cashshop.MP3", //5

				"../resource/mySound/CaveOfHontale.MP3", //6  
				"../resource/mySound/HonTale.MP3" //7

		
			};
			entity->addComponent<Sound>().CreateBGSound(_countof(strBGM), strBGM);
			



		}
		//HP //로비, 인게임용
		else if (type_ == UItype::Hp)
		{
			// cout << "HP" << endl;
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.18f, 1.f, 1.f));

			entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"StatusShader");
			
			entity->getComponent<AtlasAnimation>().insertSprite(L"hp", L"../resource/myUI/hp.png", L"../resource/myUI/hp.json");
			entity->getComponent<AtlasAnimation>().isZRender = false;
			entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		}
		//MP //로비, 인게임용
		else if (type_ == UItype::Mp)
		{
			// cout << "MP" << endl;
				// cout << "HP" << endl;
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.18f, 1.f, 1.f));

			entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"StatusShader");

			entity->getComponent<AtlasAnimation>().insertSprite(L"MP", L"../resource/myUI/mp.png", L"../resource/myUI/mp.json");
			entity->getComponent<AtlasAnimation>().isZRender = false;
			entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

		}
		//인벤토리
		else if (type_ == UItype::inventory)
		{
			
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<BoxCollider>(_vec3(0.f, 130.f, 0.f), _vec3(0.f, 0.f, 0.f), _vec3(250.f, 100.f, 100.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/inventory1.png");
		}

	
		
		//아이템갯수
		else if (type_ == UItype::num0) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_0.png");
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
			//entity->getComponent<Sprite>().blendEnable_ = false;
		}
		else if (type_ == UItype::num1) {

			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_1.png");
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
			//entity->getComponent<Sprite>().blendEnable_ = false;
		}
		else if (type_ == UItype::num2) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_2.png");
		}
		else if (type_ == UItype::num3) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_3.png");
		}
		else if (type_ == UItype::num4) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_4.png");
		}
		else if (type_ == UItype::num5) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_5.png");
		}
		else if (type_ == UItype::num6) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_6.png");
		}
		else if (type_ == UItype::num7) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_7.png");
		}
		else if (type_ == UItype::num8) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_8.png");
		}
		else if (type_ == UItype::num9) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/boss_9.png");

		}

		//보스체력 back
		else if (type_ == UItype::bossBack) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(5.f, 3.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/boss_back.png");

		}
		
		//혼테일아이콘

		else if (type_ == UItype::bossIcon) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"StatusShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/myUI/icon.png");

		}
	
		else if (type_ == UItype::bossRed) //boss Red
		{
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(5.5f, 1.f, 1.f));

			entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"StatusShader");

			entity->getComponent<AtlasAnimation>().insertSprite(L"hp", L"../resource/myUI/hp.png", L"../resource/myUI/hp.json");
			entity->getComponent<AtlasAnimation>().destBlendOp_ = D3DBLEND_DESTALPHA;

			
		}

		//떄릴떄
		else if (type_ == UItype::Hnum0) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_0.png");
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
			//entity->getComponent<Sprite>().blendEnable_ = false;
		}
		else if (type_ == UItype::Hnum1) {

			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_1.png");
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
			//entity->getComponent<Sprite>().blendEnable_ = false;
		}
		else if (type_ == UItype::Hnum2) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_2.png");
		}
		else if (type_ == UItype::Hnum3) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_3.png");
		}
		else if (type_ == UItype::Hnum4) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_4.png");
		}
		else if (type_ == UItype::Hnum5) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_5.png");
		}
		else if (type_ == UItype::Hnum6) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_6.png");
		}
		else if (type_ == UItype::Hnum7) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_7.png");
		}
		else if (type_ == UItype::Hnum8) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_8.png");
		}
		else if (type_ == UItype::Hnum9) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/hit_9.png");

		}



		 
		//떄릴때 (크리)
		else if (type_ == UItype::Cnum0) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri0.png");
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
			//entity->getComponent<Sprite>().blendEnable_ = false;
		}
		else if (type_ == UItype::Cnum1) {

			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri1.png");
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
			//entity->getComponent<Sprite>().blendEnable_ = false;
		}
		else if (type_ == UItype::Cnum2) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri2.png");
		}
		else if (type_ == UItype::Cnum3) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri3.png");
		}
		else if (type_ == UItype::Cnum4) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri4.png");
		}
		else if (type_ == UItype::Cnum5) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri5.png");
		}
		else if (type_ == UItype::Cnum6) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri6.png");
		}
		else if (type_ == UItype::Cnum7) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri7.png");
		}
		else if (type_ == UItype::Cnum8) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri8.png");
		}
		else if (type_ == UItype::Cnum9) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/cri9.png");

		}


		
		//맞을떄
		else if (type_ == UItype::Dnum0) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/0.png");
		}
		else if (type_ == UItype::Dnum1) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/1.png");
		}

		else if (type_ == UItype::Dnum2) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/2.png");
		}

		else if (type_ == UItype::Dnum3) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/3.png");
		}
		else if (type_ == UItype::Dnum4) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/4.png");
		}
		else if (type_ == UItype::Dnum5) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/5.png");
		}
		else if (type_ == UItype::Dnum6) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/6.png");
		}
		else if (type_ == UItype::Dnum7) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/7.png");
		}
		else if (type_ == UItype::Dnum8) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/8.png");
		}
		else if (type_ == UItype::Dnum9) {
			entity->addComponent<Transform>(position_, _vec3(0.f, 0.f, 0.f), _vec3(1.f, 1.f, 1.f));
			entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
			entity->getComponent<Sprite>().insertTexture(L"../resource/NumberUi/ui/json/number/9.png");
		}

		

		//if (type_ >= 70)
		//{
			//entity->getComponent<Sprite>().destBlendOp_ = D3DBLEND_DESTALPHA;
		//}

	}


}


bool DNFUI::OnMouse()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (entity->getComponent<Ray>().rayCastCollider2D(entity->getComponent<BoxCollider>().getColliderRect2D()))
	{
		entity->getComponent<AtlasAnimation>().changeMotion(L"on");

		stateMachine.changeState(L"on");
		return true;
	}
	return false;

}
bool DNFUI::OnClick()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();

	if (OnMouse())
	{

		if ((Input.mouseDown(InputManager::MOUSEBUTTONTYPE::LEFT)))
		{
			entity->getComponent<AtlasAnimation>().changeMotion(L"left");
			stateMachine.changeState(L"left");
			return true;
		}
		if ((Input.mouseDown(InputManager::MOUSEBUTTONTYPE::RIGHT)))
		{
			stateMachine.changeState(L"right");
			return true;
		}
	}
	else
		return false;

}
bool DNFUI::OnIdle()
{
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	if (!entity->getComponent<Ray>().rayCastCollider2D(entity->getComponent<BoxCollider>().getColliderRect2D()))
	{
		entity->getComponent<AtlasAnimation>().changeMotion(L"idle");
		stateMachine.changeState(L"idle");
		return true;
	}
	else
		return false;
}


void DNFUI::update()
{
	timer += TimeManager::getInstance()->getDeltaTime();
	deletetime_ += TimeManager::getInstance()->getDeltaTime();
	

	 if (type_ == UItype::하단바)
	{


		if (L"Room2" == SceneManager::getInstance()->GetCurrentSceneName())
		{
			entity->getComponent<Sound>().AllBgSoundOFF(7, 0);
			if (!entity->getComponent<Sound>().IsPlayingBGM(0))
				entity->getComponent<Sound>().PlaySoundBG(0);
			
		}
		else if (L"CRIMSON" == SceneManager::getInstance()->GetCurrentSceneName())
		{
			entity->getComponent<Sound>().AllBgSoundOFF(7, 1);
			if (!entity->getComponent<Sound>().IsPlayingBGM(1))
				entity->getComponent<Sound>().PlaySoundBG(1);

		}
		else if (L"Room5" == SceneManager::getInstance()->GetCurrentSceneName())
		{
			entity->getComponent<Sound>().AllBgSoundOFF(7, 2);
			if (!entity->getComponent<Sound>().IsPlayingBGM(2))
				entity->getComponent<Sound>().PlaySoundBG(2);

		}
		else if (L"Room4" == SceneManager::getInstance()->GetCurrentSceneName())
		{
			entity->getComponent<Sound>().AllBgSoundOFF(7, 3);
			if (!entity->getComponent<Sound>().IsPlayingBGM(3))
				entity->getComponent<Sound>().PlaySoundBG(3);

		}
		else if (L"RoomAirport" == SceneManager::getInstance()->GetCurrentSceneName())
		{
			entity->getComponent<Sound>().AllBgSoundOFF(7, 4);
			if (!entity->getComponent<Sound>().IsPlayingBGM(4))
				entity->getComponent<Sound>().PlaySoundBG(4);

		}
		else if (L"Room3" == SceneManager::getInstance()->GetCurrentSceneName())
		{
		
			entity->getComponent<Sound>().AllBgSoundOFF(7, 3);
				if (!entity->getComponent<Sound>().IsPlayingBGM(3))
					entity->getComponent<Sound>().PlaySoundBG(3);
			
			

		}
		else if (L"RoomCash" == SceneManager::getInstance()->GetCurrentSceneName())
		{
			
			
			entity->getComponent<Sound>().AllBgSoundOFF(7, 5);
				if (!entity->getComponent<Sound>().IsPlayingBGM(5))
					entity->getComponent<Sound>().PlaySoundBG(5);
			
		}
		else if (L"RoomBlue1" == SceneManager::getInstance()->GetCurrentSceneName())
		{


			entity->getComponent<Sound>().AllBgSoundOFF(7, 6);
			if (!entity->getComponent<Sound>().IsPlayingBGM(6))
				entity->getComponent<Sound>().PlaySoundBG(6);

		}
		else if (L"BossRoom" == SceneManager::getInstance()->GetCurrentSceneName())
		{

			if (GameManager::getInstance()->getBoss() != nullptr)
			{
				entity->getComponent<Sound>().AllBgSoundOFF(7, 7);
				if (!entity->getComponent<Sound>().IsPlayingBGM(7))
					entity->getComponent<Sound>().PlaySoundBG(7);
			}
			//보스가없는상황이면
			else
			{
				entity->getComponent<Sound>().AllBgSoundOFF(7, 6);
				if (!entity->getComponent<Sound>().IsPlayingBGM(6))
					entity->getComponent<Sound>().PlaySoundBG(6);
			}
			

		}
		

	}
	else if (type_ == UItype::Hp)
	{
		auto p = GameManager::getInstance()->getPlayer();

		entity->getComponent<DNFUI>().SetUV(p->getComponent<Status>().hp_ / p->getComponent<Status>().maxHp_);
		entity->getComponent<AtlasAnimation>().isZRender = false;


	}
	else if (type_ == UItype::Mp)
	{
		auto p = GameManager::getInstance()->getPlayer();


		entity->getComponent<DNFUI>().SetUV(p->getComponent<Status>().mp_ / p->getComponent<Status>().maxMp_);
		entity->getComponent<AtlasAnimation>().isZRender = false;

	}

	





	else if (type_ == UItype::bossRed) //boss Red
	{
		if (GameManager::getInstance()->isBossSet())
		{
			if(bossEntity.lock()==nullptr)
				bossEntity = GameManager::getInstance()->getBoss();
			else
			{
				gauge_ = bossEntity.lock()->getComponent<HornTail>().HornTail_totalHP / bossMaxHp;
			}
					
		}
		
	}

	else if (type_ >= UItype::Hnum0)
	{
		
			if (0.7f >= deletetime_)
			{
				//VanishAlpha_ -= 0.1f;
				entity->getComponent<Transform>().position_.y += Time.getDeltaTime()*10.f;
			}
			else
			{
				entity->setActive(false);
			}
		
	
	}

	if (deletetime_ >= 6.f)
	{
		deletetime_ = 0.0f;
	}
	

}

void DNFUI::lateUpdate()
{


	if (type_ == UItype::퀵슬롯)
	{
		entity->getComponent<Transform>().position_ = GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition() + _vec3(482.f, -SCREEN_HEIGHT / 2.f + 80.f, -2.f);
		QuickSlotEntity->getComponent<Transform>().position_ = GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition() + _vec3(427.f, -SCREEN_HEIGHT / 2.f + 96.f, -3.f);


		if (QuickSlotEntity->getComponent<Item>().name_ != L"blank")
		{
			if (QuickSlotEntity->getComponent<Item>().getParentEntity() == nullptr)
			{

				QuickSlotEntity->getComponent<Item>().CopyItem(L"blank", 0, 1);
				QuickSlotEntity->getComponent<Item>().countReset();

			}
			if (QuickSlotEntity->getComponent<Item>().getParentEntity() != nullptr)
			{
				if (QuickSlotEntity->getComponent<Item>().getParentEntity()->getComponent<Item>().inInventory_ == false)
				{
					QuickSlotEntity->getComponent<Item>().CopyItem(L"blank", 0, 1);
					QuickSlotEntity->getComponent<Item>().countReset();
					QuickSlotEntity->getComponent<Item>().SetParentEntity(nullptr);
				}

			}

		}
	

	//	if(QuickSlotEntity->get)
	}
	else if (type_ == UItype::하단바)
	{
		
		entity->getComponent<Transform>().position_ = GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition() + _vec3(-85.f, -SCREEN_HEIGHT/2.f+73.f,-2.f);

	}
	else if (type_ == UItype::Hp)
	{
		entity->getComponent<Transform>().position_ = GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition() + _vec3(-225.f, -SCREEN_HEIGHT / 2.f + 65.f, -100.f);

	}

	else if (type_ == UItype::Mp)
	{
		entity->getComponent<Transform>().position_ = GameManager::getInstance()->getPlayer()->getComponent<Camera>().getPosition() + _vec3(-36.f, -SCREEN_HEIGHT / 2.f + 65.f, -100.f);

	}
	else if (type_ == UItype::inventory)
	{
		if (InputManager::getInstance()->keyDown(DIK_I))
		{
			if (entity->getComponent<Transform>().position_.z == 20000.f)
			{
			
			
				_vec3 P_POS = GameManager::getInstance()->getPlayer()->getComponent<Transform>().position_;
				entity->getComponent<Transform>().position_ = _vec3(P_POS.x, P_POS.y + 300.F, -2.F);
			}
			else
				entity->getComponent<Transform>().position_.z = 20000.f;
		}
	}
	
	

		if (type_ == UItype::bossBack)
		{
			auto p = GameManager::getInstance()->getPlayer();
			_vec3& trans = p->getComponent<Camera>().position_;
			entity->getComponent<Transform>().position_ = trans + _vec3(0.f, SCREEN_HEIGHT / 2.f - 15.f, 1.f);
		}
		else if (type_ == UItype::bossIcon)
		{
			auto p = GameManager::getInstance()->getPlayer();
			_vec3& trans = p->getComponent<Camera>().position_;
			entity->getComponent<Transform>().position_ = trans + _vec3(-380.f, SCREEN_HEIGHT / 2.f - 20.f, 1.f);
		}



		else if (type_ == UItype::bossRed)
		{
			
				auto p = GameManager::getInstance()->getPlayer();
				_vec3& trans = p->getComponent<Camera>().position_;
				entity->getComponent<Transform>().position_ = trans+_vec3(0.f, SCREEN_HEIGHT/2.f-15.f,0.f);
		}


		
	
}

void DNFUI::render()
{

	if (type_ == UItype::Hp)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		anim.readyShaderValues(make_pair("Size", gauge_));
		anim.readyShaderValues(make_pair("Disappear", true));
		anim.readyShaderValues(make_pair("onVanish", true), make_pair("vanishAlpha", 0.5f));
	}


	else if (type_ == UItype::Mp)
	{
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		anim.readyShaderValues(make_pair("Size", gauge_));
		anim.readyShaderValues(make_pair("Disappear", true));
		anim.readyShaderValues(make_pair("onVanish", true), make_pair("vanishAlpha", 0.5f));
	}

	
	else if (type_ == UItype::bossRed)
	{
		
		AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
		anim.readyShaderValues(make_pair("Size", gauge_));
		anim.readyShaderValues(make_pair("Disappear", true));
		anim.readyShaderValues(make_pair("onVanish", true), make_pair("vanishAlpha", 0.5f));
	}


}

void DNFUI::release()
{
}

