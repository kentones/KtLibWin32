#pragma once
#include <vector>
#include "Component_Transform.h"

namespace KtLib
{
	static const int sc_RenderLayer_DefRenderable = 1000;

	//resource list
	//描画できるリソースを外部ファイルで定義する
	//今回使うものをSetup()ないで読み込む
	//Render()内でKtRendererBase::描画機能を使って描画する




	class KtRenderableBase
	{
	public:
		virtual bool Setup()	= 0;	//Resourceを読み込みなど


		//Priority と RenderTargetはどうしますか？
		virtual void Render()	= 0;	//描画
	private:

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

		void SetZSortCameraTransform(const Transform& cameraTransform)
		{
			m_ZSortCamera = cameraTransform;
		}

	private:

		Transform m_ZSortCamera;
		std::vector<KtRenderableBase*>	m_apRenderable;
	};

}	//namespace KtLib
