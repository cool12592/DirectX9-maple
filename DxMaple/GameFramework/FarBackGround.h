#pragma once
#include "MapBasic.h"

class FarBackGround :
	public MapBasic
{
public:
	FarBackGround() {}
	~FarBackGround() {}
	FarBackGround(int type) { type_ = type; }

	virtual void initialize() override;
	virtual void update() override;
	_vec2 mapSize_;
	bool nextMapReady = false;
private:
	int type_;
	vector <wstring> ani = { L"0",L"1",L"2",L"3" ,L"4" ,L"5" ,L"6" ,L"7" ,L"8" ,L"9" ,L"10" ,L"11" ,L"12" ,L"13" ,L"14" };
	vector <wstring> ani2 = { L"15",L"16",L"17",L"18" ,L"19" ,L"20" ,L"21" ,L"22" ,L"23" ,L"24" ,L"25" ,L"26" ,L"27" ,L"28" ,L"29" };
	int page_ = 1;

	shared_ptr<Entity> crimsonEntity[2];


};