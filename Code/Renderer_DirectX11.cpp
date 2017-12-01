#include "pch.h"

#include "Renderer_DirectX11.h"
#include "GraphicBuffer_DirectX11.h"
#include "VertexShader.h"
#include "PixelShader.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;


namespace KtLib
{
	//////////////////////////////////////////////////////////////////////////////////
	// Public
	//////////////////////////////////////////////////////////////////////////////////
	KtRenderer::KtRenderer() :
		m_window(nullptr),
		m_outputWidth(800),
		m_outputHeight(600),
		m_featureLevel(D3D_FEATURE_LEVEL_9_1)
	{
	}



	bool KtRenderer::Init(HWND window, int width, int height)
	{
		m_window = window;
		m_outputWidth = std::max(width, 1);
		m_outputHeight = std::max(height, 1);

		CreateDevice();

		CreateResources();

		SetupAllVertexShader();
		SetupAllPixelShader();

		return true;
	}
	void KtRenderer::Release()
	{
		for (int i = 0; i < eVERTEXSHADER_MAX; i++)
		{
			SafeDelete(m_apVertexShader[i]);
		}
		for (int i = 0; i < ePIXELSHADER_MAX; i++)
		{
			SafeDelete(m_apPixelShader[i]);
		}

		//スマートポインターで作った物は削除しないように（自動で削除されるので）
	}
	void KtRenderer::Render()
	{
		// バックバッファをクリア
		Clear();
		
		// 描画処理
		for (int i = 0; i < eRENDERLAYER_MAX; i++)
		{
			RenderSetting(static_cast<eRenderLayer>(i));
			m_RenderLayer[i].Render();
			m_RenderLayer[i].Clear();
		}

		// バックバッファを画面に出す
		Present();
	}

	void KtRenderer::PushToRenderLayer(KtRenderableBase* pRenderable, eRenderLayer eLayer)
	{
		m_RenderLayer[eLayer].PushBack(pRenderable);
	}

	// Message handlers
	void KtRenderer::OnActivated()
	{
		// TODO: Game is becoming active window.

	}
	void KtRenderer::OnDeactivated()
	{
		// TODO: Game is becoming background window.
	}
	void KtRenderer::OnSuspending()
	{
		// TODO: Game is being power-suspended (or minimized).
	}
	void KtRenderer::OnResuming()
	{
		// TODO: Game is being power-resumed (or returning from minimize).
	}
	void KtRenderer::OnWindowSizeChanged(int width, int height)
	{
		m_outputWidth = std::max(width, 1);
		m_outputHeight = std::max(height, 1);

		CreateResources();

		// TODO: Game window is being resized.
	}

