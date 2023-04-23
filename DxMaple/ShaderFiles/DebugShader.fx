float4x4 worldMatrix : World;
float4x4 viewMatrix : View;
float4x4 projectionMatrix : Projection;

int shaderMode;
struct VS_INPUT
{
	float4 position:POSITION0;

};

struct VS_OUTPUT
{
	float4 position:POSITION0;
	
};


VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.position = mul(Input.position, worldMatrix);
	Output.position = mul(Output.position, viewMatrix);
	Output.position = mul(Output.position, projectionMatrix);


	return Output;
}


float4 ps_main() : COLOR0
{
	float4 color;
	if (0 == shaderMode)
		color.rgba = float4(1.f, 1.f, 1.f, 1.f);
	else if(1== shaderMode)
		color.rgba = float4(1.f, 0.f, 0.f, 1.f);
	else if (2 == shaderMode)
		color.rgba = float4(0.f, 1.f, 0.f, 1.f);
	else if (3 == shaderMode)
		color.rgba = float4(0.f, 0.f, 1.f, 1.f);
	return color;
}

technique DebugShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}

}

