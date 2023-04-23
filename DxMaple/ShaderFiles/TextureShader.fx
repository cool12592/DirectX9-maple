float4x4 worldMatrix : World;
float4x4 viewMatrix : View;
float4x4 projectionMatrix : Projection;



texture baseTexture;
//float pixelateRatio;
sampler2D diffuseSampler = sampler_state
{
	Texture = baseTexture;
};
struct VS_INPUT
{
	float4 position:POSITION0;
	float2 texcoord:TEXCOORD0;

};

struct VS_OUTPUT
{
	float4 position:POSITION0;
	float2 texcoord:TEXCOORD0;
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.position = mul(Input.position, worldMatrix);
	Output.position = mul(Output.position, viewMatrix);
	Output.position = mul(Output.position, projectionMatrix);

	
	Output.texcoord = Input.texcoord;
	return Output;
}


struct PS_INPUT
{
	float4 position:POSITION0;
	float2 texcoord:TEXCOORD0;
};
//
//float2 pixelate(float2 texcoord)
//{
//	return floor(texcoord*pixelateRatio) / pixelateRatio;
//}


float4 ps_main(PS_INPUT Input) : COLOR0
{
	
	//finalTex = pixelate(finalTex);
	float4 diffuse = tex2D(diffuseSampler,Input.texcoord);
	

	return diffuse;
}

technique TextureShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}

}
