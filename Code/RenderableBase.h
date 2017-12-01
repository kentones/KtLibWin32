#pragma once
#include <vector>
#include "Component_Transform.h"
#include "common_Struct.h"

namespace KtLib
{
	//Layer�����T�C�Y
	static const int sc_RenderLayer_DefRenderable = 1000;

	//resource list
	//�`��ł��郊�\�[�X���O���t�@�C���Œ�`����
	//����g�����̂�Setup()�Ȃ��œǂݍ���
	//Render()����KtRendererBase::�`��@�\���g���ĕ`�悷��

	class KtVertexBuffer;
	class KtVertexBufferIndexed;



	class KtRenderableBase
	{
	public:
		virtual bool Setup()	= 0;	//Resource��ǂݍ��݂Ȃ�


		//Priority �� RenderTarget�͂ǂ����܂����H
		virtual void Render()	= 0;	//�`��
	private:
	};

	//???Texture���p������ׂ��H???
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





	//�`�惌�C���[
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
