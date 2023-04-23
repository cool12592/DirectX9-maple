#pragma once
#include "ECS.h"

class ItemComponent :
	public Component
{
	
public:



	// Component��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	



	HRESULT ownItem()
	{
		return S_OK;
	}

	template<typename ValuePair>
	HRESULT ownItem(ValuePair& valuePair)
	{
		int random = (rand() % 100) + 1;

		if (random <= valuePair.second)
			myitem.emplace_back(valuePair.first);


		return S_OK;
	}



	//�������� ���ø�(�������Ѿ���) 
	//...�����Ѿ��� 
	//ó����...�����ϱ� ���ڷ��ϳ��� ��������ߵ�
	template<typename ValuePair, typename... ValuePairs>
	HRESULT ownItem(ValuePair valuePair, ValuePairs... valuePairs)
	{

		int random = (rand() % 100)+1;
		
		if(random<= valuePair.second)
		myitem.emplace_back(valuePair.first);


		if (FAILED(ownItem(valuePairs...)))
			return E_FAIL;
		return S_OK;

	}

	void dropItem();
	


private:
	//�����۸�� ���Ȯ��
	vector<wstring> myitem;


};

