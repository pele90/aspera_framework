#include "Transform.h"

Transform::Transform() : Component(10, "TRANSFORM")
{
	
}

Transform::~Transform()
{

}

bool Transform::Initialize()
{
	bool result;

	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;

	return true;
}

void Transform::Shutdown()
{

}

void Transform::SetTransform(const Transform other)
{
	m_positionX = other.m_positionX;
	m_positionY = other.m_positionY;
	m_positionZ = other.m_positionZ;

	m_rotationX = other.m_rotationX;
	m_rotationY = other.m_rotationY;
	m_rotationZ = other.m_rotationZ;
}

void Transform::SetPosition(float posX, float posY, float posZ)
{
	m_positionX = posX;
	m_positionY = posY;
	m_positionZ = posZ;
}

void Transform::SetRotation(float rotX, float rotY, float rotZ)
{
	m_rotationX = rotX;
	m_rotationY = rotY;
	m_rotationZ = rotZ;
}

XMFLOAT3 Transform::GetPosition()
{
	return XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

XMFLOAT3 Transform::GetRotation()
{
	return XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void Transform::Reset()
{
	m_positionX = 0;
	m_positionY = 0;
	m_positionZ = 0;

	m_rotationX = 0;
	m_rotationY = 0;
	m_rotationZ = 0;
}