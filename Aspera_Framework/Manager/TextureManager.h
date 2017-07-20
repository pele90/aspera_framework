#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <map>
#include <string>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../Graphics/Texture.h"

class TextureManager
{
public:
	TextureManager();
	TextureManager(const TextureManager&);
	~TextureManager();

	bool Initialize();
	void Shutdown();

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, string);

	ID3D11ShaderResourceView* GetTexture(string);

private:
	map<string, Texture> m_TextureArray;
	int m_textureCount;
};

#endif "_TEXTURE_MANAGER_H_"