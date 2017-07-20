#include "Cube.h"

Cube::Cube() : GameObject("CubeGO")
{
	m_renderer = 0;
	m_model = 0;
	m_transform = 0;
}

Cube::~Cube(){}

bool Cube::Initialize()
{
	return true;
}

bool Cube::Initialize(char* filename)
{
	bool result;

	m_transform = new Transform;
	if (!m_transform)
		return false;

	result = m_transform->Initialize();
	if (!result)
		return false;
	AddComponent(m_transform);

	m_model = new ModelMesh;
	if (!m_model)
		return false;

	result = m_model->Initialize(filename);
	if (!result)
		return false;
	AddComponent(m_model);

	m_renderer = new Renderer;
	if (!m_renderer)
		return false;

	vector<string> textureIds = vector<string>{ "cube" };
	result = m_renderer->Initialize(ShaderType::TEXTURE, textureIds);
	AddComponent(m_renderer);

	return true;
}

void Cube::Shutdown()
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