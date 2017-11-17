#include "pch.h"

#include "RenderableBase.h"
#include "SystemBase.h"
#include "Renderer_DirectX11.h"

namespace KtLib
{
	bool RenderableRect::Setup()
	{
		// Create Vertex(using types from VertexStruct.h )
		// Create Vertex Buffer
		// Create Constant Buffer(if needed)
		
		//Vertex vertex[]= 
		//{
		//	{ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f , 1.0f, 1.0f, 1.0f, 1.0f },
		//	{  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f , 1.0f, 1.0f, 1.0f, 1.0f },
		//	{ -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f , 1.0f, 1.0f, 1.0f, 1.0f },
		//	{  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f , 1.0f, 1.0f, 1.0f, 1.0f }
		//};

		//KtSystem::GetInstance()->GetRenderer()->CreateVertexBuffer( &vertex, sizeof(Vertex), 4, m_pVtxBuffer);

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
		KtSystem::GetInstance()->GetRenderer()->SetPrimitiveTopology(KtRenderer::ePRIMITIVETOPOLOGY_TRIANGLESTRIP);
		KtSystem::GetInstance()->GetRenderer()->DrawPrimitive(4);
	}


}	//namespace KtLib