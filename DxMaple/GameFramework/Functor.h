#pragma once

template<typename T>
static void safeDelete(T& ptr)
{
	if (nullptr != ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}
template<typename T>
static void safeDeleteArray(T& ptr)
{
	if (nullptr != ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template<typename T>
static void safeRelease(T& ptr)
{
	if (nullptr != ptr)
	{
		ptr->Release();
		ptr = nullptr;
	}
}



static _mat calculateWorldmatrix(const _vec3& position, const _vec3& rotation, const _vec3& scale)
{
	_mat matWorld, matTranslation, matRotation, matScale;
	D3DXMatrixTranslation(&matTranslation, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&matRotation, rotation.y, rotation.x, rotation.z);
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	matWorld = matScale * matRotation * matTranslation;
	return matWorld;
}




