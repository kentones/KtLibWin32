#pragma once

namespace KtLib
{
	//////////////////////////////////////////////////////////////////////////////////
	// Vertex Buffer
	//////////////////////////////////////////////////////////////////////////////////

	class KtVertexBufferBase
	{
	public:
		virtual ~KtVertexBufferBase() {}
		enum eVextexBufferType
		{
			eVERTEXBUFFERTYPE_DX11_VERTEX,
			eVERTEXBUFFERTYPE_DX11_VERTEXINDEXED,
			eVERTEXBUFFERTYPE_MAX
		};

		eVextexBufferType GetType()const { return m_VertexBufferType; }

	protected:
		unsigned int		m_SingleVertexBytes;
		eVextexBufferType	m_VertexBufferType;

	};

	//////////////////////////////////////////////////////////////////////////////////
	// Constant Buffer
	//////////////////////////////////////////////////////////////////////////////////
	class KtConstantBufferBase
	{
	public:
		virtual ~KtConstantBufferBase() {}
		enum eConstantBufferType
		{
			eCONSTANTBUFFERTYPE_DX11,
			eCONSTANTBUFFERTYPE_MAX
		};

		eConstantBufferType GetType()const { return m_ConstantBufferType; }

	protected:
		eConstantBufferType	m_ConstantBufferType;

	};





}	//namespace KtLib
