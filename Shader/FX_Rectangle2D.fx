//--------------------------------------------------------------------------------------
// File: Tutorial07.fx
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
cbuffer Position : register( b0 )
{
	float4 position;
}; 
cbuffer Size : register( b1 )
{
	float2 size;
	float2 viewportSize;
};
cbuffer Color : register( b2 )
{
	float4 color;
};



//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
float4 VS( float4 Pos : POSITION) : SV_POSITION
{

    return float4(	(	Pos.x * size.x + position.x ) / viewportSize.x,
					(	Pos.y * size.y + position.y ) / viewportSize.y,
						Pos.z, 1.0f);
}


//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(float4 Pos : SV_POSITION) : SV_Target
{
    return color;
}