	// Vertex Buffer
	bool KtRenderer::CreateVertexBuffer(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, KtVertexBuffer* pOut)
	{
		KtVertexBuffer* pOutBufferTemp = nullptr;
		pOutBufferTemp = new KtVertexBuffer;
		if (!pOutBufferTemp) 
		{
			return false;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = singleVertexBytes * totalVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = pVertexDataIn;
		if (FAILED(m_d3dDevice->CreateBuffer(&bd, &InitData, &pOutBufferTemp->m_pVtxBuffer)))
		{
			delete pOutBufferTemp;
			return false;
		}
		pOutBufferTemp->m_SingleVertexBytes = singleVertexBytes;
		pOut = pOutBufferTemp;
		return true;
	}
	bool KtRenderer::CreateVertexBufferIndexed(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, unsigned int* const pIndexDataIn, unsigned int totalIndex, KtVertexBufferIndexed* pOut)
	{
		KtVertexBufferIndexed* pOutBufferTemp = nullptr;
		pOutBufferTemp = new KtVertexBufferIndexed;
		if (!pOutBufferTemp)
		{
			return false;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = singleVertexBytes * totalVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = pVertexDataIn;
		if (FAILED(m_d3dDevice->CreateBuffer(&bd, &InitData, &pOutBufferTemp->m_pVtxBuffer)))
		{
			delete pOutBufferTemp;
			return false;
		}

		// Create index buffer
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int) * totalIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		InitData.pSysMem = pIndexDataIn;
		if (FAILED(m_d3dDevice->CreateBuffer(&bd, &InitData, &pOutBufferTemp->m_pIdxBuffer)))
		{
			delete pOutBufferTemp;
			return false;
		}
		pOutBufferTemp->m_SingleVertexBytes = singleVertexBytes;
		pOut = pOutBufferTemp;

		return true;

	}
	void KtRenderer::SetVertexBuffer(KtVertexBuffer* const pIn)
	{
		m_d3dContext->IASetVertexBuffers(0, 1, &pIn->m_pVtxBuffer, &pIn->m_SingleVertexBytes, 0);
	}
	void KtRenderer::SetVertexBufferIndexed(KtVertexBufferIndexed* const pIn)
	{
		m_d3dContext->IASetVertexBuffers(0, 1, &pIn->m_pVtxBuffer, &pIn->m_SingleVertexBytes, 0);
		m_d3dContext->IASetIndexBuffer(pIn->m_pIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
	}
	

	// Constant Buffer
	bool KtRenderer::CreateConstantBuffer( unsigned int structSizeBytes, KtConstantBuffer* pOut)
	{
		KtConstantBuffer* pOutBufferTemp = nullptr;
		pOutBufferTemp = new KtConstantBuffer;
		if (!pOutBufferTemp)
		{
			return false;
		}

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.ByteWidth = structSizeBytes;

		if (FAILED(m_d3dDevice->CreateBuffer(&bd, nullptr, &pOutBufferTemp->m_pConstantBuffer)))
		{
			delete pOutBufferTemp;
			return false;
		}

		pOut = pOutBufferTemp;
		return true;

	}
	void KtRenderer::UpdateConstantBuffer(const void* pDataIn, KtConstantBuffer* pOut)
	{
		m_d3dContext->UpdateSubresource(pOut->m_pConstantBuffer, 0, nullptr, pDataIn, 0, 0);
	}
	void KtRenderer::VSSetConstantBuffer(unsigned int slot, unsigned int numBuffers, KtConstantBuffer* const pIn)
	{
		m_d3dContext->VSSetConstantBuffers(slot, numBuffers, &pIn->m_pConstantBuffer);
	}
	void KtRenderer::PSSetConstantBuffer(unsigned int slot, unsigned int numBuffers, KtConstantBuffer* const pIn)
	{
		m_d3dContext->PSSetConstantBuffers(slot, numBuffers, &pIn->m_pConstantBuffer);
	}

	// DrawPrimitive
	void KtRenderer::DrawPrimitive(unsigned int totalVertex)
	{
		m_d3dContext->Draw(totalVertex, 0);
	}
	void KtRenderer::DrawPrimitiveIndexed(unsigned int totalIndex)
	{
		m_d3dContext->DrawIndexed(totalIndex, 0, 0);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Private
	//////////////////////////////////////////////////////////////////////////////////
	// Helper method to clear the back buffers.
	void KtRenderer::Clear()
	{

		// Clear the views.
		m_d3dContext->ClearRenderTargetView(m_renderTargetView.Get(), Colors::CornflowerBlue);
		m_d3dContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		m_d3dContext->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());

		// Set the viewport.
		CD3D11_VIEWPORT viewport(0.0f, 0.0f, static_cast<float>(m_outputWidth), static_cast<float>(m_outputHeight));
		m_d3dContext->RSSetViewports(1, &viewport);
	}

	// Presents the back buffer contents to the screen.
	void KtRenderer::Present()
	{
		// The first argument instructs DXGI to block until VSync, putting the application
		// to sleep until the next VSync. This ensures we don't waste any cycles rendering
		// frames that will never be displayed to the screen.
		HRESULT hr = m_swapChain->Present(1, 0);

		// If the device was reset we must completely reinitialize the renderer.
		if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
		{
			OnDeviceLost();
		}
		else
		{
			DX::ThrowIfFailed(hr);
		}
	}

	// These are the resources that depend on the device.
	void KtRenderer::CreateDevice()
	{
		UINT creationFlags = 0;

#ifdef _DEBUG
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		static const D3D_FEATURE_LEVEL featureLevels[] =
		{
			// TODO: Modify for supported Direct3D feature levels
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1,
		};

		// Create the DX11 API device object, and get a corresponding context.
		ComPtr<ID3D11Device> device;
		ComPtr<ID3D11DeviceContext> context;
		DX::ThrowIfFailed(D3D11CreateDevice(
			nullptr,                            // specify nullptr to use the default adapter
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			featureLevels,
			_countof(featureLevels),
			D3D11_SDK_VERSION,
			device.ReleaseAndGetAddressOf(),    // returns the Direct3D device created
			&m_featureLevel,                    // returns feature level of device created
			context.ReleaseAndGetAddressOf()    // returns the device immediate context
		));

#ifndef NDEBUG
		ComPtr<ID3D11Debug> d3dDebug;
		if (SUCCEEDED(device.As(&d3dDebug)))
		{
			ComPtr<ID3D11InfoQueue> d3dInfoQueue;
			if (SUCCEEDED(d3dDebug.As(&d3dInfoQueue)))
			{
#ifdef _DEBUG
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_CORRUPTION, true);
				d3dInfoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR, true);
#endif
				D3D11_MESSAGE_ID hide[] =
				{
					D3D11_MESSAGE_ID_SETPRIVATEDATA_CHANGINGPARAMS,
					// TODO: Add more message IDs here as needed.
				};
				D3D11_INFO_QUEUE_FILTER filter = {};
				filter.DenyList.NumIDs = _countof(hide);
				filter.DenyList.pIDList = hide;
				d3dInfoQueue->AddStorageFilterEntries(&filter);
			}
		}
#endif

		DX::ThrowIfFailed(device.As(&m_d3dDevice));
		DX::ThrowIfFailed(context.As(&m_d3dContext));

		// TODO: Initialize device dependent objects here (independent of window size).

	}

