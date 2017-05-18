#ifndef _TEXTUREMANAGERCLASS_H_
#define _TEXTUREMANAGERCLASS_H_

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

	bool Initialize(int);
	void Shutdown();

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, int);

	ID3D11ShaderResourceView* GetTexture(int);

private:
	TextureClass* m_TextureArray;
	int m_textureCount;
};

#endif "_TEXTUREMANAGERCLASS_H_"