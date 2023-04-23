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

bool onOutline;
float outlineTimer;

bool onTint;
float3 tintColor;
float tintTimer;

bool damagedShader = false;
bool I_AM_SUN = false;
float sunPower = 0.1f;
float4 myColor=float4(0.65,0.65,0.65,1);
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
	float2 baseTexcoord:TEXCOORD1;
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.position = mul(Input.position, worldMatrix);
	Output.position = mul(Output.position, viewMatrix);
	Output.position = mul(Output.position, projectionMatrix);

	if(isRight)
		Output.texcoord.x = (frameOffset.x - sourceSizeOffset.x + Input.texcoord.x * originalSize.x) / totalSize.x;
	else
		Output.texcoord.x = (frameOffset.x - sourceSizeOffset.x + originalSize.x - originalSize.x * Input.texcoord.x) / totalSize.x;

	Output.texcoord.y = (frameOffset.y - sourceSizeOffset.y + Input.texcoord.y * originalSize.y) / totalSize.y;
	Output.baseTexcoord = Input.texcoord*myColor;
	//Output=Output*myColor;
	return Output;
}


struct PS_INPUT
{
	float4 position:POSITION0;
	float2 texcoord:TEXCOORD0;
	float2 baseTexcoord:TEXCOORD1;
	
  	float3 mDiffuse : TEXCOORD1;
   	float3 mViewDir: TEXCOORD2;
   	float3 mReflection: TEXCOORD3;
};
//
//float2 pixelate(float2 texcoord)
//{
//	return floor(texcoord*pixelateRatio) / pixelateRatio;
//}
float4 outlineShading(float4 diffuse, float2 texcoord)
{
	if (diffuse.a == 0)
	{
		if (tex2D(diffuseSampler, texcoord + float2(0, 0.0005)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(0, -0.0005)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(0.0005, 0)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(-0.0005, 0)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(-0.0005, 0.0005)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(-0.0005, -0.0005)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(0.0005, 0.0005)).a != 0 ||
			tex2D(diffuseSampler, texcoord + float2(0.0005, -0.0005)).a != 0)
		{
			float value = fmod(outlineTimer * 3, 3);
			if (2 <= value)
				diffuse = float4(1, 1, 0, 1);
			else if (1 <= value)
				diffuse = float4(1, 0, 0, 1);
			else
				diffuse = float4(0, 0, 1, 1);

		}

	}
	return diffuse;
}

float4 tintShading(float4 diffuse)
{
	float4 color = { tintColor.x,tintColor.y,tintColor.z,1.f };
	if (diffuse.a >= 1.f)
		diffuse += color *tintTimer;

	return diffuse;
}


float4 ps_main(PS_INPUT Input) : COLOR0
{
	float2 finalTex = Input.texcoord;
	//finalTex = pixelate(finalTex);
	float4 diffuse = tex2D(diffuseSampler,finalTex);

	if (onVanish)
		diffuse.a = vanishAlpha;

	//if (onOutline)
		//diffuse = outlineShading(diffuse, finalTex);

	if (onTint)
		diffuse = tintShading(diffuse);


	if(damagedShader)
		diffuse = diffuse * myColor;

	if (finalTex.x<frameOffset.x / totalSize.x || finalTex.x>(frameOffset.x + frameSize.x) / totalSize.x
		|| finalTex.y<frameOffset.y / totalSize.y || finalTex.y>(frameOffset.y + frameSize.y) / totalSize.y)
		diffuse.a = 0;


	if (I_AM_SUN)
	{
		float3 diffuse2 = saturate(Input.mDiffuse);

		float3 reflection = normalize(Input.mReflection);
		float3 viewDir = normalize(Input.mViewDir);
		float3 specular = 0;
		if (diffuse2.x > 0)
		{
			specular = saturate(dot(reflection, -viewDir));
			specular = pow(specular, 20.0f);
		}

		float3 ambient = float3(sunPower, sunPower, sunPower);

		
		return float4(ambient  + specular, 1);
	
	}


	return diffuse;
}

technique AtlasShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}

}

