#pragma once

#include "RenderableBase.h"

namespace KtLib
{

	class Transform;
	class Vertex;
	class Material;
	class RenderLayer;




	class KtRendererBase
	{
	public:

		
		enum eRenderLayer
		{//ï`âÊèáî‘Ç∆ìØÇ∂
			eRENDERLAYER_2D_BG,
			eRENDERLAYER_3D_SKYDOME,
			eRENDERLAYER_3D_TERRAIN,
			eRENDERLAYER_3D_OBJECT,
			eRENDERLAYER_EFFECT,
			eRENDERLAYER_UI,
			eRENDERLAYER_FADE,
			eRENDERLAYER_MAX
		};


		virtual bool Init(HWND window, int width, int height) = 0;
		virtual void Release() = 0;
		virtual void Render() = 0;

		// Messages
		virtual void OnActivated() {};
		virtual void OnDeactivated() {};
		virtual void OnSuspending() {};
		virtual void OnResuming() {};
		virtual void OnWindowSizeChanged(int width, int height) {};

		// Render Layer Access
		void PushToRenderLayer(KtRenderableBase* pRenderable, eRenderLayer eLayer);



		//äeéÌï`âÊ
		//ÇQÇc
		virtual void DrawRect(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		virtual void DrawRectCenter(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }

		//ÇRÇc
		virtual void RenderBillBoard(const Transform& inTransform, const Material& inMaterial)const {}
		virtual void RenderPrimtive(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, bool isTriangleStrip) const{}
		virtual void RenderIndexed(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}
		

		// Debug Shape
		// 2D
		virtual void DbgDrawRect		(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		virtual void DbgDrawRectCenter	(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		virtual void DbgDrawCircle		(float posX, float posY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }
		virtual void DbgDrawCircleCenter(float centerX, float centerY, float sizeX, float sizeY)const {/*Alert("not overrided!");*/ }

		// 3D
		virtual void DbgRenderBox(const Transform& inTransform, const Material& inMaterial)const {}
		virtual void DbgRenderSphere(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}
		virtual void DbgRenderCylinder(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}
		virtual void DbgRenderCone(const Transform& inTransform, const Material& inMaterial, const Vertex* inVertex, const int* inIndex, bool isTriangleStrip)const {}


	protected:
		RenderLayer m_RenderLayer[eRENDERLAYER_MAX];

	};



}	//namespace KtLib
