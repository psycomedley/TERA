float4x4	g_matWVP : WorldViewProjection;
texture		DiffuseMap_Tex;
texture		DiffuseMap_Tex2;
float		g_fTime;
float		g_fAlpha;

sampler2D DiffuseSampler = sampler_state
{
	Texture = <DiffuseMap_Tex>;
};

sampler2D DiffuseSampler2 = sampler_state
{
	Texture = <DiffuseMap_Tex2>;
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
// Frame Add Shader
//--------------------------------------------------------------//

VS_OUTPUT vs_frameMoveX(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV = float2(Input.mUV.x + g_fTime, Input.mUV.y);

	return Output;
}

VS_OUTPUT vs_frameMoveY(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV = float2(Input.mUV.x, Input.mUV.y + g_fTime);

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
// Test Shader
//--------------------------------------------------------------//

float4 ps_test(VS_OUTPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mUV);
	albedo.b = albedo.b * 4;

	float4 albedo2 = tex2D(DiffuseSampler2, Input.mUV);
	albedo2.b = albedo2.b * 4;

	return ((albedo + albedo2) / 2);
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
		VertexShader = compile vs_2_0 vs_main();
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