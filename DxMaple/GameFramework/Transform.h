#pragma once
#include "ECS.h"
class Transform:public Component
{
public:
	Transform();
	Transform(_vec3 position, _vec3 rotation, _vec3 scale);
	virtual ~Transform();

	// Component��(��) ���� ��ӵ�
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
	virtual void release() override;
	void setParentMatrix(_mat* parentMatrix) { parentMatrix_ = parentMatrix; }
	void setRevolution(float revolutionAngle) { revolutionAngle_ = revolutionAngle; }

	_mat getParentPositionMatrix();
public:
	//�׳� �̰� ������ ���ɵ˴ϴ�
	_vec3 position_;
	_vec3 rotation_;
	_vec3 scale_;
	_mat worldMatrix_;
	_mat worldMatrix2D_;

	float revolutionAngle_=0.f;
	_mat* parentMatrix_ = nullptr;
public:
	//�������� ����
	_vec3 interPosition_;
	bool isInterpolate_;
	
	
};

