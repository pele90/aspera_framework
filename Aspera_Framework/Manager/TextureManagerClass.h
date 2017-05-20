#ifndef _TEXTUREMANAGERCLASS_H_
#define _TEXTUREMANAGERCLASS_H_

#include <map>
#include <string>
using namespace std;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "../Graphics/TextureClass.h"

class TextureManagerClass
{
public:
	TextureManagerClass();
	TextureManagerClass(const TextureManagerClass&);
	~TextureManagerClass();

	bool Initialize();
	void Shutdown();

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, string);

	ID3D11ShaderResourceView* GetTexture(string);

private:
	map<string, TextureClass> m_TextureArray;
	int m_textureCount;
};

#endif "_TEXTUREMANAGERCLASS_H_"