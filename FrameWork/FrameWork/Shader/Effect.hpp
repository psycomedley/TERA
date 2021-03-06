float4x4	g_matWVP : WorldViewProjection;
texture		DiffuseMap_Tex;
texture		DiffuseMap_Tex2;
texture		DiffuseMap_Tex3;
texture		BumpMap_Tex;
float		g_fPassedTime;
float		g_fRemoveRatio;
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
	float4 base = tex2D(DiffuseSampler2, Input.mUV);

	base.r = base.r * 0.5;
	base.g = base.g * 0.5;
	base.b = base.b * 2;

	return base;
}

float4 ps_orcaSkill1_2(VS_OUTPUT Input) : COLOR
{
	float4 base = tex2D(DiffuseSampler3, Input.mUV);

//	base.r = base.r * 0.5;
//	base.g = base.g * 0.25;
//	base.b = base.b * 4;

	return base;
}

float4 ps_asdf(VS_OUTPUT Input) : COLOR
{
	float4 base = tex2D(DiffuseSampler, Input.mUV);

	//	base.r = base.r * 0.5;
	//	base.g = base.g * 0.25;
	//	base.b = base.b * 4;

	return base;
}

float4 ps_orcaSkill1_Remove(VS_OUTPUT Input) : COLOR
{
	float2 uv = float2(Input.mUV.x + g_fPassedTime * 0.2, Input.mUV.y);
	float3 normal;

	normal = tex2D(BumpSampler, uv);

	float4 base = tex2D(DiffuseSampler, Input.mUV.xy + 0.03 * normal.xy);

	base.r = base.r * 0.5;
	base.g = base.g * 0.125;
	base.b = base.b * 4;

	base.rgb = base.rgb - (base.rgb * g_fRemoveRatio);

	return base;
}

float4 ps_orcaSkill1_Remove_1(VS_OUTPUT Input) : COLOR
{
	float4 base = tex2D(DiffuseSampler2, Input.mUV);

	base.r = base.r * 0.5;
	base.g = base.g * 0.5;
	base.b = base.b * 2;

	base.rgb = base.rgb - (base.rgb * g_fRemoveRatio);

	return base;
}

float4 ps_orcaSkill1_Remove_2(VS_OUTPUT Input) : COLOR
{
	float4 base = tex2D(DiffuseSampler3, Input.mUV);

	base.rgb = base.rgb - (base.rgb * g_fRemoveRatio);

	return base;
}

//--------------------------------------------------------------//
// Decrease Alpha Shader
//--------------------------------------------------------------//

float4 ps_DecAlpha(VS_OUTPUT Input) : COLOR
{
	float2 uv = float2(Input.mUV.x, Input.mUV.y);

	float4 base = tex2D(DiffuseSampler, Input.mUV);

	base.rgb = base.rgb - (base.rgb * g_fRemoveRatio);
	return base;
}

//--------------------------------------------------------------//
// Orca Skill2 Shader
//--------------------------------------------------------------//

float4 ps_orcaSkill2(VS_OUTPUT Input) : COLOR
{
	float4 base2 = tex2D(DiffuseSampler2, Input.mUV);
	float4 base;
	float4 Output;
	if (g_fPassedTime >= 0.5)
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * 6 + float2(0.5, 0.5));
		Output.rgb = base2 - (g_fPassedTime - 0.5);
	}
	else
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * (30 - g_fPassedTime * 48) + float2(0.5, 0.5));
		Output.rgb = base2;
	}
	Output.a = base;

	return Output;
}

//--------------------------------------------------------------//
// Orca BackAtk Shader
//--------------------------------------------------------------//

float4 ps_orcaBackAtk(VS_OUTPUT Input) : COLOR
{
	float4 base2 = tex2D(DiffuseSampler2, Input.mUV);
	float4 base;
	float4 Output;
	if (g_fPassedTime >= 0.5)
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * 1.5 + float2(0.5, 0.5 - g_fPassedTime * 0.2));
//		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * 7 + float2(0.5, 0.5));
		Output.rgb = base2 - (g_fPassedTime - 0.5);
	}
	else
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * (4.5 - g_fPassedTime * 6) + float2(0.5, 0.5 - g_fPassedTime * 0.2));
		Output.rgb = base2;
	}

	Output.a = base;

	return Output;
}

