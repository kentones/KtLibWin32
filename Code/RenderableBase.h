#pragma once

namespace KtLib
{
	class KtRenderableBase
	{
	public:
		virtual bool Setup()	= 0;	//Resourceを読み込みなど


		//Priority と RenderTargetはどうしますか？
		virtual void Render()	= 0;	//描画
	private:

	};

	//Model
	//Skin with animation
	//Particle emitter
	//Billboard
	//Basic shape
	//2D rect with texture



}	//namespace KtLib
