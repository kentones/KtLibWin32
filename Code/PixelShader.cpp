#include "pch.h"
#include <d3dcompiler.h>
#include "PixelShader.h"
#include "SystemBase.h"
#include "Renderer_DirectX11.h"



namespace KtLib
{
	void KtPixelShaderBase::SetPixelShader()
	{
		KtSystem::GetInstance()->GetRenderer()->GetDeviceContext()->PSSetShader(m_pPixelShader, nullptr, 0);
	}
	
	HRESULT KtPixelShaderBase::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr = S_OK;

		unsigned int dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
		// Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
		// Setting this flag improves the shader debugging experience, but still allows 
		// the shaders to be optimized and to run exactly the way they will run in 
		// the release configuration of this program.
		dwShaderFlags |= D3DCOMPILE_DEBUG;

		// Disable optimizations to further improve shader debugging
		dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob)
			{
				OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
				pErrorBlob->Release();
			}
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		return S_OK;
	}
	// protected init helper
	bool KtPixelShaderBase::InitShaderFromFile(WCHAR* szFileName)
	{
		HRESULT hr;
		
		// Compile the pixel shader
		ID3DBlob* pPSBlob = nullptr;
		hr = CompileShaderFromFile(szFileName, "PS", "ps_4_0", &pPSBlob);
		if (FAILED(hr))
		{
			MessageBox(nullptr,
				L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return false;
		}

		// Create the pixel shader
		ID3D11PixelShader* pPShader = nullptr;

		ID3D11Device *pDevice = KtSystem::GetInstance()->GetRenderer()->GetDevice();

		hr = pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &pPShader);
		if (FAILED(hr))
		{
			pPSBlob->Release();
			return false;
		}
		m_pPixelShader = pPShader;

		pPSBlob->Release();

		return true;
	}



	bool PixelShaderBasic::Init()
	{
		// Compile the vertex shader
		return InitShaderFromFile(L"code/Shader/BasicEffect.fx");
	}



}	//namespace KtLib