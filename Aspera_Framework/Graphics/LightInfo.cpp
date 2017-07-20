#include "LightInfo.h"

LightInfo::LightInfo(){}

LightInfo::LightInfo(const LightInfo& other){}

LightInfo::~LightInfo(){}

void LightInfo::SetAmbientColor(float red, float green, float blue, float alpha)
{
	m_ambientColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightInfo::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = XMFLOAT4(red, green, blue, alpha);
	return;
}

void LightInfo::SetLookAt(float x, float y, float z)
{
	m_lookAt = XMVectorSet(x, y, z, 0);
	return;
}

void LightInfo::SetPosition(float x, float y, float z)
{
	m_position = XMVectorSet(x, y, z, 0);
	return;
}

XMFLOAT4 LightInfo::GetAmbientColor()
{
	return m_ambientColor;
}

XMFLOAT4 LightInfo::GetDiffuseColor()
{
	return m_diffuseColor;
}

XMVECTOR LightInfo::GetLookAt()
{
	return m_lookAt;
}

XMVECTOR LightInfo::GetPosition()
{
	return m_position;
}

void LightInfo::GenerateViewMatrix()
{
	// Setup the vector that points upwards.
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	// Create the view matrix from the three vectors.
	m_viewMatrix = XMMatrixLookAtLH(m_position, m_lookAt, up);

	return;
}

void LightInfo::GenerateProjectionMatrix(float screenDepth, float screenNear)
{
	float fieldOfView, screenAspect;


	// Setup field of view and screen aspect for a square light source.
	fieldOfView = (float)XM_PI / 2.0f;
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	m_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	return;
}

void LightInfo::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}

void LightInfo::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
	projectionMatrix = m_projectionMatrix;
	return;
}