#include "pch.h"

#include "Renderer_DirectX11.h"
#include "GraphicBuffer_DirectX11.h"

using namespace DirectX;
using Microsoft::WRL::ComPtr;

namespace
{
	// KtRendererBaseの primitive topologyをD3DX11に変換
	static const D3D_PRIMITIVE_TOPOLOGY sc_PrimitiveTopologyTable[KtLib::KtRendererBase::ePrimitiveTopology::ePRIMITIVETOPOLOGY_MAX] =
	{
		D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED,
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
	};
}


namespace KtLib
{
	//////////////////////////////////////////////////////////////////////////////////
	// Public
	//////////////////////////////////////////////////////////////////////////////////
	RendererDirectX11::RendererDirectX11() :
		m_window(nullptr),
		m_outputWidth(800),
		m_outputHeight(600),
		m_featureLevel(D3D_FEATURE_LEVEL_9_1)
	{
	}



	bool RendererDirectX11::Init(HWND window, int width, int height)
	{
		m_window = window;
		m_outputWidth = std::max(width, 1);
		m_outputHeight = std::max(height, 1);

		CreateDevice();

		CreateResources();

		return true;
	}
	void RendererDirectX11::Release()
	{
		//スマートポインターで作った物は削除しないように（自動で削除されるので）
	}
	void RendererDirectX11::Render()
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



	// Message handlers
	void RendererDirectX11::OnActivated()
	{
		// TODO: Game is becoming active window.

	}
	void RendererDirectX11::OnDeactivated()
	{
		// TODO: Game is becoming background window.
	}
	void RendererDirectX11::OnSuspending()
	{
		// TODO: Game is being power-suspended (or minimized).
	}
	void RendererDirectX11::OnResuming()
	{
		// TODO: Game is being power-resumed (or returning from minimize).
	}
	void RendererDirectX11::OnWindowSizeChanged(int width, int height)
	{
		m_outputWidth = std::max(width, 1);
		m_outputHeight = std::max(height, 1);

		CreateResources();

		// TODO: Game window is being resized.
	}

