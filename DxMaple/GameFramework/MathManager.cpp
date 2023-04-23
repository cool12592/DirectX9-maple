#include "stdafx.h"
#include "MathManager.h"
USING(ws)
_vec3 Math::divideVector(const _vec3& targetVec, const _vec3& divideVec)
{
    _vec3 resultVec = { 0.f,0.f,0.f };
    
    if (divideVec.x != 0.f)
        resultVec.x = targetVec.x / divideVec.x;
    else
        resultVec.x = targetVec.x;

    if (divideVec.y != 0.f)
        resultVec.y = targetVec.y / divideVec.y;
    else
        resultVec.y = targetVec.y;

    if (divideVec.z != 0.f)
        resultVec.z = targetVec.z / divideVec.z;
    else
        resultVec.z = targetVec.z;

    return resultVec;
}

_vec3 Math::clampVector(_vec3 targetVec, _vec3 firstVec, _vec3 secondVec)
{
    float maxX, minX, maxY, minY, maxZ, minZ;
    if (firstVec.x > secondVec.x)
    {
        maxX = firstVec.x;
        minX = secondVec.x;
    }
    else
    {
        maxX = secondVec.x;
        minX = firstVec.x;
    }

    if (firstVec.y > secondVec.y)
    {
        maxY = firstVec.y;
        minY = secondVec.y;
    }
    else
    {
        maxY = secondVec.y;
        minY = firstVec.y;
    }

    if (firstVec.z > secondVec.z)
    {
        maxZ = firstVec.z;
        minZ = secondVec.z;
    }
    else
    {
        maxZ = secondVec.z;
        minZ = firstVec.z;
    }

    _vec3 minVec, maxVec;
    minVec = { minX,minY,minZ };
    maxVec = { maxX,maxY,maxZ };
    if (targetVec.x < minVec.x)
        targetVec.x = minVec.x;
    else if (targetVec.x > maxVec.x)
        targetVec.x = maxVec.x;

    if (targetVec.y < minVec.y)
        targetVec.y = minVec.y;
    else if (targetVec.y > maxVec.y)
        targetVec.y = maxVec.y;

    if (targetVec.z < minVec.z)
        targetVec.z = minVec.z;
    else if (targetVec.z > maxVec.z)
        targetVec.z = maxVec.z;

    return targetVec;
}

_vec3 Math::clampVectorExceptY(_vec3 targetVec, _vec3 firstVec, _vec3 secondVec)
{
    float maxX, minX, maxY, minY, maxZ, minZ;
    if (firstVec.x > secondVec.x)
    {
        maxX = firstVec.x;
        minX = secondVec.x;
    }
    else
    {
        maxX = secondVec.x;
        minX = firstVec.x;
    }

    if (firstVec.y > secondVec.y)
    {
        maxY = firstVec.y;
        minY = secondVec.y;
    }
    else
    {
        maxY = secondVec.y;
        minY = firstVec.y;
    }

    if (firstVec.z > secondVec.z)
    {
        maxZ = firstVec.z;
        minZ = secondVec.z;
    }
    else
    {
        maxZ = secondVec.z;
        minZ = firstVec.z;
    }

    _vec3 minVec, maxVec;
    minVec = { minX,minY,minZ };
    maxVec = { maxX,maxY,maxZ };
    if (targetVec.x < minVec.x)
        targetVec.x = minVec.x;
    else if (targetVec.x > maxVec.x)
        targetVec.x = maxVec.x;


    if (targetVec.z < minVec.z)
        targetVec.z = minVec.z;
    else if (targetVec.z > maxVec.z)
        targetVec.z = maxVec.z;

    return targetVec;
}

float Math::lerp(float srcValue, float destValue, float dt)
{
	return srcValue * (1.f - dt) + destValue * dt;
}

_mat Math::calculateWorldMatrix2D(const _vec3& position, const _vec3& rotation, const _vec3& scale)
{
    _mat matWorld, matTranslation, matRotation, matScale;
    D3DXMatrixTranslation(&matTranslation, position.x, position.y + position.z, 0.f);
    D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.y, rotation.x, rotation.z);
    D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
    matWorld = matScale * matRotation * matTranslation;
    return matWorld;
}

float Math::calculateAngle2D(const _vec3& standardVector, const _vec3& targetVector)
{
    _vec3 standardVector2D = { standardVector.x,standardVector.y + standardVector.z,0.f };
    _vec3 targetVector2D = { targetVector.x,targetVector.y + targetVector.z,0.f };

    float dot;
    D3DXVec3Normalize(&standardVector2D, &standardVector2D);
    D3DXVec3Normalize(&targetVector2D, &targetVector2D);

    dot = D3DXVec3Dot(&standardVector2D, &targetVector2D);

    float angle;
    angle = acosf(dot);

    _vec3 cross;
    D3DXVec3Cross(&cross, &standardVector2D, &targetVector2D);
    if (cross.z < 0.f)
        angle *= -1.f;

    return D3DXToDegree(angle);
}
