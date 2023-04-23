#include "stdafx.h"
#include "ExcelLoader.h"

#undef max
#undef min
#include "xlnt/xlnt.hpp"

#include "ECS.h"
#include "AtlasAnimation.h"
#include "StateMachine.h"
#include "Status.h"
#include "Skill.h"
#include "FighterState.h"
#include"ItemComponent.h"
#include "Item.h"
ClassTypeMap ExcelLoader::mapClassType_;
StateMap ExcelLoader::mapState_;
TransitionMap ExcelLoader::mapTransition_;
keyTypeMap ExcelLoader::mapKeyType_;
SkillTypeMap ExcelLoader::mapSkillType_;
NameMap ExcelLoader::mapName_;

wstring convertStrToWstr(const string& str)
{
	wstring wstr;
	wstr.assign(str.begin(), str.end());
	return wstr;
}

void ExcelLoader::initialize()
{
	//매핑 데이터


	mapName_.emplace(L"blank", L"blank");
	mapName_.emplace(L"coin", L"coin");
	mapName_.emplace(L"money", L"money");
	mapName_.emplace(L"mush_tem", L"주황 버섯의 갓");
	mapName_.emplace(L"portion", L"엘릭서");
	mapName_.emplace(L"return", L"마을 귀환 주문서");
	mapName_.emplace(L"apple", L"사과");
	mapName_.emplace(L"green_mush_tem", L"초록버섯의 갓");
	mapName_.emplace(L"ston_tem", L"스톤골렘의 돌조각");
	mapName_.emplace(L"darkston_tem", L"다크 스톤골렘의 돌조각");
	mapName_.emplace(L"scal_tem", L"스켈레곤의 뿔");
	mapName_.emplace(L"white_surigum", L"화이트 수리검");
	mapName_.emplace(L"normal_surigum", L"뇌전 수리검");



	mapName_.emplace(L"mush", L"주황버섯");
	mapName_.emplace(L"greenmush", L"초록버섯");
	mapName_.emplace(L"ston", L"스톤골렘");
	mapName_.emplace(L"darkston", L"다크스톤골렘");
	mapName_.emplace(L"scal", L"스켈레톤");

	mapName_.emplace(L"a", L"주황 버섯의 갓");
	mapName_.emplace(L"b", L"초록버섯의 갓");
	mapName_.emplace(L"c", L"스톤골렘의 돌조각");
	mapName_.emplace(L"d", L"다크 스톤골렘의 돌조각");
	mapName_.emplace(L"e", L"스켈레곤의 뿔");


	mapClassType_.emplace(L"FIGHTER", (int)Status::CLASSTYPE::FIGHTER);
	mapClassType_.emplace(L"SWORDMAN", (int)Status::CLASSTYPE::SWORDMAN);

	mapState_.emplace(L"FighterState::Idle", &FighterState::Idle::instance);
	mapState_.emplace(L"FighterState::Walk", &FighterState::Walk::instance);
	mapState_.emplace(L"FighterState::Dash", &FighterState::Dash::instance);
	mapState_.emplace(L"FighterState::Jump", &FighterState::Jump::instance);
	mapState_.emplace(L"FighterState::Attack_1", &FighterState::Attack_1::instance);
	mapState_.emplace(L"FighterState::Attack_2", &FighterState::Attack_2::instance);
	mapState_.emplace(L"FighterState::Attack_3", &FighterState::Attack_3::instance);
	mapState_.emplace(L"FighterState::Attack_4", &FighterState::Attack_4::instance);
	mapState_.emplace(L"FighterState::Attack_Dash", &FighterState::Attack_Dash::instance);
	mapState_.emplace(L"FighterState::Attack_Jump", &FighterState::Attack_Jump::instance);
	mapState_.emplace(L"FighterState::HammerKick", &FighterState::HammerKick::instance);
	mapState_.emplace(L"FighterState::LowKick", &FighterState::LowKick::instance);
	mapState_.emplace(L"FighterState::Hosinyeongeok", &FighterState::Hosinyeongeok::instance);
	mapState_.emplace(L"FighterState::Damaged", &FighterState::Damaged::instance);
	mapState_.emplace(L"FighterState::Downed", &FighterState::Downed::instance);
	mapState_.emplace(L"FighterState::HoverStomp", &FighterState::HoverStomp::instance);
	mapState_.emplace(L"FighterState::Boonggwon", &FighterState::Boonggwon::instance);
	mapState_.emplace(L"FighterState::Ganggwon", &FighterState::Ganggwon::instance);
	mapState_.emplace(L"FighterState::BoneCrusher", &FighterState::BoneCrusher::instance);
	mapState_.emplace(L"FighterState::Jilpoonggak", &FighterState::Jilpoonggak::instance);
	mapState_.emplace(L"FighterState::RisingKnuckle", &FighterState::RisingKnuckle::instance);
	mapState_.emplace(L"FighterState::Bitdrive", &FighterState::Bitdrive::instance);
	mapState_.emplace(L"FighterState::PowerfulLowkick", &FighterState::PowerfulLowkick::instance);
	mapState_.emplace(L"FighterState::Chulsango", &FighterState::Chulsango::instance);
	mapState_.emplace(L"FighterState::OneInchPunch", &FighterState::OneInchPunch::instance);
	mapState_.emplace(L"FighterState::LighteningDance", &FighterState::LighteningDance::instance);
	mapState_.emplace(L"FighterState::BackStep", &FighterState::BackStep::instance);
	mapState_.emplace(L"FighterState::QuickStanding", &FighterState::QuickStanding::instance);
	mapState_.emplace(L"FighterState::Flash", &FighterState::Flash::instance);
	mapState_.emplace(L"FighterState::Rope", &FighterState::Rope::instance);
	mapState_.emplace(L"FighterState::KneelDown", &FighterState::KneelDown::instance);

	mapTransition_.emplace(L"IDLE", (int)Transition::IDLE);
	mapTransition_.emplace(L"WALK", (int)Transition::WALK);
	mapTransition_.emplace(L"DASH", (int)Transition::DASH);
	mapTransition_.emplace(L"ATTACK", (int)Transition::ATTACK);
	mapTransition_.emplace(L"JUMP", (int)Transition::JUMP);
	mapTransition_.emplace(L"STAND", (int)Transition::STAND);
	mapTransition_.emplace(L"FLASH", (int)Transition::FLASH);
	mapTransition_.emplace(L"ROPE", (int)Transition::ROPE);
	mapTransition_.emplace(L"KNEELDOWN", (int)Transition::KNEELDOWN);

	mapKeyType_.emplace(L"z", DIK_Z);
	mapKeyType_.emplace(L"x", DIK_X);
	mapKeyType_.emplace(L"c", DIK_C);
	mapKeyType_.emplace(L"space", DIK_SPACE);
	mapKeyType_.emplace(L"right", DIK_RIGHT);
	mapKeyType_.emplace(L"left", DIK_LEFT);
	mapKeyType_.emplace(L"up", DIK_UP);
	mapKeyType_.emplace(L"down", DIK_DOWN);
	mapKeyType_.emplace(L"a", DIK_A);
	mapKeyType_.emplace(L"s", DIK_S);
	mapKeyType_.emplace(L"d", DIK_D);
	mapKeyType_.emplace(L"f", DIK_F);
	mapKeyType_.emplace(L"g", DIK_G);
	mapKeyType_.emplace(L"h", DIK_H);
	mapKeyType_.emplace(L"q", DIK_Q);
	mapKeyType_.emplace(L"w", DIK_W);
	mapKeyType_.emplace(L"e", DIK_E);
	mapKeyType_.emplace(L"r", DIK_R);
	mapKeyType_.emplace(L"t", DIK_T);
	mapKeyType_.emplace(L"y", DIK_Y);
	mapKeyType_.emplace(L"u", DIK_U);
	mapKeyType_.emplace(L"j", DIK_J);
	mapKeyType_.emplace(L"k", DIK_K);
	mapKeyType_.emplace(L"insert", DIK_INSERT);
	mapKeyType_.emplace(L"home", DIK_HOME);
	mapKeyType_.emplace(L"pgup", DIK_PGUP);
	mapKeyType_.emplace(L"delete", DIK_DELETE);
	mapKeyType_.emplace(L"end", DIK_END);
	mapKeyType_.emplace(L"pgdn", DIK_PGDN);


	mapSkillType_.emplace(L"GROUND", (int)Skill::SKILLTYPE::GROUND);
	mapSkillType_.emplace(L"JUMP", (int)Skill::SKILLTYPE::JUMP);

}

