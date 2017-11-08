#pragma once

namespace KtLib
{
	class KtRenderableBase
	{
	public:
		virtual bool Setup()	= 0;	//Resource‚ğ“Ç‚İ‚İ‚È‚Ç


		//Priority ‚Æ RenderTarget‚Í‚Ç‚¤‚µ‚Ü‚·‚©H
		virtual void Render()	= 0;	//•`‰æ
	private:

	};

	//Model
	//Skin with animation
	//Particle emitter
	//Billboard
	//Basic shape
	//2D rect with texture



}	//namespace KtLib
