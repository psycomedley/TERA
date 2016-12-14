float4x4	g_matWVP : WorldViewProjection;
texture		DiffuseMap_Tex;
texture		DiffuseMap_Tex2;
texture		DiffuseMap_Tex3;
texture		BumpMap_Tex;
float		g_fPassedTime;
float		g_fAlpha;


float		g_fRatioX;
float		g_fRatioY;
int			g_nOffsetX;
int			g_nOffsetY;


sampler2D DiffuseSampler = sampler_state
{
	Texture = <DiffuseMap_Tex>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = border;
	AddressV = border;
};

sampler2D DiffuseSampler2 = sampler_state
{
	Texture = <DiffuseMap_Tex2>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = border;
	AddressV = border;
};

sampler2D DiffuseSampler3 = sampler_state
{
	Texture = <DiffuseMap_Tex3>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
	AddressU = border;
	AddressV = border;
};

sampler2D BumpSampler = sampler_state
{
	Texture = <BumpMap_Tex>;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Linear;
};

//--------------------------------------------------------------//
// Structure
//--------------------------------------------------------------//

struct VS_INPUT
{
	float4 mPosition : POSITION;
	float2 mUV : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition : POSITION;
	float2 mUV : TEXCOORD0;
};

//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
// Vertex Shader
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	//	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
	//	Output.mPosition = mul(Output.mPosition, gViewMatrix);
	//	Output.mPosition = mul(Output.mPosition, gProjectionMatrix);
	Output.mPosition = mul(Input.mPosition, g_matWVP);

	Output.mUV = Input.mUV;

	return Output;
}

//--------------------------------------------------------------//
// Frame Move Shader
//--------------------------------------------------------------//

VS_OUTPUT vs_frameMoveX(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV = float2(Input.mUV.x + g_fPassedTime, Input.mUV.y);

	return Output;
}

VS_OUTPUT vs_frameMoveY(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV = float2(Input.mUV.x, Input.mUV.y + g_fPassedTime);

	return Output;
}

//--------------------------------------------------------------//
// Rotation Shader
//--------------------------------------------------------------//

VS_OUTPUT vs_Rotation(VS_INPUT Input)
{
	VS_OUTPUT Output;

	float sinX = sin(0.2 * g_fPassedTime);
	float cosX = cos(0.2 * g_fPassedTime);
	float2x2 rotationMatrix = float2x2(cosX, -sinX, sinX, cosX);

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV = mul((Input.mUV - float2(0.5, 0.5)), rotationMatrix) + float2(0.5, 0.5);

	return Output;
}

//--------------------------------------------------------------//
// Frame Add Shader
//--------------------------------------------------------------//

VS_OUTPUT vs_FrameAdd(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV.x = Input.mUV.x * g_fRatioX + mul(g_nOffsetX, g_fRatioX);  /*float2(mul(g_nOffsetX, g_fRatioX), mul(g_nOffsetY, g_fRatioY));*/
	Output.mUV.y = Input.mUV.y * g_fRatioY + mul(g_nOffsetY, g_fRatioY);

	return Output;
}

//////////////////////////////////////////////////////////////////
//--------------------------------------------------------------//
// Pixel Shader
//--------------------------------------------------------------//
//////////////////////////////////////////////////////////////////

float4 ps_main(VS_OUTPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mUV);

	return albedo;
}

//--------------------------------------------------------------//
// Blue Shader
//--------------------------------------------------------------//

float4 ps_blueShader(VS_OUTPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mUV) * ((1 - Input.mUV.y) * 2);

	albedo.r = albedo.r * 0.5;
	albedo.g = albedo.g * 0.5;
	albedo.b = albedo.b * 2;

	return albedo;
}

//--------------------------------------------------------------//
// Wave Shader
//--------------------------------------------------------------//

