#pragma once

#include "..\pch.h"

namespace KtLib
{
	typedef DirectX::SimpleMath::Color		KtColor;
	typedef DirectX::SimpleMath::Matrix		KtMatrix;
	typedef DirectX::SimpleMath::Plane		KtPlane;
	typedef DirectX::SimpleMath::Quaternion KtQuaternion;
	typedef DirectX::SimpleMath::Rectangle	KtRectangle;
	typedef DirectX::SimpleMath::Vector2	KtVector2;
	typedef DirectX::SimpleMath::Vector3	KtVector3;
	typedef DirectX::SimpleMath::Vector4	KtVector4;
	typedef DirectX::SimpleMath::Ray		KtRay;


	struct VertexPosNorTex
	{
		KtVector3	pos;
		KtVector3	normal;
		KtVector2	uv;

		void SetValue(const KtVector3& posRef, const KtVector3& normalRef, const KtVector2& uvRef)
		{
			pos		= posRef;
			normal	= normalRef;
			uv		= uvRef;
		}
	};
	struct VertexPosNorCol
	{
		KtVector3	pos;
		KtVector3	normal;
		KtColor		color;

		void SetValue(const KtVector3& posRef, const KtVector3& normalRef, const KtColor& colorRef)
		{
			pos		= posRef;
			normal	= normalRef;
			color	= colorRef;
		}
	};


	//skin vertex


}	//namespace KtLib
