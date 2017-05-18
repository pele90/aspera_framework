#include "Renderer.h"

Renderer::Renderer() : Component(7, "RENDERER")
{
}

Renderer::~Renderer(){}

bool Renderer::Initialize()
{
	return true;
}

bool Renderer::Initialize(ShaderType type)
{
	bool result;

	m_shaderType = type;

	return true;

}

void Renderer::Shutdown()
{

}

ShaderType Renderer::GetShaderType()
{
	return m_shaderType;
}