void ExcelLoader::loadPlayerData(const wchar_t* filePath, Entity* entity, const wchar_t* className)
{
	Status& status = entity->getComponent<Status>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	Skill& skill = entity->getComponent<Skill>();

	xlnt::workbook wb;
	wb.load(filePath);
	xlnt::worksheet ws = wb.sheet_by_index(0);
	//스테이터스 데이터 로드
	for (auto& row : ws.rows(false))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		//맞는 이름 찾으면 status 데이터 넣기
		wstring wstrClassName= convertStrToWstr((*cellIter).value<string>());
		
		if (wcscmp(className, wstrClassName.c_str()) == 0)
		{
			wstring wstrClassType= convertStrToWstr((*(++cellIter)).value<string>());

			Status::CLASSTYPE classType = (Status::CLASSTYPE)mapClassType_[wstrClassType];
			double initHp = (*(++cellIter)).value<double>();
			double initMp = (*(++cellIter)).value<double>();
			double physicalAttack = (*(++cellIter)).value<double>();
			double physicalDefense = (*(++cellIter)).value<double>();
			double magicalAttack = (*(++cellIter)).value<double>();
			double magicalDefense = (*(++cellIter)).value<double>();
			double moveSpeed = (*(++cellIter)).value<double>();
			double attackSpeed = (*(++cellIter)).value<double>();
			double castingSpeed = (*(++cellIter)).value<double>();

			wstring wstrTexturePath = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrAtlasPath = convertStrToWstr((*(++cellIter)).value<string>());

			status.setStatus(classType, initHp, initMp, physicalAttack, physicalDefense,magicalAttack,magicalDefense, moveSpeed, attackSpeed, castingSpeed);
			anim.insertSprite(wstrClassName, wstrTexturePath.c_str(), wstrAtlasPath.c_str());
			break;
		}
	}
	//애니메이션 모션 데이터 넣기
	ws = wb.sheet_by_index(1);
	for (auto& row : ws.rows(true))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());
		if (wcscmp(className, wstrClassName.c_str()) == 0)
		{
			wstring wstrMotionName = convertStrToWstr((*(++cellIter)).value<string>());

			int startIndex = (*(++cellIter)).value<int>();
			int endIndex = (*(++cellIter)).value<int>();
			
			anim.insertMotionData(wstrClassName, wstrMotionName, startIndex, endIndex);
		}
	}

	//상태 데이터 넣기
	ws = wb.sheet_by_index(2);
	for (auto& row : ws.rows(true))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());
		if (wcscmp(className, wstrClassName.c_str()) == 0)
		{
			wstring wstrStateName = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrStateClassName = convertStrToWstr((*(++cellIter)).value<string>());

			stateMachine.insertState(wstrStateName, mapState_[wstrStateClassName]);
		}
	}

	//상태 전이 데이터 넣기
	ws = wb.sheet_by_index(3);
	for (auto& row : ws.rows(true))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());
		if (wcscmp(className, wstrClassName.c_str()) == 0)
		{
			wstring wstrCurrentStateName = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrTransitionName = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrTransStateName = convertStrToWstr((*(++cellIter)).value<string>());

			stateMachine.insertTransitionCondition(wstrCurrentStateName, mapTransition_[wstrTransitionName],wstrTransStateName);
		}
	}

	//스킬 데이터 넣기
	ws = wb.sheet_by_index(4);
	for (auto& row : ws.rows(true))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());
		if (wcscmp(className, wstrClassName.c_str()) == 0)
		{
			wstring wstrStateName = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrSkillTypeName = convertStrToWstr((*(++cellIter)).value<string>());
			bool cancelable = (*(++cellIter)).value<bool>();
			bool isPercentDamage = (*(++cellIter)).value<bool>();
			float damageValue= (*(++cellIter)).value<float>();
			float coolTime= (*(++cellIter)).value<float>();
			int quickCommand= mapKeyType_[convertStrToWstr((*(++cellIter)).value<string>())];

			vector<int> commandList;
			while ((*(++cellIter)).has_value())
			{
				commandList.push_back(mapKeyType_[convertStrToWstr((*cellIter).value<string>())]);
			}

			skill.insertSkillInfo(wstrStateName, (Skill::SKILLTYPE)mapSkillType_[wstrSkillTypeName], cancelable, isPercentDamage, damageValue, coolTime, quickCommand, commandList);
		}
	}
}