	// Vertex Buffer
	bool RendererDirectX11::CreateVertexBuffer(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, KtVertexBufferBase* pOut)
	{
		VertexBufferDirectX11* pOutBufferTemp = nullptr;
		pOutBufferTemp = new VertexBufferDirectX11;
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
		pOutBufferTemp->m_VertexBufferType = KtVertexBufferBase::eVextexBufferType::eVERTEXBUFFERTYPE_DX11_VERTEX;
		pOut = pOutBufferTemp;
		return true;
	}
	bool RendererDirectX11::CreateVertexBufferIndexed(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, unsigned int* const pIndexDataIn, unsigned int totalIndex, KtVertexBufferBase* pOut)
	{
		VertexBufferIndexedDirectX11* pOutBufferTemp = nullptr;
		pOutBufferTemp = new VertexBufferIndexedDirectX11;
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
		pOutBufferTemp->m_VertexBufferType = KtVertexBufferBase::eVextexBufferType::eVERTEXBUFFERTYPE_DX11_VERTEXINDEXED;
		pOut = pOutBufferTemp;

		return true;

	}
	void RendererDirectX11::SetVertexBuffer(KtVertexBufferBase* const pIn)
	{
		switch ( pIn->GetType() )
		{
		case KtVertexBufferBase::eVextexBufferType::eVERTEXBUFFERTYPE_DX11_VERTEX:
			{
				VertexBufferDirectX11* pTempIn = static_cast<VertexBufferDirectX11*>(pIn);
				m_d3dContext->IASetVertexBuffers(0, 1, &pTempIn->m_pVtxBuffer, &pTempIn->m_SingleVertexBytes, 0);
			}
			break;

		case KtVertexBufferBase::eVextexBufferType::eVERTEXBUFFERTYPE_DX11_VERTEXINDEXED:
			{
				VertexBufferIndexedDirectX11* pTempIn = static_cast<VertexBufferIndexedDirectX11*>(pIn);
				m_d3dContext->IASetVertexBuffers(0, 1, &pTempIn->m_pVtxBuffer, &pTempIn->m_SingleVertexBytes, 0);
				m_d3dContext->IASetIndexBuffer(pTempIn->m_pIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
			}
			break;
		}
	}
	void RendererDirectX11::SetPrimitiveTopology(ePrimitiveTopology topology)
	{
		m_d3dContext->IASetPrimitiveTopology(sc_PrimitiveTopologyTable[topology]);
	}

	// Constant Buffer
	bool RendererDirectX11::CreateConstantBuffer( unsigned int structSizeBytes, KtConstantBufferBase* pOut)
	{
		ConstantBufferDirectX11* pOutBufferTemp = nullptr;
		pOutBufferTemp = new ConstantBufferDirectX11;
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

		pOutBufferTemp->m_ConstantBufferType = KtConstantBufferBase::eConstantBufferType::eCONSTANTBUFFERTYPE_DX11;
		pOut = pOutBufferTemp;
		return true;

	}
	void RendererDirectX11::UpdateConstantBuffer(const void* pDataIn, KtConstantBufferBase* pOut)
	{
		switch (pOut->GetType())
		{
		case KtConstantBufferBase::eConstantBufferType::eCONSTANTBUFFERTYPE_DX11:
			{
				ConstantBufferDirectX11* pTemp = static_cast<ConstantBufferDirectX11*>(pOut);
				m_d3dContext->UpdateSubresource(pTemp->m_pConstantBuffer, 0, nullptr, pDataIn, 0, 0);
			}
			break;
		}
	}
	void RendererDirectX11::VSSetConstantBuffer(unsigned int slot, unsigned int numBuffers, KtConstantBufferBase* const pIn)
	{
		switch (pIn->GetType())
		{
		case KtConstantBufferBase::eConstantBufferType::eCONSTANTBUFFERTYPE_DX11:
			{
				ConstantBufferDirectX11* pTemp = static_cast<ConstantBufferDirectX11*>(pIn);
				m_d3dContext->VSSetConstantBuffers(slot, numBuffers, &pTemp->m_pConstantBuffer);
			}
			break;
		}
	}
	void RendererDirectX11::PSSetConstantBuffer(unsigned int slot, unsigned int numBuffers, KtConstantBufferBase* const pIn)
	{
		switch (pIn->GetType())
		{
		case KtConstantBufferBase::eConstantBufferType::eCONSTANTBUFFERTYPE_DX11:
			{
				ConstantBufferDirectX11* pTemp = static_cast<ConstantBufferDirectX11*>(pIn);
				m_d3dContext->PSSetConstantBuffers(slot, numBuffers, &pTemp->m_pConstantBuffer);
			}
		break;
		}
	}

	// DrawPrimitive
	void RendererDirectX11::DrawPrimitive(unsigned int totalVertex)
	{
		m_d3dContext->Draw(totalVertex, 0);
	}
	void RendererDirectX11::DrawPrimitiveIndexed(unsigned int totalIndex)
	{
		m_d3dContext->DrawIndexed(totalIndex, 0, 0);
	}

	//////////////////////////////////////////////////////////////////////////////////
	// Private
	//////////////////////////////////////////////////////////////////////////////////
	// Helper method to clear the back buffers.
	void RendererDirectX11::Clear()
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
	void RendererDirectX11::Present()
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
	void RendererDirectX11::CreateDevice()
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
	void RendererDirectX11::CreateResources()
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

	void RendererDirectX11::OnDeviceLost()
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

	void RendererDirectX11::RenderSetting(eRenderLayer eLayer)
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
	// Vertex Buffer
	//////////////////////////////////////////////////////////////////////////////////
		// Public
		//////////////////////////////////////////////////////////////////////////////////





		//////////////////////////////////////////////////////////////////////////////////
		// Private
		//////////////////////////////////////////////////////////////////////////////////









}	//namespace KtLib