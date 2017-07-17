#include "Light.h"

Light::Light() : Component(19, "LIGHT") {}

Light::~Light() {}

bool Light::Initialize()
{
	m_ambientColor = XMFLOAT4(0.01f, 0.01f, 0.01f, 0.0);
	m_diffuseColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 0.0);
	return true;
}

bool Light::Initialize(XMFLOAT4 ambientColor, XMFLOAT4 diffuseColor) {
	m_ambientColor = ambientColor;
	m_diffuseColor = diffuseColor;
	return true;
}

void Light::Shutdown()
{
}

XMFLOAT4 Light::GetAmbientColor() {
	return m_ambientColor;
}

XMFLOAT4 Light::GetDiffuseColor()
{
	return m_diffuseColor;
}

void Light::SetAmbientColor(XMFLOAT4 ambient)
{
	m_ambientColor = ambient;
}

void Light::SetDiffuseColor(XMFLOAT4 diffuse)
{
	m_diffuseColor = diffuse;
}