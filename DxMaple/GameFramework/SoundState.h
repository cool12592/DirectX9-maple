#pragma once
#include "IState.h"
#include "Sound.h"
BEGIN(SoundState)
	enum Transition { IDLE, WALK, DASH, JUMP, ATTACK, HIT };

	class Idle :public IState
	{
	public:
		static Idle instance;
		// IState을(를) 통해 상속됨
		virtual void enter(Entity* entity) override
		{
			Sound& sound = entity->getComponent<Sound>();
			sound.initialize();
			
			//sound.CreateBGSound();
		}
		virtual void update(Entity* entity) override
		{
			Sound& sound = entity->getComponent<Sound>();
			sound.PlaySoundBG();
			sound.update();

		}
		virtual void exit(Entity* entity) override
		{
			Sound& sound = entity->getComponent<Sound>();
			sound.release();
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
			Sound& sound = entity->getComponent<Sound>();
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
			Sound& sound = entity->getComponent<Sound>();
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
			Sound& sound = entity->getComponent<Sound>();
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
			Sound& sound = entity->getComponent<Sound>();
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