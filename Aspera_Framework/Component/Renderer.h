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
	virtual bool Initialize(ShaderType);
	virtual void Shutdown();

	ShaderType GetShaderType();

private:
	ShaderType m_shaderType;
};

#endif // !_RENDERER_H_


