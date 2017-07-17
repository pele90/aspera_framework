#include "DirectionalLight.h"

#include "..\Base\GameObject.h"

DirectionalLight::DirectionalLight() : GameObject("DIRECTIONAL_LIGHT")
{
	m_transform = 0;
	m_light = 0;
}

DirectionalLight::~DirectionalLight() {}

bool DirectionalLight::Initialize()
{
	bool result;

	m_transform = new Transform;
	if (!m_transform)
		return false;

	result = m_transform->Initialize();
	if (!result)
		return false;

	AddComponent(m_transform);

	m_light = new Light;
	if (!m_light)
		return false;

	result = m_light->Initialize();
	if (!result)
		return false;

	AddComponent(m_light);

	return result;
}

void DirectionalLight::Shutdown()
{
	if (m_transform) {
		m_transform->Shutdown();
		delete m_transform;
		m_transform = 0;
	}

	if (m_light) {
		m_light->Shutdown();
		delete m_light;
		m_light = 0;
	}
}

XMMATRIX DirectionalLight::GenerateViewMatrix()
{
	// Setup the vector that points upwards.
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	XMVECTOR position = XMLoadFloat3(&m_transform->GetPosition());
	XMVECTOR lookAt = XMLoadFloat3(&m_transform->GetRotation());

	// Create the view matrix from the three vectors.
	return XMMatrixLookAtLH(position, lookAt, up);
}

XMMATRIX DirectionalLight::GenerateProjectionMatrix(float screenNear, float screenDepth)
{
	float fieldOfView, screenAspect;

	// Setup field of view and screen aspect for a square light source.
	fieldOfView = (float)XM_PI / 2.0f;
	screenAspect = 1.0f;

	// Create the projection matrix for the light.
	return XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
}