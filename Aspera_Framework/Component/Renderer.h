#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "../Base/Component.h"
#include "../MISC/Enums.h"

class Renderer : public Component
{
public:
	Renderer();
	~Renderer();

	virtual bool Initialize();
	virtual bool Initialize(ShaderType, vector<string>);
	virtual void Shutdown();

	ShaderType GetShaderType();
	vector<string> GetTextureIds();

private:
	ShaderType m_shaderType;
	vector<string> m_textureIds;
};

#endif // !_RENDERER_H_


