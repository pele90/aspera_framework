#include "TextureManagerClass.h"

TextureManagerClass::TextureManagerClass()
{
}

TextureManagerClass::TextureManagerClass(const TextureManagerClass& other)
{
}

TextureManagerClass::~TextureManagerClass()
{
}

bool TextureManagerClass::Initialize()
{
	return true;
}

void TextureManagerClass::Shutdown()
{
	for (auto& x : m_TextureArray)
	{
		x.second.Shutdown();
	}

	return;
}

bool TextureManagerClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename, string id)
{
	bool result;

	// Add and initialize the texture object.
	m_TextureArray[id] = TextureClass();
	result = m_TextureArray[id].Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* TextureManagerClass::GetTexture(string id)
{
	return m_TextureArray[id].GetTexture();
}