#pragma once
#include "../pch.h"
#include "common_Template.h"
namespace KtLib
{

	class KtPixelShader
	{
	public:
		KtPixelShader(WCHAR* szFileName) : m_pPixelShader(nullptr), m_InitSuccess(false)
		{
			m_InitSuccess = InitShaderFromFile(szFileName);
		}
		~KtPixelShader()
		{
			SafeRelease(m_pPixelShader);
			m_InitSuccess = false;
		}
		const bool IsInitialized()const;
		void SetPixelShader();

	private:
		KtPixelShader();
		KtPixelShader(const KtPixelShader&) {}
		void operator=(const KtPixelShader& src) {}

		bool InitShaderFromFile(WCHAR* szFileName);

		HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

		ID3D11PixelShader*		m_pPixelShader;
		bool					m_InitSuccess;
	};
}	//namespace KtLib
