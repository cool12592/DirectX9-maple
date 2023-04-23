#pragma once
#include <cmath>
#include "Typedef.h"
BEGIN(ws)
class Math
{
public:
	static _vec3 divideVector(const _vec3& targetVec, const _vec3& divideVec);
	static _vec3 clampVector(_vec3 targetVec, _vec3 firstVec, _vec3 secondVec);
	static _vec3 clampVectorExceptY(_vec3 targetVec, _vec3 firstVec, _vec3 secondVec);
	static float lerp(float srcValue, float destValue, float dt);

	static _mat calculateWorldMatrix2D(const _vec3& position, const _vec3& rotation, const _vec3& scale);

	//기준 벡터는 보통 x축 양의 방향(1.f,0.f,0.f)
	static float calculateAngle2D(const _vec3& standardVector, const _vec3& targetVector);
};

END