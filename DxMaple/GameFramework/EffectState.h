#pragma once
#include "IState.h"
#include "Effect.h"

BEGIN(EffectState)
	enum Transition { IDLE, WALK, DASH, JUMP, ATTACK, HIT };

	class Idle :public IState
	{
	public:
		static Idle instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//effect.initialize();
		}
		virtual void update(Entity* entity) override
		{
			Effect& effect = entity->getComponent<Effect>();

		}
		virtual void exit(Entity* entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//
		}

	};
	Idle Idle::instance;

	class Walk :public IState
	{
	public:
		static Walk instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity * entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//sound.changeCurrentSprite(L"Move");
		}

		virtual void update(Entity * entity) override
		{

		}

		virtual void exit(Entity * entity) override
		{

		}

	};
	Walk Walk::instance;

	class Dash :public IState
	{
	public:
		static Dash instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity * entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//sound.changeCurrentSprite(L"Move");
		}

		virtual void update(Entity * entity) override
		{

		}

		virtual void exit(Entity * entity) override
		{

		}

	};
	Dash Dash::instance;

	class Jump :public IState
	{
	public:
		static Jump instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//effect.changeCurrentSprite(L"jump");
		}
		virtual void update(Entity* entity) override
		{

		}
		virtual void exit(Entity* entity) override
		{

		}

	};
	Jump Jump::instance;

	class Attack :public IState
	{
	public:
		static Attack instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity * entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//effect.changeCurrentSprite(L"attack");
		}

		virtual void update(Entity * entity) override
		{

		}

		virtual void exit(Entity * entity) override
		{

		}

	};
	Attack Attack::instance;


	class Hit :public IState
	{
	public:
		static Hit instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity * entity) override
		{
			Effect& effect = entity->getComponent<Effect>();
			//effect.changeCurrentSprite(L"hit");
		}

		virtual void update(Entity * entity) override
		{

		}

		virtual void exit(Entity * entity) override
		{

		}

	};
	Hit Hit::instance;
END
