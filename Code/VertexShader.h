#pragma once
#include "../pch.h"
#include "common_Template.h"
namespace KtLib
{

	class KtVertexShaderBase
	{
	public:
		KtVertexShaderBase() : m_pVertexShader(nullptr), m_pInputLayout(nullptr)
		{
			Init();
		}
		virtual ~KtVertexShaderBase()
		{
			SafeRelease(m_pVertexShader);
			SafeRelease(m_pInputLayout);
		}

		void SetVertexShader();

	protected:
		virtual bool Init() = 0;
		bool InitShaderFromFile(WCHAR* szFileName, D3D11_INPUT_ELEMENT_DESC layout[], unsigned int elementLayoutSize);
		void SetPrimtiveTopology(D3D_PRIMITIVE_TOPOLOGY ePrimtiveTopology);

	private:
		HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

		ID3D11VertexShader*		m_pVertexShader;
		ID3D11InputLayout*		m_pInputLayout;
		D3D_PRIMITIVE_TOPOLOGY	m_PrimtiveTopology;

	};

	class VertexShaderBasic : public KtVertexShaderBase
	{
	public:
		
	private:
		bool Init()override;
		
	};


}	//namespace KtLib
