#pragma once

#include <d3d11_1.h>
#include "common_Template.h"
#include "GraphicBufferBase.h"

namespace KtLib
{
	//////////////////////////////////////////////////////////////////////////////////
	// Vertex Buffer
	//////////////////////////////////////////////////////////////////////////////////

	class VertexBufferDirectX11 : public KtVertexBufferBase
	{
		friend class RendererDirectX11;
	public:
		VertexBufferDirectX11():m_pVtxBuffer(nullptr){}
		~VertexBufferDirectX11()
		{
			SafeRelease(m_pVtxBuffer);
		}

	protected:
		ID3D11Buffer* m_pVtxBuffer;

	};

	class VertexBufferIndexedDirectX11 : public KtVertexBufferBase
	{
		friend class RendererDirectX11;
	public:
		VertexBufferIndexedDirectX11() :m_pVtxBuffer(nullptr), m_pIdxBuffer(nullptr) {}
		~VertexBufferIndexedDirectX11()
		{
			SafeRelease(m_pVtxBuffer);
			SafeRelease(m_pIdxBuffer);
		}
	protected:
		ID3D11Buffer* m_pVtxBuffer;
		ID3D11Buffer* m_pIdxBuffer;

	};

	//////////////////////////////////////////////////////////////////////////////////
	// Constant Buffer
	//////////////////////////////////////////////////////////////////////////////////
	class ConstantBufferDirectX11 : public KtConstantBufferBase
	{
		friend class RendererDirectX11;
	public:
		ConstantBufferDirectX11() :m_pConstantBuffer(nullptr) {}
		~ConstantBufferDirectX11()
		{
			SafeRelease(m_pConstantBuffer);
		}
	protected:
		ID3D11Buffer* m_pConstantBuffer;

	};






}	//namespace KtLib
