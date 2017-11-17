#pragma once

#include <d3d11_1.h>
#include "common_Template.h"

namespace KtLib
{
	//////////////////////////////////////////////////////////////////////////////////
	// Vertex Buffer
	//////////////////////////////////////////////////////////////////////////////////

	class KtVertexBuffer
	{
		friend class KtRenderer;
	public:
		KtVertexBuffer():m_pVtxBuffer(nullptr){}
		~KtVertexBuffer()
		{
			SafeRelease(m_pVtxBuffer);
		}

	protected:
		unsigned int	m_SingleVertexBytes;
		ID3D11Buffer*	m_pVtxBuffer;

	};

	class KtVertexBufferIndexed
	{
		friend class KtRenderer;
	public:
		KtVertexBufferIndexed() :m_pVtxBuffer(nullptr), m_pIdxBuffer(nullptr) {}
		~KtVertexBufferIndexed()
		{
			SafeRelease(m_pVtxBuffer);
			SafeRelease(m_pIdxBuffer);
		}
	protected:
		unsigned int	m_SingleVertexBytes;
		ID3D11Buffer*	m_pVtxBuffer;
		ID3D11Buffer*	m_pIdxBuffer;

	};

	//////////////////////////////////////////////////////////////////////////////////
	// Constant Buffer
	//////////////////////////////////////////////////////////////////////////////////
	class KtConstantBuffer
	{
		friend class KtRenderer;
	public:
		KtConstantBuffer() :m_pConstantBuffer(nullptr) {}
		~KtConstantBuffer()
		{
			SafeRelease(m_pConstantBuffer);
		}
	protected:
		ID3D11Buffer* m_pConstantBuffer;

	};






}	//namespace KtLib
