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


	//âºÅiñºëOÇà”ñ°ï™Ç©ÇÈÇÊÇ§Ç…Ç∑Ç◊Ç´Åj
	struct SimpleVertex2D
	{
		KtVector2 pos;
	};
	struct SimpleVertex3D
	{
		KtVector3	pos;
		KtVector3	normal;
		KtColor		color;
	};
	struct Vertex3D
	{
		KtVector3	pos;
		KtVector3	normal;
		KtVector2	uv;
		KtColor		color;
	};

	//skin vertex


}	//namespace KtLib