float4 ps_waveShader(VS_OUTPUT Input) : COLOR
{
	//Input.mUV.y = Input.mUV.y + (sin(Input.mUV.y * 100) * 0.03);
	//float4 albedo = tex2D(DiffuseSampler, Input.mUV);

	//return albedo;


	float2 uv = float2(Input.mUV.x + g_fPassedTime * 0.4, Input.mUV.y + g_fPassedTime * 0.2);
	float3 normal;

	normal = tex2D(BumpSampler, uv);

	float4 base = tex2D(DiffuseSampler, Input.mUV.xy + 0.03 * normal.xy);

	float4 c = base;
	return c;
}

//--------------------------------------------------------------//
// Orca Skill1 Shader
//--------------------------------------------------------------//

float4 ps_orcaSkill1(VS_OUTPUT Input) : COLOR
{
	float2 uv = float2(Input.mUV.x + g_fPassedTime * 0.2, Input.mUV.y /*+ g_fPassedTime * 0.2*/);
	float3 normal;

	normal = tex2D(BumpSampler, uv);

	float4 base = tex2D(DiffuseSampler, Input.mUV.xy + 0.03 * normal.xy);

	base.r = base.r * 0.5;
	base.g = base.g * 0.125;
	base.b = base.b * 4;
	
	return base;
}

float4 ps_orcaSkill1_1(VS_OUTPUT Input) : COLOR
{
	float2 uv = float2(Input.mUV.x, Input.mUV.y /*+ g_fPassedTime * 0.2*/);

	float4 base = tex2D(DiffuseSampler2, Input.mUV);

	base.r = base.r * 0.5;
	base.g = base.g * 0.5;
	base.b = base.b * 2;

	return base;
}

float4 ps_orcaSkill1_2(VS_OUTPUT Input) : COLOR
{
	float2 uv = float2(Input.mUV.x, Input.mUV.y /*+ g_fPassedTime * 0.2*/);

	float4 base = tex2D(DiffuseSampler3, Input.mUV);

//	base.r = base.r * 0.5;
//	base.g = base.g * 0.25;
//	base.b = base.b * 4;

	return base;
}

//--------------------------------------------------------------//
// Test Shader
//--------------------------------------------------------------//

float4 ps_test(VS_OUTPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mUV);
	float4 albedo2 = tex2D(DiffuseSampler2, Input.mUV);

	return ((albedo + albedo2) / 2);
}


//--------------------------------------------------------------//
// Technique Section for NormalShader
//--------------------------------------------------------------//

technique NormalShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}

//--------------------------------------------------------------//
// Technique Section for BlueShader
//--------------------------------------------------------------//

technique BlueShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_Rotation();
		PixelShader = compile ps_2_0 ps_blueShader();
	}
}

//--------------------------------------------------------------//
// Technique Section for Frame MoveX
//--------------------------------------------------------------//
technique FrameMoveX
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_frameMoveX();
		PixelShader = compile ps_2_0 ps_main();
	}
}

//--------------------------------------------------------------//
// Technique Section for Frame MoveY
//--------------------------------------------------------------//
technique FrameMoveY
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_frameMoveY();
		PixelShader = compile ps_2_0 ps_main();
	}
}

//--------------------------------------------------------------//
// Technique Section for Wave
//--------------------------------------------------------------//
technique Wave
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_waveShader();
	}
}

//--------------------------------------------------------------//
// Technique Section for Frame Add
//--------------------------------------------------------------//
technique FrameAdd
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_FrameAdd();
		PixelShader = compile ps_2_0 ps_main();
	}
}

//--------------------------------------------------------------//
// Technique Section for Orca Skill1
//--------------------------------------------------------------//
technique Orca1
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_orcaSkill1();
	}
	pass Pass_1
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_orcaSkill1_1();
	}
	pass Pass_2
	{
		VertexShader = compile vs_2_0 vs_FrameAdd();
		PixelShader = compile ps_2_0 ps_orcaSkill1_2();
	}
}

//--------------------------------------------------------------//
// Technique Section for Test
//--------------------------------------------------------------//
technique Test
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_test();
	}
}