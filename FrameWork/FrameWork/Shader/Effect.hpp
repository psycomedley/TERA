float4x4	g_matWVP : WorldViewProjection;
texture		DiffuseMap_Tex;
float		g_fTime;

sampler2D DiffuseSampler = sampler_state
{
	Texture = <DiffuseMap_Tex>;
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

//--------------------------------------------------------------//
// Vertex Shader
//--------------------------------------------------------------//

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
	Output.mUV = float2(Input.mUV.x + g_fTime, Input.mUV.y);;

	return Output;
}

VS_OUTPUT vs_frameMoveY(VS_INPUT Input)
{
	VS_OUTPUT Output;

	Output.mPosition = mul(Input.mPosition, g_matWVP);
	Output.mUV = float2(Input.mUV.x, Input.mUV.y + g_fTime);;

	return Output;
}

//--------------------------------------------------------------//
// Pixel Shader
//--------------------------------------------------------------//

//--------------------------------------------------------------//
// Test Shader
//--------------------------------------------------------------//

float4 ps_main(VS_OUTPUT Input) : COLOR
{
	float4 albedo = tex2D(DiffuseSampler, Input.mUV);
//	albedo.a = 0.5;
//	albedo = albedo * float4(0.0f, 1.0f, 1.0f, 0.5f);
	return albedo;
}




//--------------------------------------------------------------//
// Technique Section for ColorShader
//--------------------------------------------------------------//

technique ColorShader
{
	pass Pass_0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}

//--------------------------------------------------------------//
// Frame MoveX
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
	// Frame MoveY
	//--------------------------------------------------------------//
	technique FrameMoveY
		{
			pass Pass_0
			{
				VertexShader = compile vs_2_0 vs_frameMoveY();
				PixelShader = compile ps_2_0 ps_main();
			}
		}