void ExcelLoader::loadEnemyData(const wchar_t * filePath, Entity * entity,  wstring name)
{

	Status& status = entity->getComponent<Status>();
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	StateMachine& stateMachine = entity->getComponent<StateMachine>();
	//Skill& skill = entity->getComponent<Skill>();

	xlnt::workbook wb;
	wb.load(filePath);
	xlnt::worksheet ws = wb.sheet_by_index(0);
	//스테이터스 데이터 로드
	for (auto& row : ws.rows(false))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		//맞는 이름 찾으면 status 데이터 넣기
		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());

		if (name == mapName_[wstrClassName])
		{
			//wstring wstrClassType = convertStrToWstr((*(++cellIter)).value<string>());

			Status::CLASSTYPE classType = Status::CLASSTYPE::ETC;
			double initHp = (*(++cellIter)).value<double>();
			double initMp = (*(++cellIter)).value<double>();
			double physicalAttack = (*(++cellIter)).value<double>();
			double physicalDefense = (*(++cellIter)).value<double>();
			double magicalAttack = (*(++cellIter)).value<double>();
			double magicalDefense = (*(++cellIter)).value<double>();
			double moveSpeed = (*(++cellIter)).value<double>();
			double attackSpeed = (*(++cellIter)).value<double>();
			double castingSpeed = (*(++cellIter)).value<double>();

			wstring wstrTexturePath = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrAtlasPath = convertStrToWstr((*(++cellIter)).value<string>());

			status.setStatus(classType, initHp, initMp, physicalAttack, physicalDefense, magicalAttack, magicalDefense, moveSpeed, attackSpeed, castingSpeed);
			anim.insertSprite(L"monster1", wstrTexturePath.c_str(), wstrAtlasPath.c_str());
			break;
		}
	}

	//애니메이션 모션 데이터 넣기
	ws = wb.sheet_by_index(1);
	for (auto& row : ws.rows(true))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());
		if (name == mapName_[wstrClassName])
		{
			wstring wstrMotionName = convertStrToWstr((*(++cellIter)).value<string>());

			int startIndex = (*(++cellIter)).value<int>();
			int endIndex = (*(++cellIter)).value<int>();

			anim.insertMotionData(L"monster1", wstrMotionName, startIndex, endIndex);
		}
	}


}

