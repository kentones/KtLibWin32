#pragma once
#include "../pch.h"
#include <DirectXMath.h>
#include <d3d11_1.h>
#include "common_Template.h"
#include "RendererBase.h"

namespace KtLib
{
	class Transform;
	class Vertex;
	class Material;

	class RendererDirectX11 : public KtRendererBase
	{
	public:
		RendererDirectX11();

		bool Init(HWND window, int width, int height)override;
		void Release()override;
		void Render()override;

		// Messages
		void OnActivated()override;
		void OnDeactivated()override;
		void OnSuspending()override;
		void OnResuming()override;
		void OnWindowSizeChanged(int width, int height)override;

		// Vertex Buffer

		bool CreateVertexBuffer(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, KtVertexBufferBase* pOut)override;
		bool CreateVertexBufferIndexed(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, unsigned int* const pIndexDataIn, unsigned int totalIndex, KtVertexBufferBase* pOut)override;
		void SetVertexBuffer(KtVertexBufferBase* const pIn)override;

		void SetPrimitiveTopology( /* topology type */ );

		void SetInputLayout( /* input layout type */ );

		// Shader
		bool SetupShader(); //�S�̃V�F�[�_�[�ݒ�
		bool _CreateVertexShader();
		void SetVertexShader( /* vertex shader */ );
		bool _CreatePixelShader();
		void SetPixelShader( /* pixel shader */ );
		
		bool SetupInputLayout();
		bool SetupSampler();
		void SetSampler();

		// Constant Buffer
		bool CreateConstantBuffer( unsigned int structSizeBytes, KtConstantBufferBase* pOut );
		void UpdateConstantBuffer( const void* pDataIn, KtConstantBufferBase* pOut );
		void VSSetConstantBuffer( unsigned int slot, unsigned int numBuffers, KtConstantBufferBase* const pIn );
		void PSSetConstantBuffer( unsigned int slot, unsigned int numBuffers, KtConstantBufferBase* const pIn );


		//////////////////////////////////////////////////////////////////////////////////
		// �e��`��
		//////////////////////////////////////////////////////////////////////////////////
		//�Q�c
		void DrawRect(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		void DrawRectCenter(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }

		//�R�c
		void RenderBillBoard(const Transform& inTransform, const Material& inMaterial)const {}
		void RenderIndexed(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}


		// Debug Shape
		// 2D
		void DbgDrawRect		(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		void DbgDrawRectCenter	(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		void DbgDrawCircle		(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		void DbgDrawCircleCenter(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }

		// 3D
		void DbgRenderBox(const Transform& inTransform, const Material& inMaterial)const {}
		void DbgRenderSphere(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}
		void DbgRenderCylinder(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}
		void DbgRenderCone(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}


	private:

		void Clear();
		void Present();

		void CreateDevice();
		void CreateResources();

		void OnDeviceLost();

		void RenderSetting( eRenderLayer eLayer);

		// Device resources.
		HWND                                            m_window;
		int                                             m_outputWidth;
		int                                             m_outputHeight;

		D3D_FEATURE_LEVEL                               m_featureLevel;
		Microsoft::WRL::ComPtr<ID3D11Device1>           m_d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext1>    m_d3dContext;

		Microsoft::WRL::ComPtr<IDXGISwapChain1>         m_swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView>  m_renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView>  m_depthStencilView;


	};









}	//namespace KtLib
