#pragma once
#include "ECS.h"
#include "AtlasLoader.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include <variant>
//아틀라스 전용 컴포넌트
class AtlasAnimation:public Component
{
public:
	AtlasAnimation(wstring bufferName,wstring shaderName); //버퍼이름, 셰이더 이름
	virtual ~AtlasAnimation();


	HRESULT setBuffer(wstring bufferName);
	HRESULT setShader(wstring shaderName);
	HRESULT insertSprite(wstring spriteName, const wchar_t* spritePath, const wchar_t* atlasPath); //스프라이트 이름, 텍스쳐 경로, 아틀라스 데이터 경로
	HRESULT insertMotionData(wstring spriteName, wstring motionName, int startIndex, int endIndex); //스프라이트 이름, 모션 이름, 시작 인덱스, 끝 인덱스
	HRESULT changeCurrentSprite(wstring spriteName); //해당 이름의 스프라이트로 교체
	HRESULT changeMotion(wstring motionName); //모션 체인지
	void	setAnimationSpeed(float speed) { animationSpeed_ = speed; } //애니메이션 스피드 세팅
	void	setRight(bool isRight) { isRight_ = isRight; } //스프라이트 좌우 반전 여부
	void	setUserPivot(_vec2 pivot) { userPivot_ = pivot; }
	void    SetMultiple(int row, int col) { row_ = row; col_ = col; }
	void    SetNotMultiple() { row_ = 1; col_ = 1; }
	void    setSpacing(float space) { spacing_ = space; }
	void    setAddPos(_vec3 addpos) { addPos_ = addpos; }
	void	setCurrentIndex(float index);
	wstring    getCurrentAnim();
	wstring		getCurrentMotionName();
	_vec2   getAltInfo();
	bool	getIsRight() { return isRight_; }
	float	getCurrentIndex() { return currentSpriteIndex_; }
	_vec2	getUserPivot()const { return userPivot_; }

	bool	isSpriteEnd();
	bool	isStopState() { return isStop; }
	//멈춤 지속시간, 멈춤 끝난 이후 트리거 함수 연결
	void	stopAnimation(float duration,function<void()> stopEndTrigger);
	void	resumeAnimation();
	void	PauseAnimation();
	
	//셰이더 value를 make_pair("셰이더전역변수 이름", 변수값) 형태로 넣는다. 몇개를 넣어도 상관없음
	HRESULT readyShaderValues()
	{
		return S_OK;
	}
	template<typename ValuePair>
	HRESULT readyShaderValues(ValuePair& valuePair)
	{
		ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader is not set", E_FAIL);
		auto& find_iter = mapShaderValues_.find(valuePair.first);
		if (mapShaderValues_.end() != find_iter)
			mapShaderValues_[valuePair.first] = valuePair.second;
		else
			mapShaderValues_.emplace(valuePair.first, valuePair.second);
		return S_OK;
	}

	template<typename ValuePair, typename... ValuePairs>
	HRESULT readyShaderValues(ValuePair valuePair, ValuePairs... valuePairs)
	{
		ASSERT_MESSAGE_RETURN(!shader_.expired(), "shader is not set", E_FAIL);
		auto& find_iter = mapShaderValues_.find(valuePair.first);
		if (mapShaderValues_.end() != find_iter)
			mapShaderValues_[valuePair.first] = valuePair.second;
		else
			mapShaderValues_.emplace(valuePair.first, valuePair.second);

		//ASSERT_MESSAGE_RETURN(mapShaderValues_.end() == find_iter, "value name already exist", E_FAIL);
		if (FAILED(readyShaderValues(valuePairs...)))
			return E_FAIL;
		return S_OK;
	}
	// Component을(를) 통해 상속됨
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
private:
	////셰이더 없을때
	//HRESULT setAtlasUV(int atlasIndex); 
	//HRESULT setWorldMatrix(const _vec3& position, const _vec3& rotation, const _vec3& scale);

	//셰이더 있을때
	HRESULT readyAtlasValues();
	HRESULT readyTransforms(int row, int col);
	HRESULT readyTransformsNotZRender(int row, int col);
	HRESULT readyPreShaderValues();

	HRESULT setShaderValuesAll();
private:
	mutex animLock_;
	LPDIRECT3DDEVICE9	device_;

	unordered_map<wstring, vector<tuple<wstring, int, int>>> mapSpriteIndexData_;//키 : 스프라이트 이름, 값 : (모션 이름, 시작 인덱스,끝 인덱스)
	unordered_map<wstring, pair<weak_ptr<Texture>, Atlas::ATLASINFO>> mapSprites_;//스프라이트 데이터 보관
	wstring				currentSpriteName_;
	wstring				currentMotionName_;
	float				animationSpeed_;
	float				baseAnimationSpeed_;
	
	//현재 진행중인 스프라이트 정보
	float				startSpriteIndex_;
	float				endSpriteIndex_;
	float				currentSpriteIndex_;
	//resourceManagement에서 가져옴
	weak_ptr<Buffer>	buffer_;		
	weak_ptr<Shader>	shader_;

	_vec2 userPivot_;
	//셰이더 value들 보관. render 할 때, 한꺼번에 세팅
	map<const char*, variant<bool, int, float, double, _vec2, _vec3, _mat>> mapShaderValues_;
	bool isRight_;
	int row_ = 1, col_ = 1;
	float spacing_ = 1.f;
	_vec3 addPos_=_vec3(0.f,0.f,0.f);
	

	//스프라이트 일시정지
	bool isStop = false;
	function<void()> stopEndTrigger_;
	float stopTimer = 0.f;
	float stopDuration = 0.f;
	bool isPause = false;
public:
	//선형 보간 변수
	float interSpriteIndex_;
	bool isInterpolate_;

	//z값 적용 렌더 여부. y = y+z
	bool isZRender;

	DWORD destBlendOp_;
	DWORD srcBlendOp_;
	bool blendEnable_;
};

