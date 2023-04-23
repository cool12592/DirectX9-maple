#pragma once
#include "ECS.h"

#include "ComponentsHeader.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "DeviceManager.h"
class MonoBehaviour :
	public Component
{
public:
	MonoBehaviour() { }
	virtual ~MonoBehaviour() {}

	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void lateUpdate() = 0;
	virtual void render() = 0;
	virtual void release() = 0;

public:
	//매니저 편하게 쓰기 위함
	static InputManager& Input;
	static TimeManager& Time;
	static DeviceManager& Device;
};

