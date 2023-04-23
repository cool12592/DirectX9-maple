#pragma once
class Entity;
class IState;
using ClassTypeMap = unordered_map<wstring, int>;
using StateMap = unordered_map<wstring, IState*>;
using TransitionMap = unordered_map<wstring, int>;
using keyTypeMap = unordered_map<wstring, int>;
using SkillTypeMap = unordered_map<wstring, int>;
using NameMap = unordered_map<wstring, wstring>;

class ExcelLoader
{
public:
	static void initialize();
	static void loadPlayerData(const wchar_t* filePath,Entity* entity,const wchar_t* className);
	static void loadEnemyData(const wchar_t* filePath, Entity* entity, wstring name);
	static void loadItemData(const wchar_t* filePath, Entity* entity, wstring name);

	static void loadOtherPlayerData(const wchar_t* filePath, Entity* entity, const wchar_t* className);
	static int getSceneNumberByName(const wchar_t* filePath, wstring sceneName);
	static wstring getSceneNameByNumber(const wchar_t* filePath, int sceneNumber);


private:
	static ClassTypeMap mapClassType_;
	static StateMap mapState_;
	static TransitionMap mapTransition_;
	static keyTypeMap mapKeyType_;
	static SkillTypeMap mapSkillType_;
	static NameMap mapName_;
};
