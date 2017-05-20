#include "Renderer.h"

Renderer::Renderer() : Component(7, "RENDERER")
{
}

Renderer::~Renderer(){}

bool Renderer::Initialize()
{
	return true;
}

bool Renderer::Initialize(ShaderType type, vector<string> ids)
{
	m_shaderType = type;
	m_textureIds = ids;

	return true;

}

void Renderer::Shutdown()
{

}

ShaderType Renderer::GetShaderType()
{
	return m_shaderType;
}

vector<string> Renderer::GetTextureIds()
{
	return m_textureIds;
}