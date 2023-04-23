#pragma once
#include "ECS.h"
class Skill :
    public Component
{
public:
    enum class SKILLTYPE{GROUND,JUMP};
    enum class GETTYPE{SKILLTYPE = 0,CANCELABLE,ISPERCENT,DAMAGEVALUE,COOLTIME,CURRENTTIME,QUICKCOMMAND,COMMANDLIST,GETTYPE_END};
public:
    bool checkSkillAvailableAndExecute();
private:
    template<typename CommandKey>
    void setCommandInfo(wstring stateName, CommandKey commandkey)
    {
        get<(int)Skill::GETTYPE::COMMANDLIST>(mapSkills_[stateName]).push_back(commandkey);
    }

    template<typename CommandKey,typename... CommandKeys>
    void setCommandInfo(wstring stateName, CommandKey commandkey, CommandKeys... commandkeys)
    {
        get<(int)Skill::GETTYPE::COMMANDLIST>(mapSkills_[stateName]).push_back(commandkey);
        setCommandInfo(stateName, commandkeys...);
    }
public:
    template<typename... CommandKeys>
    HRESULT insertSkillInfo(wstring stateName, SKILLTYPE skillType, bool cancelable, bool isPercentDamage, float damageValue,float cooltime, int quickCommand, CommandKeys... commandKeys)
    {
#ifdef _DEBUG
        auto& find_iter = mapSkills_.find(stateName);
        ASSERT_MESSAGE_RETURN(mapSkills_.end() == find_iter, "Skill info already exist", E_FAIL);
#endif
        mapSkills_.emplace(stateName, make_tuple(skillType, cancelable, isPercentDamage, damageValue,cooltime, cooltime, quickCommand, vector<int>()));
        setCommandInfo(stateName, commandKeys...);
        return S_OK;
    }

    HRESULT insertSkillInfo(wstring stateName, SKILLTYPE skillType, bool cancelable, bool isPercentDamage, float damageValue, float cooltime, int quickCommand, vector<int> commandList);

    variant<SKILLTYPE, bool, float, int, vector<int>> getSkillInfo(const wstring stateName, Skill::GETTYPE getType)
    {
#ifdef _DEBUG
        auto& find_iter = mapSkills_.find(stateName);
        ASSERT_MESSAGE(mapSkills_.end() != find_iter, "Skill info does not exist");
        //ASSERT_MESSAGE(getType != Skill:GETTYPE::GETTYPE_END, "get type value exceed");
#endif
        switch (getType)
        {
        case Skill::GETTYPE::SKILLTYPE:
            return get<(int)Skill::GETTYPE::SKILLTYPE>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::CANCELABLE:
            return get<(int)Skill::GETTYPE::CANCELABLE>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::ISPERCENT:
            return get<(int)Skill::GETTYPE::ISPERCENT>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::DAMAGEVALUE:
            return get<(int)Skill::GETTYPE::DAMAGEVALUE>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::COOLTIME:
            return get<(int)Skill::GETTYPE::COOLTIME>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::CURRENTTIME:
            return get<(int)Skill::GETTYPE::CURRENTTIME>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::QUICKCOMMAND:
            return get<(int)Skill::GETTYPE::QUICKCOMMAND>(mapSkills_[stateName]);
            break;
        case Skill::GETTYPE::COMMANDLIST:
            return get<(int)Skill::GETTYPE::COMMANDLIST>(mapSkills_[stateName]);
            break;
      
        }
    }

    float getCooltime(const wstring stateName);
    float getCurrentTime(const wstring stateName);
    bool getIsPercent(const wstring stateName);
    float getDamageValue(const wstring stateName);
public:
    // Component을(를) 통해 상속됨
    virtual void initialize() override;
    virtual void update() override;
    virtual void lateUpdate() override;
    virtual void render() override;
    virtual void release() override;
private:
    //키: 상태이름, 값 : 스킬타입, 캔슬가능여부, 퍼뎀/고뎀 여부, 퍼센트or데미지,스킬쿨타임,현재쿨타임 단축기, 커맨드키
    unordered_map<wstring, tuple<SKILLTYPE, bool, bool, float,float,float, int, vector<int>>> mapSkills_;
};

