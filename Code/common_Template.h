#ifndef _COMMON_TEMPLATE_H_
#define _COMMON_TEMPLATE_H_

namespace KtLib
{
	template <typename T>
	inline void SafeDelete(T*& p)
	{
		if (p != nullptr)
		{
			delete (p);
			(p) = nullptr;
		}
	}

	template <typename T>
	inline void SafeDeleteArray(T*& p)
	{
		if (p != nullptr)
		{
			delete[](p);
			(p) = nullptr;
		}
	}

	template <typename T>
	inline void SafeReleaseDelete(T*& p)
	{
		if (p != nullptr)
		{
			(p)->Release();
			delete (p);
			(p) = nullptr;
		}
	}

}	//namespace KtLib
#endif