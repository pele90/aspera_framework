#include "TextureManager.h"

TextureManager::TextureManager(){}

TextureManager::TextureManager(const TextureManager& other){}

TextureManager::~TextureManager(){}

bool TextureManager::Initialize()
{
	return true;
}

void TextureManager::Shutdown()
{
	for (auto& x : m_TextureArray)
	{
		x.second.Shutdown();
	}

	return;
}

bool TextureManager::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, string id)
{
	bool result;

	// Add and initialize the texture object.
	m_TextureArray[id] = Texture();
	result = m_TextureArray[id].Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* TextureManager::GetTexture(string id)
{
	return m_TextureArray[id].GetTexture();
}