#pragma once
#include "../pch.h"
#include "common_Template.h"
namespace KtLib
{

	class KtPixelShaderBase
	{
	public:
		KtPixelShaderBase() : m_pPixelShader(nullptr)
		{
			Init();
		}
		virtual ~KtPixelShaderBase()
		{
			SafeRelease(m_pPixelShader);
		}

		void SetPixelShader();

	protected:
		virtual bool Init() = 0;
		bool InitShaderFromFile(WCHAR* szFileName);

	private:
		HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

		ID3D11PixelShader*		m_pPixelShader;

	};

	class PixelShaderBasic : public KtPixelShaderBase
	{
	public:
		
	private:
		bool Init()override;
		
	};


}	//namespace KtLib
