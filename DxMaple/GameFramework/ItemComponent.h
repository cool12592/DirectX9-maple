#pragma once
#include "ECS.h"

class ItemComponent :
	public Component
{
	
public:



	// Component을(를) 통해 상속됨
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



	//가변인자 템플릿(인자제한없음) 
	//...은제한없음 
	//처음껀...없으니까 인자로하나는 무조건줘야됨
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
	//아이템명과 드랍확률
	vector<wstring> myitem;


};

