#include "MultiAnimation.vsh"


float4		vLightDiffus;		// = { 1.0f, 1.0f, 1.0f, 1.0f };   // Light Diffuse
float4		vMaterialAmbient;	// : MATERIALAMBIENT = { 1.0f, 0.1f, 0.1f, 1.0f };
float4		vMaterialDiffuse;	// : MATERIALDIFFUSE = { 0.8f, 0.8f, 0.8f, 1.0f };
float4		vWorldLightPos		= float4( 0.00, 500.00, -500.00, 1.00 );
float4		vWorldCameraPos		= float4( -50.00, 50.00, -50.00, 1.00 );

float4x4	g_mWorld			: WORLD;
float4x4	g_mViewProj			: VIEWPROJECTION;
texture		g_txScene;
texture		DiffuseMap_Tex;
texture		SpecularMap_Tex;
texture		NormalMap_Tex;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler g_samScene =
	sampler_state
{
	Texture = <g_txScene>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};

sampler DiffuseSampler =
	sampler_state
{
   Texture = <DiffuseMap_Tex>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};

sampler SpecularSampler =
	sampler_state
{
   Texture = <SpecularMap_Tex>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};

sampler NormalSampler =
	sampler_state
{
   Texture = <NormalMap_Tex>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4  Pos         : POSITION;
	float3  BlendWeights: BLENDWEIGHT;
	float4  BlendIndices: BLENDINDICES;
	float3  Normal      : NORMAL;
	float3  TexCoord    : TEXCOORD0;
	float3	Tangent		: TANGENT;
	float3	Binormal	: BINORMAL;
};

struct VS_OUTPUT
{
	float4	Pos			: POSITION;
	float2	TexCoord	: TEXCOORD0;
	float3	fLightDir	: TEXCOORD1;
	float3	fViewDir	: TEXCOORD2;
	float3	T			: TEXCOORD3;
	float3	B			: TEXCOORD4;
	float3	N			: TEXCOORD5;
	
};

struct PS_INPUT
{
   float2 TexCoord		: TEXCOORD0;
   float3 fLightDir		: TEXCOORD1;
   float3 fViewDir		: TEXCOORD2;
   float3 T				: TEXCOORD3;
   float3 B				: TEXCOORD4;
   float3 N				: TEXCOORD5;
};

float3 gLightColor
<
   string UIName = "gLightColor";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 1.00;
> = float3( 0.70, 0.70, 1.00 );

//픽셀 셰이더
float4 PixScene(PS_INPUT Input) : COLOR
{
	float3 tangentNormal = tex2D(NormalSampler, Input.TexCoord).xyz;
	tangentNormal = normalize(tangentNormal * 2 -1);
	
	float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
	TBN = transpose(TBN);
	float3 wolrdNormal = mul(TBN, tangentNormal);
	
	float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
	float3 lightDir = normalize(Input.fLightDir);
	float3 diffuse = saturate(dot(wolrdNormal, -lightDir));
	diffuse = gLightColor * albedo.rgb * diffuse;
	
	float3 specular = 0;
	if ( diffuse.x > 0 )
	{
		float3 reflection = reflect(lightDir, wolrdNormal);
		float3 viewDir = normalize(Input.fViewDir); 
		
		specular = saturate(dot(reflection, -viewDir ));
		specular = pow(specular, 20.0f);
		
		float4 specularIntensity  = tex2D(SpecularSampler, Input.TexCoord);
		specular *= specularIntensity.rgb * gLightColor;
	}

	float3 ambient = float3(0.1f, 0.1f, 0.1f);

	return float4(ambient + diffuse + specular, 1);
   
   
	
	
	// float3 color		= saturate(Diffuse);
	// float3 reflaction	= normalize(fReflection);
	// float3 viewDir		= normalize(fViewDir);
	// float3 specular		= 0;

	// if(color.x > 0)
	// {
		// specular = saturate(dot(reflaction, -viewDir));
		// specular = pow(specular, 20.0f);	
	// }

	// float4 Color = tex2D( g_samScene, TexCoord ) * float4(color + specular, 1.0f);
	// return Color;
}

//버텍스 셰이더
VS_OUTPUT VertSkinning( VS_INPUT Input, uniform int nNumBones )
{
	VS_OUTPUT   Output;
	
	Output.fViewDir		= float3(0, 0, 0);

	float3	Pos			= 0.0f;
	float3	Normal		= 0.0f;
	float	LastWeight	= 0.0f;

	// skin VB inputs
	VS_SKIN_INPUT vsi = { Input.Pos, Input.BlendWeights, Input.BlendIndices, Input.Normal };
	VS_SKIN_OUTPUT vso = VS_Skin( vsi, nNumBones );

	// transform position from world space into view and then projection space
	Output.Pos = mul( float4( vso.vPos.xyz, 1.0f ), g_mViewProj );
	
	// copy the input texture coordinate through
	Output.TexCoord  = Input.TexCoord.xy;
	

	// normalize normals
	Normal = normalize( vso.vNor );

	float3 lightDir = vso.vPos.xyz - vWorldLightPos.xyz;
	Output.fLightDir = normalize(lightDir);

	float3 ViewDir = vso.vPos.xyz - vWorldCameraPos.xyz;
	Output.fViewDir = normalize(ViewDir);
	
	float3 worldNormal = mul( Input.Normal, (float3x3)g_mWorld );
	Output.N = normalize(worldNormal);
   
	float3 worldTangent = mul(Input.Tangent, (float3x3)g_mWorld );
	Output.T = normalize(worldTangent);
   
	float3 worldBinormal = mul(Input.Binormal, (float3x3)g_mWorld );
	Output.B = normalize(worldBinormal);
	
	// Shade (Ambient + etc.)
	//Output.Diffuse = float4( vMaterialAmbient.xyz + saturate( dot( Normal, lightDir.xyz ) ) * vMaterialDiffuse.xyz, 1.0 );

	return Output;
}


int CurNumBones = 10;

VertexShader vsArray20[ 4 ] = { 
	compile vs_2_0 VertSkinning( 1 ),
	compile vs_2_0 VertSkinning( 2 ),
	compile vs_2_0 VertSkinning( 3 ),
	compile vs_2_0 VertSkinning( 4 ) };


//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------

technique Skinning20
{
	pass p0
	{
		VertexShader = ( vsArray20[ CurNumBones ] );
		PixelShader = compile ps_2_0 PixScene();
	}
}
