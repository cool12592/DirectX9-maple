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
	//�Ŵ��� ���ϰ� ���� ����
	static InputManager& Input;
	static TimeManager& Time;
	static DeviceManager& Device;
};