void ExcelLoader::loadItemData(const wchar_t * filePath, Entity * entity, wstring name)
{

	
	
	bool isImage = true;
	//Skill& skill = entity->getComponent<Skill>();

	xlnt::workbook wb;
	wb.load(filePath);
	xlnt::worksheet ws = wb.sheet_by_index(0);
	//스테이터스 데이터 로드
	for (auto& row : ws.rows(false))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		//맞는 이름 찾으면 status 데이터 넣기
		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());

		if (name == mapName_[wstrClassName])
		{

			entity->getComponent<Item>().price_= (*(++cellIter)).value<double>();
			entity->getComponent<Item>().kinds = (*(++cellIter)).value<double>();
			//wstring wstrClassType = convertStrToWstr((*(++cellIter)).value<string>());
			isImage= (*(++cellIter)).value<double>();
			
			//wstring wstrTexturePath = convertStrToWstr((*(++cellIter)).value<string>());
			//wstring wstrAtlasPath = convertStrToWstr((*(++cellIter)).value<string>());

			if (isImage)
			{
				wstring wstrTexturePath = convertStrToWstr((*(++cellIter)).value<string>());
				if (!entity->hasComponent<Sprite>())
					entity->addComponent<Sprite>(L"AtlasBuffer", L"TextureShader");
				entity->getComponent<Sprite>().insertTexture(wstrTexturePath.c_str());
			}
			else
			{
				if (!entity->hasComponent<AtlasAnimation>())
					entity->addComponent<AtlasAnimation>(L"AtlasBuffer", L"AtlasShader");


				wstring wstrTexturePath = convertStrToWstr((*(++cellIter)).value<string>());
				wstring wstrAtlasPath = convertStrToWstr((*(++cellIter)).value<string>());

				entity->getComponent<AtlasAnimation>().insertSprite(L"idle", wstrTexturePath.c_str(), wstrAtlasPath.c_str());
				entity->getComponent<AtlasAnimation>().changeCurrentSprite(L"idle");
			
				

			}
	
		}
	}

}

