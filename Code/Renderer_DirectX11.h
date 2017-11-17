#pragma once
#include "../pch.h"
#include <DirectXMath.h>
#include <d3d11_1.h>
#include "common_Template.h"
#include "RenderableBase.h"

namespace KtLib
{
	class Transform;
	class Vertex;
	class Material;
	class KtVertexBuffer;
	class KtVertexBufferIndexed;
	class KtConstantBuffer;
	class KtRenderableBase;

	class KtRenderer
	{
	public:
		enum eRenderLayer
		{//描画順番になる
			eRENDERLAYER_2D_BG,
			eRENDERLAYER_3D_SKYDOME,
			eRENDERLAYER_3D_TERRAIN,
			eRENDERLAYER_3D_OBJECT,
			eRENDERLAYER_EFFECT,
			eRENDERLAYER_UI,
			eRENDERLAYER_FADE,
			eRENDERLAYER_MAX
		};
		enum ePrimitiveTopology
		{
			ePRIMITIVETOPOLOGY_UNDEFINED,
			ePRIMITIVETOPOLOGY_POINTLIST,
			ePRIMITIVETOPOLOGY_LINELIST,
			ePRIMITIVETOPOLOGY_LINESTRIP,
			ePRIMITIVETOPOLOGY_TRIANGLELIST,
			ePRIMITIVETOPOLOGY_TRIANGLESTRIP,
			ePRIMITIVETOPOLOGY_MAX
		};
		enum eVertexShaderType
		{

		};
		enum ePixelShaderType
		{

		};
		enum eInputLayoutType
		{

		};


		KtRenderer();

		// Main Function
		bool Init(HWND window, int width, int height);
		void Release();
		void Render();

		// Windows Messages ( only call by Game.cpp )
		void OnActivated();
		void OnDeactivated();
		void OnSuspending();
		void OnResuming();
		void OnWindowSizeChanged(int width, int height);

		// Render Layer Access
		void PushToRenderLayer(KtRenderableBase* pRenderable, eRenderLayer eLayer);	// このフレームに描画したいものをレイヤーに入れる（フレームことクリアされる）


		// Setup Function ( will called by constructor )
	private:
		bool SetupAllVertexShader();	// 頂点シェーダー
		bool SetupAllPixelShader();		// ピクセルシェーダー
		bool SetupAllInputLayout();		// 頂点フォーマット
		bool SetupGeneralTexture();		// システムによく使われる汎用テクスチャ


	public:

		// RenderTarget
		void SetRenderTarget();
		void ClearRenderTarget();//??
		void ClearStencil();//??





		// Shader
		void SetVertexShader( /* vertex shader */ );
		void SetPixelShader( /* pixel shader */ );
		
		// Rendering Function ( only call by Renderable class )
		void SetInputLayout( /* input layout type */);

		// Vertex Buffer (only call by Renderable class)
		bool CreateVertexBuffer(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, KtVertexBuffer* pOut);
		bool CreateVertexBufferIndexed(void* const pVertexDataIn, unsigned int singleVertexBytes, unsigned int totalVertex, unsigned int* const pIndexDataIn, unsigned int totalIndex, KtVertexBufferIndexed* pOut);
		void SetVertexBuffer(KtVertexBuffer* const pIn);
		void SetVertexBufferIndexed(KtVertexBufferIndexed* const pIn);
		void SetPrimitiveTopology(ePrimitiveTopology topology);

		// Constant Buffer (only call by Renderable class)
		bool CreateConstantBuffer( unsigned int structSizeBytes, KtConstantBuffer* pOut );
		void UpdateConstantBuffer( const void* pDataIn, KtConstantBuffer* pOut );
		void VSSetConstantBuffer( unsigned int slot, unsigned int numBuffers, KtConstantBuffer* const pIn );
		void PSSetConstantBuffer( unsigned int slot, unsigned int numBuffers, KtConstantBuffer* const pIn );


		void DrawPrimitive( unsigned int totalVertex );
		void DrawPrimitiveIndexed( unsigned int totalIndex );


		bool SetupInputLayout();
		bool SetupSampler();
		void SetSampler();


		//////////////////////////////////////////////////////////////////////////////////
		// 各種描画
		//////////////////////////////////////////////////////////////////////////////////
		//２Ｄ
		void DrawRect(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		void DrawRectCenter(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }

		//３Ｄ
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



		RenderLayer m_RenderLayer[eRENDERLAYER_MAX];



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
