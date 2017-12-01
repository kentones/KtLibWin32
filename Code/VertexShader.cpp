#include "pch.h"
#include <d3dcompiler.h>
#include "VertexShader.h"
#include "SystemBase.h"
#include "Renderer_DirectX11.h"



namespace KtLib
{
	void KtVertexShader::SetVertexShader()
	{
		KtSystem::GetInstance()->GetRenderer()->GetDeviceContext()->VSSetShader(m_pVertexShader, nullptr, 0);
		KtSystem::GetInstance()->GetRenderer()->GetDeviceContext()->IASetInputLayout(m_pInputLayout);
	}

	const bool KtVertexShader::IsInitialized()const
	{
		return m_InitSuccess;
	}

	
	HRESULT KtVertexShader::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
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
		hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
			dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
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
	bool KtVertexShader::InitShaderFromFile(WCHAR* szFileName, D3D11_INPUT_ELEMENT_DESC layout[], unsigned int elementLayoutSize)
	{
		HRESULT hr;
		
		// Compile the vertex shader
		ID3DBlob* pVSBlob = nullptr;
		hr = CompileShaderFromFile(szFileName, "VS", "vs_5_0", &pVSBlob);
		if (FAILED(hr))
		{
			MessageBox(nullptr,	L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
			return false;
		}

		// Create the vertex shader
		ID3D11VertexShader* pVShader = nullptr;

		ID3D11Device *pDevice = KtSystem::GetInstance()->GetRenderer()->GetDevice();

		hr = pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &pVShader);
		if (FAILED(hr))
		{
			pVSBlob->Release();
			return false;
		}
		m_pVertexShader = pVShader;

		// Create the input layout
		ID3D11InputLayout* pInputLayout = nullptr;
		hr = pDevice->CreateInputLayout(layout, elementLayoutSize, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &pInputLayout);
		pVSBlob->Release();
		if (FAILED(hr))
		{
			return false;
		}

		m_pInputLayout = pInputLayout;
		return true;
	}

	void KtVertexShader::SetPrimtiveTopology(D3D_PRIMITIVE_TOPOLOGY ePrimtiveTopology)
	{
		m_PrimtiveTopology = ePrimtiveTopology;
	}

	/*
	bool VertexShaderBasic::Init()
	{
		SetPrimtiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		// Define the input layout
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		// Compile the vertex shader
		return InitShaderFromFile(L"code/Shader/BasicEffect.fx", layout, ARRAYSIZE(layout));
	}
	*/


}	//namespace KtLib