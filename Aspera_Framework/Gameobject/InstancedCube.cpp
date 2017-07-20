#include "InstancedCube.h"

InstancedCube::InstancedCube() : GameObject("InstancedCubeGO")
{
	m_renderer = 0;
	m_model = 0;
	m_transform = 0;
}

InstancedCube::~InstancedCube() {}

bool InstancedCube::Initialize()
{
	return true;
}

bool InstancedCube::Initialize(char* filename)
{
	bool result;

	m_transform = new Transform;
	if (!m_transform)
		return false;

	result = m_transform->Initialize();
	if (!result)
		return false;
	AddComponent(m_transform);

	m_model = new InstancingMesh;
	if (!m_model)
		return false;

	result = m_model->Initialize(filename, 500);
	if (!result)
		return false;
	AddComponent(m_model);

	m_renderer = new Renderer;
	if (!m_renderer)
		return false;

	vector<string> textureIds = vector<string>{ "cube" };
	result = m_renderer->Initialize(ShaderType::TEXTURE_INSTANCED, textureIds);
	AddComponent(m_renderer);

	return true;
}

void InstancedCube::Shutdown()
{
	if (m_transform)
	{
		m_transform->Shutdown();
		delete m_transform;
		m_transform = 0;
	}

	if (m_renderer)
	{
		m_renderer->Shutdown();
		delete m_renderer;
		m_renderer = 0;
	}

	if (m_model)
	{
		m_model->Shutdown();
		delete m_model;
		m_model = 0;
	}
}