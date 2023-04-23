#include "stdafx.h"
#include "MonoBehaviour.h"

InputManager& MonoBehaviour::Input = *InputManager::getInstance();
TimeManager& MonoBehaviour::Time = *TimeManager::getInstance();
DeviceManager& MonoBehaviour::Device = *DeviceManager::getInstance();