#include "pch.h"

#include "RenderableBase.h"
#include "SystemBase.h"
#include "Renderer_DirectX11.h"
#include "common_Struct.h"

namespace KtLib
{


	bool RenderableRect::Setup()
	{
		// Create Vertex(using types from VertexStruct.h )
		
		// Create Vertex Buffer
		// Create Constant Buffer(if needed)
		m_Vtx[0].SetValue(KtVector3(-0.5f, -0.5f, 0.0f), KtVector3(0.0f, 0.0f, 1.0f), KtColor(1.0f, 1.0f, 1.0f, 1.0f));
		m_Vtx[1].SetValue(KtVector3( 0.5f, -0.5f, 0.0f), KtVector3(0.0f, 0.0f, 1.0f), KtColor(1.0f, 1.0f, 1.0f, 1.0f));
		m_Vtx[2].SetValue(KtVector3(-0.5f,  0.5f, 0.0f), KtVector3(0.0f, 0.0f, 1.0f), KtColor(1.0f, 1.0f, 1.0f, 1.0f));
		m_Vtx[3].SetValue(KtVector3( 0.5f,  0.5f, 0.0f), KtVector3(0.0f, 0.0f, 1.0f), KtColor(1.0f, 1.0f, 1.0f, 1.0f));

		KtSystem::GetInstance()->GetRenderer()->CreateVertexBuffer( &m_Vtx, sizeof(VertexPosNorTex), 4, m_pVtxBuffer);
		KtSystem::GetInstance()->GetRenderer()->CreateConstantBuffer( 10, m_pConstantBuffer );
		return true;
	}

	void RenderableRect::Render()
	{
		//Set InputLayout
		//Set Vertex Shader
		//Set Pixel Shader
		//Set Sampler
		//Set Primitive toplogy
		//Set Vertex Buffer
		//Set Constant Buffer(if needed)
		//Draw Primitive(or Primitive Indexed)

		KtSystem::GetInstance()->GetRenderer()->SetVertexBuffer(m_pVtxBuffer);
		KtSystem::GetInstance()->GetRenderer()->SetVertexShader(eVERTEXSHADER_TEST);
		KtSystem::GetInstance()->GetRenderer()->SetPixelShader(ePIXELSHADER_TEST);
		KtSystem::GetInstance()->GetRenderer()->DrawPrimitive(4);
	}

	void RenderableRect::UpdatePos(float x, float y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
		KtSystem::GetInstance()->GetRenderer()->UpdateConstantBuffer()
	}
	void RenderableRect::UpdateSize(float sizeX, float sizeY)
	{
		m_Size.x = sizeX;
		m_Size.y = sizeY;
	}
	void RenderableRect::UpdateViewport(float viewportWidth, float viewportHeight)
	{
		m_ViewportSize.x = viewportWidth;
		m_ViewportSize.y = viewportHeight;
	}
	void RenderableRect::UpdateColor(float r, float g, float b, float a)
	{
		m_Color.R = r;
		m_Color.G = g;
		m_Color.B = b;
		m_Color.A = a;
	}



}	//namespace KtLib