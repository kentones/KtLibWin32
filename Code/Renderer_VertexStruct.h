#pragma once

namespace KtLib
{
	//���iVec3�Ȃ�..�ɂȂ�j
	struct Position
	{
		float x, y, z;
	};
	struct Normal
	{
		float x, y, z;
	};
	struct UV
	{
		float u, v;
	};
	struct Color
	{
		float r, g, b, a;
	};

	struct SimpleVertex2D
	{
		Position pos;
	};
	struct SimpleVertex3D
	{
		Position	pos;
		Normal		normal;
		Color		color;
	};
	struct Vertex3D
	{
		Position	pos;
		Normal		normal;
		UV			uv;
		Color		color;
	};

	//skin vertex


}	//namespace KtLib
