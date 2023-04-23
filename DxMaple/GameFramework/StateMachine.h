#pragma once
#include "ECS.h"
#include "IState.h"
class StateMachine :
	public Component
{
public:
	StateMachine() {}
	//make_pair("�����̸�",&��������Ŭ����) ���·� �ֱ�
	template<typename PairNameState,typename... PairNameStates>
	StateMachine(PairNameState pairState,PairNameStates... pairStates):StateMachine(pairStates...)
	{
		auto& find_iter = mapStates_.find(pairState.first);
		ASSERT_MESSAGE(mapStates_.end() == find_iter, "state name already exist");
		
		if (mapStates_.empty())
		{
			mapStates_.emplace(pairState.first, pairState.second);
			currentStateName = pairState.first;
		}
		else
			mapStates_.emplace(pairState.first, pairState.second);

	}
	virtual ~StateMachine();

	// Component��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void release() override;

public:
	

	HRESULT insertState(wstring stateName, IState* state);

	//(���ۻ���-����->��������) ���� �ֱ�
	HRESULT insertTransitionCondition(wstring firstStateName, int transitionCondition, wstring secondStateName);
	HRESULT transitionState(int transitionCondition); //���� ���¿� ���ǿ� �´� ���°� ������ ��ȯ
	HRESULT changeState(wstring stateName); //�ش� �̸��� ���·� ��ȯ
	//IState* getCurrentState()const; �̰� �ʿ������ ������...

	wstring getCurrentStateName()const { return currentStateName; }
public:
	//�̰� �Ⱦ���
	virtual void lateUpdate() override;
	virtual void render() override;

private:
	wstring currentStateName; //���� ���� �̸�
	unordered_map<wstring, IState*> mapStates_; //���� �̸�, ���� ������
	vector<tuple<wstring, int, wstring>> vecTransitions_;//���� ����,���� ����,�ٲ� ����
};