	// Allocate all memory resources that change on a window SizeChanged event.
	void KtRenderer::CreateResources()
	{
		// Clear the previous window size specific context.
		ID3D11RenderTargetView* nullViews[] = { nullptr };
		m_d3dContext->OMSetRenderTargets(_countof(nullViews), nullViews, nullptr);
		m_renderTargetView.Reset();
		m_depthStencilView.Reset();
		m_d3dContext->Flush();

		UINT backBufferWidth = static_cast<UINT>(m_outputWidth);
		UINT backBufferHeight = static_cast<UINT>(m_outputHeight);
		DXGI_FORMAT backBufferFormat = DXGI_FORMAT_B8G8R8A8_UNORM;
		DXGI_FORMAT depthBufferFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
		UINT backBufferCount = 2;

		// If the swap chain already exists, resize it, otherwise create one.
		if (m_swapChain)
		{
			HRESULT hr = m_swapChain->ResizeBuffers(backBufferCount, backBufferWidth, backBufferHeight, backBufferFormat, 0);

			if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET)
			{
				// If the device was removed for any reason, a new device and swap chain will need to be created.
				OnDeviceLost();

				// Everything is set up now. Do not continue execution of this method. OnDeviceLost will reenter this method 
				// and correctly set up the new device.
				return;
			}
			else
			{
				DX::ThrowIfFailed(hr);
			}
		}
		else
		{
			// First, retrieve the underlying DXGI Device from the D3D Device.
			ComPtr<IDXGIDevice1> dxgiDevice;
			DX::ThrowIfFailed(m_d3dDevice.As(&dxgiDevice));

			// Identify the physical adapter (GPU or card) this device is running on.
			ComPtr<IDXGIAdapter> dxgiAdapter;
			DX::ThrowIfFailed(dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()));

			// And obtain the factory object that created it.
			ComPtr<IDXGIFactory2> dxgiFactory;
			DX::ThrowIfFailed(dxgiAdapter->GetParent(IID_PPV_ARGS(dxgiFactory.GetAddressOf())));

			// Create a descriptor for the swap chain.
			DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
			swapChainDesc.Width = backBufferWidth;
			swapChainDesc.Height = backBufferHeight;
			swapChainDesc.Format = backBufferFormat;
			swapChainDesc.SampleDesc.Count = 1;
			swapChainDesc.SampleDesc.Quality = 0;
			swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			swapChainDesc.BufferCount = backBufferCount;

			DXGI_SWAP_CHAIN_FULLSCREEN_DESC fsSwapChainDesc = {};
			fsSwapChainDesc.Windowed = TRUE;

			// Create a SwapChain from a Win32 window.
			DX::ThrowIfFailed(dxgiFactory->CreateSwapChainForHwnd(
				m_d3dDevice.Get(),
				m_window,
				&swapChainDesc,
				&fsSwapChainDesc,
				nullptr,
				m_swapChain.ReleaseAndGetAddressOf()
			));

