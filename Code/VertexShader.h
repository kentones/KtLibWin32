#pragma once
#include "../pch.h"
#include "common_Template.h"
namespace KtLib
{

	class KtVertexShader
	{
	public:
		KtVertexShader(WCHAR* szFileName, D3D11_INPUT_ELEMENT_DESC layout[], unsigned int elementLayoutSize, D3D_PRIMITIVE_TOPOLOGY ePrimtiveTopology) : m_pVertexShader(nullptr), m_pInputLayout(nullptr), m_InitSuccess(false)
		{
			m_InitSuccess = InitShaderFromFile(szFileName, layout, elementLayoutSize);
			SetPrimtiveTopology(ePrimtiveTopology);
		}
		~KtVertexShader()
		{
			SafeRelease(m_pVertexShader);
			SafeRelease(m_pInputLayout);
			m_InitSuccess = false;
		}
		const bool IsInitialized()const;
		void SetVertexShader();

	private:
		KtVertexShader();
		KtVertexShader(const KtVertexShader&) {}
		void operator=(const KtVertexShader& src) {}

		bool InitShaderFromFile(WCHAR* szFileName, D3D11_INPUT_ELEMENT_DESC layout[], unsigned int elementLayoutSize);
		void SetPrimtiveTopology(D3D_PRIMITIVE_TOPOLOGY ePrimtiveTopology);

		HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

		ID3D11VertexShader*		m_pVertexShader;
		ID3D11InputLayout*		m_pInputLayout;
		D3D_PRIMITIVE_TOPOLOGY	m_PrimtiveTopology;
		bool					m_InitSuccess;
	};


}	//namespace KtLib
