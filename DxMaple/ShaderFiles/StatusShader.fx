float4x4 worldMatrix : World;
float4x4 viewMatrix : View;
float4x4 projectionMatrix : Projection;

float2 totalSize;
float2 frameSize;
float2 frameOffset;
float2 sourceSizeOffset;
float2 originalSize;
bool	isRight;

//점점 페이드아웃
bool onVanish;
float vanishAlpha;

float Size;
texture baseTexture;
//float pixelateRatio;

bool yRatio;
bool Disappear;


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
	float2 baseTexcoord:TEXCOORD1;
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.position = mul(Input.position, worldMatrix);
	Output.position = mul(Output.position, viewMatrix);
	Output.position = mul(Output.position, projectionMatrix);

	if (isRight)
		Output.texcoord.x = (frameOffset.x - sourceSizeOffset.x + Input.texcoord.x * originalSize.x) / totalSize.x;
	else
		Output.texcoord.x = (frameOffset.x - sourceSizeOffset.x + originalSize.x - originalSize.x * Input.texcoord.x) / totalSize.x;

	Output.texcoord.y = (frameOffset.y - sourceSizeOffset.y + Input.texcoord.y * originalSize.y) / totalSize.y;
	Output.baseTexcoord = Input.texcoord;
	return Output;
}


struct PS_INPUT
{
	float4 position:POSITION0;
	float2 texcoord:TEXCOORD0;
};


float4 ratio(float4 diffuse,float2 texcoord)
{



	if (yRatio)
	{
		if ( texcoord.x > Size)
		{
			diffuse.a = 0;
		}

	}
	else
	{
		if (diffuse.a == 0)
		{
			diffuse.a = 0;
		}
		else if (texcoord.x < Size)
		{
			diffuse.a = 1;
		}
		else
		{
			diffuse.a = 0;
		}
	}
	return diffuse;
}


float4 ps_main(PS_INPUT Input) : COLOR0
{


	float4 diffuse = tex2D(diffuseSampler,Input.texcoord);
	float2 tex=Input.texcoord;
	//if (1-Input.texcoord.y > Size)
	//{
	//	diffuse.a = 0;
	//}
 	
	   
 
 	
	//diffuse = ratio(diffuse,Input.texcoord);
	


	if (onVanish)
		diffuse.a = vanishAlpha;
	
	if (Disappear)
	{
		if (tex.x > Size)
			return 0;
	}
	
	return diffuse;
}

technique StatusShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}

}