//--------------------------------------------------------------//
// MagicArray Shader
//--------------------------------------------------------------//

float4 ps_magicArrayShader(VS_OUTPUT Input) : COLOR
{
	/*float4 albedo = tex2D(DiffuseSampler, Input.mUV) * ((1 - Input.mUV.y) * 2);

	albedo.r = albedo.r * 0.5;
	albedo.g = albedo.g * 0.5;
	albedo.b = albedo.b * 2;*/


	float4 base;
	float4 Output;
	if (g_fPassedTime <= 1)
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * (11 - g_fPassedTime * 10) + float2(0.5, 0.5)) * ((1 - Input.mUV.y) * 2);
		Output.r = base.r * 0.5;
		Output.g = base.g * 0.5;
		Output.b = base.b * 2;
		Output.a = base.a;
	}
	else if (g_fPassedTime >= 4)
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) + float2(0.5, 0.5)) * ((1 - Input.mUV.y) * 2);
		Output.r = base.r * 0.5;
		Output.g = base.g * 0.5;
		Output.b = base.b * 2;
		Output.rgb = Output.rgb - (Output.rgb * ((g_fPassedTime - 4) / 1));
//		Output.a = base.a;
	}
	else
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) + float2(0.5, 0.5)) * ((1 - Input.mUV.y) * 2);
		Output.r = base.r * 0.5;
		Output.g = base.g * 0.5;
		Output.b = base.b * 2;
		Output.a = base.a;
	}

	return Output;
}

//--------------------------------------------------------------//
// Globe Attack Shader
//--------------------------------------------------------------//

float4 ps_globeAtk(VS_OUTPUT Input) : COLOR
{
	float4 base2 = tex2D(DiffuseSampler2, Input.mUV);
	float4 base;
	float4 Output;
	if (g_fPassedTime >= 0.5)
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * 10 + float2(0.5, 0.5));
		Output.rgb = base2 - (g_fPassedTime - 0.5);
	}
	else
	{
		base = tex2D(DiffuseSampler, (Input.mUV - float2(0.5, 0.5)) * (34 - g_fPassedTime * 48) + float2(0.5, 0.5));
		Output.rgb = base2;
	}
	Output.a = base;

	return Output;
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
// Technique Section for Orca Skill1 Remove
//--------------------------------------------------------------//
technique Orca1_Remove
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_orcaSkill1_Remove();
	}
	pass Pass_1
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_orcaSkill1_Remove_1();
	}
	pass Pass_2
	{
		VertexShader = compile vs_2_0 vs_FrameAdd();
		PixelShader = compile ps_2_0 ps_orcaSkill1_Remove_2();
	}
}

//--------------------------------------------------------------//
// Technique Section for Orca Skill2
//--------------------------------------------------------------//
technique Orca2
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_orcaSkill2();
	}
}

//--------------------------------------------------------------//
// Technique Section for BackAtk
//--------------------------------------------------------------//
technique OrcaBackAtk
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_orcaBackAtk();
	}
}

//--------------------------------------------------------------//
// Technique Section for MagicArray
//--------------------------------------------------------------//

technique MagicArray
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_Rotation();
		PixelShader = compile ps_2_0 ps_magicArrayShader();
	}
}

//--------------------------------------------------------------//
// Technique Section for GlobeAtk
//--------------------------------------------------------------//
technique GlobeAtk
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_globeAtk();
	}
}

//--------------------------------------------------------------//
// Technique Section for GlobeAtk
//--------------------------------------------------------------//
technique GlobeAtk2
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_FrameAdd();
		PixelShader = compile ps_2_0 ps_asdf();
	}
}



//--------------------------------------------------------------//
// Test Shader
//--------------------------------------------------------------//

float4 ps_test(VS_OUTPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mUV);

//	albedo.r = albedo.r * 0.5;
//	albedo.g = albedo.g * 0.5;
//	albedo.b = albedo.b * 2;
//	albedo = 1;
	return albedo;
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




