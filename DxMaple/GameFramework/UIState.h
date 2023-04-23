#pragma once
#include "IState.h"
//+FontState
BEGIN(UIState) 

enum Transition { IDLE = 0, MOVE, Timer, LEFT, RIGHT, ON, OFF,};

	class Idle :public IState
	{
	public:
		static Idle instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{

			//DNFUI.changeCurrentSprite(L"stick");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	//Idle Idle::instance;

	class Move :public IState
	{
	public:
		static Move instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity * entity) override
		{

			//DNFUI.changeCurrentSprite(L"movable");
		}

		virtual void update(Entity * entity) override
		{

		}

		virtual void exit(Entity * entity) override
		{

		}

	};
	//Move Move::instance;

	class Timer :public IState
	{
	public:
		static Timer instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{

			//DNFUI.changeCurrentSprite(L"stick");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	//Timer Timer::instance;

	class Left :public IState
	{
	public:
		static Left instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{

			//DNFUI.changeCurrentSprite(L"stick");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	//Click Click::instance;
	class Right :public IState
	{
	public:
		static Right instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{

			//DNFUI.changeCurrentSprite(L"stick");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	//Click Click::instance;

	class On :public IState
	{
	public:
		static On instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{

			//DNFUI.changeCurrentSprite(L"stick");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	//On On::instance;

	class Off :public IState
	{
	public:
		static Off instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{

			//DNFUI.changeCurrentSprite(L"stick");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	//On On::instance;



END