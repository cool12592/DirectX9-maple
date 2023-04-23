#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif


#define SCREEN_WIDTH 1152
#define SCREEN_HEIGHT 864
#define MAX_KEY_COUNT 256
#define MAX_COMPONENT_COUNT 64

#define DEFAULT_NEAR_DISTANCE 0.1
#define DEFAULT_FAR_DISTANCE 10000

#define MAX_KEYBOARD_QUEUESIZE 5
#define KEYBOARD_QUEUE_POP_TIMER 0.2f
//status define
#define DEFAULT_SUPERARMOR_DURATION 10.f
//rigidbody define
#define DRAG_LIMIT 10000.f
#define JUMP_FORCE 250.f
#define DEFAULT_MOVE_SPEED 200.f
#define ATTACK_ACCEL 200.f
#define DEFAULT_DAMAGE_FORCE 100.f

//transform define
#define INTERPOLATE_SPEED 25.f

//Camera define
#define CAMERA_INTERPOLATE_SPEED 10.f

//AtlasAnimation Define
#define DEFAULT_USER_PIVOT_X 245.f
#define DEFAULT_USER_PIVOT_Y 390.f
#define DEFAULT_ANIMATION_SPEED 10.f
#define CAN_ATTACK_DELAY 0.4f
#define INFINITE_STOP 100000.f
#define BACKSTEP_FORCE 200.f

//Statemachine define
#define JILPOONGGAK_ROTATE_COUNT 6
#define BOONGGWON_ACCEL 800.f
#define HOVERSTOMP_STOP_TIMER 0.2f
#define HOVERSTOMP_ACCEL -30.f
#define RISINGKNUCKLE_UP_ACCEL 800.f
#define RISINGKNUCKLE_DOWN_ACCEL -1000.f
#define LIGHTENINGDANCE_DELAY 0.2f
#define LIGHTENINGDANCE_MAX_HITCOUNT 10
#define PLAYER_SEARCH_DISTNACE 400.f
#define BITDRIVE_ACCEL 200.f
#define BITDRIVE_TIMER 3.f
#define MAX_CHARGE_TIMER 5.f
#define ONEINCHPUNCH_DELAY 1.f

#define MAX_BUF 256
#define mandarinZ -120.f

#define LOBBY_READY_TIMER 5.f


#define DEFAULT_TAG L"unnamed"
#define DEFAULT_NAME L""
/*assert(trueSituation&&message);*/
#ifndef WIN64
#define ASSERT_MESSAGE(trueSituation,message) {if((trueSituation)==false){MessageBoxA(nullptr,message,"Assert Message",MB_OK);_asm{int 3};}}
#define ASSERT_MESSAGE_RETURN(trueSituation,message,returnValue) {if((trueSituation)==false){MessageBoxA(nullptr,message,"Assert Message",MB_OK);_asm{int 3};return returnValue;}}
#define ASSERT_MESSAGE_NULLRETURN(trueSituation,message) {if((trueSituation)==false){MessageBoxA(nullptr,message,"Assert Message",MB_OK);_asm{int 3};return;}}
#else
#define ASSERT_MESSAGE(trueSituation,message) {if((trueSituation)==false){MessageBoxA(nullptr,message,"Assert Message",MB_OK);}}
#define ASSERT_MESSAGE_RETURN(trueSituation,message,returnValue) {if((trueSituation)==false){MessageBoxA(nullptr,message,"Assert Message",MB_OK);return returnValue;}}
#define ASSERT_MESSAGE_NULLRETURN(trueSituation,message) {if((trueSituation)==false){MessageBoxA(nullptr,message,"Assert Message",MB_OK);return;}}
#endif
#define BEGIN(NameSpace) namespace NameSpace {
#define END	}
#define USING(NameSpace) using namespace NameSpace;

#define DECLARE_SINGLETON(Classname)	public: static Classname* getInstance(){	\
													if(nullptr==instance)			\
														instance=new Classname;		\
													return instance; }				\
												void destroyInstance(){				\
													if(nullptr!=instance){			\
														delete instance;			\
														instance=nullptr;			\
													}}								\
										private: Classname(const Classname&);		\
												 Classname& operator=(const Classname&);\
										private: static Classname* instance;

#define IMPLEMENT_SINGLETON(Classname)	Classname* Classname::instance=nullptr;


