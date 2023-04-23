//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//
//  - Although many improvements were made to RenderMonkey FX  
//    file export, there are still situations that may cause   
//    compilation problems once the file is exported, such as  
//    occasional naming conflicts for methods, since FX format 
//    does not support any notions of name spaces. You need to 
//    try to create workspaces in such a way as to minimize    
//    potential naming conflicts on export.                    
//    
//  - Note that to minimize resulting name collisions in the FX 
//    file, RenderMonkey will mangle names for passes, shaders  
//    and function names as necessary to reduce name conflicts. 
//**************************************************************//

//--------------------------------------------------------------//
// Textured
//--------------------------------------------------------------//
//--------------------------------------------------------------//
// Pass 0
//--------------------------------------------------------------//
string Textured_Pass_0_Model : ModelData = "..\\..\\..\\Program Files (x86)\\AMD\\RenderMonkey 1.82\\Examples\\Media\\Models\\Cube.x";

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




texture base_Tex
<
   string ResourceName = "E:\\000Frame0.png";
>;
sampler2D baseMap = sampler_state
{
   Texture = (base_Tex);
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
   MINFILTER = LINEAR;
   MAGFILTER = LINEAR;
};
float2 size;
float4 myColor_1
<
   string UIName = "myColor_1";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 0.45, 0.45, 0.45, 1.00 );

struct PS_INPUT 
{
   float2 Texcoord : TEXCOORD0;
   
};

float4 Textured_Pass_0_Pixel_Shader_ps_main( PS_INPUT Input ) : COLOR0
{


   float2 tex=Input.Texcoord;
   

   
   float4 color  =tex2D( baseMap,tex);
   
   color=color*myColor_1;
   
   
   return color;
   
}




//--------------------------------------------------------------//
// Technique Section for Textured
//--------------------------------------------------------------//
technique Textured
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Textured_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Textured_Pass_0_Pixel_Shader_ps_main();
   }

}

