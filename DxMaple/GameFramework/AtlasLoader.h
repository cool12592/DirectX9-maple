#pragma once
#include "stdafx.h"
namespace Atlas
{
	typedef struct tagFrame
	{
		int x, y, w, h;
	}FRAME;

	typedef struct tagSpriteSourceSize
	{
		int x, y, w, h;
	}SPRITESOURCESIZE;
	typedef struct tagSourceSize
	{
		int w, h;
	}SOURCESIZE;
	typedef struct tagPivot
	{
		float x, y;
	}PIVOT;
	typedef struct tagFrameInfo
	{
		string frameName;
		FRAME frame;
		bool rotated;
		bool trimmed;
		SPRITESOURCESIZE spriteSourceSize;
		SOURCESIZE sourceSize;
		PIVOT pivot;
	}FRAMEINFO;
	typedef struct tagMeta
	{
		string imageName;
		SOURCESIZE size;
	}META;

	//최종 구조체
	typedef struct tagAtlasInfo
	{
		vector<FRAMEINFO> frames;
		META meta;
	}ATLASINFO;

	static HRESULT loadAtlasInfo(OUT ATLASINFO& outputInfo, const wchar_t* path)
	{
		ifstream fin;
		Json::Value root;
		Json::CharReaderBuilder rbuilder;
		string strErr;
		bool isSuccess;

		fin.open(path, ios::binary);
		ASSERT_MESSAGE_RETURN(!fin.fail(), "atlas json file does not exist",E_FAIL);

		isSuccess = Json::parseFromStream(rbuilder, fin, &root, &strErr);
		ASSERT_MESSAGE_RETURN(isSuccess, "json parsing failed",E_FAIL);

		auto& frames = root["frames"];
		auto& meta = root["meta"];
		int i = 0;
		for (const auto& frameName : frames.getMemberNames())
		{
			auto& frame = frames[frameName];
			FRAMEINFO frameInfo;
			frameInfo.frameName = frameName.c_str();
			auto& frameData = frame["frame"];
			auto& spriteSourceSizeData = frame["spriteSourceSize"];
			auto& sourceSizeData = frame["sourceSize"];
			auto& pivotData= frame["pivot"];
			frameInfo.frame.x = frameData["x"].asInt();
			frameInfo.frame.y = frameData["y"].asInt();
			frameInfo.frame.w = frameData["w"].asInt();
			frameInfo.frame.h = frameData["h"].asInt();
			frameInfo.rotated = frame["rotated"].asBool();
			frameInfo.trimmed = frame["trimmed"].asBool();
			frameInfo.spriteSourceSize.x = spriteSourceSizeData["x"].asInt();
			frameInfo.spriteSourceSize.y = spriteSourceSizeData["y"].asInt();
			frameInfo.spriteSourceSize.w = spriteSourceSizeData["w"].asInt();
			frameInfo.spriteSourceSize.h = spriteSourceSizeData["h"].asInt();
			frameInfo.sourceSize.w = sourceSizeData["w"].asInt();
			frameInfo.sourceSize.h = sourceSizeData["h"].asInt();
			frameInfo.pivot.x = pivotData["x"].asFloat();
			frameInfo.pivot.y = pivotData["y"].asFloat();

			outputInfo.frames.push_back(frameInfo);
		}
		outputInfo.meta.imageName = meta["image"].asCString();
		outputInfo.meta.size.w = meta["size"]["w"].asInt();
		outputInfo.meta.size.h = meta["size"]["h"].asInt();

		fin.close();

		return S_OK;
	}
}
