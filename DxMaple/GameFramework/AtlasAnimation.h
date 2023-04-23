#pragma once
#include "ECS.h"
#include "AtlasLoader.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"
#include <variant>
//��Ʋ�� ���� ������Ʈ
class AtlasAnimation:public Component
{
public:
	AtlasAnimation(wstring bufferName,wstring shaderName); //�����̸�, ���̴� �̸�
	virtual ~AtlasAnimation();


	HRESULT setBuffer(wstring bufferName);
	HRESULT setShader(wstring shaderName);
	HRESULT insertSprite(wstring spriteName, const wchar_t* spritePath, const wchar_t* atlasPath); //��������Ʈ �̸�, �ؽ��� ���, ��Ʋ�� ������ ���
	HRESULT insertMotionData(wstring spriteName, wstring motionName, int startIndex, int endIndex); //��������Ʈ �̸�, ��� �̸�, ���� �ε���, �� �ε���
	HRESULT changeCurrentSprite(wstring spriteName); //�ش� �̸��� ��������Ʈ�� ��ü
	HRESULT changeMotion(wstring motionName); //��� ü����
	void	setAnimationSpeed(float speed) { animationSpeed_ = speed; } //�ִϸ��̼� ���ǵ� ����
	void	setRight(bool isRight) { isRight_ = isRight; } //��������Ʈ �¿� ���� ����
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
	//���� ���ӽð�, ���� ���� ���� Ʈ���� �Լ� ����
	void	stopAnimation(float duration,function<void()> stopEndTrigger);
	void	resumeAnimation();
	void	PauseAnimation();
	
	//���̴� value�� make_pair("���̴��������� �̸�", ������) ���·� �ִ´�. ��� �־ �������
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
	// Component��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
private:
	////���̴� ������
	//HRESULT setAtlasUV(int atlasIndex); 
	//HRESULT setWorldMatrix(const _vec3& position, const _vec3& rotation, const _vec3& scale);

	//���̴� ������
	HRESULT readyAtlasValues();
	HRESULT readyTransforms(int row, int col);
	HRESULT readyTransformsNotZRender(int row, int col);
	HRESULT readyPreShaderValues();

	HRESULT setShaderValuesAll();
private:
	mutex animLock_;
	LPDIRECT3DDEVICE9	device_;

	unordered_map<wstring, vector<tuple<wstring, int, int>>> mapSpriteIndexData_;//Ű : ��������Ʈ �̸�, �� : (��� �̸�, ���� �ε���,�� �ε���)
	unordered_map<wstring, pair<weak_ptr<Texture>, Atlas::ATLASINFO>> mapSprites_;//��������Ʈ ������ ����
	wstring				currentSpriteName_;
	wstring				currentMotionName_;
	float				animationSpeed_;
	float				baseAnimationSpeed_;
	
	//���� �������� ��������Ʈ ����
	float				startSpriteIndex_;
	float				endSpriteIndex_;
	float				currentSpriteIndex_;
	//resourceManagement���� ������
	weak_ptr<Buffer>	buffer_;		
	weak_ptr<Shader>	shader_;

	_vec2 userPivot_;
	//���̴� value�� ����. render �� ��, �Ѳ����� ����
	map<const char*, variant<bool, int, float, double, _vec2, _vec3, _mat>> mapShaderValues_;
	bool isRight_;
	int row_ = 1, col_ = 1;
	float spacing_ = 1.f;
	_vec3 addPos_=_vec3(0.f,0.f,0.f);
	

	//��������Ʈ �Ͻ�����
	bool isStop = false;
	function<void()> stopEndTrigger_;
	float stopTimer = 0.f;
	float stopDuration = 0.f;
	bool isPause = false;
public:
	//���� ���� ����
	float interSpriteIndex_;
	bool isInterpolate_;

	//z�� ���� ���� ����. y = y+z
	bool isZRender;

	DWORD destBlendOp_;
	DWORD srcBlendOp_;
	bool blendEnable_;
};

