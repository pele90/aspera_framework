#ifndef _ENUMS_H_
#define _ENUMS_H_

enum ShaderType
{
	COLOR,
	TEXTURE,
	TEXTURE_INSTANCED,
	LIGHT,
	TERRAIN,
	SKYDOME,
	FONT,
	SHADOW
};

enum MeshType
{
	TERRAIN_CELL,
	MODEL_MESH,
	D3INSTANCE_MESH
};

#endif