void ExcelLoader::loadOtherPlayerData(const wchar_t* filePath, Entity* entity, const wchar_t* className)
{
	AtlasAnimation& anim = entity->getComponent<AtlasAnimation>();
	xlnt::workbook wb;
	wb.load(filePath);
	xlnt::worksheet ws = wb.sheet_by_index(0);
	//스테이터스 데이터 로드
	for (auto& row : ws.rows(false))
	{
		if (!row.front().has_value())
			continue;

		auto& cellIter = row.begin();

		//맞는 이름 찾으면 status 데이터 넣기
		wstring wstrClassName = convertStrToWstr((*cellIter).value<string>());

		if (wcscmp(className, wstrClassName.c_str()) == 0)
		{
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			++cellIter;
			wstring wstrTexturePath = convertStrToWstr((*(++cellIter)).value<string>());
			wstring wstrAtlasPath = convertStrToWstr((*(++cellIter)).value<string>());

			anim.insertSprite(wstrClassName, wstrTexturePath.c_str(), wstrAtlasPath.c_str());
			break;
		}
	}
}

int ExcelLoader::getSceneNumberByName(const wchar_t* filePath, wstring sceneName)
{
	xlnt::workbook wb;
	wb.load(filePath);
	xlnt::worksheet ws = wb.sheet_by_index(0);
	//씬 데이터 확인
	for (auto& row : ws.rows(false))
	{
		if (!row.front().has_value())
			continue;
		auto& cellIter = row.begin();

		wstring wstrSceneName = convertStrToWstr((*cellIter).value<string>());
		if (wcscmp(sceneName.c_str(), wstrSceneName.c_str()) == 0)
		{
			return (*(++cellIter)).value<int>();
		}
	}
	return -1;
}

wstring ExcelLoader::getSceneNameByNumber(const wchar_t* filePath, int sceneNumber)
{
	xlnt::workbook wb;
	wb.load(filePath);
	xlnt::worksheet ws = wb.sheet_by_index(0);
	//씬 데이터 확인
	for (auto& row : ws.rows(false))
	{
		if (!row.front().has_value())
			continue;
		auto& cellIter = row.rbegin();
		
		int cellSceneNumber = (*cellIter).value<int>();
		if (cellSceneNumber==sceneNumber)
		{
			wstring wstrSceneName = convertStrToWstr((*(++cellIter)).value<string>());
			return wstrSceneName;
		}
	}

	return L"";
}
