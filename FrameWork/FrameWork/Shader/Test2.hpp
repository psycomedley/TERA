#include "MultiAnimation.vsh"


float4		vLightDiffuse;		// = { 1.0f, 1.0f, 1.0f, 1.0f };   // Light Diffuse
float4		vMaterialAmbient;	// : MATERIALAMBIENT = { 1.0f, 0.1f, 0.1f, 1.0f };
float4		vMaterialDiffuse;	// : MATERIALDIFFUSE = { 0.8f, 0.8f, 0.8f, 1.0f };
float4		vWorldLightPos		= float4( 0.00, 500.00, -500.00, 1.00 );
float4		vWorldCameraPos		= float4( -50.00, 50.00, -50.00, 1.00 );

float4x4	g_mWorld			: WORLD;
float4x4	g_mViewProj			: VIEWPROJECTION;
texture		g_txScene;
texture		g_txDiff;
texture		g_txSpec;
texture		g_txNorm;

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
	Texture = <g_txDiff>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};
sampler SpecularSampler =
	sampler_state
{
	Texture = <g_txSpec>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};
sampler NormalSampler =
	sampler_state
{
	Texture = <g_txNorm>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};


//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4  mPosition		: POSITION;
	float3  mNormal			: NORMAL;
	float2  mUV				: TEXCOORD0;
	float3	mTangent		: TANGENT;
	float3	mBinormal		: BINORMAL;
	float3  mBlendWeights	: BLENDWEIGHT;
	float4  mBlendIndices	: BLENDINDICES;
};

struct VS_OUTPUT
{
	float4 mPosition	: POSITION;
	float2 mUV			: TEXCOORD0;
	float3 mLightDir	: TEXCOORD1;
	float3 mViewDir		: TEXCOORD2;
	float3 T			: TEXCOORD3;
	float3 B			: TEXCOORD4;
	float3 N			: TEXCOORD5;
//	float4 Diffuse		: COLOR0;
//	float3 mReflection	: TEXCOORD3;
//	float3 mDiffuse		: TEXCOORD1;
};

struct PS_INPUT
{
	float2 mUV			: TEXCOORD0;
	float3 mLightDir	: TEXCOORD1;
	float3 mViewDir		: TEXCOORD2;
	float3 T			: TEXCOORD3;
	float3 B			: TEXCOORD4;
	float3 N			: TEXCOORD5;
};


VS_OUTPUT VertSkinning( VS_INPUT Input, uniform int nNumBones )
{
	VS_OUTPUT   Output;
	
	Output.mViewDir		= float3(0, 0, 0);

	float3	Pos			= 0.0f;
	float3	Normal		= 0.0f;
	float	LastWeight	= 0.0f;

	// skin VB inputs
	VS_SKIN_INPUT vsi = { Input.mPosition, Input.mBlendWeights, Input.mBlendIndices, Input.mNormal, Input.mTangent, Input.mBinormal };
	VS_SKIN_OUTPUT vso = VS_Skin(vsi, nNumBones);

	// transform position from world space into view and then projection space
	Output.mPosition = mul(float4(vso.vPos.xyz, 1.0f), g_mViewProj);
	Output.mUV = Input.mUV;

	float3 lightDir = vso.vPos.xyz - vWorldLightPos.xyz;
	Output.mLightDir = normalize(lightDir);

	float3 ViewDir = normalize(vso.vPos.xyz - vWorldCameraPos.xyz);
	Output.mViewDir = ViewDir;

//	Normal = normalize(vso.vNor);
//	float3 worldNormal = normalize(Normal);
//	Output.N = worldNormal;


//	float3 worldNormal = mul(Input.mNormal, (float3x3)g_mWorld);
//	Output.N = normalize(worldNormal);

//	float3 worldTangent = mul(Input.mTangent, (float3x3)g_mWorld);
//	Output.T = normalize(worldTangent);

//	float3 worldBinormal = mul(Input.mBinormal, (float3x3)g_mWorld);
//	Output.B = normalize(worldBinormal);






	// normalize normals
	Normal = normalize(vso.vNor);
	float3 worldNormal = normalize(Normal);
	Output.N = worldNormal;

	float3 Tangent = normalize(vso.vTangent);
	float3 worldTangent = normalize(Tangent);
	Output.T = worldTangent;

	float3 Bitangent = normalize(vso.vBinormal);
	float3 worldBiTangent = normalize(Bitangent);
	Output.B = worldBiTangent;


	// Shade (Ambient + etc.)
//	Output.Diffuse = float4(vMaterialAmbient.xyz + saturate(dot(Normal, lightDir.xyz)) * vMaterialDiffuse.xyz, 1.0);
//	Output.mReflection = reflect(lightDir, worldNormal);

	return Output;
}


float4 PixScene(PS_INPUT Input) : COLOR
{
	float3 tangentNormal = tex2D(NormalSampler, Input.mUV).xyz;
	tangentNormal = normalize(tangentNormal * 2 - 1);

	float3x3 TBN = float3x3(normalize(Input.T), normalize(Input.B), normalize(Input.N));
	TBN = transpose(TBN);
	float3 wolrdNormal = mul(TBN, tangentNormal);

	float4 albedo = tex2D(DiffuseSampler, Input.mUV);
	float3 lightDir = normalize(Input.mLightDir);
	float3 diffuse = saturate(dot(wolrdNormal, -lightDir));
	diffuse = vLightDiffuse.rgb * albedo.rgb * diffuse;

	float3 specular = 0;
	if (diffuse.x > 0)
	{
		float3 reflection = reflect(lightDir, wolrdNormal);
		float3 viewDir = normalize(Input.mViewDir);

		specular = saturate(dot(reflection, -viewDir));
		specular = pow(specular, 20.0f);

		float4 specularIntensity = tex2D(SpecularSampler, Input.mUV);
		specular *= specularIntensity.rgb * vLightDiffuse.rgb;
	}

	float3 ambient = float3(0.1f, 0.1f, 0.1f);

	return float4(ambient + diffuse + specular, 1);



//	float3 color = saturate(Diffuse);
//	float3 reflaction = normalize(fReflection);
//	float3 viewDir = normalize(fViewDir);
//	float3 specular = 0;

//	if (color.x > 0)
//	{
//		specular = saturate(dot(reflaction, -viewDir));
//		specular = pow(specular, 20.0f);
//	}

//	float4 Color = tex2D(g_samScene, TexCoord) * float4(color + specular, 1.0f);
//	return Color;
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
