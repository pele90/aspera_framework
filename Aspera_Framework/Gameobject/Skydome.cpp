#include "Skydome.h"

Skydome::Skydome() :GameObject("SkydomeGO")
{
	m_transform = 0;
	m_modelMesh = 0;
	m_renderer = 0;
}

Skydome::~Skydome()
{
}

bool Skydome::Initialize()
{
	return true;
}

bool Skydome::Initialize(char* filename)
{
	bool result;

	m_transform = new Transform;
	if (!m_transform)
		return false;

	m_transform->Initialize();
	AddComponent(m_transform);

	m_modelMesh = new ModelMesh;
	if (!m_modelMesh)
		return false;

	result = m_modelMesh->Initialize(filename);
	if (!result)
		return false;
	AddComponent(m_modelMesh);

	m_renderer = new Renderer;
	if (!m_renderer)
		return false;

	vector<string> textureIds = vector<string>();
	m_renderer->Initialize(ShaderType::SKYDOME, textureIds);
	AddComponent(m_renderer);

	// Set the color at the top of the sky dome.
	m_apexColor = XMFLOAT4(0.0f, 0.05f, 0.6f, 1.0f);

	// Set the color at the center of the sky dome.
	m_centerColor = XMFLOAT4(0.0f, 0.5f, 0.8f, 1.0f);

	return true;
}

void Skydome::Shutdown()
{
	if (m_transform)
	{
		m_transform->Shutdown();
		delete m_transform;
		m_transform = 0;
	}

	if (m_modelMesh)
	{	
		m_modelMesh->Shutdown();
		delete m_modelMesh;
		m_modelMesh = 0;
	}

	if (m_renderer)
	{
		m_renderer->Shutdown();
		delete m_renderer;
		m_renderer = 0;
	}
}