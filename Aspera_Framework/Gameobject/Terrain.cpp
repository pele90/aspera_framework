#include "Terrain.h"

Terrain::Terrain() : GameObject("TerrainGO")
{
	m_terrainMesh = 0;
	m_transform = 0;
	m_renderer = 0;
}

Terrain::~Terrain()
{

}

bool Terrain::Initialize()
{
	return true;
}

bool Terrain::Initialize(char* filename)
{
	bool result;

	m_transform = new Transform;
	if (!m_transform)
		return false;

	result = m_transform->Initialize();
	if (!result)
		return false;

	AddComponent(m_transform);

	m_terrainMesh = new TerrainMesh;
	if (!m_terrainMesh)
		return false;

	result = m_terrainMesh->Initialize(filename);
	if (!result)
		return false;
	AddComponent(m_terrainMesh);

	m_renderer = new Renderer;
	if (!m_renderer)
		return false;

	vector<string> textureIds = vector<string>{ "dirt01d", "dirt01n" };
	result = m_renderer->Initialize(ShaderType::TERRAIN, textureIds);
	if (!result)
		return false;
	AddComponent(m_renderer);

	return true;
}

void Terrain::Shutdown()
{
	if (m_transform)
	{
		m_transform->Shutdown();
		delete m_transform;
		m_transform = 0;
	}

	if (m_terrainMesh)
	{
		m_terrainMesh->Shutdown();
		delete m_terrainMesh;
		m_terrainMesh = 0;
	}

	if (m_renderer)
	{
		m_renderer->Shutdown();
		delete m_renderer;
		m_renderer = 0;
	}
}