			// This template does not support exclusive fullscreen mode and prevents DXGI from responding to the ALT+ENTER shortcut.
			DX::ThrowIfFailed(dxgiFactory->MakeWindowAssociation(m_window, DXGI_MWA_NO_ALT_ENTER));
		}

		// Obtain the backbuffer for this window which will be the final 3D rendertarget.
		ComPtr<ID3D11Texture2D> backBuffer;
		DX::ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBuffer.GetAddressOf())));

		// Create a view interface on the rendertarget to use on bind.
		DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, m_renderTargetView.ReleaseAndGetAddressOf()));

		// Allocate a 2-D surface as the depth/stencil buffer and
		// create a DepthStencil view on this surface to use on bind.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(depthBufferFormat, backBufferWidth, backBufferHeight, 1, 1, D3D11_BIND_DEPTH_STENCIL);

		ComPtr<ID3D11Texture2D> depthStencil;
		DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&depthStencilDesc, nullptr, depthStencil.GetAddressOf()));

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		DX::ThrowIfFailed(m_d3dDevice->CreateDepthStencilView(depthStencil.Get(), &depthStencilViewDesc, m_depthStencilView.ReleaseAndGetAddressOf()));

		// TODO: Initialize windows-size dependent objects here.


	}

	void KtRenderer::OnDeviceLost()
	{
		// TODO: Add Direct3D resource cleanup here.


		m_depthStencilView.Reset();
		m_renderTargetView.Reset();
		m_swapChain.Reset();
		m_d3dContext.Reset();
		m_d3dDevice.Reset();

		CreateDevice();

		CreateResources();
	}

	void KtRenderer::RenderSetting(eRenderLayer eLayer)
	{
		//共通設定
		

		//個別設定
		switch (eLayer)
		{
		case eRENDERLAYER_2D_BG:
			break;
		case eRENDERLAYER_3D_SKYDOME:
			break;
		case eRENDERLAYER_3D_TERRAIN:
			break;
		case eRENDERLAYER_3D_OBJECT:
			//m_RenderLayer[eLayer].ZSortNearToFar();
			break;
		case eRENDERLAYER_EFFECT:
			//m_RenderLayer[eLayer].ZSortFarToNear();
			break;
		case eRENDERLAYER_UI:
			break;
		case eRENDERLAYER_FADE:
			break;
		default:
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Vertex Shader
	//////////////////////////////////////////////////////////////////////////////////
		// Public
		//////////////////////////////////////////////////////////////////////////////////
	void KtRenderer::SetVertexShader(eVertexShaderType eVSType)
	{
		m_apVertexShader[eVSType]->SetVertexShader();
	}
	void KtRenderer::SetPixelShader(ePixelShaderType ePSType)
	{
		m_apPixelShader[ePSType]->SetPixelShader();
	}





		//////////////////////////////////////////////////////////////////////////////////
		// Private
		//////////////////////////////////////////////////////////////////////////////////
	bool KtRenderer::SetupAllVertexShader()
	{
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			m_apVertexShader[eVERTEXSHADER_TEST] = new KtVertexShader(L"Shader/FX_Rectangle2D.fx", layout, ARRAYSIZE(layout), D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		}
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			m_apVertexShader[eVERTEXSHADER_PHONE] = new KtVertexShader(L"Shader/FX_Rectangle2D.fx", layout, ARRAYSIZE(layout), D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		for (int i = 0; i < eVERTEXSHADER_MAX; i++)
		{
			if (!m_apVertexShader[i]->IsInitialized())
			{	return false;	}
		}
		return true;
	}

	bool KtRenderer::SetupAllPixelShader() 
	{
		m_apPixelShader[ePIXELSHADER_TEST]	= new KtPixelShader(L"Shader/FX_Rectangle2D.fx");
		m_apPixelShader[ePIXELSHADER_PHONE] = new KtPixelShader(L"Shader/FX_Rectangle2D.fx");
		m_apPixelShader[ePIXELSHADER_BLINN] = new KtPixelShader(L"Shader/FX_Rectangle2D.fx");

		for (int i = 0; i < ePIXELSHADER_MAX; i++)
		{
			if (!m_apPixelShader[i]->IsInitialized())
			{	return false;	}
		}
		return true;
	}









}	//namespace KtLib