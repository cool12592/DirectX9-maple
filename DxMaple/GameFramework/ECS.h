#pragma once
#include <vector>
#include <list>
#include <unordered_map>
#include <map>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Define.h"
#include "Extern.h"

class Component;
class Entity;

using ComponentID = size_t;

inline ComponentID getComponentID()
{
	static ComponentID lastID = 0;
	return lastID++;
}

template<typename T>
inline ComponentID getComponentID() noexcept
{
	static ComponentID typeID = getComponentID();
	return typeID;
}

constexpr size_t maxComponents = MAX_COMPONENT_COUNT;
using ComponentBitset = bitset<maxComponents>;
using ComponentArray = array<Component*, maxComponents>;

class Component
{
public:
	Component() {}
	virtual ~Component() {}

	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void lateUpdate() = 0;
	virtual void render() = 0;
	virtual void release() = 0;
	Entity* entity;
};

class Entity
{
public:
	enum class ENTITYTYPE { UNKNOWN = 0, PLAYER, ENEMY, DNFUI, MAP, TRAP, EFFECT,ENEMYEFFECT,GOLD,ITEM,FILDITEM };
public:
	explicit Entity() 
	{ 
		name = L""; 
		active = true;
		//userIDN = NetworkManager::getInstance()->getUserIDN();
		entityNumber = globalEntityNumber++;
		entityType = ENTITYTYPE::UNKNOWN;
	} 
	explicit Entity(const Entity&) = delete;
	virtual ~Entity() {}
	void setUserIDN(int _userIDN)
	{
		userIDN = _userIDN;
	}
	void setEntityNumber(int _entityNumber)
	{
		entityNumber = _entityNumber;
	}
	void setTypeAndName(ENTITYTYPE _entityType, wstring _name)
	{
		name = _name;
		entityType = _entityType;
	}
	
	void setActive(bool _active)
	{
		active = _active;
	}
	void setEntityNumber(u_int _entityNumber) { entityNumber = _entityNumber; }
	ENTITYTYPE getType() { return entityType; }
	wstring getName() { return name; }

	void getEntityNetworkInfo(OUT int& _userIDN, OUT int& _entityNumber, OUT ENTITYTYPE& _entityType)
	{
		_userIDN = userIDN;
		_entityNumber = entityNumber;
		_entityType = entityType;
	}
public:
	void update()
	{
		for (auto& component : components)
		{
			component->update();
		}
	}
	void lateUpdate()
	{
		for (auto& component : components)
		{
			component->lateUpdate();
		}
	}
	void render()
	{
		for (auto& component : components)
		{
			component->render();
		}
	}
	bool isActive()const { return active; }
	void destroy() { active = false; }

	template<typename T>
	bool hasComponent()const
	{
		return componentBitset[getComponentID<T>()];
	}
	template<typename T,typename... TArgs>
	T& addComponent(TArgs&&... _args)
	{
		T* component(new T(std::forward<TArgs>(_args)...)); //완벽전달
		component->entity = this;
		unique_ptr<Component> ptr(component);
		components.emplace_back(std::move(ptr)); //emplace라 그냥 component만 줘도 될듯 (emplace는 인자만주면되거든)

		componentArray[getComponentID<T>()] = component;
		componentBitset[getComponentID<T>()] = true;
		
		component->initialize();
		return *component;
	}
	

	template<typename T>
	T& getComponent()const
	{
		auto ptr(componentArray[getComponentID<T>()]);
		return *static_cast<T*>(ptr);
	}
	//왠만하면 쓰지 말자
	void eraseAllComponents()
	{
		components.clear();
		componentBitset.reset();
		for (auto& component : componentArray)
		{
			component = nullptr; //실 인스턴스는 위위에서 지워짐
		}
	}
private:
	bool active = true;
	wstring name;

	int userIDN;
	int entityNumber;
	ENTITYTYPE entityType;

	vector<unique_ptr<Component>> components;
	ComponentArray componentArray;
	ComponentBitset componentBitset;
};
