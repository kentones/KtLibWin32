#pragma once
#include <vector>
#include "Component_Transform.h"
#include "common_Struct.h"

namespace KtLib
{
	//Layer初期サイズ
	static const int sc_RenderLayer_DefRenderable = 1000;

	//resource list
	//描画できるリソースを外部ファイルで定義する
	//今回使うものをSetup()ないで読み込む
	//Render()内でKtRendererBase::描画機能を使って描画する

	class KtVertexBuffer;
	class KtVertexBufferIndexed;



	class KtRenderableBase
	{
	public:
		virtual bool Setup()	= 0;	//Resourceを読み込みなど


		//Priority と RenderTargetはどうしますか？
		virtual void Render()	= 0;	//描画
	private:
	};

	//???Textureを継承するべき？???
	class RenderableRenderTarget : public KtRenderableBase
	{
	public:
		bool Setup()override;
		void Render()override;

	private:
		KtVertexBuffer* m_pVtxBuffer;
		//texture
	};


	class RenderableRect : public KtRenderableBase
	{
	public:
		bool Setup()override;
		void Render()override;

		void UpdatePos(float x, float y);
		void UpdateSize(float sizeX, float sizeY);
		void UpdateViewport( float viewPortWidth, float viewPortHeight);
		void UpdateColor(float r, float g, float b, float a);

	private:
		KtVertexBuffer*		m_pVtxBuffer;
		KtConstantBuffer*	m_pConstantBuffer;
		VertexPosNorCol		m_Vtx[4];
		KtVector2			m_Pos;
		KtVector2			m_Size;
		KtVector2			m_ViewportSize;
		KtColor				m_Color;

	};



	class RenderableModel : public KtRenderableBase
	{
	public:
		bool Setup()override;
		void Render()override;
	private:

	};



	//Model
	//Skin with animation
	//Particle emitter
	//Billboard
	//Basic shape
	//2D rect with texture





	//描画レイヤー
	class RenderLayer
	{
	public:
		RenderLayer()
		{
			m_apRenderable.reserve(sc_RenderLayer_DefRenderable);
		}

		void Render()
		{
			for (auto itr : m_apRenderable)
			{
				itr->Render();
			}
		}
		void PushBack(KtRenderableBase* pRenderable)
		{
			m_apRenderable.push_back(pRenderable);
		}
		void Clear() { m_apRenderable.clear(); }
		void ShrinkToFit() { m_apRenderable.shrink_to_fit(); }

		void ZSortNearToFar();
		void ZSortFarToNear();
		void CameraCulling();

		void SetZSortCameraTransform(const Transform& cameraTransform)
		{
			m_ZSortCamera = cameraTransform;
		}
		
	private:

		Transform m_ZSortCamera;
		std::vector<KtRenderableBase*>	m_apRenderable;
	};

}	//namespace KtLib
