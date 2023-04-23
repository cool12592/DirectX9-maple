float4x4 matViewProjection : ViewProjection;

struct VS_INPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Texcoord : TEXCOORD0;
   
};

VS_OUTPUT Textured_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position, matViewProjection );
   Output.Texcoord = Input.Texcoord;

   return( Output );
   
}

texture base_Tex;
sampler2D baseMap = sampler_state
{
   Texture = (base_Tex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MINFILTER = LINEAR;
   MAGFILTER = LINEAR;
};

bool isRipple=false;
float time;

bool isFade = false;
float fadeValue = 1.f;

bool isPixelate = false;
float pixelateRatio;
struct PS_INPUT 
{
   float2 uv : TEXCOORD0;
   
};

float4 sphere(float2 tc) :COLOR0 {
  float2 p = -1.0 + 2.0 * tc;
  float r =  dot(p,p);
  
  if (r > 1.0) 
     return 0; 
     
  float f = (1.0-sqrt(1.0-r))/(r);
  float2 uv;
  uv.x = p.x*f + time;
  uv.y = p.y*f+ time;
  
 
   return tex2D(baseMap,uv);
}

float4 ripple(float2 tc) :COLOR0{

  float2 p = -1.0 + 2.0 * tc;
  float len = length(p);
  float2 np= p/len;
  float2 uv = tc + np* cos(len*12.0-time*4.0)*0.03;
  float3 col = tex2D(baseMap,uv).xyz;
  return float4(col,1.0);  
}

float4 fade(float4 diffuse,float2 texcoord, float value)
{
    if (texcoord.x + texcoord.y < value * 2.f)
        diffuse.rgba = float4(0,0,0,1);

    return diffuse;
}
float2 pixelate(float2 texcoord)
{
	return floor(texcoord*pixelateRatio) / pixelateRatio;
}
float4 Textured_Pass_0_Pixel_Shader_ps_main( PS_INPUT input ) : COLOR0
{
   float2 tc = input.uv;
   
   if (isRipple)
       return ripple(tc);
   if(isPixelate)
       tc = pixelate(tc);
   float4 diffuse = tex2D(baseMap, tc);

   if (isFade)
       diffuse = fade(diffuse, input.uv, fadeValue);
   return diffuse;
   
}




//--------------------------------------------------------------//
// Technique Section for Textured
//--------------------------------------------------------------//
technique Textured
{
   pass Pass_0
   {
      ALPHABLENDENABLE = TRUE;
      SRCBLEND = SRCCOLOR;
      DESTBLEND = INVSRCALPHA;

      VertexShader = compile vs_2_0 Textured_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Textured_Pass_0_Pixel_Shader_ps_main();
   }

}

