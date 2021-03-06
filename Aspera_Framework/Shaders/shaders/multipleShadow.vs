#define NUM_LIGHTS 4

cbuffer MatrixBuffer
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
    matrix lightViewMatrix[NUM_LIGHTS];
    matrix lightProjectionMatrix[NUM_LIGHTS];
};

struct PointLight
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightPosition;
	float padding;
};

cbuffer LightBuffer
{
	PointLight lights[NUM_LIGHTS];
};


//////////////
// TYPEDEFS //
//////////////
struct VertexInputType
{
    float4 position : POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float3 normal : NORMAL;
    float4 lightViewPosition[NUM_LIGHTS] : TEXCOORD4;
    float3 lightPos[NUM_LIGHTS] : TEXCOORD8;
};

////////////////////////////////////////////////////////////////////////////////
// Vertex Shader
////////////////////////////////////////////////////////////////////////////////
PixelInputType ShadowVertexShader(VertexInputType input)
{

    PixelInputType output;
    float4 worldPosition;
    
    // Change the position vector to be 4 units for proper matrix calculations.
    input.position.w = 1.0f;

    // Calculate the position of the vertex against the world, view, and projection matrices.
    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

	[unroll]
	for( uint i = 0;i < NUM_LIGHTS; i++)
	{
		// Calculate the position of the vertice as viewed by the light source.
		output.lightViewPosition[i] = mul(input.position, worldMatrix);
		output.lightViewPosition[i] = mul(output.lightViewPosition[i], lightViewMatrix[i]);
		output.lightViewPosition[i] = mul(output.lightViewPosition[i], lightProjectionMatrix[i]);
	}

    // Store the texture coordinates for the pixel shader.
    output.tex = input.tex;
    
    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3)worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    // Calculate the position of the vertex in the world.
    worldPosition = mul(input.position, worldMatrix);

	[unroll]
	for( uint j = 0;j < NUM_LIGHTS; j++ )
	{
		// Determine the light position based on the position of the light and the position of the vertex in the world.
		output.lightPos[j] = lights[j].lightPosition.xyz - worldPosition.xyz;
	
		// Normalize the light position vector.
		output.lightPos[j] = normalize(output.lightPos[j]);
	}

    return output;
}