#pragma once

namespace KtLib
{
	class KtRenderableBase
	{
	public:
		virtual bool Setup()	= 0;	//Resource��ǂݍ��݂Ȃ�


		//Priority �� RenderTarget�͂ǂ����܂����H
		virtual void Render()	= 0;	//�`��
	private:

	};

	//Model
	//Skin with animation
	//Particle emitter
	//Billboard
	//Basic shape
	//2D rect with texture



}	//namespace KtLib
